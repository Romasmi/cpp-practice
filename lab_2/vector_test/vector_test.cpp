#include "stdafx.h"
#include "../../lab_2/vector/vector.h"
using namespace std;

TEST_CASE("Empty input vector")
{
	BaseVector emptyVector = {};
	BaseVector secondEmptyVector = {};
	ProcessVector(emptyVector);
	CHECK(emptyVector == secondEmptyVector);
}

TEST_CASE("Correct vector")
{
	BaseVector nonProcessedVector = {5, 10, 10, 5};
	BaseVector processedVector = {1, 2, 2, 1};
	ProcessVector(nonProcessedVector);
	CHECK(nonProcessedVector == processedVector);
}