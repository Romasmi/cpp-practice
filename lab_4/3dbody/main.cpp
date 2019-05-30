#include "pch.h"

#include "CBodyControl.h"

using namespace std;

int main()
{
	CBodyControl control(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		try
		{
			if (!control.HandleCommand())
			{
				cout << control.GetLastError() << '\n';
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << '\n';
		}
	}

	return 0;
}
