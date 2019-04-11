#pragma once

#include "pch.h"

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
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const int gear);
	bool SetSpeed(const unsigned int speed);

private:
	EngineState m_engineState;
	Direction m_direction;
	unsigned int m_speed;
	int m_gear;
	bool GearExist(int gear);
	bool GearCorrespondsToSpeed(const int gear);
	bool SpeedCorrespondsToGear(const unsigned int speed);
	void SetDirection();
};
