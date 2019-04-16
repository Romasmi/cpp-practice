#pragma once

#include <boost/noncopyable.hpp>
#include <functional>
#include <map>
#include <vector>
#include "Car.h"

class Car;

class CarControl : boost::noncopyable
{
public:
	CarControl(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	std::string GetLastError() const;

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	using ParamsVector = std::vector<std::string>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::string m_error;

private:
	bool EngineOn(std::istream & args);
	bool EngineOff(std::istream& args);
	bool SetSpeed(std::istream& args);
	bool SetGear(std::istream& args);
	bool Info(std::istream& args);
	ParamsVector StreamLineToVector(std::istream& args);
	std::string EngineStateToString(const EngineState state) const;
	std::string DirectionToString(const Direction direction) const;
};
