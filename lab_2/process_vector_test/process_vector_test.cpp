#include "pch.h"

#include "../process_vector/process_vector.h"

using namespace std;

vector<double> in = {};
vector<double> out = {};

TEST_CASE("Process vector test")
{
	/*Empty input*/
	in = {};
	out = {};
	REQUIRE(out == GetProcesedVector(in));

	/*One non-negative number*/
	in = { 1 };
	out = { 0 };
	REQUIRE(out == GetProcesedVector(in));

	/*One negative number*/
	in = { -1 };
	out = { -1 };
	REQUIRE(out == GetProcesedVector(in));

	/*Two numbers*/
	in = { 1, 2 };
	out = { -2, 4 };
	REQUIRE(out == GetProcesedVector(in));

	/* Some elements, sum of non-negative`s is 7*/
	in = { -1, 2, 4, 1, -2 };
	out = { -8, 4, -3, 2, -9 };
	REQUIRE(out == GetProcesedVector(in));
}
