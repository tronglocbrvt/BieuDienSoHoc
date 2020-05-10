#include "QFloat.h"

//--------------------------------------------------------------
//NHOM HAM CHUYEN DOI

QFloat QFloat::fromBinToQFloat(string str)
{
	QFloat res;

	unsigned short length = str.size(); // lưu chiều dài chuỗi

	for (int i = 0; i < length; i++)
	{
		res.SetBit(length - 1 - i, str[i] - '0');
	}

	return res;
}

QFloat QFloat::fromDecToQFloat(string str)
{
	QFloat res;

	if (str == "0.0" || str == "0") // kiểm tra người dùng nhập 0.0 hay không
	{
		return res; // vì res được khởi tạo mặc định là 0
	}

	// set bit dấu
	if (str[0] == '-') // số âm
	{
		res.SetBit(MAX_LENGTH - 1, 1); // set bit dấu là 1
		str.erase(str.begin() + 0);
	}

	// nếu không phải số âm mặc định là bit 0 ở lúc khởi tạo nên ta không cần xét

	if (str.find('.') == string::npos) // nếu không tìm thấy dấu . (hàm find trả về string::npos nếu không tìm thấy)
	{
		str = str + ".0";
	}

	stringstream X(str);

	string intPart;
	string fracPart;

	getline(X, intPart, '.'); // lấy phần nguyên
	getline(X, fracPart); // lấy phần thập phân
	// chèn thêm vào phần thập phân 0.
	fracPart.insert(fracPart.begin(), '.');
	fracPart.insert(fracPart.begin(), '0');

	// chuyển phần nguyên thành nhị phân
	string intPartBit;
	intPartBit = IntToBin(intPart);

	// chuyển phần thập phân thành nhị phân
	string fracPartBit;
	int exp = 0;
	int count = 0;
	bool checkRound = false; // biến check xem phần thập phân đã được 1.0 sau khi x2 liên tiếp hay chưa
	
	if (intPartBit != "") // phần nguyên khác 0 -> dạng chuẩn hóa được
	{
		exp = intPartBit.size() - 1 + BIAS; // vì phần nguyên khác 0 nên tối thiểu là length intPartBit = 1
		// -> số mũ = chiều dài dãy bit phần nguyên - 1 bit, sau đó +BIAS
		for (int i = 0; i < SIGNIFICAND - intPartBit.size() + 1; i++)
		{
			fracPart = plusStringFloat(fracPart, fracPart); // nhân 2 
			fracPartBit += fracPart[0]; // lấy phần nguyên
			fracPart[0] = '0'; // gán phần nguyên bằng 0
			// Điều kiện dừng khi fracPart = 1.0 nhưng để đủ bit ta tiếp tục nhân -> thêm các bit 0
			if (fracPart == "1") // đã tìm được vị trí xuất hiện 1.0
			{
				checkRound = true;
			}
		}
	}

	else // phần nguyên bằng 0 -> 2 TH: chuẩn hóa được hoặc không chuẩn hóa được
	{
		while (count < BIAS) // vì phần thập phân 
		{
			fracPart = plusStringFloat(fracPart, fracPart); // nhân 2 
			fracPartBit += fracPart[0]; // lấy phần nguyên
			fracPart[0] = '0'; // gán phần nguyên bằng 0
			
			if (fracPartBit.back() == '1') // đã xác định được vị trí số 1 xuất hiện
				break;
			count++;
		}

		exp = -(count + 1) + BIAS; // xác định số mũ 
		if (count + 1 < BIAS) // số có thể chuẩn hóa 
		{
			for (int i = 0; i < SIGNIFICAND; i++) {
				fracPart = plusStringFloat(fracPart, fracPart); // nhân 2 
				fracPartBit += fracPart[0]; // lấy phần nguyên

				fracPart[0] = '0'; // gán phần nguyên bằng 0
				if (fracPart == "1") // đã tìm được vị trí xuất hiện 1.0
				{
					checkRound = true;
				}
			}
		}
		else
		{
			fracPartBit = "";
			while (exp < 1) {
				fracPart = plusStringFloat(fracPart, fracPart); // nhân 2 
				fracPartBit += fracPart[0]; // lấy phần nguyên
				fracPart[0] = '0'; // gán phần nguyên bằng 0
				exp++;
				if (fracPart == "1") // đã tìm được vị trí xuất hiện 1.0
				{
					checkRound = true;
				}
			}
			
		}
	}

	if (checkRound == false) // chưa tìm được vị trí xuất hiện 1.0 -> ta tiếp tục lấy tiếp 3 bit lưu vào string a;
	{
		string a;
		for (int i = 0; i < 3; i++)
		{
			fracPart = plusStringFloat(fracPart, fracPart); // nhân 2 
			a += fracPart[0]; // lấy phần nguyên
			fracPart[0] = '0'; // gán phần nguyên bằng 0
		}
		roundingFrac(a, fracPartBit);
	}

	// làm tròn phần nguyên: khi thập phân toàn bit 1, ta cộng 1 vào exp và set lại phần thập phân là 0
	// ví dụ: 10.1111 -> làm tròn: 11.0000
	bool checkRoundInt = true; // kiểm tra có cần làm tròn phần Int hay không?
	for (int i = 0; i < fracPartBit.size(); i++)
	{
		if (fracPartBit[i] == '0')
		{
			checkRoundInt = false; // có bit 0 ở phân thập phân -> không làm tròn
			break;
		}
	}

	if (checkRoundInt)
	{
		exp += exp;
		fracPartBit = "0";
	}

	string resStr = intPartBit + fracPartBit;
	while (resStr.size() < 113) 
		resStr += '0';
	
	// đổi exp sang nhị phân 
	string exponent = IntToBin(to_string(exp));
	int lengthExp = exponent.length();
	if (lengthExp < EXPONENT) // đảm bảo exponent luôn 15 bit
	{
		for (int i = 0; i < EXPONENT - lengthExp; i++)
			exponent = '0' + exponent;
	}

	// Đặt phần mũ
	for (int i = 1; i <= EXPONENT; i++)
		res.SetBit(MAX_LENGTH - 1 - i, exponent[i-1] - 48);

	// Đặt phần trị
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		res.SetBit(MAX_LENGTH - 1 - i, resStr[i - 15 + count] - 48);
	
	return res;
}

