#include "stdafx.h"
using namespace std;

string StringReplace(string line, const string search, const string replace)
{
	string newLine = "";
	size_t currentPosition = 0;
	size_t searchLength = search.length();
	size_t lineLength = line.length();
	while (currentPosition + searchLength < lineLength)
	{
		const string subString = line.substr(currentPosition, searchLength);
		if (subString == search)
		{
			newLine += replace;
			currentPosition += searchLength;
		}
		else
		{
			newLine += line[currentPosition];
			++currentPosition;
		}
	}
	if (lineLength - currentPosition > 0)
	{
		newLine += line.substr(currentPosition, lineLength - currentPosition);
	}
	return newLine;
}

void CopyFileByReplacing(fstream& input, fstream& output, const string search,
	const string replace)
{
	string currentLine;
	while (getline(input, currentLine))
	{
		const string newLine = StringReplace(currentLine, search, replace);
		output << newLine << '\n';
	}
}

int main(const int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid parameter`s count" << endl;
		return 1;
	}

	fstream input(argv[1], istream::in);
	fstream output(argv[2], ostream::out);

	if (!input.is_open() || !output.is_open())
	{
		cout << "File(s) incorrect" << endl;
		return 1;
	}

	if (argv[3] == "")
	{
		cout << "Input search string have not to be empty" << endl;
		return 1;
	}

	CopyFileByReplacing(input, output, argv[3], argv[4]);
	return 0;
}
