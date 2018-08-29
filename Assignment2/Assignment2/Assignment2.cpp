/*
Aaron Shaneen
CS 2130 SUM' 15
Assignment 2
*/

//Copyright 2015, Bradley Peterson, Weber State University, all rights reserved.

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

// Function Declarations
bool isNumber(const char& nextSym);
bool isNumber(const string& sym);
bool isOperator(const string& sym);
bool greaterOrEqualPrecedence(const string& otherOperator, const string& symOperator);

// convertToPfx()
string convertToPfx(const string& infx)
{
	string pfx = "";
	stack<string> s;
	string sym = "";
	int position = 0;

	while (position < infx.size())
	{
		sym += infx.at(position);

		// if sym is a number
		if (isNumber(sym))
		{
			while (position + 1 < infx.size() && isNumber(infx.at(position + 1)))
			{
				sym += infx.at(position + 1);
				position++;
			}

			pfx += sym + " ";
		}

		// if sym is (
		else if (sym == "(")
		{
			s.push(sym);
		}

		// if sym is )
		else if (sym == ")")
		{
			do
			{
				string tempSym;

				if (!s.empty())
				{
					tempSym = s.top();
				}

				if (isOperator(tempSym))
				{
					pfx += tempSym + " ";
					s.pop();
				}

				else if (tempSym == "(")
				{
					s.pop();
					break;						// ugly I know, but it had to be done
				}

			} while (!s.empty());
		}

		// if sym is an operator
		else if (isOperator(sym))
		{
			string tempSym = "";

			if (!s.empty())
			{
				tempSym = s.top();
			}

			while (isOperator(tempSym) && greaterOrEqualPrecedence(tempSym, sym)) {
				{
					pfx += tempSym + " ";
					s.pop();
					tempSym = "";
				}

				if (!s.empty())
				{
					tempSym = s.top();
				}
			}

			s.push(sym);
		}

		sym = "";
		position++;
	} // end while loop

	// Cleaning out the stack
	while (!s.empty())
	{
		pfx += s.top() + " ";
		s.pop();
	}

	return pfx;
} // end convertToPfx

// isNumber() Definition
bool isNumber(const string& sym)
{
	if (sym.at(0) == '0' || sym.at(0) == '1' || sym.at(0) == '2' || sym.at(0) == '3' || sym.at(0) == '4' ||
		sym.at(0) == '5' || sym.at(0) == '6' || sym.at(0) == '7' || sym.at(0) == '8' || sym.at(0) == '9')
	{
		return true;
	}

	else
	{
		return false;
	}
}

// Overloaded isNumber() Definition
bool isNumber(const char& nextSym)
{
	if (nextSym == '0' || nextSym == '1' || nextSym == '2' || nextSym == '3' || nextSym == '4' ||
		nextSym == '5' || nextSym == '6' || nextSym == '7' || nextSym == '8' || nextSym == '9')
	{
		return true;
	}

	else
	{
		return false;
	}
}

// isOperator() Definition
bool isOperator(const string& sym)
{
	if (sym == "+" || sym == "-" || sym == "*" || sym == "/" || sym == "^")
	{
		return true;
	}

	else
	{
		return false;
	}
}

// greaterOrEqualPrecedence() Definition
bool greaterOrEqualPrecedence(const string& otherOperator, const string& symOperator)
{
	int symOpPrecValue;
	int otherOpPrecValue;

	switch (otherOperator.at(0))
	{
	case '+':
		otherOpPrecValue = 1;
		break;

	case '-':
		otherOpPrecValue = 1;
		break;

	case '*':
		otherOpPrecValue = 2;
		break;

	case '/':
		otherOpPrecValue = 2;
		break;

	case '^':
		otherOpPrecValue = 3;
		break;
	} // end otherOperator switch

	switch (symOperator.at(0))
	{
	case '+':
		symOpPrecValue = 1;
		break;

	case '-':
		symOpPrecValue = 1;
		break;

	case '*':
		symOpPrecValue = 2;
		break;

	case '/':
		symOpPrecValue = 2;
		break;

	case '^':
		symOpPrecValue = 3;
		break;
	} // end symOperator switch

	if (otherOpPrecValue >= symOpPrecValue)
	{
		return true;
	}

	else
	{
		return false;
	}
} // end greaterOrEqualPrecedence()

//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	//get rid of spaces
	whatItIs.erase(whatItIs.begin(), std::find_if(whatItIs.begin(), whatItIs.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	whatItIs.erase(std::find_if(whatItIs.rbegin(), whatItIs.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), whatItIs.end());

	if (whatItShouldBe == whatItIs) {
		cout << "Passed test " << testName << " ***  Output was \"" << whatItIs << "\"" << endl;
		return true;
	}
	else {
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \"" << whatItIs << "\"" << endl << "  Output should have been blank. " << endl;
		}
		else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \"" << whatItIs << "\"" << endl << "  Output should have been \"" << whatItShouldBe << "\"" << endl;
		}
		return false;
	}
}

// main()
int main() {

	string expression = "(2+3)";
	string result = convertToPfx(expression);
	checkTest("Test #1", "2 3 +", result);

	expression = "2+3";
	result = convertToPfx(expression);
	checkTest("Test #2", "2 3 +", result);

	expression = "(123+456)";
	result = convertToPfx(expression);
	checkTest("Test #3", "123 456 +", result);

	expression = "(8-5)";
	result = convertToPfx(expression);
	checkTest("Test #4", "8 5 -", result);

	expression = "((3-4)-5)";
	result = convertToPfx(expression);
	checkTest("Test #5", "3 4 - 5 -", result);

	expression = "(3 - (4 - 5))";
	result = convertToPfx(expression);
	checkTest("Test #6", "3 4 5 - -", result);

	expression = "(3*(8/2))";
	result = convertToPfx(expression);
	checkTest("Test #7", "3 8 2 / *", result);

	expression = "3 + 8 / 2";
	result = convertToPfx(expression);
	checkTest("Test #8", "3 8 2 / +", result);

	expression = "24 / 3 + 2";
	result = convertToPfx(expression);
	checkTest("Test #9", "24 3 / 2 +", result);

	expression = "((1 + 2) * (3 + 4))";
	result = convertToPfx(expression);
	checkTest("Test #10", "1 2 + 3 4 + *", result);

	expression = "2^3";
	result = convertToPfx(expression);
	checkTest("Test #11", "2 3 ^", result);

	expression = "8 + 3^4";
	result = convertToPfx(expression);
	checkTest("Test #12", "8 3 4 ^ +", result);

	expression = "(((3+12)-7)*120)/(2+3)";
	result = convertToPfx(expression);
	checkTest("Test #13", "3 12 + 7 - 120 * 2 3 + /", result);

	expression = "((((9+(2*(110-(20/2))))*8)+1000)/2)-((400*2500)-1000001)";
	result = convertToPfx(expression);
	checkTest("Test #14", "9 2 110 20 2 / - * + 8 * 1000 + 2 / 400 2500 * 1000001 - -", result);

	system("pause");
	return 0;
}