QFloat QFloat::fromStringToQFloat(string str, unsigned short b)
{
	if (b == 2)
		return fromBinToQFloat(str);
	if (b == 10)
		return fromDecToQFloat(str);
}

string QFloat::QFloatToBinStr()
{
	string res;

	for (int i = MAX_LENGTH - 1; i >= 0; i--)
	{
		res += GetBit(i) + '0';
	}
	
	return res;
}

string QFloat::QFloatToDecStr()
{
	if (CheckZero()) // nếu là 0
		return "0";
	
	if (CheckNaN()) // nếu là NaN
		return "NaN";

	string qfloat = QFloatToBinStr(); // chuyển sang chuỗi nhị phân để dễ thao tác

	// bước 1: xác định dấu, tách phần mũ và phần trị
	string sign;
	if (qfloat[0] == '1')
		sign = '-';

	if (CheckInf())
		return ((sign == "-") ? "-Inf" : "Inf");

	string exponent = qfloat.substr(1, EXPONENT); // phần mũ
	
	string fracPart = qfloat.substr(EXPONENT + 1, MAX_LENGTH - 1); // phần trị sau dấu chấm

	string intPart; // phần nguyên trước dấu chấm

	int exp; // giá trị phần mũ

	// bước 2: tính exp = giá trị của dãy bit - BIAS (riêng số âm: -(2^14 - 2) = -(BIAS - 1))
	if (CheckDenormalized()) // nếu là dạng không chuẩn -> phần mũ = 0
	{
		intPart = '0'; // dạng không chuẩn -> 0.F
		exp = 0 - (BIAS - 1);
	}
	else // dạng chuẩn hóa được
	{
		intPart = '1'; // dạng chuẩn hóa được -> 1.F
		exp = stoi(exponent, nullptr, 2) - BIAS;
	}
	
	// bước 3: dời dấu chấm động khi exp != 0
	// nếu ta dời qua bên phải -> exp dương
	// nếu ta dời qua bên trái -> exp âm

	while (exp != 0)
	{
		// TH1: xét exp dương  ->  dời qua phải
		if (exp > 0)
		{
			// VD: 1001.1 x 2^2, exp = 2 > 0
			// dời lần 1: phần thập phân từ 1 -> hết, phần nguyên từ 1001 -> 10011  ->>> 10011 * 2^1
			// dời lần 2: phần thập phân hết -> ta thêm 0 vào phần nguyên từ 10011 -> 100110  ->>> 100110 * 2^0
			// --> mỗi lần dịch phần nguyên + thêm và phần thập phân xóa bớt
			// nếu đã dịch hết phần thập phân -> ta thêm 0 vào phần nguyên
			if (fracPart.size() > 0)													
			{ 
				intPart += fracPart[0];
				fracPart.erase(fracPart.begin() + 0);
			}
			else																	
			{
				intPart += '0';
			}
						
			exp--;
		}
		// TH2: xét exp âm  ->  dời qua trái
		else // exp < 0
		{
			// VD: 1.0011 x 2^-2, exp = 2 < 0 
			// dời lần 1: phần thập phân từ 0011 -> 10011, phần nguyên từ 1 -> hết  ->>> 0.10011 * 2^-1
			// dời lần 2: phần thập phân từ 10011 -> 010011 (ta thêm 0 vào trước vì phần nguyên hết)  ->>> 0.010011 * 2^0
			// --> mỗi lần dịch phần nguyên xóa bớt và phần thập phân cộng thêm
			// nếu đã dịch hết phần nguyên -> ta thêm 0 vào phần thập phân
			if (intPart.size() > 0)													
			{
				fracPart = intPart[intPart.length() - 1] + fracPart;
				intPart.erase(intPart.begin() + intPart.length() - 1);
			}

			else		
			{
				fracPart = '0' + fracPart;
			}
			exp++;
		}
	}

	// Bước 4: chuyển phần nguyên về thập phân
	string intDec = BinToDec(intPart);

	// Bước 5: chuyển phần thập phân về dạng thập phân 
	string fracDec = "0";

	string tmp = "0.5"; // tmp để lưu giá trị tại 2^n, ban đầu 2^-1 = 0.5
	for (int i = 0; i < fracPart.length(); i++)
	{
		if (fracPart[i] == '1') // chỉ cập nhật giá trị tại những nơi có bit = 1
			fracDec = plusStringFloat(fracDec, tmp);
		tmp = FracDiv2(tmp);
	}

	fracDec.erase(fracDec.begin() + 0);

	return (sign + intDec + fracDec);
}

// chuyển QInt sang chuỗi ở hệ cơ số b
string QFloat::QFloatToString(unsigned short b)
{
	if (b == 2)
		return QFloatToBinStr();
	if (b == 10)
		return QFloatToDecStr();
}

string QFloat::BaseToBase(string str, unsigned short a, unsigned short b)
{
	QFloat q = fromStringToQFloat(str, a);

	string res = q.QFloatToString(b);

	return res;
}

////chuyen chuoi nhi phan sang Qfloat
//void QFloat::StringBinToQFloat(string str)
//{
//	while (str.size() < MAX_LENGTH) str.push_back('0');
//	for (int i = 0; i < MAX_LENGTH; i++)
//	{
//		SetBit(MAX_LENGTH - i - 1, str[i] - '0');
//	}
//}
//
////chuyen so QFloat nhi phan sang thap phan
//QFloat QFloat::BinToDec(bool *bit)
//{
//	QFloat ans;
//	for (int i = 0; i < MAX_LENGTH; i++)
//	{
//		ans.SetBit(MAX_LENGTH - i - 1, bit[i]);
//	}
//	return ans;
//}
//
////chuyen so QFloat thap phan sang nhi phan
//bool* QFloat::DecToBin(QFloat x)
//{
//	bool* bit = new bool[MAX_LENGTH];
//	for (int i = 0; i < MAX_LENGTH; i++)
//	{
//		bit[i] = GetBit(MAX_LENGTH - i - 1);
//	}
//	return bit;
//}

