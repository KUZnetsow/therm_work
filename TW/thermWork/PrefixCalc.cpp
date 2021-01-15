#include "PrefixCalc.h"

void PrefixCalc::split() {								//split inputed string with expression 
	std::string buffer = "";
	for (int i = 0; i < sourceExp.length(); i++)
	{
		if (isdigit(sourceExp[i])) {                    // if meet digit add to buffer
			if (buffer == "" || buffer[buffer.length() - 1] == '.' 
				|| isdigit(buffer[buffer.length() - 1])) {
				buffer += sourceExp[i];
			}
			else {
				throw std::runtime_error("Can't be digit on possition" + std::to_string(i));
			}
		}
		else if (sourceExp[i] == '.') {					//if meet dot add to buffer and check valid of buffer
			if (buffer.length() > 0 && std::isdigit(buffer[buffer.length() - 1])
				&& std::count(buffer.begin(), buffer.end(), '.') < 1) {
				buffer += '.';
			}
			else {
				throw std::runtime_error("Can't be dot on possition" + std::to_string(i));
			}
		}
		else if (isalpha(sourceExp[i])) {				//if meet alpha add to buffer and check it
			if (buffer.length() == 0 || isalpha(buffer[buffer.length() - 1])) {
				buffer += sourceExp[i];
			}
			else {
				throw std::runtime_error("Can't be alpha symbol on possition " + std::to_string(i));
			}
		}
		else if (isBinaryOperator(sourceExp[i])) {		//if meet binary operator 
			if (isNumber(buffer)) {                     //check if in buffer is number add it to result vector and clear
				vec.push_back(buffer);
				buffer = "";
				vec.push_back(symbolToString(sourceExp[i]));
			}											//if met symbol determine if it unary operaotor 
			else if (sourceExp[i] == '-' && (i == 0 || sourceExp[i - 1] == '(')) {
				vec.push_back("--");
			}
			else {                                     
				if (sourceExp[i - 1] == ')') {             //binary operator can be afer number and close bracket
					vec.push_back(symbolToString(sourceExp[i]));
				}
				else {
					throw std::runtime_error("Symbol on index: " + std::to_string(i - 1) + "can't be before binary operator");
				}
			}
		}
		 
		else if (sourceExp[i] == '(') {					//if met open bracket
			if (isNumber(buffer)) {                     //no numbers before 
				throw std::runtime_error("Can't be number before open bracket at index: " + std::to_string(i));
			}
			if (buffer.length() > 0) {                  //before can only be operators
				if (isUnaryOperator(buffer)) {
					vec.push_back(buffer);
				}
				else {
					throw std::runtime_error("No such operator: " + std::to_string(i - buffer.length()));
				}
			}
			buffer = "";
			vec.push_back("(");
		}

		else if (sourceExp[i] == ')') {                 //before close bracket can be only numbers
			if (!isNumber(buffer) && sourceExp[i - 1] != ')') {
				throw std::runtime_error("Can't be operators before close bracket at index: " + std::to_string(i));
			}
			if (buffer.length() > 0) {
				vec.push_back(buffer);
			}
			buffer = "";
			vec.push_back(")");
		}
	}
	//add last element of expresssion
	if (buffer.length() > 0) {
		if (isUnaryOperator(buffer) || isNumber(buffer) || isBinaryOperator(buffer)) {                          //add element at 
			vec.push_back(buffer);
		}
		else {
			throw std::runtime_error("Error with last element of express");
		}
	}
}

bool PrefixCalc::isBinaryOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
		return true;
	}
	else return false;
}

bool PrefixCalc::isBinaryOperator(std::string ch) {
	if (ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "^") {
		return true;
	}
	else return false;
}
bool PrefixCalc::isUnaryOperator(std::string el) {
	if (el == "sin" || el == "cos" || el == "tg" ||
		el == "ctg" || el == "arccos" || el == "arcsin" ||
		el == "arctg" || el == "arcctg" ||
		el == "sqrt" || el == "ln" || el == "log" || el == "--") {
		return true;
	}
	return false;
}

bool PrefixCalc::isNumber(std::string el) {
	if (el == "pi" || el == "e") {  //strings of constants is numbers too
		return true;
	}
	try
	{
		double value = std::stod(el);
		return true;
	}
	catch (std::exception& e)
	{
		return false;
	}
}

double PrefixCalc::parseDouble(std::string number) {  //parse numbers and constants
	if (number == "e") {
		return 2.71828182845904523536;
	}
	else if (number == "pi") {
		return 3.14159265358979323846;
	}
	else {
		return std::stod(number);
	}
}

