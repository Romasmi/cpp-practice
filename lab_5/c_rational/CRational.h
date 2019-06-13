#pragma once

#include "math_util.h"
#include <math.h>
#include <iostream>
#include <utility>

class CRational final
{
public:
	CRational(const int numerator = 0, const int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	void Normalize();
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator+() const;
	CRational const operator-() const;
	CRational& operator+=(const CRational& n);
	CRational& operator-=(CRational const& n);
	CRational& operator*=(const CRational& n);
	CRational& operator/=(const CRational& n);

private:
	int m_numerator;
	int m_denominator;
};

CRational const operator+(const CRational& n1, const CRational& n2);
CRational const operator-(const CRational& n1, const CRational& n2);
CRational const operator*(const CRational& n1, const CRational& n2);
CRational const operator/(const CRational& n1, const CRational& n2);
bool const operator==(const CRational& n1, const CRational& n2);
bool const operator!=(const CRational& n1, const CRational& n2);
bool const operator < (const CRational& n1, const CRational& n2);
bool const operator <= (const CRational& n1, const CRational& n2);
bool const operator > (const CRational& n1, const CRational& n2);
bool const operator >= (const CRational& n1, const CRational& n2);

std::istream& operator >> (std::istream & input, CRational& n);
std::ostream& operator << (std::ostream & output, const CRational& n);