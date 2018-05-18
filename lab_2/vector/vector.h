#pragma once
using BaseVector = std::vector<double>;
BaseVector GetVectorFromStream(std::istream& input);
void PrintVector(const BaseVector& vector);
void ProcessVector(BaseVector& vector);