std::string PrefixCalc::symbolToString(char ch) {
	std::string res = "";
	res += ch;
	return res;
}

int PrefixCalc::binOpsPriority(std::string str) {
	if (str == "-" || str == "+") {
		return 1;
	}
	else if (str == "*" || str == "/") {
		return 2;
	}
	else if (str == "^") {
		return 3;
	}
	return 0;
}

double PrefixCalc::doOperator(double a, std::string op) {
	if (op == "sin") {
		return sin(a);
	}
	if (op == "cos") {
		return cos(a);
	}
	if (op == "tg") {
		return tan(a);
	}
	if (op == "ctg") {
		return 1.0 / tan(a);
	}
	if (op == "arcsin") {
		return asin(a);
	}
	if (op == "arccos") {
		return acos(a);
	}
	if (op == "arctg") {
		return atan(a);
	}
	if (op == "arcctg") {
		return atan(1 / a);
	}
	if (op == "sqrt") {
		return pow(a, 0.5);
	}
	if (op == "ln") {
		return log(a);
	}
	if (op == "log") {
		return log10(a);
	}
	if (op == "--") {
		return -a;
	}
	throw std::runtime_error("No such operator: " + op);
}

double PrefixCalc::doOperator(double a, double b, std::string op) {
	if (op == "+") {
		return a + b;
	}
	if (op == "-") {
		return a - b;
	}
	if (op == "*") {
		return a * b;
	}
	if (op == "/") {
		return a / b;
	}
	if (op == "^") {
		return pow(a, b);
	}
	throw std::runtime_error("No such operator: " + op);
}

PrefixCalc::PrefixCalc(std::string sourceExp) {
	this->sourceExp = sourceExp;
}

std::string PrefixCalc::prefixToString() {					//join vector by " "
	std::string str = "";
	for (int i = 0; i < prefixFormExpVec.length() - 1; i++)
	{
		str += prefixFormExpVec[i] + " ";
	}
	str += prefixFormExpVec[prefixFormExpVec.length() - 1];
	return str;
}

Vector<std::string> PrefixCalc::toPrefixForm() {
	split();
	Stack<std::string> binOps = Stack<std::string>();
	Stack<std::string> expInPrefixForm = Stack<std::string>();
	for (int i = vec.length() - 1; i >= 0; i--)
	{
		if (vec[i] == ")") {
			binOps.push(")");
		}
		else if (isNumber(vec[i]) || isUnaryOperator(vec[i])) {
			expInPrefixForm.push(vec[i]);

		}
		else if (vec[i] == "(") {
			while (binOps.top() != ")") {
				try {
					expInPrefixForm.push(binOps.pop());
				}
				catch (const std::runtime_error& error) {
					throw std::runtime_error("No close bracket to open bracket at index: " + std::to_string(i));
				}
			}
			binOps.pop();

		}
		else if (isBinaryOperator(vec[i])) {
			while (!binOps.isEmpty() && this->binOpsPriority(vec[i]) <= this->binOpsPriority(binOps.top())) {
				expInPrefixForm.push(binOps.pop());
			}
			binOps.push(vec[i]);
		}
	}

	while (!(binOps.isEmpty())) {
		expInPrefixForm.push(binOps.pop());
		if (vec[vec.length() - 1] == "(") {
			throw std::runtime_error("No open bracket");
		}
	};
	prefixFormExpVec = expInPrefixForm.toArray();

	return prefixFormExpVec;
}

double PrefixCalc::calculate() {								//calculating 
	Stack<double> numbers = Stack<double>();
	for (int i = prefixFormExpVec.length() - 1; i >= 0; i--)    //iterating from end to start of prefix form of expression
	{
		if (isNumber(prefixFormExpVec[i])) {                    //numbers add to stack
			numbers.push(parseDouble(prefixFormExpVec[i]));
		}
		else {																		//do operators
			if (isUnaryOperator(prefixFormExpVec[i]) && numbers.size() > 0) {
				double first = numbers.pop();
				numbers.push(doOperator(first, prefixFormExpVec[i]));
			}
			else if (isBinaryOperator(prefixFormExpVec[i]) && numbers.size() > 1) {
				double first = numbers.pop();
				double second = numbers.pop();
				numbers.push(doOperator(first, second, prefixFormExpVec[i]));
			}
		}
	}
	return numbers.top();
}
