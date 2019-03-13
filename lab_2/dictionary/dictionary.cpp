#include "pch.h"

#include <fstream>
#include <iterator>
#include <map>
#include "dictionary.h"

using namespace std;

Dictionary::Dictionary()
	: externalDictionaryFileName("")
{
}

Dictionary::Dictionary(const std::string& fileName)
	: externalDictionaryFileName(fileName)
{
	ifstream input(this->externalDictionaryFileName);
	if (input.is_open())
	{
		this->Load(input);
	}
}

void Dictionary::Load(istream& in)
{
	string entry;
	string str;
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

void Dictionary::UnLoad(ostream& out) const
{	
	for (const auto &it : this->storage)
	{
		out << it.first;
		out << it.second;
	}
}

bool Dictionary::Save() const
{
	return this->Save("");
}

bool Dictionary::Save(const std::string& fileName) const
{
	const std::string outFileName = !this->externalDictionaryFileName.empty() ? this->externalDictionaryFileName : fileName;
	ofstream out(outFileName);
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

string Dictionary::Translate(const std::string& entry) const
{
	string translation;
	//pair<multimap<string, string>::iterator, multimap<string, string>::iterator> values;
	const auto values = this->storage.equal_range(this->ToLower(entry));
	for (auto it = values.first; it != values.second; ++it)
	{
		translation += it->second + ", ";
	}
	if (!translation.empty())
	{
		translation.erase(translation.size() - 2, 2);
	}
	return translation;
}

void Dictionary::Add(std::string entry, std::string translation)
{
	entry = ToLower(entry);
	translation = ToLower(translation);
	this->storage.insert({ entry, translation });
	if (entry != translation)
	{
		this->storage.insert({ translation, entry });
	}
}

std::string Dictionary::ToLower(const std::string& str) const
{
	string strToTransform = str;
	transform(strToTransform.begin(), strToTransform.end(), strToTransform.begin(), ::tolower);
	return strToTransform;
}
