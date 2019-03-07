#include "pch.h"

#include "process_vector.h"
#include "util.h"

using namespace std;

int main()
{
	vector<double> inputVector;
	LoadVectorFromStream(inputVector, cin);
	if (inputVector.size() == 0)
	{
		cout << "Invalid input.\n"
			 << "Correct input: <double number> [<double numbers separated by "
				"space>]";
		return 1;
	}

	ProcessVector(inputVector);
	sort(inputVector.begin(), inputVector.end());
	cout << inputVector;
	return 0;
}
