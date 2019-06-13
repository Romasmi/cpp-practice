#pragma once

#include "math_util.h"
#include <math.h>
#include <iostream>

class CRational final
{
public:
	CRational();
	CRational(const CRational& n);
	CRational(const int value);
	CRational(const int numerator, const int denominator);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	CRational const operator+() const;
	CRational const operator-() const;
	CRational& operator+=(const CRational& n);
	CRational& operator+=(const int n);
	CRational& operator-=(CRational const& n);
	CRational& operator-=(const int n);
	CRational& operator*=(const CRational& n);
	CRational& operator*=(const int n);
	CRational& operator/=(const CRational& n);
	CRational& operator/=(const int n);
	void Normalize();

private:
	int m_numerator;
	int m_denominator;
};

CRational const operator+(const CRational& n1, const CRational& n2);
CRational const operator+(const int n1, const CRational& n2);
CRational const operator+(const CRational& n1, const int n2);

CRational const operator-(const CRational& n1, const CRational& n2);
CRational const operator-(const int n1, const CRational& n2);
CRational const operator-(const CRational& n1, const int n2);

CRational const operator*(const CRational& n1, const CRational& n2);
CRational const operator*(const int n1, const CRational& n2);
CRational const operator*(const CRational& n1, const int n2);

CRational const operator/(const CRational& n1, const CRational& n2);
CRational const operator/(const int n1, const CRational& n2);
CRational const operator/(const CRational& n1, const int n2);

bool const operator==(const CRational& n1, const CRational& n2);
bool const operator==(const CRational& n1, const int n2);
bool const operator==(const int n1, const CRational& n2);

bool const operator!=(const CRational& n1, const CRational& n2);
bool const operator!=(const CRational& n1, const int n2);
bool const operator != (const int n1, const CRational& n2);

bool const operator < (const CRational& n1, const CRational& n2);
bool const operator < (const CRational& n1, const int n2);
bool const operator < (const int n1, const CRational& n2);

bool const operator <= (const CRational& n1, const CRational& n2);
bool const operator <= (const CRational& n1, const int n2);
bool const operator <= (const int n1, const CRational& n2);

bool const operator > (const CRational& n1, const CRational& n2);
bool const operator > (const CRational& n1, const int n2);
bool const operator > (const int n1, const CRational& n2);

bool const operator >= (const CRational& n1, const CRational& n2);
bool const operator >= (const CRational& n1, const int n2);
bool const operator >= (const int n1, const CRational& n2);

std::istream& const operator >> (std::istream & input, CRational& n);
std::ostream& const operator << (std::ostream & output, const CRational& n);