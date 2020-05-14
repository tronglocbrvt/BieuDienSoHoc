#include "QFloat.h"

// ====================================== NHÓM HÀM CHUYỂN ĐỔI ======================================

// chuyển từ chuỗi nhị phân sang QFloat
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

// chuyển từ chuỗi thập phân sang QFloat
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
		res.SetBit(MAX_LENGTH - 1 - i, exponent[i - 1] - 48);

	// Đặt phần trị
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		res.SetBit(MAX_LENGTH - 1 - i, resStr[i - 15 + count] - 48);

	return res;
}

// chuyển từ chuỗi ở hệ 2 hoặc 10 sang QFloat
QFloat QFloat::fromStringToQFloat(string str, unsigned short b)
{
	if (b == 2)
		return fromBinToQFloat(str);
	if (b == 10)
		return fromDecToQFloat(str);
}

// chuyển từ QFloat sang chuỗi nhị phân
string QFloat::QFloatToBinStr()
{
	string res;

	for (int i = MAX_LENGTH - 1; i >= 0; i--)
	{
		res += GetBit(i) + '0';
	}

	return res;
}

// chuyển từ QFloat sang chuỗi thập phân
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

// chuyển từ chuỗi ở hệ a sang chuỗi ở hệ b
string QFloat::BaseToBase(string str, unsigned short a, unsigned short b)
{
	QFloat q = fromStringToQFloat(str, a);

	string res = q.QFloatToString(b);

	return res;
}

// ====================================== TOÁN TỬ ======================================

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
	// Tính phần mũ
	int eX = x.exponentValue();
	int eY = y.exponentValue();

	// lấy phần trị lưu vào QInt
	QInt qX, qY;

	if (x.CheckDenormalized() == false)  // thêm phần nguyên vào QInt, số chuẩn phần nguyên là 1, không chuẩn mặc định là 0
		qX.SetBit(SIGNIFICAND, 1);

	if (y.CheckDenormalized() == false) // thêm phần nguyên vào QInt, số chuẩn phần nguyên là 1, không chuẩn mặc định là 0 
		qY.SetBit(SIGNIFICAND, 1);

	for (int i = SIGNIFICAND - 1; i >= 0; i--) // set bit vào QInt
	{
		qX.SetBit(i, x.GetBit(i));
		qY.SetBit(i, y.GetBit(i));
	}

	// kiểm tra phần mũ có bằng nhau hay không
	if (eX != eY) // 2 mũ không bằng nhau
	{
		if (eX < eY) // nếu eX < eY ta đổi vị trí x, y
			return (y + x);

		// dịch phải số có phần mũ nhỏ hơn (ta đã có bước hoán vị ở trên nên y là số có mũ nhỏ hơn)
		// Thêm bit vào eY để cân bằng số mũ
		while (eX > eY)
		{
			qY = qY >> 1; // dịch phải
			eY++; // tăng số mũ
		}

		if (qY.isZero())
			return x;
	}

	// eX = eY
	int e = eX; // mũ của kết quả
	bool sign; // dấu kết quả
	QFloat result; // kết quả cuối cùng

	bool xSign = x.GetBit(MAX_LENGTH - 1); // dấu x
	bool ySign = y.GetBit(MAX_LENGTH - 1); // dấu y

	QInt res = addSigned(qX, qY, sign, xSign, ySign);

	// Trường hợp số không chuẩn nhưng phần nguyên bằng = 1 -> tăng exp lên 1
	if (res.GetBit(SIGNIFICAND) && x.CheckDenormalized() && y.CheckDenormalized())
		e++;

	if (res.isZero())
	{
		return QFloat();
	}

	if (res.GetBit(SIGNIFICAND + 1) == 1) // tràn -> shift right
	{
		res = res >> 1;
		e++; // tăng số mũ

		if (e > BIAS) // exponent overflow
		{
			if (sign)
				return QFloat("-Inf");
			return QFloat("Inf");
		}
	}

	while (res.GetBit(SIGNIFICAND) == 0 && e != (1 - BIAS)) // số không chuẩn -> shift left
	{
		res = res << 1; // dịch trái
		e--; // giảm số mũ
		if (e < 1 - BIAS) // exponent underflow
		{
			if (sign)
				return QFloat("-Inf");
			return QFloat("Inf");
		}
	}

	// đổi exp sang nhị phân 
	if (e == 1 - BIAS) // số không chuẩn
		e = 0;
	else
		e += BIAS;

	if (sign) // nếu là âm
	{
		result.SetBit(MAX_LENGTH - 1, 1);
	}

	QInt exponent(e);

	// Đặt phần mũ
	for (int i = 1; i <= EXPONENT; i++)
		result.SetBit(MAX_LENGTH - 1 - i, exponent.GetBit(EXPONENT - i));

	// Đặt phần trị
	for (int i = EXPONENT + 1; i < MAX_LENGTH; i++)
		result.SetBit(MAX_LENGTH - 1 - i, res.GetBit(MAX_LENGTH - 1 - i));

	return result;
}

