#include "pch.h"

#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include "util.h"

#include <iostream>
#include <locale>
#include <map>
#include <regex>

using namespace std;

const map<Protocol, string> PROTOCOL_IN_STRING = {
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" },
};

const map<string, Protocol> STRING_TO_PROTOCOL = {
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS },
};

const map<Protocol, Port> PROTOCOL_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
};

const regex URL_MASK("(^https?)://([a-zA-Z0-9-.]+)(/+[a-zA-Z0-9-./]*)*(:{1}[0-9]*)?$");

CHttpUrl::CHttpUrl(std::string const& url) try
{
	smatch urlParts;
	if (!regex_match(url, urlParts, URL_MASK))
	{
		throw CUrlParsingError("Invalid url");
	}
	ssub_match urlPart = urlParts[1];
	m_protocol = STRING_TO_PROTOCOL.at(urlPart.str());
	urlPart = urlParts[2];
	m_domain = urlPart.str();
	urlPart = urlParts[3];
	m_document = urlPart.str();
	urlPart = urlParts[4];
	if (urlPart.str().size() > 0)
	{
		const string port = urlPart.str().substr(1);
		m_port = static_cast<Port>(stoi(port));
	}
	else
	{
		m_port = PROTOCOL_PORT.at(m_protocol);
	}
}
catch (const exception& e)
{
	throw e;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document,
	Protocol protocol) try
{
	string url = PROTOCOL_IN_STRING.at(protocol) + "://" + domain + GetProcessedDocument(document);
	CHttpUrl parsedUrl(url);

	m_protocol = parsedUrl.GetProtocol();
	m_domain = parsedUrl.GetDomain();
	m_document = parsedUrl.GetDocument();
	m_port = parsedUrl.GetPort();
}
catch (const invalid_argument& e)
{
	throw e;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document,
	Protocol protocol, Port port) 
	try
{
	CHttpUrl parsedUrl(domain, document, protocol);
	m_protocol = parsedUrl.GetProtocol();
	m_domain = parsedUrl.GetDomain();
	m_document = parsedUrl.GetDocument();
	m_port = port;
}
catch (const CUrlParsingError& e)
{
	throw e;
}

std::string CHttpUrl::GetURL() const
{
	string url = GetProtocolInString() + "://" + GetDomain() + GetDocument();
	if (GetProtocol() != GetDefaultProtocolPort())
	{
		url += ':' + GetPort();
	}
	return url;
}

std::string CHttpUrl::GetDomain() const { return m_domain; }

std::string CHttpUrl::GetDocument() const { return m_document; }

Protocol CHttpUrl::GetProtocol() const { return m_protocol; }

Port CHttpUrl::GetPort() const { return m_port; }

std::string CHttpUrl::GetProtocolInString() const
{
	return PROTOCOL_IN_STRING.at(m_protocol);
}

Port CHttpUrl::GetDefaultProtocolPort() const
{
	return PROTOCOL_PORT.at(m_protocol);
}

string CHttpUrl::GetProcessedDocument(const string& document) const
{
	return document[0] == '/' ? document : '/' + document;
}
