#include "pch.h"

#include "html_processor.h"
#include <vector>

using namespace std;

const struct
{
	char start = '&';
	char end = ';';
} HTML_CODE_DELIMITES;

const char NOT_FOUND_ENTITY = '\0';

using HtmlEntityCode = std::pair<char, std::string>;

const std::vector<HtmlEntityCode> HTML_ENTITIES_CODES = {
	{ '"', "&quot;" },
	{ '\'', "&apos;" },
	{ '<', "&lt;" },
	{ '>', "&gt;" },
	{ '&', "&amp;" }
};

std::string GetEntityCode(const char entity)
{
	for (const HtmlEntityCode& item : HTML_ENTITIES_CODES)
	{
		if (entity == item.first)
		{
			return item.second;
		}
	}
	return "";
}

char GetEntityByCode(const string& code)
{
	for (const HtmlEntityCode& item : HTML_ENTITIES_CODES)
	{
		if (code == item.second)
		{
			return item.first;
		}
	}
	return '\0';
}

std::string HtmlEncode(const std::string& str)
{
	string processedString;
	for (const char ch : str)
	{
		const string code = GetEntityCode(ch);
		if (!code.empty())
		{
			processedString.append(code);
		}
		else
		{
			processedString += ch;
		}
	}
	return processedString;
}

std::string HtmlDecode(const std::string& str)
{
	string processedString;
	string entityCode;
	bool inEntity = false;
	for (const char ch : str)
	{
		if (ch == HTML_CODE_DELIMITES.start)
		{
			entityCode = ch;
			inEntity = true;
		}
		else if (ch == HTML_CODE_DELIMITES.end)
		{
			entityCode += ch;
			const char entity = GetEntityByCode(entityCode);
			if (entity != NOT_FOUND_ENTITY)
			{
				processedString += entity;
			}
			else
			{
				processedString += entityCode;
			}
			inEntity = false;
		}
		else if (inEntity)
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
