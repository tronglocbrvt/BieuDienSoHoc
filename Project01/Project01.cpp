#include "QInt.h"
#include <fstream>

int main(int argc, char *argv[])
{
	int type = 1;

	if (argc == 4) // Tên file thực thi, file input, file ouput và type (QInt / QFloat)
	{
		type = argv[3][0] - '0';
	}

	ifstream input("input_int.txt");
	ofstream output("output.txt", ios::out);

	if (input.is_open() == 0) // kiểm tra mở file input
	{
		return 0;
	}

	if (type == 1) //  số nguyên QInt
	{
		while (!input.eof())
		{
			string baseStr; // đọc cơ số làm việc CHÍNH
			getline(input, baseStr, ' '); // đọc đến dấu cách
			
			if (baseStr == "")
			{
				return 0;
			}

			int base = stoi(baseStr); //Lưu hệ cơ số làm việc CHÍNH
			string tmpStr; // Lưu chuỗi tạm
			getline(input, tmpStr, ' ');//Đọc chuỗi cho tới dấu cách
			
			if ((tmpStr == "10") || (tmpStr == "16") || (tmpStr == "2") || (tmpStr == "~") || (tmpStr == "ror") || tmpStr == ("rol")) //Nhận diện cơ số hoặc thao tác với toán tử 1 ngôi
			{
				if (tmpStr == "10" || tmpStr == "16" || tmpStr == "2") //Phát hiện chuyển đổi cơ số
				{
					int tmp = stoi(tmpStr); // hệ cơ số cần đổi

					string str;
					getline(input, str); //Get chuỗi số cần chuyển đổi
					
					QInt res;

					output << res.BaseToBase(str, base, tmp) << endl;

				}
				else //Phát hiện các toán tử 1 ngôi còn lại
				{
					string str;
					getline(input, str); //Get chuỗi số cần chuyển đổi
					
					QInt res;
					res = res.fromStringToQInt(str, base);

					if (tmpStr == "~")
					{
						output << (~res).QIntToString(base) << endl;
					}
					if (tmpStr == "ror")
					{
						output << (res.ror()).QIntToString(base) << endl;
					}
					if (tmpStr == "rol")
					{
						output << (res.rol()).QIntToString(base) << endl;
					}
				}

			}
			else //Các toán tử 2 ngôi gồm +, -, *, /, %, &, |, ^, >>, <<
				// chuỗi tmpStr lúc này sẽ là số hạng thứ nhất
			{
				QInt firstNum;
				firstNum = firstNum.fromStringToQInt(tmpStr, base);

				getline(input, tmpStr, ' '); //Đọc toán tử

				string second;
				getline(input, second);//Đọc số hạng thứ 2
				QInt secondNum;
				secondNum = secondNum.fromStringToQInt(second, base);

				QInt res; // lưu kết quả

				if (tmpStr == "+")
				{
					res = firstNum + secondNum;
				}
				else if (tmpStr == "-")
				{
					res = firstNum - secondNum;
				}
				else if (tmpStr == "*")
				{
					res = firstNum * secondNum;
				}
				else if (tmpStr == "/")
				{
					res = firstNum / secondNum;
				}
				else if (tmpStr == "%")
				{
					res = firstNum % secondNum;
				}
				else if (tmpStr == "&")
				{
					res = firstNum & secondNum;
				}
				else if (tmpStr == "|")
				{
					res = firstNum | secondNum;
				}
				else if (tmpStr == "^")
				{
					res = firstNum ^ secondNum;
				}
				else if (tmpStr == "<<")
				{
					res = firstNum << stoi(second);
				}
				else if (tmpStr == ">>")
				{
					res = firstNum >> stoi(second);
				}
				
				output << res.QIntToString(base) << endl;
			}
		}
	}

	input.close();
	output.close();
	system("cls");

	return 0;
}

