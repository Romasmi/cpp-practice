#pragma once
#include "CSolidBody.h"
class CCone : public CSolidBody
{
public:
	CCone(const double density, const double radius, const double height);
	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& out) const override;
	const double m_radius;
	const double m_height;
};
