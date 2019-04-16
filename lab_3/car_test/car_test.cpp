#include "pch.h"

#include "../car/Car.h"

struct CarState
{
	EngineState engineState;
	unsigned int speed;
	int gear;
	Direction direction;
};

void ExpectCorrectState(const CarState& expectState, const Car& car)
{
	REQUIRE(expectState.engineState == car.GetEngineState());
	REQUIRE(expectState.speed == car.GetSpeed());
	REQUIRE(expectState.gear == car.GetGear());
	REQUIRE(expectState.direction == car.GetDirection());
}

TEST_CASE("test engine")
{
	Car car;
	REQUIRE(true == car.TurnOnEngine());
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);

	/*turn active engine on*/
	REQUIRE(false == car.TurnOnEngine());
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);

	/*turn engine off with no zero gear*/
	REQUIRE(true == car.SetGear(1));
	ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);

	REQUIRE(false == car.TurnOffEngine());
	ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);

	/*turn engine off with zero gear*/
	REQUIRE(true == car.SetGear(0));
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
	REQUIRE(true == car.TurnOffEngine());
	ExpectCorrectState(CarState({ EngineState::OFF, 0, 0, Direction::NONE }), car);

	/*turn disactive engine off */
	REQUIRE(false == car.TurnOffEngine());
	ExpectCorrectState(CarState({ EngineState::OFF, 0, 0, Direction::NONE }), car);
}

TEST_CASE("Not existing gear")
{
	Car car;
	REQUIRE(true == car.TurnOnEngine());
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);

	REQUIRE(false == car.SetGear(10));
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
	REQUIRE(false == car.SetGear(-2));
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
}

