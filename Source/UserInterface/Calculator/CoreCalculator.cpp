#include "CoreCalculator.h"


CoreCalculator::CoreCalculator()
{
}

BinaryNumber CoreCalculator::binaryCalculate(std::string oper, BinaryNumber n1, BinaryNumber n2)
{
	if (oper == "+")
	{
		return n1 + n2;
	}
	else if (oper == "-")
	{
		return n1 - n2;
	}
	else if (oper == "x")
	{
		return n1 * n2;
	}
	else if (oper == "/" && n2.isZero())
	{
		throw std::invalid_argument("Error!");
	}
	else if (oper == "/")
	{
		return n1 / n2;
	}
	else if (oper == "MOD")
	{
		return n1 % n2;
	}
	else if (oper == "And")
	{
		return n1 & n2;
	}
	else if (oper == "Or")
	{
		return n1 | n2;
	}
	else if (oper == "Xor")
	{
		return n1 ^ n2;
	}
	else if (oper == "Lsh")
	{
		int a = stoi(n2.binaryToString(10));
		return n1 << (a);
	}
	else if (oper == "Rsh")
	{
		int a = stoi(n2.binaryToString(10));
		return n1 >> (a);
	}
	else if (oper == "RoL")
	{
		int a = stoi(n2.binaryToString(10));
		return n1.rol(a);
	}
	else if (oper == "RoR")
	{
		int a = stoi(n2.binaryToString(10));
		return n1.ror(a);
	}
	else
		return n2;
}
BinaryNumber CoreCalculator::unaryCalculate(std::string oper, BinaryNumber n)
{
	if (oper == "+/-")
	{
		QInt sign1(-1);
		QFloat sign2("-1");
		BinaryNumber s(sign1, sign2);
		return n * s;

	}
	else if (oper == "RoL")
	{
		return n.rol(1);
	}
	else if (oper == "RoR")
	{
		return n.ror(1);
	}
	else if (oper == "Not")
	{
		return ~n;
	}
	return n;
}