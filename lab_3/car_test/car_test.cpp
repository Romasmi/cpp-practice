#include "pch.h"

#include "../car/Car.h"

TEST_CASE("Test Car class")
{
	Car car;

	/*Action with disactive engine*/
	REQUIRE(false == car.SetGear(1));
	REQUIRE(false == car.SetSpeed(10));

	car.TurnOnEngine();
	/*Set impossible gear*/
	REQUIRE(false == car.SetGear(10));

	/*Set mismatch gear*/
	car.SetSpeed(10);
	REQUIRE(false == car.SetGear(5));

	/*Set appropriate gear*/
	car.SetSpeed(10);
	REQUIRE(false == car.SetGear(1));
}
