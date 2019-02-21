#include "pch.h"
using namespace std;
const double MULTIPLICATOR = 2;

void LoadVectorFromStream(vector<double> &v, istream &input) {
  string currentLine;
  double number;
  while (input >> number) {
    v.push_back(number);
  }
}

void Print(const vector<double> v) {
  copy(v.begin(), v.end(), ostream_iterator<double>(cout, " "));
}

double GetNegativeNumbersSum(const vector<double> &v) {
  return accumulate(v.begin(), v.end(), 0.0,
                    [](const double sum, const double number) {
                      return (number < 0) ? sum + number : sum;
                    });
}

bool IsEven(size_t number)
{
	return number % 2 == 0;
}

/*Ёлементы, сто€щие на четных позици€х массива умножить на 2, а из элементов,
 * сто€щих на нечетных позици€х, вычесть сумму всех неотрицательных элементов*/
void ProcessVector(vector<double> &v) 
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

int main() {
  vector<double> inputVector;
  LoadVectorFromStream(inputVector, cin);
  if (inputVector.size() == 0) {
    cout << "Invalid input.\n Correct input: <double number> [<double numbers "
            "separatet by space>]";
    return 1;
  }

  ProcessVector(inputVector);
  sort(inputVector.begin(), inputVector.end());
  Print(inputVector);
  return 0;
}
