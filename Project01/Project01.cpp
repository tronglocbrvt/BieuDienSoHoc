#include "QInt.h"

int main()
{
	string a = "152"; 

	string b = "5673";
	QInt res;
	//res = res.fromDecToQInt(a);

	cout << res.plusString(a, b) << endl;

	return 0;
}

