#include "QInt.h"

int main()
{
	//int x = 2147483649;
	//cout << x;
	string a = "-17";
	string b = "-91"; 

	QInt res1;
	res1 = res1.fromDecToQInt(a);
	QInt res2;
	res2 = res2.fromDecToQInt(b);
	QInt res3;
	res3 = res2;
	QInt res = res1 + res3;
	//res = res.fromDecToQInt(b);

	//bool check = res1 > res2;
	//cout << res1.QIntToBinStr() << endl;
	res1 = res1 >> 2;
	cout << res1.QIntToDecStr() << endl;

	return 0;
}

