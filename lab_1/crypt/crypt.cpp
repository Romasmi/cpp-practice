#include "pch.h"
using namespace std;
using CryptFunction = function<void(unsigned char& byte, const unsigned char key)>;

struct BytePosition
{
	unsigned char left;
	unsigned char right;
};

const unsigned int ARGS_COUNT = 5;
const unsigned char MIN_KEY = 0;
const unsigned char MAX_KEY = 255;
const vector<BytePosition> BYTE_POSITION = {
	{ 7, 5 },
	{ 6, 1 },
	{ 5, 0 },
	{ 4, 7 },
	{ 3, 6 },
	{ 2, 4 },
	{ 1, 3 },
	{ 0, 2 }
};

template <class T>
bool Between(T item, T min, T max)
{
	return item >= min && item <= max;
}

void PutByte(const unsigned char byteHolder, unsigned char& byteGetter, const char position, const char newPosition)
{
	char mask = 0x1;
	mask = (mask & (byteHolder >> position)) << newPosition;
	byteGetter = byteGetter | mask;
}

void Encrypt(unsigned char& byte, const unsigned char key)
{
	unsigned char processedByte = 0;
	byte = byte ^ key;
	for (const BytePosition& position : BYTE_POSITION)
	{
		PutByte(byte, processedByte, position.left, position.right);
	}
	byte = processedByte;
}

void Decrypt(unsigned char& byte, const unsigned char key)
{
	unsigned char processedByte = 0;
	for (const BytePosition& position : BYTE_POSITION)
	{
		PutByte(byte, processedByte, position.right, position.left);
	}
	byte = processedByte;
	byte = byte ^ key;
}

const pair<string, CryptFunction> COMMAND_TO_CRYPT_FUNCTION[] = {
	{ "crypt", Encrypt },
	{ "decrypt", Decrypt },
};

CryptFunction CommandToCryptFunction(const string& command)
{
	for (auto& p : COMMAND_TO_CRYPT_FUNCTION)
	{
		if (p.first == command)
		{
			return p.second;
		}
	}
	return nullptr;
}

void Crypt(istream& in, ostream& out, const unsigned char key, CryptFunction const& cryptFunction)
{
	char byte;
	while (in.get(byte))
	{
		uint8_t b = static_cast<uint8_t>(byte);
		cryptFunction(b, key);
		out.put(b);
	} 
} 
 
bool Crypt(
	const string& inputFileName,
	const string& outputFileName,
	const unsigned char key,
	CryptFunction const& cryptFunction)
{
	ifstream infile(inputFileName, ios_base::in | ios_base::binary);
	ofstream outile(outputFileName, ios_base::out | ios_base::binary);

	if (!(infile.is_open() && outile.is_open()))
	{
		return false;
	}
	Crypt(infile, outile, key, cryptFunction);
	return true;
}

bool IsValidParams(int argc, char* argv[])
{
	if (argc != ARGS_COUNT)
	{
		return false;
	}

	unsigned char key;
	try
	{
		key = static_cast<char>(stoi(argv[4]));
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return false;
	}

	if (!Between<unsigned char>(key, MIN_KEY, MAX_KEY))
	{
		return false;
	}

	return CommandToCryptFunction(argv[1]) != nullptr;
}

int main(int argc, char* argv[])
{
	if (!IsValidParams(argc, argv))
	{
		cout << "Invalid params\n";
		return 1;
	}

	const string command = argv[1];
	const string inputFileName = argv[2];
	const string outputFileName = argv[3];
	const unsigned char key = static_cast<unsigned char>(stoul(argv[4]));
	CryptFunction cryptFunction = CommandToCryptFunction(command);

	return Crypt(inputFileName, outputFileName, key, cryptFunction) ? 0 : 1;
}
