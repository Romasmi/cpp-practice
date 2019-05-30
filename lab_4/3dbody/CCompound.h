#pragma once
#include "pch.h"

#include "CBody.h"
class CCompound : public CBody
{
public:
	CCompound();
	double GetDensity() const;
	double GetVolume() const;
	double GetMass() const;
	bool AddChildBody(std::shared_ptr<CBody> child);

private:
	void AppendProperties(std::ostream& out) const;
	std::vector<std::shared_ptr<CBody>> m_children;
};
