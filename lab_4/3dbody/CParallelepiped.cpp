#include "pch.h"

#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(const double density, const double width, const double height, const double depth)
	: CSolidBody("Parallelepiped", density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return GetWidth() * GetHeight() * GetDepth();
}

void CParallelepiped::AppendProperties(std::ostream& out) const
{
	out << "width = " << GetWidth() << '\n';
	out << "height = " << GetHeight() << '\n';
	out << "depth = " << GetDepth() << '\n';
}
