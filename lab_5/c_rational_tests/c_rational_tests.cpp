#include "pch.h"

#include "../c_rational/CRational.h"
#include <iostream>
#include <sstream>

using namespace std;

SCENARIO("rational number can be constructed by inputing 0, 1 or 2 parameters")
{
	WHEN("to input 0 parameters")
	{
		CRational n1;

		THEN("it creates number = 0/1 or 0")
		{
			REQUIRE(n1.GetNumerator() == 0);
			REQUIRE(n1.GetDenominator() == 1);
			REQUIRE(n1.ToDouble() == 0);
		}
	}

	WHEN("to input 1 parameter")
	{
		CRational n1(10);

		THEN("it creates number = 10/1 or 10")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
			REQUIRE(n1.ToDouble() == 10);
		}
	}

	GIVEN("2 parameters for input")
	{
		WHEN("to input 2 whole numbers as parameters")
		{
			CRational n1(10, 5);

			THEN("it creates number = 10/5 or 2")
			{
				REQUIRE(n1.GetNumerator() == 10);
				REQUIRE(n1.GetDenominator() == 5);
				REQUIRE(n1.ToDouble() == 2);
			}
		}

		WHEN("to input 1 whole number and 0 as parameters")
		{
			THEN("it throw exception")
			{
				try
				{
					CRational n1(10, 0);
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					cout << e.what() << '\n';
					REQUIRE(true);
				}
			}
		}
	}
}

SCENARIO("check convertion to double")
{
	WHEN("convert  3/5 ot double")
	{
		CRational n(3, 5);
		THEN("get 0.6")
		{
			REQUIRE(n.ToDouble() == 0.6);
		}
	}
}

SCENARIO("check unary + and -")
{
	CRational n(10, 5);

	WHEN("apply - to n")
	{
		n = -n;

		THEN("it changes numerator sign")
		{
			REQUIRE(n.GetNumerator() == -10);
			REQUIRE(n.GetDenominator() == 5);
		}
	}

	WHEN("apply + to n")
	{
		n = +n;

		THEN("it doesn't changes numerator sign")
		{
			REQUIRE(n.GetNumerator() == 10);
			REQUIRE(n.GetDenominator() == 5);
		}
	}
}

