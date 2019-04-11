#include "pch.h"

#include "Car.h"
#include "util.h"
#include <map>
#include <iterator>

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

Car::Car() {
	m_gear = 0;
	m_speed = 0;
	m_direction = NONE;
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
	return false;
}

bool Car::SetGear(const int gear)
{
	if (m_engineState == OFF)
	{
		return false;
	}
	if (!GearExist(gear))
	{
		return false;
	}
	if (gear == m_gear)
	{
		return false;
	}
	if (!GearCorrespondsToSpeed(gear))
	{
		return false;
	}
	if (gear == -1 && m_speed != 0)
	{
		return false;
	}
	if (m_gear == -1 && m_speed != 0 && gear == 1)
	{
		return false;
	}
	m_gear = gear;
	return true;
}

bool Car::SetSpeed(const unsigned int speed)
{
	if (m_engineState == OFF)
	{
		return false;
	}
	if (!SpeedCorrespondsToGear(speed))
	{
		return false;
	}
	if (m_gear == 0 && m_speed < speed)
	{
		return false;
	}
	m_speed = speed;
	SetDirection();

	return true;
}

bool Car::GearExist(const int gear)
{
	auto it = transmission.find(gear);
	return it != transmission.end();
}

bool Car::GearCorrespondsToSpeed(const int gear)
{
	GearSpeed speedInterval = transmission.find(gear)->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between(m_speed, speedInterval.minSpeed, speedInterval.maxSpeed);
}

bool Car::SpeedCorrespondsToGear(const unsigned int speed)
{
	GearSpeed speedInterval = transmission.find(m_gear)->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between(m_speed, speedInterval.minSpeed, speedInterval.maxSpeed);
}

void Car::SetDirection()
{
	if (m_speed != 0)
	{
		if (m_gear < 0)
		{
			m_direction = BACK;
		}
		else
		{
			m_direction = FORWARD;
		}
	}
	else
	{
		m_direction = NONE;
	}
}