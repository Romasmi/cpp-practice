#pragma once

template <class T>
bool Between(const T& item, const T& min, const T& max)
{
	return item >= min && item <= max;
}