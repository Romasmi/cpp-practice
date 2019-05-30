#pragma once
#include "CSolidBody.h"
class CCylinder : public CSolidBody
{
public:
	CCylinder(const double density, const double radius, const double height);
	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& out) const override;
	const double m_radius;
	const double m_height;
};
