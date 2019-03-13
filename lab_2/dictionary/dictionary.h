#include "pch.h"

#include <map>

class Dictionary
{
public:
	Dictionary();
	Dictionary(const std::string& fileName);
	std::string Translate(const std::string& entry) const;
	bool Save() const;
	bool Save(const std::string& out) const;
	void Add(std::string entry, std::string translation);

private:
	void Load(std::istream &in);
	void UnLoad(std::ostream& out) const;
	std::string ToLower(const std::string& str) const;

	std::multimap<std::string, std::string> storage;
	const std::string externalDictionaryFileName;
};
