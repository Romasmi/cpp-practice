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
			}
			catch (const CUrlParsingError& e)
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
			}
			catch (const CUrlParsingError& e)
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
			}
			catch (const CUrlParsingError& e)
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
			}
			catch (const CUrlParsingError& e)
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
			catch (const CUrlParsingError& e)
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
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("set incorrect document")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("vk.com", "music&photos", Protocol::HTTPS);
				REQUIRE(false);
			}
			catch (const CUrlParsingError& e)
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
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
}

SCENARIO("check getting of url entirely")
{
	WHEN("set url without port")
	{
		THEN("get url without port")
		{
			try
			{
				CHttpUrl url("http://vk.com/music");
				REQUIRE(url.GetURL() == "http://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
	WHEN("set url without default port")
	{
		THEN("get url without port")
		{
			try
			{
				CHttpUrl url("http://vk.com/music:80");
				REQUIRE(url.GetURL() == "http://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set url with not default port")
	{
		THEN("get url with port")
		{
			try
			{
				CHttpUrl url("http://vk.com/music:85");
				REQUIRE(url.GetURL() == "http://vk.com/music:85");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set url by passing parts without port")
	{
		THEN("get url without port")
		{
			try
			{
				CHttpUrl url("vk.com", "music");
				REQUIRE(url.GetURL() == "http://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
	WHEN("set url by passing parts with default port")
	{
		THEN("get url without port")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, 443);
				REQUIRE(url.GetURL() == "https://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set url by passing parts with no default port")
	{
		THEN("get url with port")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, 445);
				REQUIRE(url.GetURL() == "https://vk.com/music:445");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}
}

SCENARIO("check port bounrady values")
{
	WHEN("set min port value")
	{
		THEN("get correct url")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, 1);
				REQUIRE(url.GetURL() == "https://vk.com/music:1");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set min - 1 port value")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, 0);
				REQUIRE(url.GetURL() == "https://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}

	WHEN("set max port value")
	{
		THEN("get correct url")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, USHRT_MAX);
				REQUIRE(url.GetURL() == "https://vk.com/music:" + std::to_string(USHRT_MAX));
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(false);
			}
		}
	}

	WHEN("set max + 1 port value")
	{
		THEN("get exception")
		{
			try
			{
				CHttpUrl url("vk.com", "music", Protocol::HTTPS, USHRT_MAX + 1);
				REQUIRE(url.GetURL() == "https://vk.com/music");
			}
			catch (const CUrlParsingError& e)
			{
				cout << e.what() << endl;
				REQUIRE(true);
			}
		}
	}
}