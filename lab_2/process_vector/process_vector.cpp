#include "pch.h"

#include "process_vector.h"

const double MULTIPLICATOR = 2;

void LoadVectorFromStream(std::vector<double>& v, std::istream& input)
{
	std::string currentLine;
	double number;
	while (input >> number)
	{
		v.push_back(number);
	}
}

void Print(const std::vector<double> v)
{
	copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, " "));
}

double GetNegativeNumbersSum(const std::vector<double>& v)
{
	return accumulate(v.begin(), v.end(), 0.0,
		[](const double sum, const double number) {
			return (number < 0) ? sum + number : sum;
		});
}

bool IsEven(size_t number) { return number % 2 == 0; }

/*��������, ������� �� ������ �������� ������� �������� �� 2, � �� ���������,
 * ������� �� �������� ��������, ������� ����� ���� ��������������� ���������*/
void ProcessVector(std::vector<double>& v)
{
	double negativeNumbersSum = GetNegativeNumbersSum(v);
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (IsEven(i + 1))
		{
			v[i] *= MULTIPLICATOR;
		}
		else
		{
			v[i] -= negativeNumbersSum;
		}
	}
}
