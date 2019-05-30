#include "pch.h"

#include "CSphere.h"

CSphere::CSphere(const double density, const double radius)
	: CSolidBody("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (pow(GetRadius(), 3) * M_PI) * 4 / 3;
}

void CSphere::AppendProperties(std::ostream& out) const
{
	out << "radius = " << GetRadius() << '\n';
}
