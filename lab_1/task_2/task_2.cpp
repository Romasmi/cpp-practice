#include "stdafx.h"
using namespace std;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const char MIN_LETTER = 'A';
const char MAX_LETTER = 'Z';
const char AMinus10 = 'A' - 10;

template <typename T>
bool InInterval(const T& value, const T& min, const T& max)
{
	return !(value < min) && !(max < value);
}

unsigned int LetterToNumber(char letter)
{
	letter = toupper(letter);
	return InInterval(letter, '0', '9') ? static_cast<int>(letter - '0') : static_cast<int>(letter) - AMinus10;
}

char NumberToLetter(int number)
{
	return InInterval(number, 0, 9) ? static_cast<char>(number + '0') : static_cast<char>(number + AMinus10);
}

bool IsAllowableLetter(char letter)
{
	letter = toupper(letter);
	return InInterval(letter, MIN_LETTER, MAX_LETTER);
}

bool IsAllowableRadix(int radix)
{
	return InInterval(radix, MIN_RADIX, MAX_RADIX);
}

bool IsSignedNumber(const string& number, char& sign)
{
	if (number.length())
	{
		sign = number[0];
		return number.length() && (sign == '-' || sign == '+');
	}
	else
	{
		return false;
	}
}

bool IsSignedNumber(const string& number)
{
	char sign;
	return IsSignedNumber(number, sign);
}

unsigned int GetSum(const unsigned int a, const unsigned b)
{
	if (a > numeric_limits<unsigned int>::max() - b)
	{
		throw overflow_error("Input number overflow");
	}
	else
	{
		return a + b;
	}
}

unsigned int GetMul(const unsigned int a, const unsigned b)
{
	if (a == 0 || (numeric_limits<unsigned int>::max() / b >=  a))
	{
		return a * b;
	}
	else
	{
		throw overflow_error("Input number overflow");
	}
}

unsigned int StringToInt(const string& str, const unsigned int radix, bool& wasError)
{
	if (str.length() == 0)
	{
		wasError = true;
		return 0;
	}

	unsigned int number = 0;
	for (size_t i = 0; i < str.length(); ++i)
	{
		unsigned int currentDigit = LetterToNumber(str[i]);
		if (currentDigit >= radix)
		{
			wasError = true;
			return 0;
		}

		if (!wasError)
		{
			number = GetSum(GetMul(number, radix), currentDigit);
		}
		else
		{
			return 0;
		}
	}
	return number;
}

string IntToString(unsigned int n, const unsigned int radix, bool& wasError)
{
	if (!IsAllowableRadix(radix))
	{
		wasError = true;
		return "";
	}

	string number = "";
	while (n != 0)
	{
		int remainder = n % radix;
		n = n / radix;
		number = NumberToLetter(remainder) + number;
	}

	if (number == "")
	{
		number = "0";
	}
	return number;
}

string Convert(const unsigned int startRadix, const unsigned int finishRadix, const string& number, bool& wasError)
{
	if (startRadix == finishRadix)
	{
		return number;
	}

	char sign;
	bool isSignedNumber = IsSignedNumber(number, sign);
	unsigned int convertedNumber;

	try
	{
		if (isSignedNumber)
		{
			convertedNumber = StringToInt(number.substr(1), startRadix, wasError);
		}
		else
		{
			convertedNumber = StringToInt(number, startRadix, wasError);
		}

		string finalNumber = IntToString(convertedNumber, finishRadix, wasError);
		return isSignedNumber ? sign + finalNumber : finalNumber;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		wasError = true;
		return "";
	}
}

bool IsValidRadix(const string& number, const unsigned int radix)
{
	unsigned int i = IsSignedNumber(number) ? 1 : 0;
	for (i; i < number.length(); ++i)
	{
		if (!(LetterToNumber(number[i]) < radix))
		{
			return false;
		}
	}
	return true;
}

bool ValidStringNumber(string number)
{
	try
	{
		int tempNumber = stoi(number);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool IsValidated(char* argv[])
{
	if (!(ValidStringNumber(argv[1]) && ValidStringNumber(argv[2])))
	{
		return false;
	}

	int startRadix = stoi(argv[1]);
	int finishRadix = stoi(argv[2]);
	if (!IsAllowableRadix(startRadix) || !IsAllowableRadix(finishRadix))
	{
		cout << "Not allowable radix" << endl;
		return false;
	}

	const string number = argv[3];
	if (number == "")
	{
		cout << "Empty input number" << endl;
		return false;
	}

	if (!IsValidRadix(number, startRadix))
	{
		cout << "Non conformity of input radix and input number" << endl;
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invaid parameters count" << endl;
		return 1;
	}

	if (!IsValidated(argv))
	{
		return 1;
	}

	bool wasError = false;
	string newNumber = Convert(stoi(argv[1]), stoi(argv[2]), argv[3], wasError);

	if (!wasError)
	{
		cout << newNumber << '\n';
		return 0;
	}
	else
	{
		cout << "Unable to convert" << endl;
		return 1;
	}
}
