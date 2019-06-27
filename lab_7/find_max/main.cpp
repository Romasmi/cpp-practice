#include "pch.h"

#include "util.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	const char* name = "b";
	const char* surname = "a";

	if (strcmp(name, surname) < 0)
	{
		cout << name;
	}
	else
	{
		cout << surname;
	}

}