//Toan tu -
QFloat QFloat::operator- (const QFloat &minus)
{
	//Phép trừ là phép cộng với số đối của nó
	QFloat oppMinus = minus;

	oppMinus.SetBit(MAX_LENGTH - 1, !(oppMinus.GetBit(MAX_LENGTH - 1))); // đổi dấu số trừ

	return (*this + oppMinus);
}

// Toán tử nhân
QFloat QFloat::operator*(const QFloat& multiply)
{
	QFloat f = multiply;
	// Nếu 1 trong 2 là số báo lỗi
	if (CheckNaN() || f.CheckNaN()) 
		return QFloat("NaN");

	// Nếu là vô cực nhân 0
	if ((CheckInf() && f.CheckZero()) || (CheckZero() && f.CheckInf()))
	{
		return QFloat("NaN");
	}

	// Nếu là vô cực nhân một số
	if (CheckInf() || f.CheckInf()) {
		if (GetBit(MAX_LENGTH - 1) ^ f.GetBit(MAX_LENGTH - 1)) 
			return QFloat("-Inf");
		return QFloat("Inf");
	}
	
	if (CheckZero() || f.CheckZero())
		return QFloat();

	string A = this->QFloatToBinStr();
	string B = f.QFloatToBinStr();

	// lấy chuỗi nhị phân phần mũ
	string expX = A.substr(1, EXPONENT);
	string expY = B.substr(1, EXPONENT);

	string firstCharX = "1", firstCharY = "1";

	// Tính phần mũ
	int eX = stoi(expX, nullptr, 2) - BIAS;
	int eY = stoi(expY, nullptr, 2) - BIAS;

	if (eX == -BIAS)
	{
		eX = -BIAS + 1;
		firstCharX = "0";
	}
	else if (eY == -BIAS)
	{
		eY = -BIAS + 1;
		firstCharY = "0";
	}

	int e = eX + eY;

	// lấy phần trị
	string significandA = A.substr(EXPONENT + 1, MAX_LENGTH - 1);
	string significandB = B.substr(EXPONENT + 1, MAX_LENGTH - 1);

	//Tính vị trí của dấu chấm từ phải qua
	int decimalPoint = countSignificantNumber(significandA) + countSignificantNumber(significandB);

	significandA = firstCharX + significandA;
	significandB = firstCharY + significandB;


	string C = multiplyBinary(significandA, significandB);

	//Tính số lần di chuyển dấu chấm để normalize
	int s = C.length() - decimalPoint - 1;

	// Tính dấu
	bool sign = !(A[0] == B[0]);
	char signChar = sign + '0';

	//Tính số mũ
	e += s;
	if (e < -BIAS + 1)
		return QFloat(); //Underflow, trả về 0
	else if (e > BIAS)
	{
		if (sign == 1)
			return QFloat("-Inf");
		return QFloat("Inf");
	}

	string m, exp, roundStr;

	while (C.length() < SIGNIFICAND + 1)
		C = C + "0";

	// Số không chuẩn
	if (e == -BIAS + 1)
	{
		m = C.substr(0, SIGNIFICAND);
		roundStr = C.substr(SIGNIFICAND, 3);

		exp = "000000000000000";
	}
	else
	{
		m = C.substr(1, SIGNIFICAND);
		roundStr = C.substr(SIGNIFICAND + 1, 3);

		e = e + BIAS;
		exp = IntToBin(to_string(e));
	}

	//Tính phần trị
	roundingFrac(roundStr, m);
	// đổi exp cho đủ độ dài
	while (exp.length() < EXPONENT)
		exp = "0" + exp;

	string res = signChar + exp + m;
	return fromBinToQFloat(res);
}