SCENARIO("check binary +")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("adjuct n2 to n1")
	{
		n1 = n1 + n2;

		THEN("it increase n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 17);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("adjuct 5 to n1")
	{
		n1 = n1 + 5;

		THEN("it increases n1 on 5")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("adjuct n1 to 5")
	{
		n1 = 5 + n1;

		THEN("it return 5 + n1 = 35/5 = 7/1")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check +=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("adjuct n2 to n1")
	{
		n1 += n2;

		THEN("it increase n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 17);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("adjuct 5 to n1")
	{
		n1 += 5;

		THEN("it increases n1 on 5")
		{
			REQUIRE(n1.GetNumerator() == 7);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary -")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("substruct n2 from n1")
	{
		n1 = n1 - n2;

		THEN("it descrease n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 11);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("substruct 5 from n1")
	{
		n1 = n1 - 5;

		THEN("it decrease n1 on 5")
		{
			REQUIRE(n1.GetNumerator() == -3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("substruct n1 from 5/3")
	{
		n1 = 5 - n1;

		THEN("it return 5 - n1 = 15/5 = 3/1")
		{
			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check -=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("substruct n2 from n1")
	{
		n1 -= n2;

		THEN("it descrease n1 on n2")
		{
			REQUIRE(n1.GetNumerator() == 11);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("substruct 5 from n1")
	{
		n1 -= 5;

		THEN("it decrease n1 on 5")
		{
			REQUIRE(n1.GetNumerator() == -3);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary *")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("multiply n1 and n2")
	{
		n1 = n1 * n2;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 6);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("multiply 5 and n1")
	{
		n1 = 5 * n1;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}

	WHEN("multiply n1 and 5")
	{
		n1 = n1 * 5;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary *=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("multiply n1 and n2")
	{
		n1 *= n2;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 6);
			REQUIRE(n1.GetDenominator() == 7);
		}
	}

	WHEN("multiply n1 and 5")
	{
		n1 *= 5;

		THEN("it return their multiplication")
		{
			REQUIRE(n1.GetNumerator() == 10);
			REQUIRE(n1.GetDenominator() == 1);
		}
	}
}

SCENARIO("check binary /")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("devide n1 by n2")
	{
		n1 = n1 / n2;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 14);
			REQUIRE(n1.GetDenominator() == 3);
		}
	}

	WHEN("devide 5 by n1")
	{
		n1 = 5 / n1;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 5);
			REQUIRE(n1.GetDenominator() == 2);
		}
	}

	WHEN("devide n1 by 5")
	{
		n1 = n1 / 5;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 2);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check /=")
{
	CRational n1(10, 5);
	CRational n2(3, 7);

	WHEN("devide n1 by n2")
	{
		n1 /= n2;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 14);
			REQUIRE(n1.GetDenominator() == 3);
		}
	}

	WHEN("devide n1 by 5")
	{
		n1 /= 5;

		THEN("it return their quotient")
		{
			REQUIRE(n1.GetNumerator() == 2);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check boolean ==")
{
	WHEN("check equality of 1/2 and 1/2")
	{
		CRational n1(1, 2);
		CRational n2(1, 2);

		THEN("it returns true")
		{
			REQUIRE(n1 == n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check equality of 1/2 and 2/3")
	{
		CRational n1(1, 2);
		CRational n2(2, 3);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n1 == n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 3);
		}
	}

	WHEN("check equality of 4/1 and 4")
	{
		CRational n(4, 1);

		THEN("it returns true")
		{
			REQUIRE(n == 4);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}

	WHEN("check equality of 4 and 4/1")
	{
		CRational n(4, 1);

		THEN("it returns true")
		{
			REQUIRE(4 == n);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check boolean !=")
{
	WHEN("check inequality of 1/2 and 1/2")
	{
		CRational n1(1, 2);
		CRational n2(1, 2);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n1 != n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 1);
			REQUIRE(n2.GetDenominator() == 2);
		}
	}

	WHEN("check inequality of 1/2 and 2/3")
	{
		CRational n1(1, 2);
		CRational n2(2, 3);

		THEN("it returns true")
		{
			REQUIRE(n1 != n2);

			REQUIRE(n1.GetNumerator() == 1);
			REQUIRE(n1.GetDenominator() == 2);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 3);
		}
	}

	WHEN("check inequality of 4/1 and 4")
	{
		CRational n(4, 1);

		THEN("it returns false")
		{
			REQUIRE_FALSE(n != 4);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}

	WHEN("check inequality of 4 and 4/1")
	{
		CRational n(4, 1);

		THEN("it returns false")
		{
			REQUIRE_FALSE(4 != n);

			REQUIRE(n.GetNumerator() == 4);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}

SCENARIO("check <")
{
	WHEN("check < of 3/5 and 2/4")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE_FALSE(n1 < n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 4);
		}
	}

	WHEN("check < of 3/5 and 4")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);

			REQUIRE(n1 < 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}

	WHEN("check < of 4 and 3/5")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(4 < n1);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check >")
{
	WHEN("check > of 3/5 and 2/4")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE(n1 > n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 4);
		}
	}

	WHEN("check > of 3/5 and 4")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(n1 > 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}

	WHEN("check > of 4 and 3/5")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE(4 > n1);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check >=")
{
	WHEN("check >= of 3/5 and 2/4")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE(n1 >= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 4);
		}
	}

	WHEN("check >= of 3/5 and 6/10")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(6, 10);

			REQUIRE(n1 >= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 6);
			REQUIRE(n2.GetDenominator() == 10);
		}
	}

	WHEN("check >= of 3/5 and 4")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(n1 >= 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}

	WHEN("check >= of 4 and 3/5")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);

			REQUIRE(4 >= n1);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check <=")
{
	WHEN("check <= of 3/5 and 2/4")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);
			CRational n2(2, 4);

			REQUIRE_FALSE(n1 <= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 2);
			REQUIRE(n2.GetDenominator() == 4);
		}
	}

	WHEN("check <= of 3/5 and 6/10")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);
			CRational n2(6, 10);

			REQUIRE(n1 <= n2);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
			REQUIRE(n2.GetNumerator() == 6);
			REQUIRE(n2.GetDenominator() == 10);
		}
	}

	WHEN("check <= of 3/5 and 4")
	{
		THEN("it returns true")
		{
			CRational n1(3, 5);

			REQUIRE(n1 <= 4);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}

	WHEN("check <= of 4 and 3/5")
	{
		THEN("it returns false")
		{
			CRational n1(3, 5);

			REQUIRE_FALSE(4 <= n1);

			REQUIRE(n1.GetNumerator() == 3);
			REQUIRE(n1.GetDenominator() == 5);
		}
	}
}

SCENARIO("check >>")
{
	WHEN("try to get from rational number from correct input")
	{
		istringstream input("3/5");
		CRational n;

		THEN("get rational number")
		{
			input >> n;
			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 5);
		}
	}

	WHEN("try to get from rational number from incorrect input")
	{
		istringstream input("3 5");
		CRational n;

		THEN("get exception")
		{
			try
			{
				input >> n;
				REQUIRE(false);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << '\n';
				REQUIRE(true);
			}
		}
	}
}

SCENARIO("check <<")
{
	WHEN("apply << for 3/5")
	{
		ostringstream output;
		CRational n(3, 5);

		THEN("get rational 3/5 in output")
		{
			output << n;
			REQUIRE(output.str() == "3/5");

			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 5);
		}
	}

	WHEN("apply << for 3")
	{
		ostringstream output;
		CRational n(3);

		THEN("get rational 3/1 in output")
		{
			output << n;
			REQUIRE(output.str() == "3/1");

			REQUIRE(n.GetNumerator() == 3);
			REQUIRE(n.GetDenominator() == 1);
		}
	}
}