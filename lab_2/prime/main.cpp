#include "pch.h"

const unsigned int COMMAND_LINE_PARAMS_COUNT = 2;
const unsigned int MAX_UPPER_BOUND = 100000000;

using namespace std;

bool ParseCommandLine(int argc, char* argv[], unsigned int& upperBound)
{
	if (argc != COMMAND_LINE_PARAMS_COUNT)
	{
		return false;
	}
	try
	{
		upperBound = stoul(argv[1]);
	}
	catch (const exception &e)
	{
		cout << e.what() << '\n';
		return false;
	}

	return upperBound <= MAX_UPPER_BOUND;
}

int main(int argc, char* argv[])
{
	unsigned int upperBound;
	if (!ParseCommandLine(argc, argv, upperBound))
	{
		cout << "Invalid max prime. Correct param is max prime < " << MAX_UPPER_BOUND;
		return 1;
	}
}