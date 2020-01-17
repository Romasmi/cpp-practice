#include "pch.h"

#include <iostream>
#include <string>

#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	string str;
	while (getline(cin, str) && !cin.eof())
	{
		try
		{
			CHttpUrl url(str);
			cout << "Protocol: " << url.ProtocolToString(url.GetProtocol()) << '\n'; 
			cout << "Domain: " << url.GetDomain() << '\n'; 
			cout << "Document: " << url.GetDocument() << '\n'; 
			cout << "Port: " << url.GetPort() << '\n'; 
		}
		catch (const exception &e)
		{
			cout << e.what() << '\n';
		}
	}
}