// Toán tử chia
QFloat QFloat::operator/(const QFloat& divide)
{
	QFloat f = divide;

	// Nếu 1 trong 2 là NaN, báo lỗi
	if (CheckNaN() || f.CheckNaN()) 
		return QFloat("NaN");

	// a / 0 = Undefined
	if (f.CheckZero())
		return QFloat("NaN");

	// 0 / a = 0 (a khác 0)
	if (CheckZero())
		return QFloat();

	// oo / oo = Undefined
	if (CheckInf() && f.CheckInf()) 
		return QFloat("NaN");

	// oo / a = oo (xét dấu)
	if (CheckInf()) {
		if (f.GetBit(MAX_LENGTH - 1) ^ GetBit(MAX_LENGTH - 1)) 
			return QFloat("-Inf");
		return QFloat("Inf");
	}
	// a / oo = 0 (a khác vô cực)
	if (f.CheckInf()) 
		return QFloat();


	string A = this->QFloatToBinStr();
	string B = f.QFloatToBinStr();

	// lấy chuỗi nhị phân phần mũ
	string expX = A.substr(1, EXPONENT);
	string expY = B.substr(1, EXPONENT);

	string firstCharX = "1", firstCharY = "1";

	// Tính phần mũ
	int eX = stoi(expX, nullptr, 2) - BIAS;
	int eY = stoi(expY, nullptr, 2) - BIAS;

	if (eX == -BIAS)
	{
		eX = -BIAS + 1;
		firstCharX = "0";
	}
	else if (eY == -BIAS)
	{
		eY = -BIAS + 1;
		firstCharY = "0";
	}

	int e = eX - eY;

	// lấy phần trị
	string significandA = A.substr(EXPONENT + 1, MAX_LENGTH - 1);
	string significandB = B.substr(EXPONENT + 1, MAX_LENGTH - 1);

	//Tính vị trí của dấu chấm từ phải qua
	int decimalPoint = countSignificantNumber(significandA) - countSignificantNumber(significandB);

	significandA = firstCharX + significandA;
	significandB = firstCharY + significandB;

	int tempNum = 0;
	string C = divideBinary(significandA, significandB, tempNum);

	//Tính số lần di chuyển dấu chấm để normalize
	int s = C.length() - decimalPoint - tempNum - 1;


	// Tính dấu
	bool sign = !(A[0] == B[0]);
	char signChar = sign + '0';

	//Tính số mũ
	e += s;
	if (e < -BIAS + 1)
		return QFloat(); //Underflow, trả về 0
	else if (e > BIAS)
	{
		if (sign == 1)
			return QFloat("-Inf");
		return QFloat("Inf");
	}

	string m, exp, roundStr;

	while (C.length() < SIGNIFICAND + 1)
		C = C + "0";

	// Số không chuẩn
	if (e == -BIAS + 1)
	{
		m = C.substr(0, SIGNIFICAND);
		roundStr = C.substr(SIGNIFICAND, 3);

		exp = "000000000000000";
	}
	else
	{
		m = C.substr(1, SIGNIFICAND);
		roundStr = C.substr(SIGNIFICAND + 1, 3);

		e = e + BIAS;
		exp = IntToBin(to_string(e));
	}

	//Tính phần trị
	roundingFrac(roundStr, m);
	// đổi exp cho đủ độ dài
	while (exp.length() < EXPONENT)
		exp = "0" + exp;

	string res = signChar + exp + m;
	return fromBinToQFloat(res);
}

// toán tử gán =
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
// ====================================== NHÓM HÀM KHỞi TẠO VÀ HỦY ======================================

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

// ====================================== NHÓM HÀM KIỂM TRA ======================================

