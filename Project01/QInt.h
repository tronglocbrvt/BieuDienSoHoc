#pragma once

#include <iostream>
#include <string>
using namespace std;

#define NUM_BLOCK 4 // số lượng block là 4 vì data có 4 phần tử
class QInt
{
private: 
	int data[4]; // lưu kiểu QInt 16 bytes dưới dạng 4 số nguyên, mỗi số nguyên là 4 bytes. 

public:
	QInt();
	QInt(const int& n);
	~QInt();

	// ============================ CÁC HÀM CHUYỂN ĐỔI ============================
	
	// Hàm nhập từ chuỗi
	QInt fromDecToQInt(string str); // chuyển chuỗi thập phân sang QInt
	QInt fromBinToQInt(string str); // chuyển chuỗi nhị phân sang QInt
	/*QInt fromHexToQInt(string str); // chuyển chuỗi thập lục phân sang QInt
	QInt fromStringToQInt(string str, unsigned short b); // chuyển chuỗi hệ cơ số b sang QInt

	// Hàm xuất từ QInt ra chuỗi
	string QIntToDecStr(); // chuyển QInt sang chuỗi thập phân
	string QIntToBinStr(); // chuyển QInt sang chuỗi nhị phân
	string QIntToHexStr(); // chuyển QInt sang chuỗi thập lục phân
	string QIntToString(unsigned short b); // chuyển QInt sang chuỗi ở hệ cơ số b */

	// Các hàm chuyển đổi khác
	QInt toTwoCompliment(QInt q); // chuyển sang dạng bù 2
	// ============================ TOÁN TỬ ============================
	
	// Toán tử + - * /
	//QInt operator+(const QInt& q);
	/* QInt operator-(const QInt& q);
	QInt operator*(const QInt& M);
	QInt operator/(const QInt& M);

	// Toán tử so sánh và gán
	bool operator>(const QInt& q);
	bool operator<(const QInt& q);
	bool operator==(const QInt& q);
	bool operator<=(const QInt& q);
	bool operator>=(const QInt& q); */
	QInt& operator=(const QInt& q);

	// Toán tử NOT AND OR XOR
	QInt operator~();
	/*QInt operator&(const QInt& q);
	QInt operator|(const QInt& q);
	QInt operator^(const QInt& q);

	// Toán tử dịch trái, dịch phải, xoay trái, xoay phải
	QInt operator<<(int x);
	QInt operator>>(int x);
	QInt& rol();
	QInt& ror(); */

	// ============================ HÀM PHỤ TRỢ ============================
	bool GetBit(unsigned short i); // lấy giá trị bit ở vị trị i
	void SetBit(unsigned short i, unsigned short bit); // tạo giá trị bit tại vị trí i

	string StrDiv2(string str); // hàm chia chuỗi thập phân dương cho 2
	bool isNegative(); // kiểm tra có phải số âm hay không
	bool isZero(); // kiểm tra có bằng 0 hay không
};

