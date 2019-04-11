#include "pch.h"

#include "Car.h"
#include "util.h"
#include <iostream>
#include <iterator>
#include <map>

using namespace std;

struct GearSpeed
{
	unsigned int minSpeed;
	unsigned int maxSpeed;
};

const map<int, GearSpeed> transmission = {
	{ -1, { 0, 20 } },
	{ 0, { 0, 0 } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

Car::Car()
{
	m_gear = 0;
	m_speed = 0;
	m_direction = NONE;
	m_engineState = OFF;
}

bool Car::TurnOnEngine()
{
	if (m_engineState == OFF)
	{
		m_engineState = ON;
		m_gear = 0;
		m_direction = NONE;
		return true;
	}
	cout << "Failed to turn on engine. Engine is already active\n";
	return false;
}

bool Car::TurnOffEngine()
{
	if (m_engineState == ON && m_gear == 0 && m_speed == 0)
	{
		m_engineState = OFF;
		m_direction = NONE;
		return true;
	}
	cout << "Failed to turn off engine. For turning off, engine has to be disactive, speed has to be equil to 0, gear has to be equil to 0\n";
	return false;
}

bool Car::SetGear(const int gear)
{
	if (m_engineState == OFF)
	{
		cout << "Failed to set gear. Engine is disactive\n";
		return false;
	}
	if (!GearExist(gear))
	{
		cout << "Failed to set gear. Such gear is not exist\n";
		return false;
	}
	if (gear == m_gear)
	{
		cout << "Failed to set gear. Gear is already the same\n";
		return false;
	}
	if (!GearCorrespondsToSpeed(gear))
	{
		cout << "Failed to set gear. Gear is not correcponds to current speed\n";
		return false;
	}
	if (gear == -1 && m_speed != 0)
	{
		cout << "Failed to set gear. Speed has to be equal to 0\n";
		return false;
	}
	if (m_gear == -1 && m_speed != 0 && gear == 1)
	{
		cout << "Failed to set gear. Speed has to be equal to 0\n";
		return false;
	}
	m_gear = gear;
	return true;
}

bool Car::SetSpeed(const unsigned int speed)
{
	if (m_engineState == OFF)
	{
		cout << "Failed to set speed. Engine is disactive\n";
		return false;
	}
	if (!SpeedCorrespondsToGear(speed))
	{
		cout << "Failed to set speed. Speed is not correcponds to current gear\n";
		return false;
	}
	if (m_gear == 0 && m_speed < speed)
	{
		cout << "Failed to set speed. On neutral gearal, it's just impossible to descrase speed\n";
		return false;
	}
	m_speed = speed;
	SetDirection();

	return true;
}

bool Car::GearExist(const int gear) const
{
	auto it = transmission.find(gear);
	return it != transmission.end();
}

bool Car::GearCorrespondsToSpeed(const int gear) const
{
	GearSpeed speedInterval = transmission.find(gear)->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between(m_speed, speedInterval.minSpeed, speedInterval.maxSpeed);
}

bool Car::SpeedCorrespondsToGear(const unsigned int speed) const
{
	GearSpeed speedInterval = transmission.find(m_gear)->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between(speed, speedInterval.minSpeed, speedInterval.maxSpeed);
}

void Car::SetDirection()
{
	if (m_speed != 0)
	{
		if (m_gear > 0)
		{
			m_direction = FORWARD;
		}
		else
		{
			m_direction = BACK;
		}
	}
	else
	{
		m_direction = NONE;
	}
}

string Car::GetEngineState() const
{
	return m_engineState == ON ? "ON" : "OFF";
}

string Car::GetDirection() const
{
	return (m_direction != NONE) ? ((m_direction == FORWARD) ? "FORWARD" : "BACK") : "NONE";
}

void Car::PrintState() const
{
	cout << "Engine state:" << GetEngineState() << ", ";
	cout << "Gear:" << m_gear << ", ";
	cout << "Speed:" << m_speed << ", ";
	cout << "Direction:" << GetDirection() << "\n";
}
