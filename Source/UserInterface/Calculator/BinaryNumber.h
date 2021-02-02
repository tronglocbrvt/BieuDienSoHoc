#pragma once
#include <string>
#include "QInt.h"
#include "QFloat.h"

//Class dùng để lưu cả QInt và QFloat

class BinaryNumber
{
private:
	QInt _qInt;
	QFloat _qFloat;
	int isQFloat;
public:
	BinaryNumber();
	BinaryNumber(QInt a, QFloat b);
	BinaryNumber(QInt a);
	BinaryNumber(QFloat a);

	// Từ string base N trả về BinaryNumber, isQFloat hỏi s là dưới dạng QFloat hay không
	static BinaryNumber fromStringtoBin(std::string s, unsigned short N, bool isQFloat);

	std::string binaryToString(unsigned short baseN);
	// Toán tử + - * / %
	BinaryNumber operator+(BinaryNumber q);
	BinaryNumber operator-(BinaryNumber q);
	BinaryNumber operator*(BinaryNumber M);
	BinaryNumber operator/(BinaryNumber M);
	BinaryNumber operator%(BinaryNumber M);

	// Toán tử so sánh và gán
	bool operator>(BinaryNumber q);
	bool operator<(BinaryNumber q);
	bool operator<=(BinaryNumber q);
	bool operator>=(BinaryNumber q);
	bool operator!=(BinaryNumber q);
	bool operator==(BinaryNumber q);

	// Toán tử NOT AND OR XOR
	BinaryNumber& operator~();
	BinaryNumber operator&(const BinaryNumber& q);
	BinaryNumber operator|(const BinaryNumber& q);
	BinaryNumber operator^(const BinaryNumber& q);

	// Toán tử dịch trái, dịch phải, xoay trái, xoay phải
	BinaryNumber operator<<(unsigned int x);
	BinaryNumber operator>>(unsigned int x);
	BinaryNumber& rol(unsigned int x);
	BinaryNumber& ror(unsigned int x);

	bool isZero();
};

