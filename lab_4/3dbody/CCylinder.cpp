#include "pch.h"

#include "CCylinder.h"

CCylinder::CCylinder(const double density, const double radius, const double height)
	: CSolidBody("Conus", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return pow(GetRadius(), 2) * M_PI * GetHeight();
}

void CCylinder::AppendProperties(std::ostream& out) const
{
	out << "radius = " << GetRadius() << '\n';
	out << "height = " << GetHeight() << '\n';
}
