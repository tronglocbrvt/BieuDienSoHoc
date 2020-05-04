#include "QInt.h"

int main()
{
	//cout << (7) % -3;
	string a = "-7";
	string b = "3"; 

	QInt res1;
	res1 = res1.fromDecToQInt(a);
	QInt res2;
	res2 = res2.fromDecToQInt(b);
	QInt res3;
	res3 = res2;
	QInt res = res1 % res3;
	//res = res.fromDecToQInt(b);

	//bool check = res1 > res2;
	cout << res.QIntToDecStr() << endl;
	//res1.ror();
	//cout << res1.QIntToDecStr() << endl;

	return 0;
}

