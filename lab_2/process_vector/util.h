#pragma once

#include "pch.h"

std::ostream& operator<<(std::ostream& out, std::vector<double> v);

template <class T>
std::vector<T> LineToVector(std::string& line)
{
	std::istringstream stringIterator(line);
	return std::vector<T>(std::istream_iterator<T>(stringIterator), std::istream_iterator<T>());
}