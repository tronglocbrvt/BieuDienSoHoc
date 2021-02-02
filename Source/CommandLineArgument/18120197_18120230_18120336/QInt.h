#pragma once

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define NUM_BLOCK 4 // s? l??ng block là 4 vì data có 4 ph?n t?
#define NUM_BIT 128 // 128 bit

class QInt
{
private:
	int data[4]; // l?u ki?u QInt 16 bytes d??i d?ng 4 s? nguyên, m?i s? nguyên là 4 bytes. 

public:

	// ============================ KH?I T?O VÀ H?Y ============================
	QInt(); // kh?i t?o m?c ??nh
	QInt(const int& n); // kh?i t?o ki?u QInt t? s? nguyên n
	~QInt();

	// ============================ CÁC HÀM CHUY?N ??I ============================

	// Hàm nh?p t? chu?i
	static QInt fromDecToQInt(string str); // chuy?n chu?i th?p phân sang QInt
	static QInt fromBinToQInt(string str); // chuy?n chu?i nh? phân sang QInt
	static QInt fromHexToQInt(string str); // chuy?n chu?i th?p l?c phân sang QInt
	static QInt fromStringToQInt(string str, unsigned short b); // chuy?n chu?i h? c? s? b sang QInt

	// Hàm xu?t t? QInt ra chu?i
	string QIntToDecStr(); // chuy?n QInt sang chu?i th?p phân
	string QIntToBinStr(); // chuy?n QInt sang chu?i nh? phân
	string QIntToHexStr(); // chuy?n QInt sang chu?i th?p l?c phân
	string QIntToString(unsigned short b); // chuy?n QInt sang chu?i ? h? c? s? b

	// Chuy?n ??i gi?a các c? s?
	static string BaseToBase(string str, unsigned short a, unsigned short b); // chuy?n ??i chu?i t? h? c? s? a sang h? c? s? b (2, 10, 16)

	// Các hàm chuy?n ??i khác
	static QInt toTwoCompliment(QInt q); // chuy?n sang d?ng bù 2
	// ============================ TOÁN T? ============================

	// Toán t? + - * / %
	QInt operator+(const QInt& plus);
	QInt operator-(const QInt& minus);
	QInt operator*(const QInt& multiply);
	QInt operator/(const QInt& divide);
	QInt operator%(const QInt& divide); // phép l?y d?

	// Toán t? so sánh và gán
	bool operator>(const QInt& other);
	bool operator<(const QInt& other);
	bool operator<=(const QInt& other);
	bool operator>=(const QInt& other);
	bool operator!=(const QInt& other);
	bool operator==(const QInt& other);
	QInt& operator=(const QInt& other);

	// Toán t? NOT AND OR XOR
	QInt& operator~();
	QInt operator&(const QInt& q);
	QInt operator|(const QInt& q);
	QInt operator^(const QInt& q);

	// Toán t? d?ch trái, d?ch ph?i, xoay trái, xoay ph?i
	QInt operator<<(unsigned int x);
	QInt operator>>(unsigned int x);
	QInt& rol(unsigned int x); // xoay trái x bit
	QInt& ror(unsigned int x); // xoay ph?i x bit

	// ============================ HÀM PH? TR? ============================
	unsigned short GetBit(unsigned short i); // l?y giá tr? bit ? v? tr? i
	void SetBit(unsigned short i, unsigned short bit); // t?o giá tr? bit t?i v? trí i
	bool isNegative(); // ki?m tra có ph?i s? âm hay không
	bool isZero(); // ki?m tra có b?ng 0 hay không
};

string StrMulti2(string str); // Nhân chu?i d??ng cho 2 = double chu?i
string plusString(string str1, string str2); // C?ng 2 chu?i th?p phân d??ng
string minusString(string str1, string str2); // tr? 2 chu?i th?p phân d??ng
string StrDiv2(string str); // hàm chia chu?i th?p phân d??ng cho 2