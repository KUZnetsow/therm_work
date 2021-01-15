#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "Vector.h"
#include "Stack.h"

class PrefixCalc
{
private:
	std::string sourceExp;
	Vector<std::string> vec = Vector<std::string>();
	Vector<std::string> prefixFormExpVec = Vector<std::string>();

	void split();

	bool isBinaryOperator(char ch);

	bool isBinaryOperator(std::string ch);

	bool isUnaryOperator(std::string el);

	bool isNumber(std::string el);

	double parseDouble(std::string number);

	std::string symbolToString(char ch);

	int binOpsPriority(std::string str);

	double doOperator(double a, std::string op);

	double doOperator(double a, double b, std::string op);

public:
	PrefixCalc(std::string sourceExp);

	std::string prefixToString();

	Vector<std::string> toPrefixForm();

	double calculate();
};

