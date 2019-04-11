#include "pch.h"

#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

using namespace std;

Dictionary::Dictionary()
{
}

Dictionary::Dictionary(const std::wstring& fileName)
	: m_externalDictionaryFileName(fileName)
{
	if (!m_externalDictionaryFileName.empty())
	{
		wifstream input(m_externalDictionaryFileName);
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
	for (const auto& it : m_storage)
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
	const std::wstring outFileName = !m_externalDictionaryFileName.empty() ? m_externalDictionaryFileName : fileName;
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
	auto search = m_storage.find(this->ToLower(entry));
	if (search != m_storage.end())
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
		translation[0] = ::toupper(translation[0]);
	}

	return translation;
}

void Dictionary::Add(std::wstring entry, std::wstring translation)
{
	if (!m_updated)
	{
		m_updated = true;
	}

	entry = ToLower(entry);
	translation = ToLower(translation);
	this->AddTranslation(entry, translation);
	this->AddTranslation(translation, entry);
}

void Dictionary::AddTranslation(std::wstring entry, std::wstring translation)
{
	auto search = m_storage.find(entry);
	if (search != m_storage.end())
	{
		search->second.insert(translation);
	}
	else
	{
		Translation translations = { translation };
		m_storage.insert({ entry, translations });
	}
}

std::wstring Dictionary::ToLower(const std::wstring& str) const
{
	wstring strToTransform = str;
	transform(strToTransform.begin(), strToTransform.end(), strToTransform.begin(), ::tolower);
	return strToTransform;
}

bool Dictionary::InputFileIsSet() const
{
	return m_externalDictionaryFileName.empty();
}

bool Dictionary::Updated() const
{
	return m_updated;
}