#include "QInt.h"

// ============================ KHỞI TẠO VÀ HỦY ============================

// hàm khởi tạo kiểu QInt, khởi tạo 4 phần tử của data đều bằng 0 -> QInt gồm 128 bit 0
QInt::QInt()
{
	for (int i = 0; i < NUM_BLOCK; i++)
		data[i] = 0;
}

// hàm khởi tạo kiểu QInt từ số nguyên n -> chuyển n sang QInt và sử dụng operator = 
QInt::QInt(const int & n)
{
	*this = (fromDecToQInt(to_string(n)));
}

QInt::~QInt()
{
}

// ============================ CÁC HÀM CHUYỂN ĐỔI ============================

// chuyển chuỗi thập phân sang QInt
QInt QInt::fromDecToQInt(string str)
{
	QInt res;

	bool sign; // lưu dấu

	if (str[0] == '-') // số âm
	{
		str.erase(str.begin() + 0);
		sign = 1;
	}
	else
		sign = 0;

	int i = 0; // bắt đầu set các bit từ data[0]
	while (str != "0" && str != "")
	{
		unsigned short bit = (str[str.length() - 1] - 48) % 2; // chia 2 lấy phần dư
		res.SetBit(i, bit); // set bit tại vị trí i
		str = StrDiv2(str); // chia chuỗi cho 2
		i++; // tăng i để set các bit tiếp theo
	}

	if (sign == 1)
		res = toTwoCompliment(res);

	return res;
}

// chuyển chuỗi nhị phân sang QInt
QInt QInt::fromBinToQInt(string str)
{
	QInt res;

	unsigned short length = str.size(); // lưu chiều dài chuỗi

	for (int i = 0; i < length; i++)
	{
		res.SetBit(length - 1 - i, str[i] - '0');
	}

	return res;
}

// chuyển chuỗi thập lục phân sang QInt
QInt QInt::fromHexToQInt(string str)
{
	QInt res;

	// Kiểm tra đầu vào và chuẩn hóa về dạng viết hoa
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		
	}

	int pos = 0;
	unsigned short digit;

	for (int i = str.size() - 1; i > -1; i--) 
	{
		if (str[i] >= '0' && str[i] <= '9') // nếu hexa ở dạng từ 0 -> 9
			digit = str[i] - '0';
		else // hexa ở dạng A B C D E F (10 -> 15)
			digit = str[i] + 10 - 'A';
		
		for (int j = 0; j < 4; j++) // mỗi ký tự trong hexa được lưu bởi 4 bit nhị phân
		{
			unsigned short bit = digit & 1; // AND với 1 để lấy ra bit cuối
			res.SetBit(pos, bit); // set bit vào QInt
			pos++; // tăng vị trí set bit
			digit = digit >> 1; // do được biểu diễn bởi 4 bit nên dịch phải 1 bit để lấy bit tiếp theo
		}
	}

	return res;
}

// chuyển chuỗi hệ cơ số b sang QInt
QInt QInt::fromStringToQInt(string str, unsigned short b)
{
	if (b == 2)
		return fromBinToQInt(str);
	if (b == 10)
		return fromDecToQInt(str);
	if (b == 16)
		return fromHexToQInt(str);
}

// chuyển QInt sang chuỗi thập phân
string QInt::QIntToDecStr()
{ 
	string res = "0";

	string tmp = "1"; // tmp để lưu giá trị tại 2^n, ban đầu 2^0 = 1
	for (int i = 0; i < NUM_BIT - 1; i++) // chạy 127 bit, bit 128 (bit dấu -> xét sau)
	{
		if (GetBit(i) == 1) // chỉ cập nhật giá trị tại những nơi có bit = 1
			res = plusString(res, tmp);
		tmp = StrMulti2(tmp);
	}

	// xét bit dấu
	if (GetBit(NUM_BIT - 1) == 1) // nếu bit dấu = 1 -> số âm -> res = -(2^127 - res) mà 2^127 = tmp
		res = '-' + minusString(tmp, res);

	return res;
}

// chuyển QInt sang chuỗi nhị phân
string QInt::QIntToBinStr()
{
	string res;

	for (int i = NUM_BIT - 1; i >= 0; i--) 
	{
		res += GetBit(i) + '0';
	}

	// xóa số 0 thừa
	for (int i = 0; i < NUM_BIT - 1; i++) // chừa lại bit cuối
	{
		if (res[i] == '0')
		{
			res.erase(res.begin() + 0);
			i--;
		}
		else
			return res;
	}

	return res;
}

