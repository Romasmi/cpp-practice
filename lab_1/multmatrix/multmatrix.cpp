#include "pch.h"
using namespace std;
const unsigned int PARAMS_COUNT = 3;
const unsigned int RESULT_PRECISION = 3;

using MatrixCell = double;
using MatrixRow = vector<MatrixCell>;
using Matrix = vector<MatrixRow>;

bool IsEquialBoundaryRowsSize(const Matrix &matrix)
{
	return matrix.front().size() == matrix.back().size();
}

bool SetMatrix(istream& input, Matrix& matrix)
{
	try
	{
		string currentLine;
		while (getline(input, currentLine))
		{
			istringstream stringIterator(currentLine);
			matrix.push_back(MatrixRow(istream_iterator<MatrixCell>(stringIterator), istream_iterator<MatrixCell>()));

			if (!IsEquialBoundaryRowsSize(matrix))
			{
				return false;
			}
		}

		return matrix.size() != 0; 
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

bool SetMatrix(const string& filename, Matrix& matrix)
{
	ifstream input(filename);
	return input.is_open() && SetMatrix(input, matrix);
}

bool Multiply(const Matrix &matrix1, const Matrix &matrix2, Matrix &result)
{
	if (matrix1.size() != matrix2.front().size())
	{
		return false;
	}

	const size_t size = matrix1.size();
	for (size_t i = 0; i < size; ++i)
	{
		MatrixRow row(size);
		row[i] = 0;
		for (size_t j = 0; j < size; ++j)
		{
			row[i] += matrix1[i][j] * matrix2[j][i];
		}
		result.push_back(row);
	}
	return true;
}

void PrintMatrix(const Matrix &matrix, const unsigned int precision = 3)
{
	cout.precision(precision);
	for (const MatrixRow row : matrix)
	{
		copy(row.begin(), row.end(), ostream_iterator<MatrixCell>(cout, " "));
		cout << "\n";
	}
}

int main(const unsigned int argc, const char* argv[])
{
	if (argc != PARAMS_COUNT)
	{
		cout << "Invalid params count\n";
		return 1;
	} 

	Matrix matrix1;
	Matrix matrix2;
	Matrix result;

	if (SetMatrix(string(argv[1]), matrix1) &&
		SetMatrix(string(argv[2]), matrix2) &&
		Multiply(matrix1, matrix2, result))
	{
		PrintMatrix(result);
		return 0;
	}
	else
	{
		cout << "Error\n";
		return 1;
	}
}
