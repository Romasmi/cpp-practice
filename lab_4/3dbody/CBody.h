#pragma once

#include <fstream>
#include <string>

class CBody
{
public:
	CBody(const std::string& type);

	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	std::string ToString() const;

	virtual ~CBody();

private:
	virtual void AppendProperties(std::ostream& out) const = 0;
	const std::string m_type;
};
