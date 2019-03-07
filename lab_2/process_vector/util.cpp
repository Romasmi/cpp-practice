#include "pch.h"
#include "util.h"

std::ostream& operator<<(std::ostream& out, std::vector<double> v)
{
	copy(v.begin(), v.end(), std::ostream_iterator<double>(out, " "));
	return out;
}