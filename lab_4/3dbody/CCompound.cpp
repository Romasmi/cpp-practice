#include "pch.h"

#include "CCompound.h"

using namespace std;

CCompound::CCompound()
	: CBody("compound")
{
}

double CCompound::GetDensity() const
{
	return GetMass() / GetDensity();
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (shared_ptr<CBody> body : m_children)
	{
		volume += body->GetMass();
	}
	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (shared_ptr<CBody> body : m_children)
	{
		mass += body->GetMass();
	}
	return mass;
}

bool CCompound::AddChildBody(shared_ptr<CBody> child)
{
	/*if (make_shared<CBody>(this) == child)
	{
		return false;
	}*/

	try
	{
		m_children.push_back(child);
	}
	catch (const exception& e)
	{
		std::cout << e.what() << '\n';
		return false;
	}
	return true;
}

void CCompound::AppendProperties(std::ostream& out) const
{
}