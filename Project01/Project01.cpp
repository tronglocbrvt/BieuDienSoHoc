#include "QInt.h"
#include "QFloat.h"
#include <fstream>

int main(int argc, char *argv[])
{
	//int type = 1;

	//if (argc == 4) // Tên file thực thi, file input, file ouput và type (QInt / QFloat)
	//{
	//	type = argv[3][0] - '0';
	//}

	//ifstream input("QInt_input.txt"); // đây là định dạng để debug, tham số dòng lệnh thay tham số là argv[1]
	//ofstream output("QInt.output.txt", ios::out); // đây là định dạng để debug, tham số dòng lệnh thay tham số là argv[2]

	//if (input.is_open() == 0) // kiểm tra mở file input
	//{
	//	return 0;
	//}

	//if (type == 1) //  số nguyên QInt
	//{
	//	while (!input.eof())
	//	{
	//		string baseStr; // đọc cơ số làm việc CHÍNH
	//		getline(input, baseStr, ' '); // đọc đến dấu cách
	//		
	//		if (baseStr == "")
	//		{
	//			return 0;
	//		}

	//		int base = stoi(baseStr); //Lưu hệ cơ số làm việc CHÍNH
	//		string tmpStr; // Lưu chuỗi tạm
	//		getline(input, tmpStr, ' ');//Đọc chuỗi cho tới dấu cách
	//		
	//		if ((tmpStr == "10") || (tmpStr == "16") || (tmpStr == "2") || (tmpStr == "~")) //Nhận diện cơ số hoặc thao tác với toán tử 1 ngôi
	//		{
	//			if (tmpStr == "10" || tmpStr == "16" || tmpStr == "2") //Phát hiện chuyển đổi cơ số
	//			{
	//				int tmp = stoi(tmpStr); // hệ cơ số cần đổi

	//				string str;
	//				getline(input, str); //Get chuỗi số cần chuyển đổi
	//				
	//				QInt res;

	//				output << res.BaseToBase(str, base, tmp) << endl;

	//			}
	//			else //Phát hiện các toán tử 1 ngôi còn lại -> phép ~
	//			{
	//				string str;
	//				getline(input, str); //Get chuỗi số cần chuyển đổi
	//				
	//				QInt res;
	//				res = res.fromStringToQInt(str, base);

	//				output << (~res).QIntToString(base) << endl;
	//				
	//			}

	//		}
	//		else //Các toán tử 2 ngôi gồm +, -, *, /, %, &, |, ^, >>, << và các phép so sánh > < >= <= == != và phép ror, rol
	//			// chuỗi tmpStr lúc này sẽ là số hạng thứ nhất
	//		{
	//			QInt firstNum;
	//			firstNum = firstNum.fromStringToQInt(tmpStr, base);

	//			getline(input, tmpStr, ' '); //Đọc toán tử

	//			string second;
	//			getline(input, second);//Đọc số hạng thứ 2
	//			QInt secondNum;
	//			secondNum = secondNum.fromStringToQInt(second, base);

	//			QInt res; // lưu kết quả
	//			bool  compare;

	//			if (tmpStr == "+")
	//			{
	//				res = firstNum + secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "-")
	//			{
	//				res = firstNum - secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "*")
	//			{
	//				res = firstNum * secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "/")
	//			{
	//				if (secondNum.isZero())
	//					output << "Khong chia duoc cho 0" << endl;
	//				else
	//				{
	//					res = firstNum / secondNum;
	//					output << res.QIntToString(base) << endl;
	//				}
	//			}
	//			else if (tmpStr == "%")
	//			{
	//				res = firstNum % secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "&")
	//			{
	//				res = firstNum & secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "|")
	//			{
	//				res = firstNum | secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "^")
	//			{
	//				res = firstNum ^ secondNum;
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "<<")
	//			{
	//				res = firstNum << stoi(second);
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == ">>")
	//			{
	//				res = firstNum >> stoi(second);
	//				output << res.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == ">")
	//			{
	//				compare = firstNum > secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == "<")
	//			{
	//				compare = firstNum < secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == ">=")
	//			{
	//				compare = firstNum >= secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == "<=")
	//			{
	//				compare = firstNum <= secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == "==")
	//			{
	//				compare = firstNum == secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == "!=")
	//			{
	//				compare = firstNum != secondNum;
	//				output << ((compare == 1) ? "True" : "False") << endl;
	//			}
	//			else if (tmpStr == "rol")
	//			{
	//				firstNum.rol(stoi(second));
	//				output << firstNum.QIntToString(base) << endl;
	//			}
	//			else if (tmpStr == "ror")
	//			{
	//				firstNum.ror(stoi(second));
	//				output << firstNum.QIntToString(base) << endl;
	//			}
	//		}
	//	}
	//}

	//input.close();
	//output.close();

	string a = "34565";
	string b = "00000000000000000111010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	QFloat res, res2;

	//res = res.fromDecToQFloat(a);
	res2 = res2.fromBinToQFloat(b);

	string res3 = res2.QFloatToDecStr();

	cout << res3 << endl;

	system("pause");

	system("cls");

	return 0;
}

