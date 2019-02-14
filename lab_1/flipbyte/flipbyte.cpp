#include "pch.h"
using namespace std;
const unsigned int ARGS_COUNT = 2;
const unsigned char NUMBER_SIZE_IN_BITS = 8;
const unsigned char BITS_IN_HALF_OF_NUMBER = NUMBER_SIZE_IN_BITS / 2;
const unsigned char MIN_NUMBER = 0;
const unsigned char MAX_NUMBER = 255;

template <class T>
bool Between(const T item, const T min, const T max)
{
	return item >= min && item <= max;
}

void FlipByte(unsigned char& number)
{
	number = number << BITS_IN_HALF_OF_NUMBER | number >> BITS_IN_HALF_OF_NUMBER;
}

bool IsValidParams(int argc, char* argv[])
{
	if (argc != ARGS_COUNT)
	{
		cout << "Invalid parametes count\n";
		return false;
	}

	unsigned int number;
	try
	{
		number = stoul(argv[1]);
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
		return false;
	}

	return Between<unsigned int>(number, MIN_NUMBER, MAX_NUMBER);
}

int main(int argc, char* argv[])
{
	if (!IsValidParams(argc, argv))
	{
		cout << "Invalid params\n"; 
		return 1;
	} 

	unsigned char numberToFlipBytes = static_cast<unsigned char>(stoul(argv[1]));
	FlipByte(numberToFlipBytes);
	cout << static_cast<unsigned int>(numberToFlipBytes) << "\n";
	return 0;
}
