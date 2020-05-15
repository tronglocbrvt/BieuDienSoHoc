#pragma once
#define NUM_BLOCK 4 //kich thuoc cua data
#define MAX_LENGTH 128 //kich thuoc toi da cua chuoi bit
#define EXPONENT 15 //kich thuoc phan so mu
#define SIGNIFICAND 112 //kich thuoc phan dinh tri
#define BIAS 16383 //gia tri cua so bias

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "QInt.h"
#include <bitset>

using namespace std;

class QFloat
{
private:
	int data[4];

public:

	// ====================================== NHÓM HÀM CHUYỂN ĐỔI ======================================

	// Nhóm hàm nhập
	static QFloat fromBinToQFloat(string str); // chuyển từ chuỗi nhị phân sang QFloat
	static QFloat fromDecToQFloat(string str); // chuyển từ chuỗi thập phân sang QFloat
	static QFloat fromStringToQFloat(string str, unsigned short b); // chuyển chuỗi hệ cơ số b sang QFloat

	// Nhóm hàm xuất
	string QFloatToBinStr() const;
	string QFloatToDecStr();
	string QFloatToString(unsigned short b); // chuyển QFloat sang chuỗi ở hệ cơ số b

	// chuyển đổi giữa các hệ cơ số
	string BaseToBase(string str, unsigned short a, unsigned short b); // chuyển đổi chuỗi từ hệ cơ số a sang hệ cơ số b (2, 10)

	// ====================================== TOÁN TỬ ======================================

	QFloat operator+ (const QFloat& plus); //Toan tu +
	QFloat operator- (const QFloat& minus); //Toan tu -
	QFloat operator* (const QFloat& multiply); //Toan tu *
	QFloat operator/ (const QFloat &divide); //Toan tu /

	QFloat& operator=(const QFloat& q); //Toán tử gán = 

	// ====================================== NHÓM HÀM KHỞi TẠO VÀ HỦY ======================================

	QFloat();
	QFloat(string str);
	~QFloat();
	// ====================================== NHÓM HÀM KIỂM TRA ======================================

	bool CheckZero() const; // Kiểm tra có phải là 0 hay không
	bool CheckDenormalized() const; // Kiểm tra dạng số không chuẩn
	bool CheckNaN() const; // Kiểm tra có phải là dạng NaN không
	bool CheckInf() const; // Kiểm tra có phải là dạng Infinity không

	// ====================================== GET, SET BIT VÀ CÁC HÀM HỖ TRỢ ======================================
	void SetBit(int i, int bit); //Set bit tại vị trí i
	int GetBit(int i) const; //Lấy bit ở vị trí i
	int exponentValue(); // lấy giá trị phần mũ
	static string plusStringFloat(string str1, string str2); // cộng chuỗi thập phân
	static string IntToBin(string str); // chuyển số nguyên sang nhị phân
	static string BinToDec(string str); // chuyển số nhị phân sang thập phân
	string FracDiv2(string str); // chia chuỗi nhị phân cho 2
	static void roundingFrac(string a, string& fracPartBit); // Làm tròn các bit phần thập phân (làm tròn bit)
	bool SignificandIsZero(string str, int intPart); // kiểm tra phần trị có bằng 0 hay không
	QInt addSigned(QInt x, QInt y, bool& sign, bool xSign, bool ySign); // cộng có dấu 2 số QInt
};

int countSignificantNumber(string& n);
string BinaryAddition(const string& a, const string& b);
string BinarySubSubtraction(const string& a, const string& b);
string multiplyBinary(string& a, string& b);
bool isStringZero(const string& s);
bool isStringBigger(const string& s1, const string& s2); // a > b, length equal
string divideBinary(string& a, string& b, int& decimalPoint);
