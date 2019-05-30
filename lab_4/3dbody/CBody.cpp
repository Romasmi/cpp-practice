#include "pch.h"

#include "CBody.h"

CBody::CBody(const std::string& type)
	: m_type(type)
{
}

CBody::~CBody()
{
}

std::string CBody::ToString() const
{
	std::ostringstream strm;
	strm << "*****"
		 << m_type << ": " << '\n'
		 << std::setprecision(2)
		 << "density = " << GetDensity() << '\n'
		 << "volume = " << GetVolume() << '\n'
		 << "mass = " << GetMass() << '\n';
	AppendProperties(strm);
	return strm.str();
}
