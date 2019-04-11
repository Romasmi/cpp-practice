#pragma once

#include "pch.h"

template <class T>
bool Between(const T a, const T min, const T max)
{
	return a >= min && a <= max;
}
