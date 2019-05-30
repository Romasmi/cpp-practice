#pragma once
#include "CSolidBody.h"
class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(const double density, const double length, const double height, const double depth);
	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& out) const override;
	const double m_width;
	const double m_height;
	const double m_depth;
};
