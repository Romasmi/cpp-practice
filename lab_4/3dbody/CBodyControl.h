#pragma once

#include "pch.h"

#include "CBody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CSphere.h"
#include "CParallelepiped.h"
#include "CCylinder.h"

class CBodyControl : boost::noncopyable
{
public:
	CBodyControl(std::istream& input, std::ostream& output);
	bool HandleCommand();
	std::string GetLastError() const;

private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	using ParamsVector = std::vector<std::string>;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::string m_error;
	std::vector<std::shared_ptr<CBody>> m_bodies;

private:
	bool AddSphere(std::istream& args);
	bool AddCone(std::istream& args);
	bool AddParallelepiped(std::istream& args);
	bool AddCylinder(std::istream& args);
	bool ShowBodies(std::istream& args);
	bool ShowMax(std::istream& args);
	bool ShowLight(std::istream& args);

	double GetWeightInWater(const double density, const double volume) const;
	ParamsVector StreamLineToVector(std::istream& args);
};
