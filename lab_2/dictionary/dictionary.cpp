#include "pch.h"

#include "dictionary.h"
#include <fstream>
#include <iterator>
#include <map>
#include <locale>
#include <functional>
#include <iostream>

using namespace std;

Dictionary::Dictionary()
{
}

Dictionary::Dictionary(const std::wstring& fileName)
	: externalDictionaryFileName(fileName)
{
	if (!this->externalDictionaryFileName.empty())
	{
		wifstream input(this->externalDictionaryFileName);
		if (input.is_open())
		{
			this->Load(input);
		}
	}
}

void Dictionary::Load(wistream& in)
{
	wstring entry;
	wstring str;
	bool isEven = false;
	while (getline(in, str))
	{
		if (!isEven)
		{
			entry = str;
			isEven = true;
		}
		else
		{
			this->Add(entry, str);
			isEven = false;
		}
	}
}

void Dictionary::UnLoad(wostream& out) const
{
	for (const auto& it : this->storage)
	{
		for (auto secondIt : it.second)
		{
			out << it.first << '\n';
			out << secondIt << '\n';
		}
	}
}

bool Dictionary::Save() const
{
	return this->Save(L"");
}

bool Dictionary::Save(const std::wstring& fileName) const
{
	const std::wstring outFileName = !this->externalDictionaryFileName.empty() ? this->externalDictionaryFileName : fileName;
	wofstream out(outFileName);
	if (out.is_open())
	{
		this->UnLoad(out);
		return true;
	}
	else
	{
		return false;
	}
}

wstring Dictionary::Translate(const std::wstring& entry) const
{
	wstring translation;
	const wstring translationSeparator = L", ";
	auto search = this->storage.find(this->ToLower(entry));
	if (search != this->storage.end())
	{
		for (auto it : search->second)
		{
			translation += it + translationSeparator;
		}
	}

	if (!translation.empty())
	{
		translation.erase(translation.size() - 2, 2);
	}

	if (!translation.empty())
	{
		translation[0] = std::bind2nd(std::ptr_fun(&std::toupper<wchar_t>), std::locale("ru_RU.UTF-8"))(translation[0]);
	}

	return translation;
}

void Dictionary::Add(std::wstring entry, std::wstring translation)
{
	entry = ToLower(entry);
	translation = ToLower(translation);
	this->AddTranslation(entry, translation);
	this->AddTranslation(translation, entry);
}

void Dictionary::AddTranslation(std::wstring entry, std::wstring translation)
{
	auto search = this->storage.find(entry);
	if (search != this->storage.end())
	{
		search->second.insert(translation);
	}
	else
	{
		Translation translations = { translation };
		this->storage.insert({ entry, translations });
	}
}

std::wstring Dictionary::ToLower(const std::wstring& str) const
{
	wstring strToTransform = str;
	transform(strToTransform.begin(), strToTransform.end(), strToTransform.begin(), std::bind2nd(std::ptr_fun(&std::tolower<wchar_t>), std::locale("ru_RU.UTF-8")));
	return strToTransform;
}

bool Dictionary::InputFileIsSet() const
{
	return this->externalDictionaryFileName.empty();
}