//Kiem tra co phai so 0 hay khong
bool QFloat::CheckZero()
{
	for (int i = 1; i < MAX_LENGTH; i++)
		if (GetBit(MAX_LENGTH - 1 - i) != 0)
			return false;
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

// ====================================== GET, SET BIT VÀ CÁC HÀM HỖ TRỢ ======================================

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

// tính giá trị phần mũ
int QFloat::exponentValue()
{
	int e = 0;

	if (CheckDenormalized())
		return 1 - BIAS; // -16382

	for (int i = EXPONENT; i >= 1; i--)
	{
		e += GetBit(MAX_LENGTH - i - 1) * (1 << (15 - i));
	}

	return e - BIAS;
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
		if (!(a[1] == '0' && a[2] == '0' && fracPartBit[fracPartBit.size() - 1] == '0'))
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

QInt QFloat::addSigned(QInt x, QInt y, bool& sign, bool xSign, bool ySign)
{
	int cal = 0;

	if (xSign != ySign)
		cal = 1;

	QInt res;

	if (cal)
	{
		if (x < y)
		{
			res = y - x;
			sign = ySign;
		}
		else
		{
			res = x - y;
			sign = xSign;
		}
	}
	else
	{
		res = x + y;
		sign = xSign;
	}

	return res;
}

int countSignificantNumber(string& n) // đếm số lượn phần trị
{
	int count = 0;
	int i = n.length() - 1;
	while (i >= 0 && n[i] != '1')
	{
		count++;
		i--;
	}

	int num = n.length() - count;
	if (num == 0)
	{
		n = "";
		return 0;
	}

	n = n.substr(0, num);
	return num;
}

string BinaryAddition(const string& a, const string& b)
{
	QInt n1 = QInt::fromBinToQInt(a);
	QInt n2 = QInt::fromBinToQInt(b);

	QInt n3 = n1 + n2;

	string res = n3.QIntToBinStr();
	while (res.length() < a.length())
		res = "0" + res;
	return res;
}

string BinarySubSubtraction(const string& a, const string& b)
{
	QInt n1 = QInt::fromBinToQInt(a);
	QInt n2 = QInt::fromBinToQInt(b);

	QInt n3 = n1 - n2;

	string res = n3.QIntToBinStr();
	while (res.length() < a.length())
		res = "0" + res;
	return res.substr(res.length() - a.length()); //Lấy a.lenth() bit cuối;
}

string multiplyBinary(string& a, string& b)
{
	while (a.length() < b.length())
		a = "0" + a;
	while (b.length() < a.length())
		b = "0" + b;

	int len = a.length();
	string M = a;
	string A(len, '0');
	string Q = b;
	string C = "0";


	for (int i = 0; i < len; i++)
	{
		if (Q[len - 1] == '1')
		{
			A = BinaryAddition(A, M);
			if (A.length() > len)
			{
				C = A[A.length() - len - 1];
			}
			A = A.substr(A.size() - len);
		}
		string ans = C + A + Q;
		ans = "0" + ans;
		ans.pop_back();
		C = ans[0];
		A = ans.substr(1, len);
		Q = ans.substr(len + 1, len);
	}
	string ans = A + Q;
	return ans.substr(ans.find("1"));
}

bool isStringZero(const string& s)
{
	if (s.empty())
		return false;
	for (char c : s)
	{
		if (c != '0')
			return false;
	}
	return true;
}
bool isStringBigger(const string& s1, const string& s2) // a > b, length equal
{
	string a = s1, b = s2;
	while (a.length() < b.length())
		a = "0" + a;
	while (b.length() < a.length())
		b = "0" + b;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] != b[i])
		{
			return a[i] > b[i];
		}
	}
	return false;
}

string divideBinary(string& a, string& b, int& decimalPoint)
{
	string R = "";
	string A = a;
	string B = b;
	string result;
	int count = 0;
	bool stopCount = true;


	while (result.length() < SIGNIFICAND + 2 && (isStringZero(R) == false || A.length() != 0))
	{
		if (!stopCount)
		{
			count++;
		}

		R = R + A[0];
		A.erase(0, 1);
		if (isStringBigger(B, R))
		{
			if (A.length() < 1)
			{
				A = "0";
				stopCount = false;
			}

			result = result + "0";
		}
		else
		{
			R = BinarySubSubtraction(R, B);
			result = result + "1";
		}

		if (result.find("1") != string::npos)
			result = result.substr(result.find("1"));

	}

	decimalPoint = count;
	if (result.find("1") == string::npos)
		return "0";
	return result.substr(result.find("1"));
}