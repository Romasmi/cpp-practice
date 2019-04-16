#include "pch.h"

#include "Car.h"
#include "CarControl.h"
#include "util.h"

using namespace std;
using namespace std::placeholders;

CarControl::CarControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "EngineOn", bind(&CarControl::EngineOn, this, _1) },
		  { "EngineOff", bind(&CarControl::EngineOff, this, _1) },
		  { "SetSpeed", bind(&CarControl::SetSpeed, this, _1) },
		  { "SetGear", bind(&CarControl::SetGear, this, _1) },
		  { "Info", bind(&CarControl::Info, this, _1) } })
{
}

bool CarControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);
	m_error.clear();

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		bool result = it->second(strm);
		m_error = m_error.empty() ? m_car.GetLastError() : m_error;
		return result;
	}
	m_error = "Unknown command\n";
	return false;
}

bool CarControl::EngineOn(std::istream& args)
{
	return m_car.TurnOnEngine();
}

bool CarControl::EngineOff(std::istream& args)
{
	return m_car.TurnOffEngine();
}

bool CarControl::SetSpeed(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 1)
	{
		m_error = "Speed  is not set";
		return false;
	}
	const unsigned int speed = stoul(params[0]);
	return m_car.SetSpeed(speed);
}

bool CarControl::SetGear(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 1)
	{
		m_error = "Gear is not set";
		return false;
	}
	const int gear = stoi(params[0]);
	return m_car.SetGear(gear);
}

bool CarControl::Info(std::istream& args)
{
	m_output << "Engine state:" << EngineStateToString(m_car.GetEngineState()) << ", ";
	m_output << "Gear:" << m_car.GetGear() << ", ";
	m_output << "Speed:" << m_car.GetSpeed() << ", ";
	m_output << "Direction:" << DirectionToString(m_car.GetDirection()) << "\n";
	return true;
}

string CarControl::GetLastError() const
{
	return m_error;
}

CarControl::ParamsVector CarControl::StreamLineToVector(std::istream& args)
{
	string str;
	getline(args, str);
	const ParamsVector v = Split(str);
	return v;
}

string CarControl::EngineStateToString(const EngineState state) const 
{
	return state == EngineState::ON ? "ON" : "OFF";
}

string CarControl::DirectionToString(const Direction direction) const
{
	return (direction != Direction::NONE) ? ((direction == Direction::FORWARD) ? "FORWARD" : "BACK") : "NONE";
}
