#include "pch.h"

#include "CUrlParsingError.h"
#include <string>

using namespace std;

CUrlParsingError::CUrlParsingError(const string &error)
	:invalid_argument(error) 
{

}
