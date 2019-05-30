#include "pch.h"

#include "util.h"

std::vector<std::string> Split(const std::string& str)
{
	std::istringstream strStream(str);
	std::vector<std::string> lineVector((std::istream_iterator<std::string>(strStream)), std::istream_iterator<std::string>());
	return lineVector;
}