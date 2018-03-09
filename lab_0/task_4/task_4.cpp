#include "stdafx.h"
using namespace std;

enum class Operation { Addition, Subration, Multiplication, Division };

const pair<char, Operation> CHAR_TO_OPERATION[] = {
    {'+', Operation::Addition},
    {'-', Operation::Subration},
    {'*', Operation::Multiplication},
    {'/', Operation::Division}};

bool DecodeOperation(const char ch, Operation &operation) {
  for (auto &op : CHAR_TO_OPERATION) {
    if (op.first == ch) {
      operation = op.second;
      return true;
    }
  }
  return false;
}

enum OperationTypes {
  plusSign = '+',
  minusSign = '-',
  multiplicationSign = '*',
  devisionSign = '/'
};

double Calculate(const double operand1, const double operand2,
                 const pair<char, Operation> operation) {
  double result;

  switch (operation.first) {
  case plusSign:
    result = operand1 + operand2;
    break;
  case minusSign:
    result = operand1 - operand2;
    break;
  case multiplicationSign:
    result = operand1 * operand2;
    break;
  case devisionSign:
    result = operand1 / operand2;
    break;
  }

  return result;
}

double Calculate(char *array[], const int operandsCount) {
  double result = stod(array[0]);
  pair<char, Operation> operation;
  for (int i = 1; i < operandsCount; ++i) {
    if (i % 2 == 0) {
      if (operation.first == devisionSign && stod(array[i]) == 0) {
        throw std::overflow_error("Division by zero");
        break;
      } else {
        result = Calculate(result, stod(array[i]), operation);
      }
    } else {
      operation.first = array[i][0];
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    cout << "Not input numbers" << endl;
    return 1;
  }

  Operation operation;
  double operand;
  try {
    for (int i = 1; i < argc; ++i) {
      if (i % 2 == 0) {
        if (!DecodeOperation(argv[i][0], operation)) {
          cout << "Can't decode operation " << argv[i];
          return 1;
        }
      } else {
        operand = stod(argv[i]);
      }
    }
  } catch (const exception &e) {
    cout << "One or more operands aren't' valid \n";
    cout << e.what() << endl;
    return 1;
  }

  try {
    operand = stod(argv[argc - 1]);
  } catch (const exception &e) {
    cout << "Last argument must be a number\n";
    cout << e.what() << endl;
    return 1;
  }

  try {
    const double result = Calculate(argv + 1, argc - 1);
    cout << "Result: " << result << endl;
  } catch (std::overflow_error devisionByZeroException) {
    cout << devisionByZeroException.what();
  }
  cout << endl;
  return 0;
}