// chuyển QInt sang chuỗi thập lục phân
string QInt::QIntToHexStr()
{
	string res; // chuỗi kết quả

	map<string,string> mp; // lưu các giá trị đặc biệt của 16 ký tự hexa
	mp["0000"] = "0";
	mp["0001"] = "1";
	mp["0010"] = "2";
	mp["0011"] = "3";
	mp["0100"] = "4";
	mp["0101"] = "5";
	mp["0110"] = "6";
	mp["0111"] = "7";
	mp["1000"] = "8";
	mp["1001"] = "9";
	mp["1010"] = "A";
	mp["1011"] = "B";
	mp["1100"] = "C";
	mp["1101"] = "D";
	mp["1110"] = "E";
	mp["1111"] = "F";
	
	for (int i = 0; i < NUM_BIT - 1; i = i + 4) // vì mỗi ký tự hexa được biểu diễn bằng 4 bit -> bước nhảy là 4
	{
		string temp; // lưu dãy bit của ký tự hexa

		for (int j = 3; j >= 0; j--) // duyệt từng bit trong bộ 4 bit đại diện cho 1 ký tự hexa
		{
			temp += GetBit(i + j) + '0';
		}

		res += mp[temp];
	}

	if (res.size() == 0) return "0";

	// xóa các số 0 thừa
	while (res.length() > 1 && res[res.length() - 1] == '0')
	{
		res.pop_back();
	}

	reverse(res.begin(), res.end()); // đảo ngược chuỗi kết quả

	return res;
}

// chuyển QInt sang chuỗi ở hệ cơ số b
string QInt::QIntToString(unsigned short b)
{
	if (b == 2)
		return QIntToBinStr();
	if (b == 10)
		return QIntToDecStr();
	if (b == 16)
		return QIntToHexStr();
}

// chuyển chuỗi từ hệ cơ số a sang hệ cơ số b
string QInt::BaseToBase(string str, unsigned short a, unsigned short b)
{
	QInt q = fromStringToQInt(str, a);

	string res = q.QIntToString(b);	

	return res;
}

// chuyển sang bù 2
QInt QInt::toTwoCompliment(QInt q)
{
	return (~q + QInt(1)); // đổi dấu rồi cộng 1
}

// ============================ TOÁN TỬ CỘNG, TRỪ, NHÂN, CHIA, LẤY DƯ ============================

// Toán tử cộng
QInt QInt::operator+(QInt q)
{
	QInt res; // lưu kết quả
	unsigned short carry = 0; // nhớ
	
	for (int i = 0; i < NUM_BIT; i++)
	{
		unsigned short tmp = GetBit(i) + q.GetBit(i) + carry;
		res.SetBit(i, tmp % 2);
		carry = tmp / 2;
	}

	return res;
}

// toán tử trừ
QInt QInt::operator-(QInt q) // ta chuyển thành cộng a - b = a + (-b)
{
	QInt res; // lưu kết quả
	unsigned short carry = 0; // nhớ
	q = toTwoCompliment(q); // chuyển q sang dạng bù 2

	// thực hiện như phép cộng
	res = *this + q;

	return res;
}

// toán tử nhân theo thuật toán Booth
QInt QInt::operator*(QInt M)
{
	QInt Q = *this; // số nhân
	QInt A;
	unsigned short tmp = 0;

	for (int i = 0; i < NUM_BIT; i++)
	{
		unsigned short lastQ = Q.GetBit(0);
		if (lastQ == 1 && tmp == 0) // Q_0 = 1 và Q_-1 = 0
			A = A - M;
		else if (lastQ == 0 && tmp == 1) // Q_0 = 0 và Q_-1 = 1
			A = A + M;

		unsigned short lastA = A.GetBit(0); // bit cuối của A
		A = A >> 1; // dịch phải số học A 1 bit.
		Q = Q >> 1; // dịch phải số học 1 bit
		// do ta thêm bit cuối của A vào đầu Q nên ta đặt lại giá trị của bit đầu của Q:
		Q.SetBit(NUM_BIT - 1, lastA); // set lại bit đầu của Q
		tmp = lastQ; // do dịch phải nên tmp bằng Q_0
	}

	return Q;
}

