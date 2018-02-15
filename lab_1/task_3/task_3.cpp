#include "stdafx.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Invalid parameters count \n";
		return 1;
	}
	
	const size_t MAX = stoi(argv[1]);
	if (MAX < 1)
	{
		cout << "Invalid MAX parameter. Max < 1 \n";
		return 1;
	}

	size_t numberCountInLine = 5;
	if (argc == 3)
	{
		numberCountInLine = stoi(argv[2]);

		if (numberCountInLine < 1 || numberCountInLine > 10)
		{
			cout << "Invalid number count in line. Allowable interval is from 1 to 10 \n";
			return 1;
		}
	}

	size_t lastNumber = 0;
	size_t currentNumber = 1;
	size_t tempNumber;
	size_t numbersCount = 1;

	while (lastNumber < MAX)
	{
		cout << lastNumber;

		if (numbersCount % numberCountInLine == 0)
		{
			cout << "\n";
		}
		else
		{
			cout << " ";
		}

		tempNumber = currentNumber;

		if ((currentNumber + lastNumber) > numeric_limits<size_t>::max())
		{
			cout << "Next Number overflow. Program has to stop.";
			return 1;
		}
		currentNumber += lastNumber;
		lastNumber = tempNumber;

		++numbersCount;
	}

	cout << "\n";

    return 0;
}

