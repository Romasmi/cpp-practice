#include "stdafx.h"

const size_t MIN = 1;
const size_t MAX = 1000;

using namespace std;

size_t SumDigits(size_t i)
{
	size_t sum = 0;

	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

void Print(const vector<size_t>& vectorToPrint)
{
	for (size_t i = 0; i < vectorToPrint.size(); ++i)
	{
		cout << vectorToPrint[i] << ' ';
	}
}

int main(int argc, char* argv[])
{
	vector<size_t> digits;

	for (size_t i = MIN; i < MAX; ++i)
	{
		if (i % SumDigits(i) == 0)
		{
			digits.push_back(i);
		}
	}

	sort(digits.begin(), digits.end());
	Print(digits);
	cout << "\n";
   
	return 0;
}

