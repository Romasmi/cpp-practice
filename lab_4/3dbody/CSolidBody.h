#pragma once

#include "pch.h"

#include "CBody.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(const std::string& type, double density);

	double GetDensity() const override;
	virtual double GetVolume() const = 0;
	double GetMass() const;
	virtual ~CSolidBody();

private:
	virtual void AppendProperties(std::ostream& out) const = 0;
	double m_density;
};
