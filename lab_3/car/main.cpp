#include "pch.h"

#include "Car.h"
#include "CarControl.h"

using namespace std;

int main()
{
	Car car;
	CarControl carControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		try
		{
			if (!carControl.HandleCommand())
			{
				cout << carControl.GetLastError();
			}
		}
		catch (const exception& e)
		{
			cout << e.what() << '\n';
		}
	}

	return 0;
}
