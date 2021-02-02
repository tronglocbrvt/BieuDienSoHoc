#include "BinaryNumber.h"

BinaryNumber::BinaryNumber()
{
	isQFloat = -1;
}
BinaryNumber::BinaryNumber(QInt a, QFloat b)
{
	_qInt = a;
	_qFloat = b;
	isQFloat = true;
}
BinaryNumber::BinaryNumber(QInt a)
{
	_qInt = a;
	isQFloat = false;
}
BinaryNumber::BinaryNumber(QFloat a)
{
	_qFloat = a;
	isQFloat = true;
}

// Từ string base N trả về BinaryNumber, isQFloat hỏi s là dưới dạng QFloat hay không
BinaryNumber BinaryNumber::fromStringtoBin(std::string s, unsigned short N, bool isQFloat)
{
	if (isQFloat)
	{
		return BinaryNumber(QFloat::fromStringToQFloat(s, N));
	}
	else
		return BinaryNumber(QInt::fromStringToQInt(s, N));
}
std::string BinaryNumber::binaryToString(unsigned short baseN)// Trả về string dạng base N
{
	if (isQFloat == -1)
		return "";
	if (isQFloat)
	{
		return _qFloat.QFloatToString(baseN);
	}
	else
		return _qInt.QIntToString(baseN);
}

// Toán tử + - * / %
BinaryNumber BinaryNumber::operator+(BinaryNumber q)
{
	if (isQFloat)
		return _qFloat + q._qFloat;
	else
		return _qInt + q._qInt;
}
BinaryNumber BinaryNumber::operator-(BinaryNumber q)
{
	if (isQFloat)
		return _qFloat - q._qFloat;
	else
		return _qInt - q._qInt;
}
BinaryNumber BinaryNumber::operator*(BinaryNumber M)
{
	if (isQFloat)
		return _qFloat * M._qFloat;
	else
		return _qInt * M._qInt;
}
BinaryNumber BinaryNumber::operator/(BinaryNumber M)
{
	if (isQFloat)
		return _qFloat / M._qFloat;
	else
		return _qInt / M._qInt;
}
BinaryNumber BinaryNumber::operator%(BinaryNumber M) // phép lấy dư
{
	return _qInt % M._qInt;
}

// Toán tử so sánh và gán
bool BinaryNumber::operator>(BinaryNumber q)
{
	return _qInt > q._qInt;
}
bool BinaryNumber::operator<(BinaryNumber q)
{
	return _qInt < q._qInt;
}
bool BinaryNumber::operator<=(BinaryNumber q)
{
	return _qInt <= q._qInt;
}
bool BinaryNumber::operator>=(BinaryNumber q)
{
	return _qInt >= q._qInt;
}
bool BinaryNumber::operator!=(BinaryNumber q)
{
	return _qInt != q._qInt;
}
bool BinaryNumber::operator==(BinaryNumber q)
{
	return _qInt == q._qInt;
}

// Toán tử NOT AND OR XOR
BinaryNumber& BinaryNumber::operator~()
{
	_qInt = ~_qInt;
	return *this;
}
BinaryNumber BinaryNumber::operator&(const BinaryNumber& q)
{
	return BinaryNumber(_qInt & q._qInt);
}
BinaryNumber BinaryNumber::operator|(const BinaryNumber& q)
{
	return BinaryNumber(_qInt | q._qInt);
}
BinaryNumber BinaryNumber::operator^(const BinaryNumber& q)
{
	return BinaryNumber(_qInt ^ q._qInt);
}

// Toán tử dịch trái, dịch phải, xoay trái, xoay phải
BinaryNumber BinaryNumber::operator<<(unsigned int x)
{
	return BinaryNumber(_qInt << (x));
}
BinaryNumber BinaryNumber::operator>>(unsigned int x)
{
	return BinaryNumber(_qInt >> (x));
}
BinaryNumber& BinaryNumber::rol(unsigned int x) // xoay trái x bit
{
	_qInt.rol(x);
	return *this;
}
BinaryNumber& BinaryNumber::ror(unsigned int x) // xoay phải x bit
{
	_qInt.ror(x);
	return *this;
}

bool BinaryNumber::isZero()
{
	if (isQFloat)
		return _qFloat.CheckZero();
	return _qInt.isZero();
}