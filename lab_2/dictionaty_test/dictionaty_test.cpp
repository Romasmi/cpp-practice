#include "pch.h"

#include <locale>
#include <functional>
#include <iostream>

#include "../dictionary/dictionary.h"

	
using namespace std;


TEST_CASE("Test dictionary without external file")
{
	Dictionary dictionary;

	/*translate empty string*/
	REQUIRE(L"" == dictionary.Translate(L""));

	/*translate unknown phrase*/
	REQUIRE(L"" == dictionary.Translate(L"Hello world"));

	/*Add and translate*/
	wstring entry = L"Hello world";
	wstring translation = L"Privet mir";

	dictionary.Add(entry, translation);
	REQUIRE(translation == dictionary.Translate(entry));
	REQUIRE(entry == dictionary.Translate(translation));

	/*Add more translation*/
	dictionary.Add(L"Privet mir", L"hi world");
	REQUIRE(L"Hello world, hi world" == dictionary.Translate(translation));
}

TEST_CASE("Test with external file")
{
	Dictionary dictionary(L"dictionary.txt");
	REQUIRE(L"Privet" == dictionary.Translate(L"Hello"));
	REQUIRE(L"Hello" == dictionary.Translate(L"privet"));

	/*Add and save*/
	dictionary.Add(L"privet", L"hi");
	dictionary.Save();

	/*Open saved dictionary*/
	Dictionary dictoonary2(L"dictionary.txt");
	REQUIRE(L"Hello, hi" == dictionary.Translate(L"privet"));
}