#include "stdafx.h"
#include "vector.h"
using namespace std;
using BaseVector = vector<double>;

BaseVector GetVectorFromStream(istream& input)
{
	BaseVector numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	return numbers;
}

void PrintVector(const BaseVector& vector)
{
	cout.precision(3);
	copy(vector.begin(), vector.end(), ostream_iterator<double>(cout, " "));
	cout << "\n";
}

void MultiplyVectorByScalar(BaseVector& vector, const double scalar)
{
	if (vector.size() == 0)
	{
		return;
	}

	transform(vector.begin(), vector.end(), vector.begin(),
		[scalar](double item) { return item * scalar; });
}

void ProcessVector(BaseVector& vector)
{
	if (vector.empty())
	{
		return;
	}

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