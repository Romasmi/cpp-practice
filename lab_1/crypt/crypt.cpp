#include "pch.h"
using namespace std;
using CryptFunction = function<void(uint8_t& byte, const uint8_t key)>;

struct BytePosition
{
	uint8_t left;
	uint8_t right;
};

const unsigned int ARGS_COUNT = 5;
const uint8_t MIN_KEY = 0;
const uint8_t MAX_KEY = 255;
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

void CopyByte(const uint8_t byteHolder, uint8_t& byteGetter, const uint8_t position, const uint8_t newPosition)
{
	uint8_t mask = 0x1;
	mask = (mask & (byteHolder >> position)) << newPosition;
	byteGetter = byteGetter | mask;
}

void Encrypt(uint8_t& byte, const uint8_t key)
{
	uint8_t processedByte = 0;
	byte = byte ^ key;
	for (const BytePosition& position : BYTE_POSITION)
	{
		CopyByte(byte, processedByte, position.left, position.right);
	}
	byte = processedByte;
}

void Decrypt(uint8_t& byte, const uint8_t key)
{
	uint8_t processedByte = 0;
	for (const BytePosition& position : BYTE_POSITION)
	{
		CopyByte(byte, processedByte, position.right, position.left);
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

void Crypt(istream& in, ostream& out, const uint8_t key, const CryptFunction const& cryptFunction)
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
	const uint8_t key,
	const CryptFunction const& cryptFunction)
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

	uint8_t key;
	try
	{
		key = static_cast<uint8_t>(stoul(argv[4]));
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return false;
	}

	if (!Between<uint8_t>(key, MIN_KEY, MAX_KEY))
	{
		return false;
	}

	return CommandToCryptFunction(argv[1]) != nullptr;
}

int main(int argc, char* argv[])
{
	if (!IsValidParams(argc, argv))
	{
		cout << "Invalid params. Correct params: crypt.txt <crypt way: encrypt|decrypt> <input_file> [<output_file>]\n";
		return 1;
	}

	const string command = argv[1];
	const string inputFileName = argv[2];
	const string outputFileName = argv[3];
	const uint8_t key = static_cast<uint8_t>(stoul(argv[4]));
	CryptFunction cryptFunction = CommandToCryptFunction(command);

	return Crypt(inputFileName, outputFileName, key, cryptFunction) ? 0 : 1;
}
