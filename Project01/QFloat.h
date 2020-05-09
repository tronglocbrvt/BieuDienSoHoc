#pragma once
#define NUM_BLOCK 4 //kich thuoc cua data
#define MAX_LENGTH 128 //kich thuoc toi da cua chuoi bit
#define EXPONENT 15 //kich thuoc phan so mu
#define SIGNIFICAND 112 //kich thuoc phan dinh tri
#define SIGN 1 //kich thuoc phan dau
#define BIAS 16383 //gia tri cua so bias

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "QInt.h"

using namespace std;

class QFloat
{
private:
	int data[4];

public:

	// ====================================== NHÓM HÀM KIỂM TRA ======================================

	// Nhóm hàm nhập
	QFloat fromBinToQFloat(string str); // chuyển từ chuỗi nhị phân sang QFloat
	QFloat fromDecToQFloat(string str); // chuyển từ chuỗi thập phân sang QFloat
	QFloat fromStringToQFloat(string str, unsigned short b); // chuyển chuỗi hệ cơ số b sang QFloat

	// Nhóm hàm xuất
	string QFloatToBinStr();
	string QFloatToDecStr();
	string QFloatToString(unsigned short b); // chuyển QFloat sang chuỗi ở hệ cơ số b

	// chuyển đổi giữa các hệ cơ số
	string BaseToBase(string str, unsigned short a, unsigned short b); // chuyển đổi chuỗi từ hệ cơ số a sang hệ cơ số b (2, 10)

	//void StringBinToQFloat(string s); //Chuyen chuoi nhi phan sang Qfloat
	//QFloat BinToDec(bool *bit); //Chuyen so QFloat nhi phan sang thap phan
	//bool* DecToBin(QFloat x); //Chuyen so QFloat thap phan sang nhi phan

	QFloat operator+ (const QFloat& plus); //Toan tu +
	//QFloat operator -( QFloat &minus); //Toan tu -
	//QFloat operator *( QFloat &multiply); //Toan tu *
	//QFloat operator /( QFloat &divide); //Toan tu /

	QFloat& operator=(const QFloat& q); //Toán tử gán = 

	QFloat();
	QFloat(string str);
	~QFloat();
	// ====================================== NHÓM HÀM KIỂM TRA ======================================
	
	bool CheckZero(); // Kiểm tra có phải là 0 hay không
	bool CheckDenormalized() ; // Kiểm tra dạng số không chuẩn
	bool CheckNaN(); // Kiểm tra có phải là dạng NaN không
	bool CheckInf(); // Kiểm tra có phải là dạng Infinity không

	// ====================================== GET,SET BIT VÀ CÁC HÀM HỖ TRỢ ======================================
	void SetBit(int i, int bit); //Set bit tại vị trí i
	int GetBit(int i) ; //Lấy bit ở vị trí i
	string plusStringFloat(string str1, string str2); // cộng chuỗi thập phân
	string IntToBin(string str); // chuyển số nguyên sang nhị phân
	string BinToDec(string str); // chuyển số nhị phân sang thập phân
	string FracDiv2(string str); // chia chuỗi nhị phân cho 2
	void roundingFrac(string a, string& fracPartBit); // Làm tròn phần thập phân
	bool SignificandIsZero(string str, int intPart); // kiểm tra phần trị có bằng 0 hay không
	string addBitString(string str1, string str2, int& carry); // cộng 2 dãy bit
	string subBitString(string str1, string str2, int& carry); // trừ 2 dãy bit
	string addSigned(string str1, string str2, QFloat x, QFloat y, int& carry);

//	int GetSign() ; //Lay dau cua QFloat
//	int SoSanhBit(bool bitX[], int lenX, bool bitY[], int lenY) ; //So sanh 2 day bit
//	int TruBit(bool bitX[], int lenX, bool bitY[], int lenY, bool bitZ[], int lenZ) ; //Tru bit: X - Y = Z
//	void SaveSign(int dau) ; //Luu dau cua QFloat
//	int CalExponent() ; //Tinh gia tri phan mu
//	void SaveExponent(int exponent) ; //Luu phan mu
//	void SaveSignificand(bool BitTri[]); //Luu phan tri
//	
//	int GetIntPart() ; //Lay gia tri phan nguyen cua QFloat
//	void ShiftRSignificand(int numBit, int &intPart) ; //Shift Right cac bit phan tri
//	void ShiftLSignificand(int numBit, int &intPart) ; //Shift Left cac bit phan tri
//	bool CheckSignificandZero(int intPart); //Kiem tra tat ca cac bit cua phan tri co = 0 hay khong
//	void ChuyenPhanTriThanhBit(bool bit[]) ; //Lay phan tri va chuyen thanh day bit
//	void CongPhanTriDuong(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) ; //Cong hai phan tri duong X + Y = Z
//	void TruPhanTriDuong(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) ; //Tru hai phan tri duong X - Y = Z
//	void CongPhanTriCoDau(QFloat X, int intX, QFloat Y, int intY, QFloat &Z, int &intZ) ; //Cong hai phan tri co dau X + Y = Z
//	void NhanPhanTri(QFloat X, QFloat Y, bool bit[], int n) ; //Nhan hai phan tri X * Y = bit (luu vao bit)
//	int LamTronNhiPhan(bool bit[]); //Lam tron so nhi phan (0.5->1, 1.5->2)
//	int GetFirstBit1(bool bit[], int n) ; //Lay vi tri bit dau tien = 1 tu trai sang, neu khong co tra ve n
//
//public:
//	QFloat GetZero(); //Lay so 0
//	QFloat GetInf(); //Lay so vo cung
//	QFloat GetNaN(); //Lay so NaN
};

