#pragma once
using namespace std;
using BaseVector = vector<double>;

bool SetVectorFromStream(BaseVector &vector, istream& input);
void PrintVector(const BaseVector& vector);
void ProcessVector(BaseVector& vector);