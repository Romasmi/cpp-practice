#include "pch.h"

bool IsSpasingSymbol(const unsigned int ch)
{
	return std::isspace(ch) || ch == '\n' || ch == '\r';
}

void LTrim(std::wstring& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](uint8_t ch) {
		return !IsSpasingSymbol(ch);
	}));
}

void RTrim(std::wstring& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), [](uint8_t ch) {
		return !IsSpasingSymbol(ch);
	}).base(),
		str.end());
}

void Trim(std::wstring& str)
{
	LTrim(str);
	RTrim(str);
}