//----------------------------------------------------------------------------
//NHOM HAM HO TRO TINH TOAN

//Set bit tai vi tri i
void QFloat::SetBit(int i, int bit) 
{
	int block = i / 32;
	int pos = i % 32;

	if (block >= NUM_BLOCK || block < 0)
		return;

	if (bit == 1)
	{
		data[block] = data[block] | (1 << pos); 
	}
	else
	{
		data[block] = data[block] & (~(1 << pos));
	}
}

//Lay bit o vi tri i
int QFloat::GetBit(int i) 
{
	int block = i / 32;
	int pos = i % 32;

	if (block >= NUM_BLOCK || block < 0)
		return 0;

	return ((data[block] & (1 << pos)) ? 1 : 0);
}

string QFloat::IntToBin(string str)
{
	string res;
	while (str != "0" && str != "")
	{
		unsigned short bit = (str[str.length() - 1] - 48) % 2; // chia 2 lấy phần dư
		res += bit + '0';
		str = StrDiv2(str); // chia chuỗi cho 2
	}

	reverse(res.begin(), res.end());
	return res;
}

// chuyển nhị phân sang thập phân
string QFloat::BinToDec(string str)
{
	string res = "0";

	string tmp = "1"; // tmp để lưu giá trị tại 2^n, ban đầu 2^0 = 1
	for (int i = str.length() - 1; i >= 0; i--) 
	{
		if (str[i] == '1') // chỉ cập nhật giá trị tại những nơi có bit = 1
			res = plusString(res, tmp);
		tmp = plusString(tmp, tmp);
	}

	return res;
}

// cộng chuỗi số thực
string QFloat::plusStringFloat(string str1, string str2)
{
	string res;
	string temp;

	// kiếm tra sự chênh lệch độ dài 2 chuỗi
	int length = str1.length() - str2.length();

	// Thêm 0 vào sau chuỗi có độ dài nhỏ hơn
	for (int i = 0; i < abs(length); i++)
		temp += '0';
	if (length < 0) // str1 ngắn hơn
		str1 = str1 + temp;
	else // str 2 ngắn hơn
		str2 = str2 + temp;

	// cộng 2 chuỗi dương
	int carry = 0; // nhớ
	for (int i = str1.length() - 1; i >= 0; i--) 
	{
		if (str1[i] == '.')
			res += '.';
		else
		{
			int tmp_1 = str1[i] - '0';
			int tmp_2 = str2[i] - '0';
			int  c = tmp_1 + tmp_2 + carry;
			carry = c / 10; // cập nhật lại nhớ
			res += c % 10 + '0';
		}
	}

	if (carry != 0)
		res += carry + '0';
	
	reverse(res.begin(), res.end()); // đảo ngược chuỗi kết quả

	// xóa các số 0 thừa phần thập phân -> tránh thừa số 0 ở cuối
	if (res.find('.') != string::npos)
	{
		int i = res.length() - 1;
		while (1)
		{
			if (res[i] == '0')
				res.pop_back();
			else if (res[i] == '.')
			{
				res.pop_back();
				break;
			}
			else break;
			i--;
		}
	}

	return res;
}

string QFloat::FracDiv2(string str)
{
	// chia cho 2 chính là nhân với 0.5
	// ta nhân chuỗi cho 5 và thêm 0. vào kết quả sau cùng
	string res;
	string temp;

	// nhân chuỗi cho 5
	int carry = 0; // nhớ
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] != '.')
		{
			int tmp = (str[i] - '0') * 5 + carry;
			carry = tmp / 10; // cập nhật lại nhớ
			res += tmp % 10 + '0';
		}
	}

	if (carry != 0) // nếu còn nhớ, thêm vào kết quả
		res += carry + '0';

	// đảo ngược chuỗi
	reverse(res.begin(), res.end());
	res.insert(res.begin(), '.');
	res.insert(res.begin(), '0');

	return res;
}

// hàm làm tròn phần thập phân
// truyền vào 3 bit sau khi đủ 112 bit và chuỗi phần thập phân
void QFloat::roundingFrac(string a, string& fracPartBit)
{
	if (a[0] == '1') // nếu bit đầu trong 3 bit = 1
	{
		if (!(a[1] == '0' && a[2] == '0' && fracPartBit[fracPartBit.size()-1] == '0'))
		{
			int trace = 1;
			for (int i = fracPartBit.size() - 1; i >= 0; i--)
			{
				if (trace > 0)
				{
					int count = fracPartBit[i] - '0' + trace;
					fracPartBit[i] = count % 2 + '0';
					trace = count / 2;
				}
				else break;
			}
		}
	}
}

bool QFloat::SignificandIsZero(string str, int intPart)
{
	for (int i = 0; i < str.size() - 1; i++)
	{
		if (str[i] == '1')
			return false;
	}
	return intPart == 0;
}

// cộng hai dãy bit
string QFloat::addBitString(string str1, string str2, int& intPart, int intPartX, int intPartY)
{
	string s; 

	int carry = 0;
	for (int i = str1.size() - 1; i >= 0; i--) {
		if (str1[i] == str2[i]) {
			s.insert(s.begin(), carry + '0');
			carry = str1[i] - '0';
		}
		else {
			s.insert(s.begin(), !carry + '0');
		}
	}

	intPart = intPartX + intPartY + carry;

	return s;
}

