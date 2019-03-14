#include "pch.h"

#include "../prime/prime.h"

using namespace std;

TEST_CASE("Test primes generation")
{
	PrimeSet testSet;

	/*empty set*/
	REQUIRE(testSet == GeneratePrimeNumbersSet(0));

	/*one prime*/
	testSet = { 2 };
	REQUIRE(testSet == GeneratePrimeNumbersSet(2));

	/*some primes*/
	testSet = { 2, 3, 5, 7, 11, 13 };
	REQUIRE(testSet == GeneratePrimeNumbersSet(13));

	REQUIRE(500 == GeneratePrimeNumbersSet(3571).size());
	REQUIRE(5761455 == GeneratePrimeNumbersSet(100000000).size());
}