// toán tử chia
QInt QInt::operator/(QInt M)
{
	QInt Q = *this; // số chia
	QInt A;
	bool sign = false; // kiểm tra M và Q có trái dấu hay không

	// Kiểm tra có chia cho 0 hay không
	if (M.isZero()) // chia cho 0
	{
		return A; // return 0
	}

	// Kiểm tra dấu Q và M và chuyển Q, M về không dấu
	if (Q.isNegative() && !M.isNegative())
	{
		Q = toTwoCompliment(Q); // chuyển Q từ âm sang dương
		sign = true;
	}

	else if (!Q.isNegative() && M.isNegative() == 1)
	{
		M = toTwoCompliment(M); // chuyển M từ âm sang dương
		sign = true;
	}

	else if (Q.isNegative() && M.isNegative())
	{
		Q = toTwoCompliment(Q); // chuyển Q từ âm sang dương
		M = toTwoCompliment(M); // chuyển M từ âm sang dương
		// vì âm chia âm ra dương nên KHÔNG set sign = true;
	}
	// chia không dấu
	for (int i = 0; i < NUM_BIT; i++)
	{
		unsigned short firstQ = Q.GetBit(127); // bit đầu của Q
		A = A << 1; // dịch trái số học A 1 bit.
		Q = Q << 1; // dịch trái số học 1 bit
		// do ta thêm bit đầu của Q vào cuối A nên ta đặt lại giá trị của bit cuối của A:
		A.SetBit(0, firstQ); // set lại bit cuối của A

		A = A - M;
		
		if (A.isNegative()) // A < 0
		{
			Q.SetBit(0, 0);
			A = A + M;
		}
		else
			Q.SetBit(0, 1);
	}

	if (sign) // nếu khác dấu
		Q = toTwoCompliment(Q); // đổi dấu thương 

	return Q;
}

// Toán tử lấy dư
QInt QInt::operator%(QInt M)
{
	QInt Q = *this; // số chia
	QInt A;
	bool sign = false; // biến sign dấu của số dư

	// Kiểm tra có chia cho 0 hay không
	if (M.isZero()) // chia cho 0
	{
		return A; // return 0
	}

	// Kiểm tra dấu Q và M và chuyển Q, M về không dấu
	if (Q.isNegative() && !M.isNegative())
	{
		Q = toTwoCompliment(Q); // chuyển Q từ âm sang dương
		sign = true; // dư là âm
	}

	else if (!Q.isNegative() && M.isNegative() == 1)
	{
		M = toTwoCompliment(M); // chuyển M từ âm sang dương
		sign = false; // dư là dương
	}

	else if (Q.isNegative() && M.isNegative())
	{
		Q = toTwoCompliment(Q); // chuyển Q từ âm sang dương
		M = toTwoCompliment(M); // chuyển M từ âm sang dương
		sign = true; // dư là âm
	}
	// chia không dấu
	for (int i = 0; i < NUM_BIT; i++)
	{
		unsigned short firstQ = Q.GetBit(127); // bit đầu của Q
		A = A << 1; // dịch trái số học A 1 bit.
		Q = Q << 1; // dịch trái số học 1 bit
		// do ta thêm bit đầu của Q vào cuối A nên ta đặt lại giá trị của bit cuối của A:
		A.SetBit(0, firstQ); // set lại bit cuối của A

		A = A - M;

		if (A.isNegative()) // A < 0
		{
			Q.SetBit(0, 0);
			A = A + M;
		}
		else
			Q.SetBit(0, 1);
	}

	if (sign) // nếu khác dấu
		A = toTwoCompliment(A); // đổi dấu thương 

	return A;
}

// ============================ TOÁN TỬ SO SÁNH & GÁN ============================

// toán tử so sánh >
bool QInt::operator>(QInt q) // so sánh this với q
{
	// trường hợp khác dấu
	if (GetBit(NUM_BIT - 1) > q.GetBit(NUM_BIT - 1))
		return false; // this < q và bit 1 biểu thị số âm

	if (GetBit(NUM_BIT - 1) < q.GetBit(NUM_BIT - 1))
		return true; // this > q và bit 0 < 1 (0 biểu thị số dương)

	// trường hợp cùng dấu
	for (int i = 126; i >= 0; i--)
	{
		if (GetBit(i) < q.GetBit(i))
			return GetBit(NUM_BIT - 1);
		if (GetBit(i) > q.GetBit(i))
			return ~GetBit(NUM_BIT - 1);
	}

	return false; // trường hợp bằng
}

bool QInt::operator<(QInt q)
{
	return !(*this == q) && !(*this > q);
}

bool QInt::operator<=(QInt q)
{
	return !(*this > q);
}

bool QInt::operator>=(QInt q)
{
	return !(*this < q);
}

bool QInt::operator!=(QInt q)
{
	return !(*this == q);
}

