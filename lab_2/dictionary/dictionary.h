#include "pch.h"

#include <map>

class Dictionary
{
public:
	Dictionary();
	Dictionary(const std::wstring& fileName);
	std::wstring Translate(const std::wstring& entry) const;
	bool Save() const;
	bool Save(const std::wstring& out) const;
	void Add(std::wstring entry, std::wstring translation);

private:
	void Load(std::wistream &in);
	void UnLoad(std::wostream& out) const;
	std::wstring ToLower(const std::wstring& str) const;

	std::multimap<std::wstring, std::wstring> storage;
	const std::wstring externalDictionaryFileName;
};