// trừ 2 dãy bit
string QFloat::subBitString(string str1, string str2, int& intPart, int intPartX, int intPartY)
{
	string s;

	if (intPartX < intPartY) {
		s = subBitString(str2, str1, intPart, intPartY, intPartX);
		s.insert(s.begin(), '-');
		return s;
	}
	
	int carry = 0;
	for (int i = str1.size() - 1; i >= 0; i--) {
		if (str1[i] == str2[i]) {
			s.insert(s.begin(), carry + '0');
		}
		else {
			s.insert(s.begin(), !carry + '0');
			carry = str2[i] - '0';
		}
	}

	if (intPartX - intPartY - carry < 0) {
		s = subBitString(str2, str1, intPart, intPartY, intPartX);
		s.insert(s.begin(), '-');
		return s;
	}

	intPart = intPartX - intPartY - carry;

	return s;
}

string QFloat::addSigned(string str1, string str2, QFloat x, QFloat y, int& intPart, int intPartX, int intPartY)
{
	string s;

	if (x.GetBit(MAX_LENGTH - 1) == 1) {
		if (y.GetBit(MAX_LENGTH - 1) == 1) 
		{ // (-) + (-) = -((+) + (+))
			s = addBitString(str1, str2, intPart, intPartX, intPartY);
			s = '-' + s;
		}
		else {					// (-) + (+) = (+) - (+)
			s = subBitString(str2, str1, intPart, intPartY, intPartX);
		}
	}
	else {
		if (y.GetBit(MAX_LENGTH - 1) == 0) { // (+) + (+) = (+) + (+)
			s = addBitString(str1, str2, intPart, intPartX, intPartY);
		}
		else {					// (+) + (-) = (+) - (+)
			s = subBitString(str1, str2, intPart, intPartX, intPartY);
		}
	}

	return s;
}

////Lay vi tri bit dau tien = 1 tu trai sang, neu khong co tra ve n
//int QFloat::GetFirstBit1(bool bit[], int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		if (bit[i] == 1)
//		{
//			return i;
//		}
//	}
//	return n;
//}
//
////So sanh 2 day bit
//int QFloat::SoSanhBit(bool bitX[], int lenX, bool bitY[], int lenY)
//{
//	if (lenX < lenY) return -1; //X < Y
//	if (lenX > lenY) return 1; //X > Y
//	//So sanh tung cap bit
//	for (int i = 0; i < lenX; i++)
//	{
//		if (bitX[i] < bitY[i]) return -1;
//		if (bitX[i] > bitY[i]) return 1;
//	}
//	return 0; //X = Y
//}
//
////Tru bit: X - Y = Z
//int QFloat::TruBit(bool bitX[], int lenX, bool bitY[], int lenY, bool bitZ[], int lenZ)
//{
//	int ans = 0;
//	int t;
//	//Khoi tao
//	for (int i = 0; i < min(lenX, lenY); i++)
//	{
//		t = bitX[lenX - i - 1] - bitY[lenY - i - 1] - ans;
//		ans = 0;
//		if (t < 0)
//		{
//			t += 2;
//			ans = 1;
//		}
//		bitZ[lenZ - i - 1] = t;
//	}
//	//Bat dau tru
//	for (int i = min(lenX, lenY); i < max(lenX, lenY); i++)
//	{
//		if (lenZ - i - 1 < 0) break;
//		if (lenX - i - 1 < 0)
//		{
//			t = 0;
//		}
//		else
//		{
//			t = bitX[lenX - i - 1];
//		}
//		if (lenY - i - 1 < 0)
//		{
//			t = t - 0;
//		}
//		else
//		{
//			t -= bitY[lenY - i - 1];
//		}
//		t -= ans;
//		ans = 0;
//		if (t < 0)
//		{
//			t += 2;
//			ans = 1;
//		}
//		bitZ[lenZ - i - 1] = t;
//	}
//	return ans;
//}
//
////Lay dau cua QFloat
//int QFloat::GetSign() 
//{
//	return GetBit(MAX_LENGTH - 1);
//}
//
////Luu dau cua QFloat
//void QFloat::SaveSign(int dau) 
//{
//	SetBit(MAX_LENGTH - 1, dau);
//}
//
////Lay so 0
//QFloat QFloat::GetZero()
//{
//	QFloat Zero;
//	for (int i = 0; i < MAX_LENGTH; ++i)
//	{
//		Zero.SetBit(i, 0);
//	}
//	return Zero;
//}
//
////Lay so vo cung
//QFloat QFloat::GetInf()
//{
//	QFloat Inf = GetZero();
//	for (int i = SIGNIFICAND; i < SIGNIFICAND + EXPONENT; i++)
//	{
//		Inf.SetBit(i, 1);
//	}
//	return Inf;
//}
//
////Lay so NaN
//QFloat QFloat::GetNaN()
//{
//	QFloat NaN = GetInf();
//	NaN.SetBit(0, 1);
//	return NaN;
//}
//
//Kiem tra co phai so 0 hay khong
bool QFloat::CheckZero() 
{
	for (int i = 0; i < NUM_BLOCK; i++)
	{
		if (data[i] != 0)
		{
			return false;
		}
	}
	return true;
}

// Kiểm tra dạng số không chuẩn
bool QFloat::CheckDenormalized() 
{
	// Phần mũ = 0, phần trị khác 0

	for (int i = 1; i <= EXPONENT; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 0)
			return false;
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 0)
			return true;
	return false;
}

//Kiểm tra có phải là dạng NaN không
bool QFloat::CheckNaN()
{
	// số NaN mũ toàn bit 1, trị khác 0
	for (int i = 1; i <= EXPONENT; i++) 
		if (GetBit(MAX_LENGTH - 1 - i) != 1)
			return false;
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 0)
			return true;
	return false;
}

