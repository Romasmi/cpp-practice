#include "pch.h"
using namespace std;
using FilesList = vector<string>;

const unsigned int MIN_ARGS_COUNT = 3;
const unsigned int bufferSize = 100;

FilesList GetFiles(char* argv[], const int count)
{
	FilesList files;
	for (int i = 1; i < count - 1; ++i)
	{
		files.push_back(argv[i]);
	}
	return files;
}

bool Join(const FilesList& filesList, const string& outFileName)
{
	ofstream outFile(outFileName, ios_base::binary | ios_base::out);
	if (!outFile.is_open())
	{
		return false;
	}

	for (const string &fileName : filesList)
	{
		ifstream inFile(fileName, ios_base::binary | ios_base::in);
		if (inFile.is_open())
		{
			char code;
			while (inFile.get(code))
			{
				outFile.put(code);
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc < MIN_ARGS_COUNT)
	{
		return 1;
	}

	FilesList filesList = GetFiles(argv, argc);
	string outFileName = argv[argc - 1];
	return Join(filesList, outFileName) ? 0 : 1;
}
