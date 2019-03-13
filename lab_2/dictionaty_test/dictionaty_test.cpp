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
	wstring entry = L"hello world";
	wstring translation = L"privet mir";

	dictionary.Add(entry, translation);
	REQUIRE(translation == dictionary.Translate(entry));
	REQUIRE(entry == dictionary.Translate(translation));

	/*Add more translation*/
	dictionary.Add(L"privet mir", L"hi mir");
	REQUIRE(L"hello world, hi mir" == dictionary.Translate(translation));
}

TEST_CASE("Test with external file")
{
	Dictionary dictionary("dictionary.txt");

	REQUIRE(L"privet" == dictionary.Translate(L"hello"));
	REQUIRE(L"hello" == dictionary.Translate(L"privet"));
}