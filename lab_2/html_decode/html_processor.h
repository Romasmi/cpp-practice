#pragma once
using namespace std;
string HtmlDecode(const string& html);
string HtmlEncode(const string& html);
void HtmlDecode(istream& input, ostream& output);
void HtmlEncode(istream& input, ostream& output);
