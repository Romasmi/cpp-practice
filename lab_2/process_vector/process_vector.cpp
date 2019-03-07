#include "pch.h"

#include "process_vector.h"
#include "util.h"

const double MULTIPLICATOR = 2;

void LoadVectorFromStream(std::vector<double>& v, std::istream& input)
{
	std::string currentLine;
	if (getline(input, currentLine))
	{
		v = LineToVector<double>(currentLine);
	}
	else
	{
		v.clear();
	}
}

double GetNonNegativeNumbersSum(const std::vector<double>& v)
{
	return accumulate(v.begin(), v.end(), 0.0,
		[](const double sum, const double number) {
			return (number >= 0) ? sum + number : sum;
		});
}

bool IsEven(size_t number) { return number % 2 == 0; }

/*Ёлементы, сто€щие на четных позици€х массива умножить на 2, а из элементов,
 * сто€щих на нечетных позици€х, вычесть сумму всех неотрицательных элементов*/
void ProcessVector(std::vector<double>& v)
{
	double nonNegativeNumbersSum = GetNonNegativeNumbersSum(v);
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (IsEven(i + 1))
		{
			v[i] *= MULTIPLICATOR;
		}
		else
		{
			v[i] -= nonNegativeNumbersSum;
		}
	}
}

std::vector<double> GetProcesedVector(const std::vector<double>& v)
{
	std::vector<double> localVector = v;
	ProcessVector(localVector);
	return localVector;
}
