#pragma once

#include "pch.h"

void Print(const std::vector<double> v);
void LoadVectorFromStream(std::vector<double>& v, std::istream& input);
void ProcessVector(std::vector<double>& v);
std::vector<double> GetProcesedVector(const std::vector<double>& v);
