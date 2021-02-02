#pragma once
#include "QInt.h"
#include "BinaryNumber.h"
#include <string>
#include <msclr\marshal_cppstd.h>

ref class CoreCalculator
{
public:
	CoreCalculator();

public:
	static BinaryNumber binaryCalculate(std::string oper, BinaryNumber n1, BinaryNumber n2);
	static BinaryNumber unaryCalculate(std::string oper, BinaryNumber n);

};

