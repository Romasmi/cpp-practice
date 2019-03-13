#include "pch.h"

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
	dictionary.Add(L"privet mir", L"hi mir");
	REQUIRE(L"Hello world, hi mir" == dictionary.Translate(translation));
}

TEST_CASE("Test with external file")
{
	Dictionary dictionary("dictionary.txt");

	REQUIRE(L"Privet" == dictionary.Translate(L"hello"));
	REQUIRE(L"Hello" == dictionary.Translate(L"privet"));
}