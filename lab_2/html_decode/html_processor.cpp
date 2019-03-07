#include "pch.h"

#include "html_processor.h"
#include <vector>

using namespace std;

const struct
{
	char start = '&';
	char end = ';';
} HTML_CODE_DELIMITES;


using HtmlEntityCode = std::pair<char, std::string>;

const std::vector<HtmlEntityCode> HTML_ENTITIES_CODES = {
	{ '"', "quot" },
	{ '\'', "apos" },
	{ '<', "lt" },
	{ '>', "gt" },
	{ '&', "amp" }
};

std::string GetEntityCode(const char entity)
{
	for (HtmlEntityCode item : HTML_ENTITIES_CODES)
	{
		if (entity == item.first)
		{
			return item.second;
		}
	}
	return "";
}

char GetEntityByCode(const string &code)
{
	for (HtmlEntityCode item : HTML_ENTITIES_CODES)
	{
		if (code == item.second)
		{
			return item.first;
		}
	}
	return '\0';
}

std::string HtmlEncode(const std::string str)
{
	string processedString;
	for (char ch : str)
	{
		std::string code = GetEntityCode(ch);
		if (!code.empty())
		{
			processedString.append(HTML_CODE_DELIMITES.start + code + HTML_CODE_DELIMITES.end);
		}
		else
		{
			processedString.append(string(1, ch));
		}
	}
	return processedString;
}

std::string HtmlDecode(const std::string str)
{
	string processedString;
	string entityCode;
	bool inEntity = false;
	for (char ch : str)
	{
		if (ch == HTML_CODE_DELIMITES.start)
		{
			entityCode.clear();
			inEntity = true;
			continue;
		}
		if (ch == HTML_CODE_DELIMITES.end)
		{
			processedString += GetEntityByCode(entityCode);
			inEntity = false;
			continue;
		}
		if (inEntity)
		{
			entityCode += ch;
		}
		else
		{
			processedString += ch;
		}
	}

	return processedString;
}
