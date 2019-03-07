#include "pch.h"
#include "../../catch/catch.hpp"
#include "../html_decode/html_processor.h"
using namespace std;

TEST_CASE("Html endocing test")
{
	/*Encode empty string*/
	REQUIRE("" == HtmlEncode(""));

	/*Encode one symbol*/
	REQUIRE("&lt;" == HtmlEncode("<"));

	/*Encodde tag*/
	REQUIRE("&lt;html&gt;&lt;/html&gt;" == HtmlEncode("<html></html>"));
}

TEST_CASE("Html decoding test")
{
	/*empty string*/
	string str;
	REQUIRE(str == HtmlDecode(HtmlEncode(str)));

	/*One symbol*/
	str = "<";
	REQUIRE(str == HtmlDecode(HtmlEncode(str)));

	/*html tags*/
	str = "<h1>My title</h1><div>Hello world</div>";
	REQUIRE(str == HtmlDecode(HtmlEncode(str)));
}
