#include "pch.h"

#include "Car.h"
#include "util.h"
#include <map>
#include <string>

using namespace std;

Car::Car()
	: m_transmission({ { -1, { 0, 20 } },
		  { 0, { 0, 0 } },
		  { 1, { 0, 30 } },
		  { 2, { 20, 50 } },
		  { 3, { 30, 60 } },
		  { 4, { 40, 90 } },
		  { 5, { 50, 150 } } })
{
	m_gear = 0;
	m_speed = 0;
	m_direction = NONE;
	m_engineState = OFF;
}

bool Car::TurnOnEngine()
{
	m_error.clear();
	if (m_engineState == OFF)
	{
		m_engineState = ON;
		m_gear = 0;
		m_direction = NONE;
		return true;
	}
	m_error = "Failed to turn on engine. Engine is already active\n";
	return false;
}

bool Car::TurnOffEngine()
{
	m_error.clear();
	if (m_engineState == ON && m_gear == 0 && m_speed == 0)
	{
		m_engineState = OFF;
		m_direction = NONE;
		return true;
	}
	m_error = "Failed to turn off engine. For turning off, engine has to be disactive, speed has to be equil to 0, gear has to be equil to 0\n";
	return false;
}

bool Car::SetGear(const int gear)
{
	m_error.clear();
	if (m_engineState == OFF)
	{
		m_error = "Failed to set gear. Engine is disactive\n";
		return false;
	}
	if (!GearExist(gear))
	{
		m_error = "Failed to set gear. Such gear is not exist\n";
		return false;
	}
	if (gear == m_gear)
	{
		m_error = "Failed to set gear. Gear is already the same\n";
		return false;
	}
	if (!GearCorrespondsToSpeed(gear))
	{
		m_error = "Failed to set gear. Gear is not correcponds to current speed\n";
		return false;
	}
	if (m_gear <= 0 && m_speed != 0 && gear > 0 || m_gear >= 0 && gear < 0 && m_speed != 0)
	{
		m_error = "Failed to set gear. Speed has to be equal to 0\n";
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(const int speed)
{
	m_error.clear();
	if (m_engineState == OFF)
	{
		m_error = "Failed to set speed. Engine is disactive\n";
		return false;
	}

	if (!SpeedCorrespondsToGear(speed))
	{
		m_error = "Failed to set speed. Speed is not correcponds to current gear\n";
		return false;
	}
	if (m_gear == 0 && abs(m_speed) < speed)
	{
		m_error = "Failed to set speed. On neutral gearal, it's just possible to descrase speed\n";
		return false;
	}
	m_speed = m_speed < 0 || m_gear < 0 ? -1 * speed : speed;
	return true;
}

bool Car::GearExist(const int gear) const
{
	auto it = m_transmission.find(gear);
	return it != m_transmission.end();
}

bool Car::GearCorrespondsToSpeed(const int gear) const
{
	auto it = m_transmission.find(gear);
	if (it == m_transmission.end())
	{
		return false;
	}
	GearSpeed speedInterval = m_transmission.find(gear)->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between<unsigned int>(abs(m_speed), speedInterval.minSpeed, speedInterval.maxSpeed);
}

bool Car::SpeedCorrespondsToGear(const unsigned int speed) const
{
	auto it = m_transmission.find(m_gear);
	if (it == m_transmission.end())
	{
		return false;
	}
	GearSpeed speedInterval = it->second;
	return speedInterval.minSpeed == speedInterval.maxSpeed || Between(speed, speedInterval.minSpeed, speedInterval.maxSpeed);
}

EngineState Car::GetEngineState() const
{
	return m_engineState;
}

Direction Car::GetDirection() const
{
	return (m_speed != 0) ? ((m_speed > 0) ? Direction::FORWARD : Direction::BACK) : Direction::NONE;
}

int Car::GetSpeed() const
{
	return abs(m_speed);
}

int Car::GetGear() const
{
	return m_gear;
}

string Car::EngineStateToString(const EngineState state)
{
	return state == ON ? "ON" : "OFF";
}

string Car::DirectionToString(const Direction direction)
{
	return (direction != Direction::NONE) ? ((direction == Direction::FORWARD) ? "FORWARD" : "BACK") : "NONE";
}

string Car::GetLastError() const
{
	return m_error;
}