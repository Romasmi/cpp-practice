#include "pch.h"

#include <map>
#include <set>

using Translation = std::set<std::wstring>;
using DictionaryStorage = std::multimap<std::wstring, Translation>;

class Dictionary
{
public:
	Dictionary();
	Dictionary(const std::wstring& fileName);
	std::wstring Translate(const std::wstring& entry) const;
	bool Save() const;
	bool Save(const std::wstring& out) const;
	bool InputFileIsSet() const;
	void Add(std::wstring entry, std::wstring translation);

private:
	void Load(std::wistream &in);
	void UnLoad(std::wostream& out) const;
	std::wstring ToLower(const std::wstring& str) const;
	void AddTranslation(std::wstring entry, std::wstring translation);

	DictionaryStorage storage;
	const std::wstring externalDictionaryFileName;
};
