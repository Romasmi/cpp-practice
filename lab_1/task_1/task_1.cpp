#include "stdafx.h"
const int MIN = 1;
const int MAX = 100;

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	for (i = MAX; i > MIN; --i)
	{
		cout << i << ", ";
	}
	cout << i << "\n";

	return 0;
}
