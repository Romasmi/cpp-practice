#pragma once
#include "CSolidBody.h"
class CSphere final : public CSolidBody
{
public:
	CSphere(const double density, const double radius);
	double GetRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& out) const override;
	const double m_radius;
};
