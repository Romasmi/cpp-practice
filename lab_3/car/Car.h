#pragma once

enum EngineState
{
	ON,
	OFF
};

enum Direction
{
	FORWARD,
	BACK,
	NONE
};

class Car
{
public:
	Car();
	~Car();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	EngineState m_engineState;
	Direction m_direction;
	unsigned int m_speed;
	int m_gear;

};

