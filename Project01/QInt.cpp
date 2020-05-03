#include "QInt.h"

// hàm khởi tạo kiểu QInt, khởi tạo 4 phần tử của data đều bằng 0 -> QInt gồm 128 bit 0
QInt::QInt()
{
	for (int i = 0; i < NUM_BLOCK; i++)
		data[i] = 0;
}

// hàm khởi tạo kiểu QInt từ số nguyên n -> chuyển n sang QInt và sử dụng operator = 
QInt::QInt(const int & n)
{
	*this = (fromDecToQInt(to_string(n)));
}

QInt::~QInt()
{
}

// chuyển chuỗi thập phân sang QInt
QInt QInt::fromDecToQInt(string str)
{
	QInt res;

	bool sign; // lưu dấu

	if (str[0] == '-') // số âm
		sign = 1;
	else
		sign = 0;

	int i = 0; // bắt đầu set các bit từ data[0]
	while (str != "0" && str != "")
	{
		if (i >= 128)
		{
			cout << "Vuot qua 128 bit" << endl;
			return res;
		}

		unsigned short bit = (str[str.length() - 1] - 48) % 2; // chia 2 lấy phần dư
		res.SetBit(i, bit); // set bit tại vị trí i
		str = StrDiv2(str); // chia chuỗi cho 2
		i++; // tăng i để set các bit tiếp theo
	}

	if (sign == 1)
		res = toTwoCompliment(res);

	return res;
}

// chuyển chuỗi nhị phân sang QInt
QInt QInt::fromBinToQInt(string str)
{
	QInt res;

	return res;
}

// lấy giá trị bit ở vị trị i
bool QInt::GetBit(unsigned short i) // lấy giá trị ở bit thứ i
{
	unsigned short block = i / 32; // Block data cần chọn
	unsigned short pos = i % 32; // Vị trí cần lấy trong block data

	if (block >= NUM_BLOCK || block < 0)
		return 0;

	return (data[block] & (1 << pos)) != 0; // true = bit 1; false = bit 0
}

// tạo giá trị bit tại vị trí i
void QInt::SetBit(unsigned short i, unsigned short bit)
{
	unsigned short block = i / 32; // Xác định Block data
	unsigned short pos = i % 32; // vi trí cần set giá trị bit

	if (block >= NUM_BLOCK || block < 0)
		return;

	if (bit == 1) // nếu là bit 1
	{
		data[block] = data[block] | (1 << i); // AND với 1 ra 1
	}
	else { // bit 0
		data[block] = data[block] & (~(1 << i)); // AND với 0 ra 0
	}
}

// hàm chia chuỗi thập phân dương cho 2
string QInt::StrDiv2(string str)
{
	string res;

	int mod = 0; // số dư bằng 0

	for (int i = 0; i < str.size(); i++)
	{
		mod = mod * 10 + (str[i] - 48); // vì chia cho 2 nên chỉ cần xét đến TH 2 chữ số, 48 là ASCII của '0'

		if ((mod >= 2 && i == 0) || i > 0) // khi chia cho 2 chỉ xét trường hợp số đầu tiên, những số sau nếu nhỏ
										  // hơn 2 vẫn chia bình thường (thương tại lần chia đó = 0)
			res.push_back((mod / 2) + '0');

		mod %= 2; // cập nhật lại số dư của lần chia đó
	}

	return res;
}

// kiểm tra có phải số âm hay không
bool QInt::isNegative()
{
	return data[NUM_BLOCK - 1] & 1; // bit đầu của QInt (bit dấu) tức là bit đầu của data[3] (lưu ý bit đầu là bit bên phải cùng vì 
						// bit được đánh số thứ tự từ phải qua; AND với 1 ta lấy ra được giá trị của bit đó.
}

// kiểm tra có bằng 0 hay không
bool QInt::isZero()
{
	for (int i = 0; i < NUM_BLOCK; i++)
		if (data[i] != 0) // nếu phát hiện khác 0 -> return false (nghĩa là QInt khác 0)
			return false;
	return true;
}

// chuyển sang bù 2
QInt QInt::toTwoCompliment(QInt q)
{
	//return (~q + QInt(1)); // đổi dấu rồi cộng 1
	return ~q;
}

//QInt QInt::operator+(const QInt & q)
//{
//	QInt Result = *this;
//	QInt Carry;
//
//	while (!(q.isZero()))
//	{
//		//Carry là những bit cùng là 1 giữa 2 số.
//		Carry = Result & q;
//
//		//Tổng các bit khác nhau của hai số (0 + 1 = 1).
//		Result = Result ^ q;
//
//		//Đưa các bit cùng là 1 bên 1 bit để tiếp tục phép cộng cần thực hiện.
//		QInt = Carry << 1;
//	}
//
//	return Result;
//}

QInt & QInt::operator=(const QInt& q)
{
	if (this != &q)
	{
		for (int i = 0; i < NUM_BLOCK; i++)
		{
			this->data[i] = q.data[i];
		}
	}

	return *this;
}

QInt QInt::operator~()
{
	for (int i = 0; i < NUM_BLOCK; i++)
	{
		this->data[i] = ~this->data[i];
	}

	return *this;
}
