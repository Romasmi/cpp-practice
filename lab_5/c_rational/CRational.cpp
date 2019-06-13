#include "pch.h"

#include "CRational.h"
#include "math_util.h"
#include <stdexcept>
#include <cmath>

using namespace std;

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(const int numerator, const int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw std::overflow_error("Divide by zero exception");
	}
	Normalize();
}

void CRational::Normalize()
{
	const int gcd = GCD(m_numerator, m_denominator);
	if (gcd != 0)
	{
		m_numerator /= gcd;
		m_denominator /= gcd;
	}
}
int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return  static_cast<double>(m_numerator) / m_denominator;
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(const CRational& n)
{
	*this = *this + n;
	return *this;
}

CRational& CRational::operator-=(const CRational& n)
{
	*this = *this - n;
	return *this;
}

CRational& CRational::operator*=(const CRational& n)
{
	*this = *this * n;
	return *this;
}

CRational& CRational::operator/=(const CRational& n)
{
	*this = *this / n;
	return *this;
}

CRational const operator+(const CRational& n1, const CRational& n2)
{
	int lcm = LCM(n1.GetDenominator(), n2.GetDenominator());
	int numerator = lcm / n1.GetDenominator() * n1.GetNumerator() + lcm / n2.GetDenominator() * n2.GetNumerator();
	CRational n = CRational(numerator, lcm);
	n.Normalize();
	return n;
}

CRational const operator-(const CRational& n1, const CRational& n2)
{
	return n1 + (-n2);
}

CRational const operator*(const CRational& n1, const CRational& n2)
{
	CRational n(n1.GetNumerator() * n2.GetNumerator(), n1.GetDenominator() * n2.GetDenominator());
	n.Normalize();
	return n;
}

CRational const operator/(const CRational& n1, const CRational& n2)
{
	if (n2.GetNumerator() == 0)
	{
		throw std::overflow_error("Divide by zero exception");
	}
	CRational n(n1.GetNumerator() * n2.GetDenominator(), n1.GetDenominator() * n2.GetNumerator());
	n.Normalize();
	return n;
}

bool const operator==(const CRational& n1, const CRational& n2)
{
	CRational r1(n1);
	CRational r2(n2);
	r1.Normalize();
	r2.Normalize();
	return r1.GetNumerator() == r2.GetNumerator() && r1.GetDenominator() == r2.GetDenominator();
}

bool const operator!=(const CRational& n1, const CRational& n2)
{
	return !(n1 == n2);
}

bool const operator<(const CRational& n1, const CRational& n2)
{
	return (n1.GetNumerator() * n2.GetDenominator()) < (n1.GetDenominator() * n2.GetNumerator());
}

bool const operator<=(const CRational& n1, const CRational& n2)
{
	return n1 < n2 || n1 == n2;
}

bool const operator>(const CRational& n1, const CRational& n2)
{
	return !(n1 <= n2);
}

bool const operator>=(const CRational& n1, const CRational& n2)
{
	return !(n1 < n2);
}

std::istream& operator>>(std::istream& input, CRational& n)
{
	int numerator;
	int denomerator;
	if (input >> numerator && input.get() == '/' && input >> denomerator)
	{
		n = CRational(numerator, denomerator);
	}
	else
	{
		throw invalid_argument("Can't get rational number");
	}
	return input;
}

std::ostream& operator<<(std::ostream& output, const CRational& n)
{
	CRational r(n);
	r.Normalize();
	output << r.GetNumerator() << '/' << r.GetDenominator();
	return output;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	const int intPart = (int)(floor(abs(ToDouble())));
	const int remainder = intPart * GetDenominator();

	int numerator;
	if (GetNumerator() != 0)
	{
		numerator = GetNumerator() > 0 ? GetNumerator() - remainder : GetNumerator() + remainder;
	}
	else
	{
		numerator = GetNumerator();
	}

	const CRational n(numerator, GetDenominator());
	return make_pair(intPart, n);
}
