#pragma once

#include <iostream>
#include <string>
using namespace std;

class QInt
{
private: 
	int data[4]; // lưu kiểu QInt 16 bytes dưới dạng 4 số nguyên, mỗi số nguyên là 4 bytes. 

public:
	QInt();
	~QInt();

	// ============================ CÁC HÀM CHUYỂN ĐỔI ============================
	QInt toTwoCompliment(); // chuyển sang dạng bù 2
	QInt fromDec(string str); // chuyển chuỗi thập phân sang QInt
	QInt fromBin(string);
	QInt fromHex(string);
	QInt fromString(string, string);


	// ============================ TOÁN TỬ ============================
	
	// Toán tử + - * /
	QInt operator+(const QInt& q);
	QInt operator-(const QInt& q);
	QInt operator*(const QInt& M);
	QInt operator/(const QInt& M);

	// Toán tử so sánh và gán
	bool operator>(const QInt& q);
	bool operator<(const QInt& q);
	bool operator==(const QInt& q);
	bool operator<=(const QInt& q);
	bool operator>=(const QInt& q);
	QInt& operator=(const string& input);

	// Toán tử AND OR XOR NOT
	QInt operator~() const;
	QInt operator&(const QInt& q);
	QInt operator|(const QInt& q);
	QInt operator^(const QInt& q);

	// Toán tử dịch trái, dịch phải, xoay trái, xoay phải
	QInt operator<<(int x);
	QInt operator>>(int x);
	QInt& rol();
	QInt& ror();

	// ============================ HÀM PHỤ TRỢ ============================
	bool GetBit(QInt q, unsigned short i); // lấy giá trị bit ở vị trị i
	void SetBit(QInt& q, unsigned short i, bool bit); // tạo giá trị bit tại vị trí i

	string StrDiv2(string str); // hàm chia chuỗi thập phân cho 2
	bool isNegative(); // kiểm tra có phải số âm hay không
	bool isZero(); // kiểm tra có bằng 0 hay không
};

