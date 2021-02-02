#pragma once

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define NUM_BLOCK 4 // s? l??ng block l� 4 v� data c� 4 ph?n t?
#define NUM_BIT 128 // 128 bit

class QInt
{
private:
	int data[4]; // l?u ki?u QInt 16 bytes d??i d?ng 4 s? nguy�n, m?i s? nguy�n l� 4 bytes. 

public:

	// ============================ KH?I T?O V� H?Y ============================
	QInt(); // kh?i t?o m?c ??nh
	QInt(const int& n); // kh?i t?o ki?u QInt t? s? nguy�n n
	~QInt();

	// ============================ C�C H�M CHUY?N ??I ============================

	// H�m nh?p t? chu?i
	static QInt fromDecToQInt(string str); // chuy?n chu?i th?p ph�n sang QInt
	static QInt fromBinToQInt(string str); // chuy?n chu?i nh? ph�n sang QInt
	static QInt fromHexToQInt(string str); // chuy?n chu?i th?p l?c ph�n sang QInt
	static QInt fromStringToQInt(string str, unsigned short b); // chuy?n chu?i h? c? s? b sang QInt

	// H�m xu?t t? QInt ra chu?i
	string QIntToDecStr(); // chuy?n QInt sang chu?i th?p ph�n
	string QIntToBinStr(); // chuy?n QInt sang chu?i nh? ph�n
	string QIntToHexStr(); // chuy?n QInt sang chu?i th?p l?c ph�n
	string QIntToString(unsigned short b); // chuy?n QInt sang chu?i ? h? c? s? b

	// Chuy?n ??i gi?a c�c c? s?
	static string BaseToBase(string str, unsigned short a, unsigned short b); // chuy?n ??i chu?i t? h? c? s? a sang h? c? s? b (2, 10, 16)

	// C�c h�m chuy?n ??i kh�c
	static QInt toTwoCompliment(QInt q); // chuy?n sang d?ng b� 2
	// ============================ TO�N T? ============================

	// To�n t? + - * / %
	QInt operator+(const QInt& plus);
	QInt operator-(const QInt& minus);
	QInt operator*(const QInt& multiply);
	QInt operator/(const QInt& divide);
	QInt operator%(const QInt& divide); // ph�p l?y d?

	// To�n t? so s�nh v� g�n
	bool operator>(const QInt& other);
	bool operator<(const QInt& other);
	bool operator<=(const QInt& other);
	bool operator>=(const QInt& other);
	bool operator!=(const QInt& other);
	bool operator==(const QInt& other);
	QInt& operator=(const QInt& other);

	// To�n t? NOT AND OR XOR
	QInt& operator~();
	QInt operator&(const QInt& q);
	QInt operator|(const QInt& q);
	QInt operator^(const QInt& q);

	// To�n t? d?ch tr�i, d?ch ph?i, xoay tr�i, xoay ph?i
	QInt operator<<(unsigned int x);
	QInt operator>>(unsigned int x);
	QInt& rol(unsigned int x); // xoay tr�i x bit
	QInt& ror(unsigned int x); // xoay ph?i x bit

	// ============================ H�M PH? TR? ============================
	unsigned short GetBit(unsigned short i); // l?y gi� tr? bit ? v? tr? i
	void SetBit(unsigned short i, unsigned short bit); // t?o gi� tr? bit t?i v? tr� i
	bool isNegative(); // ki?m tra c� ph?i s? �m hay kh�ng
	bool isZero(); // ki?m tra c� b?ng 0 hay kh�ng
};

string StrMulti2(string str); // Nh�n chu?i d??ng cho 2 = double chu?i
string plusString(string str1, string str2); // C?ng 2 chu?i th?p ph�n d??ng
string minusString(string str1, string str2); // tr? 2 chu?i th?p ph�n d??ng
string StrDiv2(string str); // h�m chia chu?i th?p ph�n d??ng cho 2