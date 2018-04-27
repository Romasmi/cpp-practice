#include "stdafx.h"
#include <algorithm>
#include <iterator>
#include <math.h>
#include <sstream>
using namespace std;

struct Matrix2D
{
	size_t rowsCount;
	size_t colsCount;
	double definer;
	vector<vector<double>> values;
};

bool IsEven(int number)
{
	return number % 2 == 0;
}

double GetGiagonalComposition(Matrix2D& matrix)
{
	double result = matrix.values[0][0];
	for (unsigned int i = 1; i < matrix.rowsCount; ++i)
	{
		result *= matrix.values[i][i];
	}
	return result;
}

void ProccessColumnForGaussMethod(Matrix2D& matrix, unsigned int startRow)
{
	for (unsigned int j = startRow + 1; j < matrix.rowsCount; ++j)
	{
		if (matrix.values[j][startRow] != 0)
		{
			swap(matrix.values[startRow], matrix.values[j]);
		}
	}
}

void FetchSubdiagonalColumnNumbersToZero(Matrix2D& matrix, unsigned int column)
{
	for (unsigned int j = column + 1; j < matrix.rowsCount; ++j)
	{
		if (matrix.values[j][column] != 0)
		{
			vector<double> subsidiaryRow = matrix.values[column];
			const double delimiter = matrix.values[column][column];
			const double factor = matrix.values[j][column];

			for (int k = 0; k < matrix.colsCount; ++k)
			{
				matrix.values[j][k] -= subsidiaryRow[k] / delimiter * factor;
			}
		}
	}
}

double GetDefiner(Matrix2D& matrix)
{
	Matrix2D helpMatrix(matrix);
	for (unsigned int i = 0; i < helpMatrix.colsCount - 1; ++i)
	{
		if (helpMatrix.values[i][i] == 0)
		{
			ProccessColumnForGaussMethod(helpMatrix, i);
		}

		if (helpMatrix.values[i][i] == 0)
		{
			return 0;
		}
		FetchSubdiagonalColumnNumbersToZero(helpMatrix, i);
	}
	return GetGiagonalComposition(helpMatrix);
}

bool SetMatrix(istream& input, Matrix2D& matrix)
{
	string currentLine;
	try
	{
		while (getline(input, currentLine))
		{
			std::istringstream stringIterator(currentLine);
			matrix.values.push_back(vector<double>(istream_iterator<double>(stringIterator), istream_iterator<double>()));

			if (matrix.values.front().size() != matrix.values.back().size())
			{
				return false;
			}
		}
		matrix.rowsCount = matrix.values.size();
		matrix.colsCount = matrix.values.front().size();
		if (matrix.rowsCount == matrix.colsCount)
		{
			matrix.definer = GetDefiner(matrix);
		}
		 
		return true;
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool SetMatrixFromFile(const string& filename, Matrix2D& matrix)
{
	ifstream input;
	input.open(filename);

	if (!input.is_open())
	{
		cout << "Incorrect file" << endl;
		return false;
	}
	else if (SetMatrix(input, matrix))
	{
		return true;
	}
	else
	{
		cout << "Could't get matrix from file" << endl;
		return false;
	}
}

void SetSubMatrix(Matrix2D& matrix, Matrix2D& subMatrix, unsigned int cutRow, unsigned int cutColumn)
{
	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		vector<double> subRow;
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			if (i != cutRow && j != cutColumn)
			{
				subRow.push_back(matrix.values[i][j]);
			}
		}
		if (subRow.size())
		{
			subMatrix.values.push_back(subRow);
		}
	}
	subMatrix.rowsCount = matrix.rowsCount - 1;
	subMatrix.colsCount = matrix.colsCount - 1;
}

void Print2DVector(Matrix2D& matrix)
{
	for_each(matrix.values.begin(), matrix.values.end(), [](vector<double>& row)
	{
		for_each(row.begin(), row.end(), [](double& element)
		{
			cout << element << setprecision(3) << ' ';
		});
		cout << "\n";
	});
}
double GetMinorOfMatrix(Matrix2D& matrix, unsigned int row, unsigned int column)
{
	Matrix2D subMatrix;
	SetSubMatrix(matrix, subMatrix, row, column);
	return GetDefiner(subMatrix);
}

void SetMinorMatrix(Matrix2D& matrix, Matrix2D& minorMatrix)
{
	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		vector<double> subRow;
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			subRow.push_back(GetMinorOfMatrix(matrix, i, j));
		}
		minorMatrix.values.push_back(subRow);
	}
}

void SetAlgebraicComplementMatrix(Matrix2D& matrix, Matrix2D& outputMatrix)
{
	SetMinorMatrix(matrix, outputMatrix);

	for (unsigned int i = 0; i < matrix.rowsCount; ++i)
	{
		for (unsigned int j = 0; j < matrix.colsCount; ++j)
		{
			outputMatrix.values[i][j] *= IsEven(i + j) ? 1 : -1;
		}
	}
	outputMatrix.colsCount = matrix.colsCount;
	outputMatrix.rowsCount = matrix.rowsCount;
}

void TransposeMatrix(Matrix2D& matrix)
{
	for (unsigned int i = 0; i < matrix.rowsCount - 1; ++i)
	{
		for (unsigned int j = i + 1; j < matrix.colsCount; ++j)
		{
			swap(matrix.values[i][j], matrix.values[j][i]);
		}
	}
}

void MatrixByScalar(Matrix2D& matrix, const double scalar)
{
	for_each(matrix.values.begin(), matrix.values.end(), [scalar](vector<double>& row) 
	{ 
		for_each(row.begin(), row.end(), [scalar](double& element)
		{
			element *= scalar;
		});
	});
}

bool InvertMatrix(Matrix2D& matrix)
{
	if (matrix.definer == 0)
	{
		return false;
	}

	Matrix2D invertedMatrix;
	SetAlgebraicComplementMatrix(matrix, invertedMatrix);
	TransposeMatrix(invertedMatrix);
	MatrixByScalar(invertedMatrix, 1 / matrix.definer);
	matrix = invertedMatrix;
	return true;
}

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid parameters count" << endl;
		return 1;
	}

	Matrix2D matrix;
	if (!SetMatrixFromFile(argv[1], matrix))
	{
		return 1;
	}

	if (matrix.rowsCount != matrix.colsCount)
	{
		cout << "Matrix is't not regular." << endl;
		return 1;
	}

	if (InvertMatrix(matrix))
	{
		Print2DVector(matrix);
		return 0;
	}
	else
	{
		cout << "It's impossible to find invert  matrix" << endl;
		return 1;
	}
}
