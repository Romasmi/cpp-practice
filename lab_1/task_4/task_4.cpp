#include "stdafx.h"
using namespace std;
enum OperationTypes {plusSign = '+', minusSign = '-', multiplicationSign = '*', devisionSign = '/'};

double Calculate(const double operand1, const double operand2, const OperationTypes operation)
{
	double result;

	switch (operation)
	{
	case plusSign:
		result = operand1 + operand2;
		break;
	case minusSign:
		result = operand1 - operand2;
		break;
	case multiplicationSign:
		result = operand1 * operand2;
		break;
	case devisionSign:
		result = operand1 / operand2;
		break;
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Not input numbers" << endl;
		return 1;
	} 

	OperationTypes operation;
	double operand;
	try
	{
		for (int i = 1; i < argc; ++i)
		{
			if (i % 2 == 0)
			{
				operation = static_cast<OperationTypes>(argv[i][0]);
			}
			else
			{
				operand = stod(argv[i]);
			}
		}
	}
	catch (exception e)
	{
		cout << "One or more operands aren't' valid \n";
		cout << e.what() << endl;
		return 1;
	}

	try
	{
		operand = stod(argv[argc - 1]);
	}
	catch (exception e)
	{
		cout << "Last argument must be number\n";
		cout << e.what() << endl;
		return 1;
	}

	double result = stod(argv[1]);
	for (int i = 2; i < argc; ++i)
	{
		if (i % 2 == 0)
		{
			operation = static_cast<OperationTypes>(argv[i][0]);
		}
		else
		{
			result = Calculate(result, stod(argv[i]), operation);
		}
	}
	
	cout << "Result: " << result << endl;
	return 0;
}

