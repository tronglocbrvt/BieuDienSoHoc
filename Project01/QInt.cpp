#include "QInt.h"
// hàm khởi tạo kiểu QInt, khởi tạo 4 phần tử của data đều bằng 0 -> QInt gồm 128 bit 0
QInt::QInt()
{
	for (int i = 0; i < 4; i++)
		data[i] = 0;
}

QInt::~QInt()
{
}
// lấy giá trị bit ở vị trị i
bool QInt::GetBit(unsigned short i) // lấy giá trị ở bit thứ i
{
	unsigned short block = i / 32; // Block data cần chọn
	unsigned short pos = i % 32; // Vị trí cần lấy trong block data
	return (data[block] & (1 << pos)) != 0; // true = bit 1; false = bit 0
}

// tạo giá trị bit tại vị trí i
void QInt::SetBit(unsigned short i, bool bit)
{
	unsigned short block = i / 32; // Xác định Block data
	unsigned short pos = i % 32; // vi trí cần set giá trị bit
	if (bit == true) // nếu là bit 1
	{
		data[block] = data[block] | (1 << i); // AND với 1 ra 1
	}
	else { // bit 0
		data[block] = data[block] & (~(1 << i)); // AND với 0 ra 0
	}
}