// Kiểm tra có phải là dạng Infinity không
bool QFloat::CheckInf()
{
	// Dạng Inf có phần mũ toàn bit 1, phần trị = 0
	for (int i = 1; i <= EXPONENT; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 1)
			return false;
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 0)
			return false;
	return true;
}
//
////lay gia tri phan nguyen cua QFloat
//int QFloat::GetIntPart() 
//{
//	if (CheckDenormalized())
//	{
//		return 0;
//	}
//	return 1;
//}
//
////Tinh gia tri phan mu
//int QFloat::CalExponent() 
//{
//	if (CheckDenormalized())
//	{
//		return 1 - BIAS;
//	}
//	int ans = 0;
//	int temp = 1;
//	for (int i = SIGNIFICAND; i < SIGNIFICAND + EXPONENT; i++)
//	{
//		ans += GetBit(i) * temp;
//		temp = temp * 2;
//	}
//	ans -= BIAS;
//	return ans;
//}
//
////Luu phan mu
//void QFloat::SaveExponent(int exponent) 
//{
//	exponent += BIAS;
//	for (int i = 0; i < EXPONENT; i++)
//	{
//		int bit = (exponent >> i) & 1U; //1U-so 1 unsigned
//		SetBit(SIGNIFICAND + i, bit);
//	}
//}
//
////Luu phan tri
//void QFloat::SaveSignificand(bool BitTri[])
//{
//	for (int i = 0; i < SIGNIFICAND; i++)
//	{
//		SetBit(SIGNIFICAND - i - 1, BitTri[i]);
//	}
//}
//
////Shift Right cac bit phan tri
//void QFloat::ShiftRSignificand(int numBit, int &intPart) 
//{
//	if (numBit <= 0) return;
//
//	int index;
//
//	for (index = 0; index + numBit < SIGNIFICAND; index++)
//	{
//		SetBit(index, GetBit(index + numBit));
//	}
//
//	index = SIGNIFICAND - numBit;
//
//	if (index >= 0)
//	{
//		SetBit(index, intPart);
//		index++;
//	}
//
//	for (index = max(0, index); index < SIGNIFICAND; index++)
//	{
//		SetBit(index, 0);
//	}
//
//	if (numBit > 0)
//	{
//		intPart = 0;
//	}
//
//	int exponent = min(CalExponent() + numBit, BIAS + 1);
//	SaveExponent(exponent);
//}
//
////Shift Left cac bit phan tri
//void QFloat::ShiftLSignificand(int numBit, int &intPart) 
//{
//	if (numBit <= 0) return;
//
//	int index = SIGNIFICAND - numBit;
//	if (index >= 0)
//	{
//		intPart = GetBit(index);
//	}
//	else
//	{
//		intPart = 0;
//	}
//	for (index = SIGNIFICAND - 1; index - numBit >= 0; index--)
//	{
//		SetBit(index, GetBit(index - numBit));
//	}
//	for (index = min(SIGNIFICAND - 1, numBit - 1); index >= 0; index--)
//	{
//		SetBit(index, 0);
//	}
//	int exponent = CalExponent() - numBit;
//	SaveExponent(exponent);
//}
//
////Kiem tra tat ca cac bit cua phan tri co = 0 hay khong
//bool QFloat::CheckSignificandZero(int intPart) 
//{
//	for (int i = 0; i < SIGNIFICAND; i++)
//	{
//		if (GetBit(i) == 1)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
////Lay phan tri va chuyen thanh day bit
//void QFloat::ChuyenPhanTriThanhBit(bool bit[]) 
//{
//	for (int i = 0; i < SIGNIFICAND; i++)
//	{
//		bit[SIGNIFICAND - i] = GetBit(i);
//	}
//
//	if (CheckDenormalized()) //Kiem tra co phai so khong chuan khong
//	{
//		bit[0] = 0;
//	}
//	else
//	{
//		bit[0] = 1;
//	}
//}
//
////Lam tron so nhi phan (0.5->1, 1.5->2)
//int QFloat::LamTronNhiPhan(bool bit[])
//{
//	int first = bit[SIGNIFICAND + 1];
//	int second = bit[SIGNIFICAND + 2];
//	int third = bit[SIGNIFICAND + 3];
//	if (first == 1)
//	{
//		if (!(second == 0 && third == 0 && bit[SIGNIFICAND] == 0))
//		{
//			int trace = 1;
//			for (int i = SIGNIFICAND; i >= 0; i--)
//			{
//				if (trace > 0)
//				{
//					int count = bit[i] + trace;
//					bit[i] = count % 2;
//					trace = count / 2;
//				}
//				else break;
//			}
//			return trace;
//		}
//	}
//	return 0;
//}
//
////Cong hai phan tri duong X + Y = Z
//void QFloat::CongPhanTriDuong(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) 
//{
//	Z.SaveSign(0);
//	Z.SaveExponent(X.CalExponent());
//	int right = 0;
//	//Cong X + Y
//	for (int i = 0; i < SIGNIFICAND; i++)
//	{
//		int t = X.GetBit(i) + Y.GetBit(i) + right;
//		Z.SetBit(i, t % 2);
//		right = t / 2;
//	}
//	//Luu ket qua vao Z
//	intZ = intX + intY + right;
//	if (intZ > 1)
//	{
//		int t = intZ % 2;
//		Z.ShiftRSignificand(1, t);
//		intZ /= 2;
//	}
//}
//
////Tru hai phan tri duong X - Y = Z hoac Y - X = Z
//void QFloat::TruPhanTriDuong(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) 
//{
//	if (intX < intY) // X < Y, lay Y - X
//	{
//		TruPhanTriDuong(Y, intY, X, intX, Z, intZ);
//		Z.SaveSign(1);
//		return;
//	}
//
//	Z.SaveSign(0);
//	Z.SaveExponent(X.CalExponent());
//	int right = 0;
//	//X > Y, lay X - Y
//	for (int i = 0; i < SIGNIFICAND; i++)
//	{
//		int t = X.GetBit(i) - Y.GetBit(i) - right;
//		right = 0;
//		if (t < 0)
//		{
//			t = t + 2;
//			right = 1;
//		}
//		Z.SetBit(i, t % 2);
//	}
//	//Z < 0
//	if (intX - intY - right < 0)
//	{
//		TruPhanTriDuong(Y, intY, X, intX, Z, intZ);
//		Z.SaveSign(1);
//		return;
//	}
//	//Z > 0
//	intZ = intX - intY - right;
//}
//
////Cong hai phan tri co dau X + Y = Z
//void QFloat::CongPhanTriCoDau(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) 
//{
//	if (X.GetSign() == 1)
//	{
//		if (Y.GetSign() == 1)
//		{
//			// X < 0 va Y < 0
//			// (-) + (-) = -((+) + (+))
//			CongPhanTriDuong(X, intX, Y, intY, Z, intZ); //Da luu ket qua vao Z
//			Z.SaveSign(1); //Z < 0
//		}
//		else
//		{
//			//X < 0 va Y > 0
//			// (-) + (+) = (+) - (+)
//			TruPhanTriDuong(Y, intY, X, intX, Z, intZ); //Da luu ket qua vao Z
//		}
//	}
//	else
//	{
//		if (Y.GetSign() == 0)
//		{
//			//X > 0 va Y > 0
//			// (+) + (+) = (+) + (+)
//			CongPhanTriDuong(X, intX, Y, intY, Z, intZ); //Da luu ket qua vao Z
//		}
//		else
//		{
//			//X > 0 va Y < 0
//			// (+) + (-) = (+) - (+)
//			TruPhanTriDuong(X, intX, Y, intY, Z, intZ); //Da luu ket qua vao Z
//		}
//	}
//}
//
////Nhan hai phan tri X * Y = bit (luu vao bit)
//void QFloat::NhanPhanTri(QFloat X, QFloat Y, bool bit[], int n) 
//{
//	//Ap dung thuat toan nhan so cham dong
//	for (int i = 0; i <= SIGNIFICAND; i++)
//	{
//		if ((i == SIGNIFICAND && Y.GetIntPart() == 0) || (i < SIGNIFICAND && Y.GetBit(i) == 0))
//		{
//			continue;
//		}
//
//		int j = n - 1 - i;
//		int right = 0;
//		int k, t;
//
//		for (k = 0; k < SIGNIFICAND; k++)
//		{
//			t = X.GetBit(k) + bit[j - k] + right;
//			bit[j - k] = t % 2;
//			right = t / 2;
//		}
//
//		t = X.GetIntPart() + bit[j - k] + right;
//		bit[j - k] = t % 2;
//		right = t / 2;
//		k++;
//
//		while (right > 0)
//		{
//			t = bit[j - k] + right;
//			bit[j - k] = t % 2;
//			right = t / 2;
//			k++;
//		}
//	}
//}
//
////-----------------------------------------------------------------------------
////PHAN THUC HIEN CAC YEU CAU CHINH
//
//Toan tu +
QFloat QFloat::operator+(const QFloat& plus)
{
	QFloat x = *this;
	QFloat y = plus;

	// Nếu 1 trong 2 hoặc cả 2 là NaN thì trả về NaN
	if (x.CheckNaN() || y.CheckNaN())
		return QFloat("NaN");

	// Nếu cả hai là số vô cực -> phép cộng nên trả về vô cực
	if (x.CheckInf() && y.CheckInf())
	{
		if (x.GetBit(MAX_LENGTH - 1) == 1 && y.GetBit(MAX_LENGTH - 1) == 1)
			return QFloat("-Inf");

		if (x.GetBit(MAX_LENGTH - 1) == 0 && y.GetBit(MAX_LENGTH - 1) == 0)
			return QFloat("Inf");

		// TH có một số là âm vô cực, một số là dương vô cực
		return QFloat("NaN");
	}

	// Nếu một trong hai là số vô cực
	if ((x.CheckInf() && x.GetBit(MAX_LENGTH - 1) == 1) || (y.CheckInf() && y.GetBit(MAX_LENGTH - 1) == 1))
		return QFloat("-Inf");

	if ((x.CheckInf() && x.GetBit(MAX_LENGTH - 1) == 0) || (y.CheckInf() && y.GetBit(MAX_LENGTH - 1) == 0))
		return QFloat("Inf");

	// Nếu 1 trong 2 số là 0, trả về số còn lại
	if (x.CheckZero())
		return y;

	if (y.CheckZero())
		return x;

	// nếu không rơi vào các TH đặc biệt ở trên
	// chuyển về dạng chuỗi để dễ tính toán
	string X = x.QFloatToBinStr();
	string Y = y.QFloatToBinStr();

	// lấy chuỗi nhị phân phần mũ
	string expX = X.substr(1, EXPONENT);
	string expY = Y.substr(1, EXPONENT);

	// Tính phần mũ
	int eX = stoi(expX, nullptr, 2);
	int eY = stoi(expY, nullptr, 2);

	// lấy phần trị
	string significandX = X.substr(EXPONENT + 1, MAX_LENGTH - 1);
	string significandY = Y.substr(EXPONENT + 1, MAX_LENGTH - 1);

	// lấy phần nguyên: dạng chuẩn -> intPart = 1; dạng không chuẩn intPart = 0
	int intPartX = (x.CheckDenormalized()) ? 0 : 1;
	int intPartY = (y.CheckDenormalized()) ? 0 : 1;

	// kiểm tra phần mũ có bằng nhau hay không
	if (eX != eY) // 2 mũ không bằng nhau
	{
		if (eX < eY) // nếu eX < eY ta đổi vị trí x, y
			return (y + x);

		// dịch phải số có phần mũ nhỏ hơn (ta đã có bước hoán vị ở trên nên y là số có mũ nhỏ hơn)
		int d = eX - eY; // tính độ chênh lệch số mũ
		// Thêm bit vào eY để cân bằng số mũ
		while (eX > eY)
		{
			significandY.insert(significandY.begin(), '0'); // thêm vào đầu phần trị
			significandY.pop_back();
			eY++; // tăng số mũ
		}

		if (d > 0 && d <= significandY.size())
		{
			significandY[d - 1] = intPartY + '0';
			intPartY = 0;
		}
		else
			intPartY = 0;

		if (SignificandIsZero(significandY, intPartY))
			return x;
	}

	// eX = eY

	//Luu kết quả: e là phần mũ, sign là dấu, intPart là phần nguyên, significand là phần trị
	int e = eX; // mũ của kết quả
	int intPart = 0; // phần nguyên của kết quả
	string significand; // phần trị của kết qả 
	string sign; // dấu của kết quả

	int carry = 0;
	significand = addSigned(significandX, significandY, x, y, intPart, intPartX, intPartY);

	if (significand[0] == '-') // kiểm tra số âm
	{
		sign = "-";
		significand.erase(significand.begin() + 0);
	}

	if (SignificandIsZero(significand, intPart))
	{
		return QFloat();
	}

	//// Trường hợp cùng dấu số không chuẩn nhưng carry = 1 -> TH không chuẩn + không chuẩn = chuẩn (Carry = 1)
	//if ((X[0] == '0' && Y[0] == '0') || (X[0] == '1' && Y[0] == '1'))
	//	if (intPartX == 0 && intPartY == 0 && carry) // shift right
	//	{
	//		intPart = 1; // cập nhật lại phần nguyên của kết quả
	//		e++;
	//	}

	//// Trường hợp không chuẩn khác dấu nhưng carry = 1 -> thực hiện bù 2
	//if ((X[0] == '0' && Y[0] == '1') || (X[0] == '1' && Y[0] == '0'))
	//	if (intPartX == 0 && intPartY == 0 && carry) // shift right
	//	{
	//		int i;
	//		// Đảo tất cả các bit
	//		for (i = 0; i < significand.size(); i++)
	//			significand[i] = (significand[i] == '0' ? '1' : '0');
	//		// Thêm 1
	//		for (i = significand.size() - 1; i >= 0; i--)
	//			if (significand[i] == '0') {
	//				significand[i] = '1';
	//				for (int j = i + 1; j < significand.size(); j++)
	//					significand[j] = '0';
	//				break;
	//			}
	//	}

	if (intPart > 1) // tràn -> shift right, chỉ có TH phép cộng intPart mới có thể > 1
	{
		significand.insert(significand.begin(), (intPart % 2) + '0'); // thêm vào đầu phần trị
		significand.pop_back();
		intPart /= 2; // cập nhật lại phần nguyên của kết quả
		e++; // tăng số mũ

		if ((e - BIAS) >= BIAS + 1) // exponent overflow
		{
			if (sign == "-")
				return QFloat("-Inf");
			return QFloat("Inf");
		}
	}

	while (intPart == 0) // số không chuẩn -> shift left
	{
		intPart = significand[0];
		significand.erase(significand.begin());
		significand.push_back('0');
		e--;

		if (e < -BIAS - 1) // exponent underflow
		{
			if (sign == "-")
				return QFloat("-Inf");
			return QFloat("Inf");
		}
	}

	// đổi exp sang nhị phân 
	if (e < 0) // e là GIÁ TRỊ phần mũ được biểu diễn ở hệ 10 từ dãy bit nhị phân -> dương (vì đã xét TH mũ toàn bit 1)
		e = 0;

	string exponent = IntToBin(to_string(e));
	int lengthExp = exponent.length();
	if (lengthExp < EXPONENT) // đảm bảo exponent luôn 15 bit
	{
		for (int i = 0; i < EXPONENT - lengthExp; i++)
			exponent = '0' + exponent;
	}

	QFloat res;

	// Đặt phần dấu

	if (sign == "-")
		res.SetBit(MAX_LENGTH - 1, 1);
	else
		res.SetBit(MAX_LENGTH - 1, 0);
	// Đặt phần mũ
	for (int i = 1; i <= EXPONENT; i++)
		res.SetBit(MAX_LENGTH - 1 - i, exponent[i - 1] - 48);

	// Đặt phần trị
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		res.SetBit(MAX_LENGTH - 1 - i, significand[i - EXPONENT - 1] - 48);

	return res;
}

