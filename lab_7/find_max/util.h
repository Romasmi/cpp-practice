#pragma once

#include <vector>
#include <functional>

template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.size() == 0)
	{
		return false;
	}

	maxValue = arr.front();
	for (const T& item : arr)
	{
		if (item > maxValue)
		{
			maxValue = item;
		}
	}
	return true;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr,
	const char*& maxValue)
{
	if (arr.size() == 0)
	{
		return false;
	}

	maxValue = arr.front();
	for (const char* item : arr)
	{
		if (strcmp(maxValue, item) < 0)
		{
			maxValue = item;
		}
	}

	return true;
}

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const & less)
{
	if (arr.size() == 0)
	{
		return false;
	}

	maxValue = arr.front();
	for (const T& item : arr)
	{
		if (less(maxValue, item))
		{
			maxValue = item;
		}
	}
	return true;
}