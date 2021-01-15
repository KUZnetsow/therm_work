#include "pch.h"
#include "CppUnitTest.h"
#include "../thermWork/PrefixCalc.h"
#include "../thermWork/PrefixCalc.cpp"
#include "../thermWork/Vector.h"
#include "../thermWork/Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		TEST_METHOD(TestTranslation1)
		{
			PrefixCalc calc = PrefixCalc("ln(log(33.3+sqrt(22+555.332/2))+22^2+sqrt(574^4))");
			calc.toPrefixForm();
			char tab[1024];
			strcpy_s(tab, calc.prefixToString().c_str());
			Assert::AreEqual("ln + log + 33.3 sqrt + 22 / 555.332 2 + ^ 22 2 sqrt ^ 574 4", tab);
		}
		TEST_METHOD(TestTranslation2)
		{
			PrefixCalc calc = PrefixCalc("(-(22+11-(11+ln(16)+cos(13)))+22)");
			calc.toPrefixForm();
			char tab[1024];
			strcpy_s(tab, calc.prefixToString().c_str());
			Assert::AreEqual("+ -- + 22 - 11 + 11 + ln 16 cos 13 22", tab);
		}
		TEST_METHOD(TestTranslation3)
		{
			PrefixCalc calc = PrefixCalc("e+pi*22-(11.11+14.1/22.5)/77.4");
			calc.toPrefixForm();
			char tab[1024];
			strcpy_s(tab, calc.prefixToString().c_str());
			Assert::AreEqual("+ e - * pi 22 / + 11.11 / 14.1 22.5 77.4", tab);
		}
		TEST_METHOD(TestTranslation4)
		{
			PrefixCalc calc = PrefixCalc("ln(sqrt((log(e))))");
			calc.toPrefixForm();
			char tab[1024];
			strcpy_s(tab, calc.prefixToString().c_str());
			Assert::AreEqual("ln sqrt log e", tab);
		}
		TEST_METHOD(TestCalculation1)
		{
			PrefixCalc calc = PrefixCalc("ln(log(33.3+sqrt(22+555.332/2))+22^2+sqrt(574^4))");
			calc.toPrefixForm();
			double number = 12.0;
			Assert::AreEqual(number, floor(calc.calculate()));
		}
		TEST_METHOD(TestCalculation2)
		{
			PrefixCalc calc = PrefixCalc("(-(22+11-(11+ln(16)+cos(13)))+22)");
			calc.toPrefixForm();
			double number = 3.0;
			Assert::AreEqual(number, floor(calc.calculate()));
		}
		TEST_METHOD(TestCalculation3)
		{
			PrefixCalc calc = PrefixCalc("e+pi*22-(11.11+14.1/22.5)/77.4");
			calc.toPrefixForm();
			double number = 71.0;
			Assert::AreEqual(number, floor(calc.calculate()));
		}
	};
}