//Toan tu -
QFloat QFloat::operator- (const QFloat &minus)
{
	//Phép trừ là phép cộng với số đối của nó
	QFloat oppMinus = minus;
	
	oppMinus.SetBit(MAX_LENGTH - 1, !(oppMinus.GetBit(MAX_LENGTH - 1))); // đổi dấu số trừ

	return (*this + oppMinus);
}

////Toan tu *
//QFloat QFloat::operator* (const QFloat &multiply)
//{
//	//So nhan = 0 hoac so bi nhan = 0
//	if (this->CheckZero() || multiply.CheckZero())
//	{
//		return GetZero();
//	}
//
//	QFloat Z; //*this * multiply = Z
//	int exponent = this->CalExponent() + multiply.CalExponent(); //phan mu
//
//	//tran so, so vo cung
//	if (exponent > BIAS)
//	{
//		Z = GetInf();
//		Z.SaveSign((this->GetSign() + multiply.GetSign()) % 2);
//		return Z;
//	}
//
//	Z.SaveSign((this->GetSign() + multiply.GetSign()) % 2);
//
//	//Nhan phan tri 
//	int n = (SIGNIFICAND + 1) * 2 + 1;
//	bool *bit = new bool[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		bit[i] = 0;
//	}
//	NhanPhanTri(*this, multiply, bit, n);
//
//	int chamDong = n - 2 * SIGNIFICAND - 1;
//	int s = chamDong - bit[chamDong - 1];
//	bit[s - 1] = LamTronNhiPhan(bit + (s));
//	int firstBit1 = GetFirstBit1(bit, n);
//	exponent += chamDong - firstBit1;
//
//	if (exponent > BIAS) //Tran bo nho, so vo cung
//	{
//		Z = GetInf();
//		Z.SaveSign((this->GetSign() + multiply.GetSign()) % 2);
//		delete[] bit;
//		return Z;
//	}
//
//	if (exponent < 1 - BIAS - SIGNIFICAND) //Tran bo nho, so underflow
//	{
//		Z = GetZero();
//		Z.SaveSign((this->GetSign() + multiply.GetSign()) % 2);
//		delete[] bit;
//		return Z;
//	}
//
//	if (exponent < 1 - BIAS) //So dang khong chuan 
//	{
//		Z.SaveExponent(-BIAS);
//		Z.SaveSignificand(bit + firstBit1 + 1 - (1 - BIAS - exponent));
//	}
//	else
//	{
//		Z.SaveExponent(exponent);
//		Z.SaveSignificand(bit + firstBit1 + 1);
//	}
//
//	delete[] bit;
//	return (Z);
//}

