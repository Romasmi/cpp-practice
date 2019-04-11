#include "pch.h"

#include "../car/Car.h"

TEST_CASE("Action with disactive engine")
{
	Car car;

	/*positive gear with disactive engine*/
	REQUIRE(true == car.SetGear(1));
	REQUIRE(false == car.SetSpeed(10));
	/*try to turn on on posititve gear*/
	REQUIRE(false == car.TurnOnEngine());

	/*positive gear with disactive engine*/
	REQUIRE(true == car.SetGear(-1));
	REQUIRE(false == car.SetSpeed(10));
	/*try to turn on on negative gear*/
	REQUIRE(false == car.TurnOnEngine());
}

TEST_CASE("Not existing gear")
{
	Car car;
	car.TurnOnEngine();

	REQUIRE(false == car.SetGear(10));
	REQUIRE(false == car.SetGear(-2));
}

TEST_CASE("test speed setting")
{
	Car car;
	car.TurnOnEngine();

	SECTION("positive gear")
	{
		/*set possible speed just for current gear*/
		REQUIRE(true == car.SetGear(1));
		REQUIRE(true == car.SetSpeed(19));
		REQUIRE(true == car.SetGear(1));
		REQUIRE(false == car.SetGear(2));

		/*set impossible speed for current gear*/
		REQUIRE(false == car.SetSpeed(31));

		/*set impossible gear for current speed*/
		REQUIRE(false == car.SetGear(2));

		/*set speed to increase gear*/
		REQUIRE(true == car.SetSpeed(20));
		REQUIRE(true == car.SetGear(2));

		/*set possible speed just for current gear*/
		REQUIRE(true == car.SetSpeed(31));

		/*reach max speed*/
		REQUIRE(true == car.SetSpeed(50));
		REQUIRE(true == car.SetGear(5));
		REQUIRE(true == car.SetSpeed(150));
		REQUIRE(false == car.SetSpeed(155));

		/*decrease gear*/
		REQUIRE(false == car.SetGear(1));
		REQUIRE(false == car.SetSpeed(19));
		REQUIRE(true == car.SetSpeed(20));
		REQUIRE(true == car.SetGear(1));

	}

	SECTION("negative gear")
	{
		/*set with no zero speed*/
		REQUIRE(false == car.SetGear(-1));

		/*set with zero speed*/
		REQUIRE(true == car.SetSpeed(0));
		REQUIRE(true == car.SetGear(-1));

		/*set impossible speed*/
		REQUIRE(false == car.SetSpeed(25));

		/*set max speed*/
		REQUIRE(true == car.SetSpeed(20));

		/*set gear 1 with no zero speed in negative direction*/
		REQUIRE(false == car.SetGear(1));
		REQUIRE(true == car.SetSpeed(0));
		REQUIRE(true == car.SetGear(1));
	}

	SECTION("neutral gear")
	{
		REQUIRE(true == car.SetGear(0));
		REQUIRE(true == car.SetSpeed(0));

		/*set speed to N when current speed < N*/
		REQUIRE(false == car.SetSpeed(2));

		/*set speed to N when current speed > N*/
		REQUIRE(true == car.SetGear(1));
		REQUIRE(true == car.SetSpeed(10));
		REQUIRE(true == car.SetGear(0));
		REQUIRE(true == car.SetSpeed(9));
	}


}