bool QInt::operator==(QInt q)
{
	for (int i = NUM_BIT - 1; i >= 0; i--)
	{
		if (GetBit(i) != q.GetBit(i))
			return false;
	}

	return true; 
}

// toán tử gán
QInt & QInt::operator=(const QInt& q)
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

// ============================ TOÁN TỬ NOT AND OR XOR ============================

// toán tử NOT
QInt& QInt::operator~()
{
	for (int i = 0; i < NUM_BLOCK; i++)
	{
		this->data[i] = ~this->data[i];
	}

	return *this;
}

// toán tử AND
QInt QInt::operator&(const QInt & q)
{
	QInt res;

	for (int i = 0; i < NUM_BLOCK; i++)
	{
		res.data[i] = this->data[i] & q.data[i];
	}

	return res;
}

// toán tử OR
QInt QInt::operator|(const QInt & q)
{
	QInt res;

	for (int i = 0; i < NUM_BLOCK; i++)
	{
		res.data[i] = this->data[i] | q.data[i];
	}

	return res;
}

// toán tử XOR
QInt QInt::operator^(const QInt & q)
{
	QInt res;

	for (int i = 0; i < NUM_BLOCK; i++)
	{
		res.data[i] = this->data[i] ^ q.data[i];
	}

	return res;
}

// ============================ TOÁN TỬ DỊCH TRÁI, DỊCH PHẢI ============================

// Phép dịch trái số học
QInt QInt::operator<<(unsigned int x) // dịch trái x bit
{
	QInt res; 

	for (int i = NUM_BIT - 1 - x; i >= 0; i--)
	{
		res.SetBit(i + x, GetBit(i));
	}

	for (int i = 0; i < x; i++) // chèn thêm bit 0
	{
		res.SetBit(i, 0);
	}

	return res;
}

// Phép dịch phải số học
QInt QInt::operator>>(unsigned int x) // dịch phải x bit
{
	QInt res; 

	for (int i = x; i < NUM_BIT; i++) // dịch phải
	{
		res.SetBit(i - x, GetBit(i));
	}

	for (int i = NUM_BIT - 1 - x; i < NUM_BIT; i++) // chèn thêm bit dấu
	{
		res.SetBit(i, GetBit(NUM_BIT - 1));
	}

	return res;
}

// ============================ TOÁN TỬ XOAY TRÁI, XOAY PHẢI ============================

// phép xoay trái
QInt & QInt::rol(unsigned int x) // xoay trái x bit
{
	int num = x % 128; // lấy số lượng bit cần xoay
	for(int i = 0; i < num; i++)
	{
			unsigned short bit = GetBit(NUM_BIT - 1); // lưu bit NUM_BIT - 1
			*this = *this << 1; // dịch trái 1 bit
			SetBit(0, bit); // chèn bit bị đẩy vào
	}
	return *this;
}

// phép xoay phải
QInt & QInt::ror(unsigned int x) // xoay phải x bit
{
	int num = x % 128; // lấy số lượng bit cần xoay
	for (int i = 0; i < num; i++)
	{
			unsigned short bit = GetBit(0); // lưu bit thứ 0
			*this = *this >> 1; // dịch phải 1 bit
			SetBit(NUM_BIT - 1, bit); // chèn bit bị đẩy vào
	}
	return *this;
}

// ============================ CÁC HÀM HỖ TRỢ ============================

// lấy giá trị bit ở vị trị i
unsigned short QInt::GetBit(unsigned short i) // lấy giá trị ở bit thứ i
{
	unsigned short block = i / 32; // Block data cần chọn
	unsigned short pos = i % 32; // Vị trí cần lấy trong block data

	if (block >= NUM_BLOCK || block < 0)
		return 0;

	return ((data[block] & (1 << pos)) ? 1 : 0);
}

// tạo giá trị bit tại vị trí i
void QInt::SetBit(unsigned short i, unsigned short bit)
{
	unsigned short block = i / 32; // Xác định Block data
	unsigned short pos = i % 32; // vi trí cần set giá trị bit

	if (block >= NUM_BLOCK || block < 0)
		return;

	if (bit == 1) // nếu là bit 1
	{
		data[block] = data[block] | (1 << i); // AND với 1 ra 1
	}
	else { // bit 0
		data[block] = data[block] & (~(1 << i)); // AND với 0 ra 0
	}
}

string QInt::StrMulti2(string str)
{
	return plusString(str, str); // str * 2 = str + str
}

