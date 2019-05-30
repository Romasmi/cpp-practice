#include "pch.h"

#include "CBodyControl.h"
#include "util.h"

using namespace std;
using namespace std::placeholders;

const double WATER_DENSITY = 1000;
const double GRAVITY = 10;

CBodyControl::CBodyControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { "Sphere", bind(&CBodyControl::AddSphere, this, _1) },
		  { "Cone", bind(&CBodyControl::AddCone, this, _1) },
		  { "Parallelepiped", bind(&CBodyControl::AddParallelepiped, this, _1) },
		  { "Cylinder", bind(&CBodyControl::AddCylinder, this, _1) },
		  { "Show", bind(&CBodyControl::ShowBodies, this, _1) },
		  { "ShowMax", bind(&CBodyControl::ShowMax, this, _1) },
		  { "ShowLight", bind(&CBodyControl::ShowLight, this, _1) } })
{
}

bool CBodyControl::HandleCommand()
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
		return result;
	}
	m_error = "Unknown command\n";
	return false;
}

bool CBodyControl::AddSphere(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 2)
	{
		m_error = "invalid params count";
		return false;
	}
	const double destiny = stod(params[0]);
	const double radius = stod(params[1]);

	auto body = make_shared<CSphere>(CSphere(destiny, radius));
	m_bodies.push_back(body);
	return true;
}

bool CBodyControl::AddCone(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 3)
	{
		m_error = "invalid params count";
		return false;
	}
	const double destiny = stod(params[0]);
	const double radius = stod(params[1]);
	const double height = stod(params[2]);

	auto body = make_shared<CCone>(CCone(destiny, radius, height));
	m_bodies.push_back(body);
	return true;
}

bool CBodyControl::AddParallelepiped(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 4)
	{
		m_error = "invalid params count";
		return false;
	}
	const double destiny = stod(params[0]);
	const double width = stod(params[1]);
	const double height = stod(params[2]);
	const double depth = stod(params[3]);

	auto body = make_shared<CParallelepiped>(CParallelepiped(destiny, width, height, depth));
	m_bodies.push_back(body);
	return true;
}

bool CBodyControl::AddCylinder(std::istream& args)
{
	ParamsVector params = StreamLineToVector(args);
	if (params.size() != 3)
	{
		m_error = "invalid params count";
		return false;
	}
	const double destiny = stod(params[0]);
	const double radius = stod(params[1]);
	const double height = stod(params[2]);

	auto body = make_shared<CCylinder>(CCylinder(destiny, radius, height));
	m_bodies.push_back(body);
	return true;
}

CBodyControl::ParamsVector CBodyControl::StreamLineToVector(std::istream& args)
{
	string str;
	getline(args, str);
	const ParamsVector v = Split(str);
	return v;
}

bool CBodyControl::ShowBodies(std::istream& args)
{
	if (m_bodies.size() == 0)
	{
		m_error = "There are no bodies";
		return false;
	}

	for (shared_ptr<CBody> body : m_bodies)
	{
		m_output << body->ToString();
	}

	return true;
}

bool CBodyControl::ShowMax(std::istream& args)
{
	if (m_bodies.size() == 0)
	{
		return false;
	}

	double maxMas = 0;
	shared_ptr<CBody> maxMasBody = nullptr;
	for (shared_ptr<CBody> body : m_bodies)
	{
		if (body->GetMass() > maxMas)
		{
			maxMas = body->GetMass();
			maxMasBody = body;
		}
	}
	m_output << maxMasBody->ToString();

	return true;
}

bool CBodyControl::ShowLight(std::istream& args)
{
	if (m_bodies.size() == 0)
	{
		return false;
	}

	double minWeight = GetWeightInWater(m_bodies.front()->GetDensity(), m_bodies.front()->GetVolume());
	shared_ptr<CBody> minWeightBody = nullptr;
	for (shared_ptr<CBody> body : m_bodies)
	{
		if (body->GetMass() < minWeight)
		{
			minWeight = body->GetMass();
			minWeightBody = body;
		}
	}
	m_output << minWeightBody->ToString();

	return true;
}

double CBodyControl::GetWeightInWater(const double density, const double volume) const
{
	return (density - WATER_DENSITY) * GRAVITY * volume;
}

std::string CBodyControl::GetLastError() const
{
	return m_error;
}
