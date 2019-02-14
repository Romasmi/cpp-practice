#include "pch.h"
using namespace std;
const unsigned int ARGS_COUNT = 2;
const unsigned char NUMBER_SIZE_IN_BITS = 8;
const unsigned char MIN_NUMBER = 0;
const unsigned char MAX_NUMBER = 255;

template <class T>
bool Between(const T item, const T min, const T max)
{
	return item >= min && item <= max;
}

void FlipByte(unsigned char& number)
{
	unsigned char flippedNumber = 0;
	for (size_t i = 0; i < NUMBER_SIZE_IN_BITS; ++i)
	{
		flippedNumber = flippedNumber << 1;
		flippedNumber = flippedNumber | (number & 0x01);
		number = number >> 1;
	}
	number = flippedNumber;
}

bool ParseCommandLine(int argc, char* argv[], unsigned char &number)
{
	if (argc != ARGS_COUNT)
	{
		cout << "Invalid parametes count\n";
		return false;
	}

	unsigned int parsedNumber;
	try
	{
		parsedNumber = stoul(argv[1]);
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
		return false;
	}

	if (Between<unsigned int>(parsedNumber, MIN_NUMBER, MAX_NUMBER))
	{
		number = static_cast<unsigned char>(parsedNumber);
		return true;
	}
	else
	{
		return false;
	}
}

int main(int argc, char* argv[])
{
	unsigned char numberToFlipBytes;
	if (!ParseCommandLine(argc, argv, numberToFlipBytes))
	{
		cout << "Invalid params\n"; 
		return 1;
	} 

	FlipByte(numberToFlipBytes);
	cout << static_cast<unsigned int>(numberToFlipBytes) << "\n";
	return 0;
}
