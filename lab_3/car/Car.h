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
	void PrintState() const;

private:
	EngineState m_engineState;
	Direction m_direction;
	unsigned int m_speed;
	int m_gear;
	bool GearExist(int gear) const;
	bool GearCorrespondsToSpeed(const int gear) const;
	bool SpeedCorrespondsToGear(const unsigned int speed) const;
	void SetDirection();
	std::string GetEngineState() const;
	std::string GetDirection() const;
};
