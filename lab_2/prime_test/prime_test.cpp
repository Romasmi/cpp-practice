#include "pch.h"

#include "../prime/prime.h"

using namespace std;

TEST_CASE("Test primes generation")
{
	PrimeSet testSet;

	/*empty set*/
	REQUIRE(testSet == GeneratePrimeNumbersSet(0));

	/*one prime*/
	testSet = { 1 };
	REQUIRE(testSet == GeneratePrimeNumbersSet(1));

	/*some primes*/
	testSet = { 1, 2, 3, 5, 7, 11, 13 };
	REQUIRE(testSet == GeneratePrimeNumbersSet(13));

	unsigned int maxSetSize = 5761455;
	REQUIRE(maxSetSize == GeneratePrimeNumbersSet(100000000).size());
}