////Toan tu /
//QFloat QFloat::operator/( QFloat &divide)
//{
//	if (this->CheckZero()) //So chia bang 0 
//	{
//		return GetZero();
//	}
//	if (divide.CheckZero()) //So bi chia bang 0 
//	{
//		return GetNaN();
//	}
//
//	//Khoi tao
//	int exponent = this->CalExponent() - divide.CalExponent(), firstBit, lenX = 0, lenY = 0;
//
//	bool* sigX = new bool[2 * BIAS + SIGNIFICAND + 1]; //Phan tri cua so chia
//	bool* sigY = new bool[SIGNIFICAND + 1]; //Phan tri cua so bi chia
//	bool* sigZ = new bool[2 * BIAS + SIGNIFICAND + 1]; //Phan tri cua ket qua
//
//	this->ChuyenPhanTriThanhBit(sigZ);
//	firstBit = GetFirstBit1(sigZ, SIGNIFICAND + 1);
//
//	for (int i = firstBit; i <= SIGNIFICAND; i++)
//	{
//		sigX[lenX++] = sigZ[i];
//	}
//
//	divide.ChuyenPhanTriThanhBit(sigZ);
//	firstBit = GetFirstBit1(sigZ, SIGNIFICAND + 1);
//
//	for (int i = firstBit; i <= SIGNIFICAND; i++) sigY[lenY++] = sigZ[i];
//
//	//Chia phan tri
//	//Dau thap phan sau bit sigZ[lenX - 1]
//	firstBit = -1;
//	int lX = 0;
//	for (int i = 0; ; i++) //Chia den khi khong chia duoc nua
//	{
//		if (firstBit >= 0 && exponent + lenX - firstBit - 1 > BIAS) //Tran bo nho (overflow)
//		{
//			QFloat Z = GetInf();
//			Z.SaveSign((this->GetSign() + divide.GetSign()) % 2);
//			delete[] sigX;
//			delete[] sigY;
//			delete[] sigZ;
//			return Z;
//		}
//
//		if (firstBit == -1 && exponent + lenX - i - 1 < 1 - BIAS - SIGNIFICAND) //Tran bo nho (underflow)
//		{
//			QFloat Z = GetZero();
//			delete[] sigX;
//			delete[] sigY;
//			delete[] sigZ;
//			return Z;
//		}
//
//		if (firstBit >= 0 && i - firstBit > SIGNIFICAND) break; //Dieu kien dung
//
//		if (i >= lenX) sigX[i] = 0;
//
//		//Bat dau chia
//		if (SoSanhBit(sigX + lX, i - lX + 1, sigY, lenY) < 0)
//		{
//			sigZ[i] = 0;
//			continue;
//		}
//		sigZ[i] = 1;
//		TruBit(sigX + lX, i - lX + 1, sigY, lenY, sigX + lX, i - lX + 1);
//		if (firstBit == -1 && sigZ[i] == 1)
//		{
//			firstBit = i;
//		}
//		while (lX <= i && sigX[lX] == 0) lX++;
//	}
//
//	QFloat Z;
//	Z.SaveSign((this->GetSign() + divide.GetSign()) % 2);
//	if (exponent + lenX - firstBit - 1 < 1 - BIAS) //So khong chuan
//	{
//		Z.SaveExponent(-BIAS);
//		Z.SaveSignificand(sigZ + (lenX + 1 + exponent - (1 - BIAS)));
//	}
//	else {
//		Z.SaveExponent(exponent + lenX - firstBit - 1);
//		Z.SaveSignificand(sigZ + firstBit + 1);
//	}
//
//	delete[] sigX;
//	delete[] sigY;
//	delete[] sigZ;
//
//	return Z;
//}
//
QFloat& QFloat::operator=(const QFloat& q)
{
	if (this != &q)
	{
		for (int i = 0; i < NUM_BLOCK; i++)
		{
			this->data[i] = q.data[i];
		}
	}

	return *this;
}
//
////------------------------------------------------------------------------------------------------
//PHAN KHOI TAO

