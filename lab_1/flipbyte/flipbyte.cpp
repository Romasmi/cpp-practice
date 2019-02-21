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

void FlipByte(uint8_t& number)
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

bool ParseCommandLine(int argc, char* argv[], uint8_t& number)
{
	if (argc != ARGS_COUNT)
	{
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
	uint8_t byteToFlip;
	if (!ParseCommandLine(argc, argv, byteToFlip))
	{
		cout << "Invalid params. Correct params: flipbyte.exe <number from 0 to 255> \n"; 
		return 1;
	} 

	FlipByte(byteToFlip);
	cout << static_cast<unsigned int>(byteToFlip) << "\n";
	return 0;
}
