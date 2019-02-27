#include "pch.h"
using namespace std;
const unsigned int MIN_ARGS_COUNT = 2;
const unsigned int MAX_ARGS_COUNT = 3;
const char BORDER_CHAR = '*';
const char UNIT_CHAR = '#';
const char EMPTINESS_CHAR = ' ';
const unsigned int MIN_WIDTH = 3;
const unsigned int MIN_HEIGHT = 3;
const unsigned int MAX_WIDTH = 256;
const unsigned int MAX_HEIGHT = 256;
set<size_t> NEIBTHOUR_COUNT_FOR_LIVING = { 2, 3 };

using MapRow = vector<char>;
using Map = vector<MapRow>;

template <class T>
bool Between(T item, T min, T max)
{
	return item >= min && item <= max;
}

bool LoadMapFromStream(istream& input, Map& map)
{
	string line;
	while (getline(input, line))
	{
		if (line.empty())
		{
			break;
		}
		MapRow row(line.begin(), line.end());
		map.push_back(row);
	}
	return map.size() != 0;
}

bool LoadMapFromFile(const string& inputFileName, Map& map)
{
	ifstream inFile(inputFileName);
	return inFile.is_open() && LoadMapFromStream(inFile, map);
}

void PrintMap(const Map& map, ostream& out = cout)
{
	for (MapRow row : map)
	{
		copy(row.begin(), row.end(), ostream_iterator<char>(out, ""));
		out << '\n';
	}
}

bool CheckVectorItems(vector<char>::iterator begin, vector<char>::iterator end, set<char> itemsSet)
{
	for (auto it = begin; it != end; ++it)
	{
		if (itemsSet.find(*it) == itemsSet.end())
		{
			return false;
		}
	}
	return true;
}

bool IsValidMap(Map& map)
{
	const size_t width = map.front().size();
	const size_t height = map.size();
	if (!Between<size_t>(width, MIN_WIDTH, MAX_WIDTH) || !Between<size_t>(height, MIN_HEIGHT, MAX_HEIGHT))
	{
		return false;
	}

	const bool firstRowHasValidItems = CheckVectorItems(map.front().begin(), map.front().end(), set<char>{ BORDER_CHAR });
	const bool endRowHasValidItems = CheckVectorItems(map.back().begin(), map.back().end(), set<char>{ BORDER_CHAR });
	const bool endRowHasValidSize = map.back().size() == width;
	if (!firstRowHasValidItems || !endRowHasValidItems || !endRowHasValidSize)
	{
		return false;
	}

	for (size_t i = 1; i < map.size() - 1; ++i)
	{
		const bool validSize = map[i].size() == width;
		const bool validItems = map[i].front() == BORDER_CHAR && CheckVectorItems(map[i].begin() + 1, map[i].end() - 1, set<char>{ UNIT_CHAR, EMPTINESS_CHAR }) && map[i].back() == BORDER_CHAR;

		if (!validSize || !validItems)
		{
			return false;
		}
	}
	return true;
}

char GetNeightbouhsCount(const Map& map, const size_t y, const size_t x, size_t width, size_t height)
{
	unsigned int count = 0;
	const size_t yBegin = y == 1 ? 1 : y - 1;
	const size_t yEnd = y == height - 2 ? height - 2 : y + 1;
	const size_t xBegin = x == 1 ? 1 : x - 1;
	const size_t xEnd = x == width - 2 ? width - 2 : x + 1;
	for (size_t i = yBegin; i <= yEnd; ++i)
	{
		for (size_t j = xBegin; j <= xEnd; ++j)
		{
			if (!(i == y && j == x) && map[i][j] == '#')
			{
				++count;
			}
		}
	}
	return count;
}

void NextLifeGeneration(Map& map)
{
	Map nextGeneration = map;
	const size_t width = map.front().size();
	const size_t height = map.size();
	for (size_t i = 1; i < height - 1; ++i)
	{
		for (size_t j = 1; j < width - 1; ++j)
		{
			const size_t neighbourCount = GetNeightbouhsCount(map, i, j, width, height);
			const bool unitCanLive = NEIBTHOUR_COUNT_FOR_LIVING.find(neighbourCount) != NEIBTHOUR_COUNT_FOR_LIVING.end();
			nextGeneration[i][j] = unitCanLive ? UNIT_CHAR : EMPTINESS_CHAR;
		}
	}
	map = nextGeneration;
}

bool ParseCommandLine(int argc, char* argv[], string& inputFileName, string& outputFileName)
{
	if (argc == MIN_ARGS_COUNT)
	{
		outputFileName = "";
		inputFileName = argv[1];
		ifstream input(inputFileName);
		return input.is_open();
	}
	else if (argc == MAX_ARGS_COUNT)
	{
		outputFileName = argv[2];
		inputFileName = argv[1];
		ifstream input(inputFileName);
		ofstream output(outputFileName);
		return input.is_open() && output.is_open();
	}
	return false;
}

int main(int argc, char* argv[])
{
	string inputFileName;
	string outputFileName;
	if (!ParseCommandLine(argc, argv, inputFileName, outputFileName))
	{
		cout << "Invaliad params. Correct params: life.exe <input_file.txt> [output_file.txt]";
		return 1;
	}

	Map map;
	if (LoadMapFromFile(inputFileName, map) && IsValidMap(map))
	{
		NextLifeGeneration(map);
		if (!outputFileName.empty())
		{
			ofstream out(outputFileName);
			PrintMap(map, out);
		}
		else
		{
			PrintMap(map, cout);
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