TEST_CASE("test speed setting")
{
	Car car;
	REQUIRE(true == car.TurnOnEngine());
	ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);

	SECTION("not existing gear")
	{
		REQUIRE_FALSE(car.SetGear(6));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
	}

	SECTION("positive gear")
	{

		/*set possible speed just for current gear*/
		REQUIRE(true == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);

		REQUIRE(true == car.SetSpeed(19));
		ExpectCorrectState(CarState({ EngineState::ON, 19, 1, Direction::FORWARD }), car);
		REQUIRE(false == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 19, 1, Direction::FORWARD }), car);
		REQUIRE(false == car.SetGear(2));
		ExpectCorrectState(CarState({ EngineState::ON, 19, 1, Direction::FORWARD }), car);

		/*set impossible speed for current gear*/
		REQUIRE(false == car.SetSpeed(31));
		ExpectCorrectState(CarState({ EngineState::ON, 19, 1, Direction::FORWARD }), car);

		/*set impossible gear for current speed*/
		REQUIRE(false == car.SetGear(2));
		ExpectCorrectState(CarState({ EngineState::ON, 19, 1, Direction::FORWARD }), car);

		/*set speed to increase gear*/
		REQUIRE(true == car.SetSpeed(20));
		ExpectCorrectState(CarState({ EngineState::ON, 20, 1, Direction::FORWARD }), car);
		REQUIRE(true == car.SetGear(2));
		ExpectCorrectState(CarState({ EngineState::ON, 20, 2, Direction::FORWARD }), car);

		/*set possible speed just for current gear*/
		REQUIRE(true == car.SetSpeed(31));
		ExpectCorrectState(CarState({ EngineState::ON, 31, 2, Direction::FORWARD }), car);

		/*reach max speed*/
		REQUIRE(true == car.SetSpeed(50));
		ExpectCorrectState(CarState({ EngineState::ON, 50, 2, Direction::FORWARD }), car);
		REQUIRE(true == car.SetGear(5));
		ExpectCorrectState(CarState({ EngineState::ON, 50, 5, Direction::FORWARD }), car);
		REQUIRE(true == car.SetSpeed(150));
		ExpectCorrectState(CarState({ EngineState::ON, 150, 5, Direction::FORWARD }), car);
		REQUIRE(false == car.SetSpeed(155));
		ExpectCorrectState(CarState({ EngineState::ON, 150, 5, Direction::FORWARD }), car);

		/*decrease gear*/
		REQUIRE(false == car.SetGear(4));
		ExpectCorrectState(CarState({ EngineState::ON, 150, 5, Direction::FORWARD }), car);
		REQUIRE(true == car.SetSpeed(90));
		ExpectCorrectState(CarState({ EngineState::ON, 90, 5, Direction::FORWARD }), car);
		REQUIRE(true == car.SetGear(4));
		ExpectCorrectState(CarState({ EngineState::ON, 90, 4, Direction::FORWARD }), car);

		/*set negative speed*/
		REQUIRE(false == car.SetSpeed(-100));
		ExpectCorrectState(CarState({ EngineState::ON, 90, 4, Direction::FORWARD }), car);
	}

	SECTION("negative gear")
	{
		/*set posititve gear*/
		REQUIRE(true == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);
		REQUIRE(true == car.SetSpeed(10));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 1, Direction::FORWARD }), car);

		/*set with no zero speed*/
		REQUIRE(false == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 1, Direction::FORWARD }), car);

		/*set with zero speed*/
		REQUIRE(true == car.SetSpeed(0));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);
		REQUIRE(true == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);

		/*set impossible speed*/
		REQUIRE(false == car.SetSpeed(25));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);

		/*set max speed*/
		REQUIRE(true == car.SetSpeed(20));
		ExpectCorrectState(CarState({ EngineState::ON, 20, -1, Direction::BACK }), car);

		/*set gear 2*/
		REQUIRE(false == car.SetGear(2));
		ExpectCorrectState(CarState({ EngineState::ON, 20, -1, Direction::BACK }), car);

		/*set gear 1 with no zero speed in negative direction*/
		REQUIRE(false == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 20, -1, Direction::BACK }), car);
		REQUIRE(true == car.SetSpeed(0));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);
		REQUIRE(true == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);
	}

	SECTION("neutral gear")
	{
		/*set speed to N when current speed < N*/
		REQUIRE(false == car.SetSpeed(2));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);

		/*set speed to N when current speed > N*/
		  /*with position gear*/
		REQUIRE(true == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);
		REQUIRE(true == car.SetSpeed(10));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 1, Direction::FORWARD }), car);
		REQUIRE(true == car.SetGear(0));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::FORWARD }), car);
		REQUIRE(false == car.SetSpeed(11));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::FORWARD }), car);
		REQUIRE(true == car.SetSpeed(9));
		ExpectCorrectState(CarState({ EngineState::ON, 9, 0, Direction::FORWARD }), car);
		REQUIRE(true == car.SetSpeed(0));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
		  /*with negative gear*/
		REQUIRE(true == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);
		REQUIRE(true == car.SetSpeed(10));
		ExpectCorrectState(CarState({ EngineState::ON, 10, -1, Direction::BACK }), car);
		REQUIRE(true == car.SetGear(0));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::BACK }), car);
		REQUIRE(false == car.SetSpeed(11));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::BACK }), car);
		REQUIRE(true == car.SetSpeed(9));
		ExpectCorrectState(CarState({ EngineState::ON, 9, 0, Direction::BACK }), car);
	}
}

TEST_CASE("test gear with direction")
{
	Car car;
	REQUIRE(true == car.TurnOnEngine());

	SECTION("set positive gear moving back")
	{
		REQUIRE(true == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);
		REQUIRE(true == car.SetSpeed(10));
		ExpectCorrectState(CarState({ EngineState::ON, 10, -1, Direction::BACK }), car);

		/*from gear -1*/
		REQUIRE(false == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 10, -1, Direction::BACK }), car);

		/*from gear 0*/
		REQUIRE(true == car.SetGear(0));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::BACK }), car);
		REQUIRE(false == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::BACK }), car);
	}

	SECTION("set negative gear moving forward")
	{
		REQUIRE(true == car.SetSpeed(0));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
		REQUIRE(true == car.SetGear(1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 1, Direction::NONE }), car);
		REQUIRE(true == car.SetSpeed(10));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 1, Direction::FORWARD }), car);

		/*from gear 1*/
		REQUIRE(false == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 1, Direction::FORWARD }), car);

		/*from gear 0*/
		REQUIRE(true == car.SetGear(0));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::FORWARD }), car);
		REQUIRE(false == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 10, 0, Direction::FORWARD }), car);

		/*with zero speed*/
		REQUIRE(true == car.SetSpeed(0));
		ExpectCorrectState(CarState({ EngineState::ON, 0, 0, Direction::NONE }), car);
		REQUIRE(true == car.SetGear(-1));
		ExpectCorrectState(CarState({ EngineState::ON, 0, -1, Direction::NONE }), car);
	}
}