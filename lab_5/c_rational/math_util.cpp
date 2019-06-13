#include "pch.h"

#include "math_util.h"
#include <math.h>

using namespace std;

void swap(int& a, int& b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int GCD(int a, int b)
{
	while (b)
	{
		a %= b;
		swap(a, b);
	}
	return a;
}

int LCM(int a, int b)
{
	int gcd = GCD(a, b);
	if (gcd == 0)
	{
		return 0;
	}

	return abs(a * b) / GCD(a, b);
}
