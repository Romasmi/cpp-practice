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
	int GetGear() const;
	int GetSpeed() const;
	EngineState GetEngineState() const;
	Direction GetDirection() const;

private:
	EngineState m_engineState;
	Direction m_direction;
	int m_speed;
	int m_gear;
	std::string m_error;
	bool GearExist(int gear) const;
	bool GearCorrespondsToSpeed(const int gear) const;
	bool SpeedCorrespondsToGear(const unsigned int speed) const;
};
