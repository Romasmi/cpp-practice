#include "pch.h"

#include "../http_url/CHttpUrl.h"
#include "../http_url/CUrlParsingError.h"
#include <iostream>
#include <stdexcept>

using namespace std;

SCENARIO("check url parsing")
{
	WHEN("url is incorrect")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("hello world");
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("protocol is not set")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("vk.com");
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("domain is not set")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("http://");
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("protocol is incorrect")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("http2://vk.com");
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("set correct url just with domain")
	{
		THEN("it's possible to get parts of url and default port")
		{
			try
			{
				CHttpUrl url("https://vk.com");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetDomain() == "vk.com");
				REQUIRE(url.GetDocument() == "");
				REQUIRE(url.GetPort() == 443);
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set correct url without port")
	{
		THEN("it's possible to get parts of url and default port")
		{
			try
			{
				CHttpUrl url("https://vk.com/friend/favourite");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetDomain() == "vk.com");
				REQUIRE(url.GetDocument() == "/friend/favourite");
				REQUIRE(url.GetPort() == 443);
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set correct url with not default port")
	{
		THEN("it's possible to get parts of url")
		{
			try
			{
				CHttpUrl url("https://vk.com/friend/favourite:80");
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetDomain() == "vk.com");
				REQUIRE(url.GetDocument() == "/friend/favourite");
				REQUIRE(url.GetPort() == 80);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
}

SCENARIO("set url by passing parts of url")
{
	WHEN("set incorrect domain")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("/vk*com", "music", Protocol::HTTPS);
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("set document domain")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("vk.com", "music&photos", Protocol::HTTPS);
				REQUIRE(false);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("set correct parts of url")
	{
		THEN("get correct url")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, 80);
				REQUIRE(url.GetProtocol() == Protocol::HTTPS);
				REQUIRE(url.GetDomain() == "vk.com");
				REQUIRE(url.GetDocument() == "/music");
				REQUIRE(url.GetPort() == 80);
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
}