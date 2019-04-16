#pragma once

#include "pch.h"
#include <map>
#include <string>

enum class EngineState
{
	ON,
	OFF
};

enum class Direction
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
	bool SetSpeed(const int speed);
	int GetGear() const;
	int GetSpeed() const;
	EngineState GetEngineState() const;
	Direction GetDirection() const;
	std::string GetLastError() const;

private:
	bool GearExist(int gear) const;
	bool GearCorrespondsToSpeed(const int gear) const;
	bool SpeedCorrespondsToGear(const unsigned int speed) const;

private:
	struct GearSpeed
	{
		unsigned int minSpeed;
		unsigned int maxSpeed;
	};

	static std::map<int, GearSpeed> m_transmission;
	EngineState m_engineState;
	Direction m_direction;
	int m_speed;
	int m_gear;
	std::string m_error;
};