// Cộng 2 chuỗi thập phân dương
string QInt::plusString(string str1, string str2)
{
	string res;
	string temp;

	// kiếm tra sự chênh lệch độ dài 2 chuỗi
	int length = str1.length() - str2.length();

	// Thêm 0 vào trước chuỗi có độ dài nhỏ hơn
	for (int i = 0; i < abs(length); i++)
		temp += '0';
	if (length < 0) // str1 ngắn hơn
		str1 = temp + str1;
	else // str 2 ngắn hơn
		str2 = temp + str2;

	// cộng 2 chuỗi dương
	int carry = 0; // nhớ
	for (int i = str1.length() - 1; i >= 0; i--) // lúc này str1.length() == str2.length() do đã thêm 0 vào trước chuỗi ngắn hơn
	{
		int tmp_1 = str1[i] - '0';
		int tmp_2 = str2[i] - '0';
		int  c = tmp_1 + tmp_2 + carry;
		carry = c / 10; // cập nhật lại nhớ
		res += c % 10 + '0';
	}

	if (carry != 0)
		res += carry + '0';

	// xóa các số 0 thừa
	while (res.length() > 1 && res[res.length() - 1] == '0')
	{
		res.pop_back();
	}

	reverse(res.begin(), res.end()); // đảo ngược chuỗi kết quả

	return res;
}

// trừ 2 chuỗi thập phân dương
string QInt::minusString(string str1, string str2)
{
	string res;
	string temp;
	bool sign = false; // dấu kết quả

	// kiếm tra sự chênh lệch độ dài 2 chuỗi
	int length = str1.length() - str2.length();

	// Thêm 0 vào trước chuỗi có độ dài nhỏ hơn
	for (int i = 0; i < abs(length); i++)
		temp += '0';
	if (length < 0) // str1 ngắn hơn
		str1 = temp + str1;
	else // str 2 ngắn hơn
		str2 = temp + str2;

	//Kiểm tra str1 hay str2 lớn hơn và chuyển str1 thành số lớn hơn.
	if (strcmp(str1.c_str(), str2.c_str()) < 0)
	{
		string TempStr = str1;
		str1 = str2;
		str2 = TempStr;
		sign = true; //a < b => a - b < 0
	}

	// trừ 2 chuỗi dương
	int carry = 0; // nhớ
	for (int i = str1.length() - 1; i >= 0; i--) // lúc này str1.length() == str2.length() do đã thêm 0 vào trước chuỗi ngắn hơn
	{
		if (str1[i] < carry + str2[i])
		{
			res += (10 + str1[i] - str2[i] - carry) + '0'; // mượn để trừ
			carry = 1;
		}
		else
		{
			res += (str1[i] - str2[i] - carry) + '0'; // trừ bình thường
			carry = 0;
		}

	}

	if (carry != 0)
		res += carry + '0';

	// xóa các số 0 thừa
	while (res.length() > 1 && res[res.length() - 1] == '0')
	{
		res.pop_back();
	}

	if (sign == true) // là số âm
		res += '-';

	reverse(res.begin(), res.end()); // đảo ngược chuỗi kết qu

	return res;
}

// hàm chia chuỗi thập phân dương cho 2
string QInt::StrDiv2(string str)
{
	string res;

	int mod = 0; // số dư bằng 0

	for (int i = 0; i < str.size(); i++)
	{
		mod = mod * 10 + (str[i] - 48); // vì chia cho 2 nên chỉ cần xét đến TH 2 chữ số, 48 là ASCII của '0'

		if ((mod >= 2 && i == 0) || i > 0) // khi chia cho 2 chỉ xét trường hợp số đầu tiên, những số sau nếu nhỏ
										  // hơn 2 vẫn chia bình thường (thương tại lần chia đó = 0)
			res.push_back((mod / 2) + '0');

		mod %= 2; // cập nhật lại số dư của lần chia đó
	}

	return res;
}

// kiểm tra có phải số âm hay không
bool QInt::isNegative()
{
	return data[NUM_BLOCK - 1] & 1; // bit đầu của QInt (bit dấu) tức là bit đầu của data[3] (lưu ý bit đầu là bit bên phải cùng vì 
						// bit được đánh số thứ tự từ phải qua; AND với 1 ta lấy ra được giá trị của bit đó.
}

// kiểm tra có bằng 0 hay không
bool QInt::isZero()
{
	for (int i = 0; i < NUM_BLOCK; i++)
		if (data[i] != 0) // nếu phát hiện khác 0 -> return false (nghĩa là QInt khác 0)
			return false;
	return true;
}