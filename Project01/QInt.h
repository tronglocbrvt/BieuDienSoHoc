#pragma once

#include <iostream>
#include <string>
#include <map>
using namespace std;

#define NUM_BLOCK 4 // số lượng block là 4 vì data có 4 phần tử
#define NUM_BIT 128 // 128 bit
class QInt
{
private: 
	int data[4]; // lưu kiểu QInt 16 bytes dưới dạng 4 số nguyên, mỗi số nguyên là 4 bytes. 

public:

	// ============================ KHỞI TẠO VÀ HỦY ============================
	QInt(); // khởi tạo mặc định
	QInt(const int& n); // khởi tạo kiểu QInt từ số nguyên n
	~QInt();

	// ============================ CÁC HÀM CHUYỂN ĐỔI ============================
	
	// Hàm nhập từ chuỗi
	QInt fromDecToQInt(string str); // chuyển chuỗi thập phân sang QInt
	QInt fromBinToQInt(string str); // chuyển chuỗi nhị phân sang QInt
	QInt fromHexToQInt(string str); // chuyển chuỗi thập lục phân sang QInt
	QInt fromStringToQInt(string str, unsigned short b); // chuyển chuỗi hệ cơ số b sang QInt

	// Hàm xuất từ QInt ra chuỗi
	string QIntToDecStr(); // chuyển QInt sang chuỗi thập phân
	string QIntToBinStr(); // chuyển QInt sang chuỗi nhị phân
	string QIntToHexStr(); // chuyển QInt sang chuỗi thập lục phân
	string QIntToString(unsigned short b); // chuyển QInt sang chuỗi ở hệ cơ số b

	// Chuyển đổi giữa các cơ số
	string BaseToBase(string str, unsigned short a, unsigned short b); // chuyển đổi chuỗi từ hệ cơ số a sang hệ cơ số b (2, 10, 16)

	// Các hàm chuyển đổi khác
	QInt toTwoCompliment(QInt q); // chuyển sang dạng bù 2
	// ============================ TOÁN TỬ ============================
	
	// Toán tử + - * / %
	QInt operator+(QInt q);
	QInt operator-(QInt q);
	QInt operator*(QInt M);
	QInt operator/(QInt M);
	QInt operator%(QInt M); // phép lấy dư

	// Toán tử so sánh và gán
	bool operator>(QInt q);
	bool operator<(QInt q);
	bool operator<=(QInt q);
	bool operator>=(QInt q); 
	bool operator!=(QInt q);
	bool operator==(QInt q);
	QInt& operator=(const QInt& q);

	// Toán tử NOT AND OR XOR
	QInt& operator~();
	QInt operator&(const QInt& q);
	QInt operator|(const QInt& q);
	QInt operator^(const QInt& q);

	// Toán tử dịch trái, dịch phải, xoay trái, xoay phải
	QInt operator<<(unsigned int x);
	QInt operator>>(unsigned int x);
	QInt& rol(unsigned int x); // xoay trái x bit
	QInt& ror(unsigned int x); // xoay phải x bit

	// ============================ HÀM PHỤ TRỢ ============================
	unsigned short GetBit(unsigned short i); // lấy giá trị bit ở vị trị i
	void SetBit(unsigned short i, unsigned short bit); // tạo giá trị bit tại vị trí i

	string StrMulti2(string str); // Nhân chuỗi dương cho 2 = double chuỗi
	string plusString(string str1, string str2); // Cộng 2 chuỗi thập phân dương
	string minusString(string str1, string str2); // trừ 2 chuỗi thập phân dương
	string StrDiv2(string str); // hàm chia chuỗi thập phân dương cho 2
	bool isNegative(); // kiểm tra có phải số âm hay không
	bool isZero(); // kiểm tra có bằng 0 hay không
};

