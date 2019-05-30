#include "pch.h"

#include "CSolidBody.h"

using namespace std;

CSolidBody::CSolidBody(const std::string& type, double density)
	: CBody(type)
	, m_density(density)
{
}

CSolidBody::~CSolidBody()
{
}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return GetVolume() * GetDensity();
}

