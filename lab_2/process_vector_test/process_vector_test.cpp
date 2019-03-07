#include "pch.h"

#include "../process_vector/process_vector.h"

using namespace std;

TEST_CASE("Process vector test")
{
	vector<double> in = {};
	vector<double> out = {};

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

	/* Some elements to input, sum of non-negative`s is 7*/
	in = { -1, 2, 4, 1, -2 };
	out = { -8, 4, -3, 2, -9 };
	REQUIRE(out == GetProcesedVector(in));
}

TEST_CASE("Load vector test")
{
	istringstream inputStream;
	vector<double> in = {};
	vector<double> out = {};

	/*Empty string*/
	inputStream.str("");
	LoadVectorFromStream(in, inputStream);
	out = {};
	REQUIRE(out == in);

	/*Incorrect one symbol for input*/
	inputStream.clear();
	inputStream.str("a");
	LoadVectorFromStream(in, inputStream);
	out = {};
	REQUIRE(out == in);

	/*Incorrect some symbols for input*/
	inputStream.clear();
	inputStream.str("a bc def");
	LoadVectorFromStream(in, inputStream);
	out = {};
	REQUIRE(out == in);

	/*correct one symbol for input*/
	inputStream.clear();
	inputStream.str("1");
	LoadVectorFromStream(in, inputStream);
	out = {1};
	REQUIRE(out == in);

	/*correct some symbols for input*/
	inputStream.clear();
	inputStream.str("1 2 3");
	LoadVectorFromStream(in, inputStream);
	out = { 1, 2, 3 };
	REQUIRE(out == in);
}
