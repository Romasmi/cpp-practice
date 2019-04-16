#include "pch.h"

#include "Car.h"
#include "CarControl.h"

using namespace std;

int main()
{
	try
	{
		Car car;
		CarControl carControl(car, cin, cout);

		while (!cin.eof() && !cin.fail())
		{
			if (!carControl.HandleCommand())
			{
				cout << carControl.GetLastError();
			}
		}
		return 0;
	}
	catch (const exception& e)
	{
		cout << e.what() << '\n';
		return 1;
	}
	return 0;
}
