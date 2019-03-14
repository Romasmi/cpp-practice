#include "pch.h"

#include "../dictionary/dictionary.h"
	
using namespace std;

TEST_CASE("Test dictionary without external file")
{
	Dictionary dictionary;

	/*translate empty string*/
	REQUIRE("" == dictionary.Translate(""));

	/*translate unknown phrase*/
	REQUIRE("" == dictionary.Translate("Hello world"));

	/*Add and translate*/
	string entry = "Hello world";
	string translation = "Privet mir";

	dictionary.Add(entry, translation);
	REQUIRE(translation == dictionary.Translate(entry));
	REQUIRE(entry == dictionary.Translate(translation));

	/*Add more translation*/
	dictionary.Add("Privet mir", "hi mir");
	REQUIRE("Hello world, hi mir" == dictionary.Translate(translation));

	dictionary.Add("кошка", "cat");
	REQUIRE("кошкаа" == dictionary.Translate("cat"));
}

TEST_CASE("Test with external file")
{
	Dictionary dictionary("dictionary.txt");

	REQUIRE("Privet" == dictionary.Translate("hello"));
	REQUIRE("Hello" == dictionary.Translate("privet"));
}