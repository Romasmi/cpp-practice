#include "pch.h"

#include <fstream>
#include <iterator>
#include <map>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary()
{}

Dictionary::Dictionary(const std::wstring& fileName)
	: externalDictionaryFileName(fileName)
{
	wifstream input(this->externalDictionaryFileName);
	if (input.is_open())
	{
		this->Load(input);
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
	for (const auto &it : this->storage)
	{
		out << it.first;
		out << it.second;
	}
}

bool Dictionary::Save() const
{
	const wstring empty;
	return this->Save(empty);
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
	//pair<multimap<wstring, wstring>::iterator, multimap<wstring, wstring>::iterator> values;
	const auto values = this->storage.equal_range(this->ToLower(entry));
	const wstring translationSeparator = L", ";
	for (auto it = values.first; it != values.second; ++it)
	{
		translation += it->second + translationSeparator;
	}
	if (!translation.empty())
	{
		translation.erase(translation.size() - 2, 2);
	}
	return translation;
}

void Dictionary::Add(std::wstring entry, std::wstring translation)
{
	entry = ToLower(entry);
	translation = ToLower(translation);
	this->storage.insert({ entry, translation });
	if (entry != translation)
	{
		this->storage.insert({ translation, entry });
	}
}

std::wstring Dictionary::ToLower(const std::wstring& str) const
{
	wstring strToTransform = str;
	transform(strToTransform.begin(), strToTransform.end(), strToTransform.begin(), ::tolower);
	return strToTransform;
}