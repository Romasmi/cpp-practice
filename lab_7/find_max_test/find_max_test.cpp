#include "pch.h"

#include "../find_max/util.h"
#include <string>
#include <vector>

using namespace std;

TEST_CASE("test FindMax with empty vector")
{
	vector<int> v;
	int maxValue;

	REQUIRE_FALSE(FindMax(v, maxValue));
}

TEST_CASE("test FindMax with int vector")
{
	vector<int> v({ 1, 3, 4, -5, 6 });
	int maxValue;

	REQUIRE(FindMax(v, maxValue));
	REQUIRE(maxValue == 6);
}

TEST_CASE("test FindMax with float vector")
{
	vector<float> v({ 1.1f, 3.225f, 4.11f, -5.11f, 6.75f });
	float maxValue;

	REQUIRE(FindMax(v, maxValue));
	REQUIRE(maxValue == 6.75);
}

TEST_CASE("test FindMax with string vector")
{
	vector<string> v({ "a", "b", "c", "ab", "abc" });
	string maxValue;

	REQUIRE(FindMax(v, maxValue));
	REQUIRE(maxValue == "c");
}

TEST_CASE("test FindMax with c_string vector")
{
	vector<const char*> v({ "a", "b", "c", "ab", "abc" });
	const char* maxValue;

	REQUIRE(FindMax(v, maxValue));
	REQUIRE(maxValue == "c");
}

struct Student
{
	string name;
	int height;
	int weight;
};

bool StudentsAreEqual(const Student& s1, const Student& s2)
{
	return s1.name == s2.name && s1.height == s2.height && s1.weight == s2.weight;
}

bool LessByHeight(const Student& s1, const Student& s2)
{
	return s1.height < s2.height;
}

bool LessByWeight(const Student& s1, const Student& s2)
{
	return s1.weight < s2.weight;
}

SCENARIO("test FindMaxEx with Less function and vector of students")
{
	const Student Vasya = { "Vasya", 175, 65 };
	const Student Nike = { "Nike", 168, 92 };
	const Student Mikki = { "Mikki", 199, 49 };
	const Student Alex = { "Alex", 169, 82 };

	vector<Student> students({ Vasya,
		Nike,
		Mikki,
		Alex });

	WHEN("try to find the talles student")
	{
		THEN("get the talles student")
		{
			Student maxHeightStudent;
			REQUIRE(FindMaxEx(students, maxHeightStudent, LessByHeight));
			REQUIRE(StudentsAreEqual(maxHeightStudent, Mikki));
		}
	}

	WHEN("try to find the most heavy student")
	{
		THEN("get the most heavy student")
		{
			Student maxWeightStudent;
			REQUIRE(FindMaxEx(students, maxWeightStudent, LessByWeight));
			REQUIRE(StudentsAreEqual(maxWeightStudent, Nike));
		}
	}
}