QFloat::QFloat()
{
	for (int i = 0; i < NUM_BLOCK; i++)
	{
		data[i] = 0;
	}
}

QFloat::QFloat(string str)
{
	if (str == "Inf" || str == "-Inf")
	{
		// Đặt phần mũ -> toàn bit 1
		for (int i = 1; i <= EXPONENT; i++)
			SetBit(MAX_LENGTH - 1 - i, 1);

		// Đặt phần trị -> toàn bit 0
		for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
			SetBit(MAX_LENGTH - 1 - i, 0);

		if (str[0] == '-') // là số âm
			SetBit(MAX_LENGTH - 1, 1);
		else // là số dương
			SetBit(MAX_LENGTH - 1, 0);
	}
	else if (str == "NaN") 
	{
		// Đặt phần mũ -> toàn bit 1
		for (int i = 1; i <= EXPONENT; i++)
			SetBit(MAX_LENGTH - 1 - i, 1);

		// Đặt phần trị -> khác bit 0 -> giả sử data[3] toàn bit 1
		for (int i = EXPONENT + 1; i < MAX_LENGTH - 32; i++)
			SetBit(MAX_LENGTH - 1 - i, 0);
		for (int i = MAX_LENGTH - 32; i < MAX_LENGTH; i++)
			SetBit(MAX_LENGTH - 1 - i, 1);

		if (str[0] == '-') // là số âm
			SetBit(MAX_LENGTH - 1, 1);
		else // là số dương
			SetBit(MAX_LENGTH - 1, 0);
	}
	else
		operator =(fromDecToQFloat(str));
}

QFloat::~QFloat()
{
}
