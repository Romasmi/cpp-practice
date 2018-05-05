#include "stdafx.h"
#include "vector.h"
using namespace std;
using BaseVector = vector<double>;

bool SetVectorFromStream(BaseVector& vector, istream& input)
{
	try
	{
		string currentLine;
		while (getline(input, currentLine))
		{
			istringstream stream(currentLine);
			double number;
			while (stream >> number)
			{
				vector.push_back(number);
			}
		}
		return true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

void PrintVector(const BaseVector& vector)
{
	cout.precision(3);
	copy(vector.begin(), vector.end(), ostream_iterator<double>(cout, " "));
	cout << "\n";
}

void MultiplyVectorByScalar(BaseVector& vector, const double scalar)
{
	transform(vector.begin(), vector.end(), vector.begin(),
		[scalar](double item) { return item * scalar; });
}

void ProcessVector(BaseVector& vector)
{
	/*Разделить элементы массива на половину максимального элемента*/
	double maxElement = *max_element(vector.begin(), vector.end());
	if (maxElement != 0)
	{
		MultiplyVectorByScalar(vector, 2 / maxElement);
	}
	else
	{
		throw overflow_error("Devide by zero exception");
	}
}