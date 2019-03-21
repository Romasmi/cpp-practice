#include "pch.h"

#include "dictionary.h"
#include "string_processor.h"
#include <iostream>

using namespace std;

bool ParseCommandLine(int argc, char* argv[], wstring& fileName)
{
	if (argc == 2)
	{
		std::string str = argv[1]; 
		fileName = wstring(str.begin(), str.end());
		wifstream file(fileName);
		return file.is_open();
	}
	return true;
}

void Dialod(Dictionary& dictionary)
{
	wstring input;
	bool wordIsAdded = false;
	while (getline(wcin, input))
	{
		Trim(input);
		if (input.empty())
		{
			continue;
		}
		if (input == L"...")
		{
			break;
		}

		wstring translation = dictionary.Translate(input);
		if (translation.empty())
		{
			wcout << "������� ��� �" << input << "� �����������. ������� ������� ��� ������ ������ ��� ������.\n";
			wstring entry = input;
			Trim(input);
			if (getline(wcin, input) && !input.empty())
			{
				dictionary.Add(entry, input);
				wcout << "�" << entry << "� ��������� � ������� ��� �" << input << "�\n";
				wordIsAdded = true;
			}
		}
		else
		{
			wcout << translation << '\n';
		}
	}

	if (wordIsAdded)
	{
		cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
		wstring answer;
		if (!(getline(wcin, answer)))
		{
			return;
		}
		Trim(answer);
		if (!(answer == L"Y" || answer == L"y"))
		{
			return;
		}

		if (dictionary.InputFileIsSet())
		{
			cout << "������� �������� ����� ��� ���������� �������\n";
			while (getline(wcin, answer))
			{
				Trim(answer);
				if (!answer.empty())
				{
					break;
				}
			}
		}
		if (dictionary.Save(answer))
		{
			cout << "������� ���������\n";
		}
		else
		{
			cout << "������ ��� ����������\n";
		}
	}
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	wstring distionaryFileName;
	if (!ParseCommandLine(argc, argv, distionaryFileName))
	{
		return 1;
	}
	wcout << distionaryFileName;
	Dictionary dictionary(distionaryFileName);
	Dialod(dictionary);
	return 0;
}
