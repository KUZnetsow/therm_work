// thermWork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <windows.h>
#include <string>
#include "Stack.h"
#include "PrefixCalc.h"
#include "Vector.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string expression = "";
    std::cout << "Введите выражение для перевода в префиксную форму и вычисления" << std::endl;
    std::cin >> expression;
    PrefixCalc calculator = PrefixCalc(expression);
    try {
        calculator.toPrefixForm();
        std::cout << "Выражение в префиксной форме: " << std::endl;
        std::cout << calculator.prefixToString() << std::endl;
        std::cout << "Результат:" << std::endl;
        std::cout << calculator.calculate() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}