#include "stdafx.h"
using namespace std;

bool PrintFibonacci(const size_t max, const int numbersCountInLine = 5) {
  size_t lastNumber = 0;
  size_t currentNumber = 1;
  size_t numbersCount = 1;

  while (lastNumber < max) {
    cout << lastNumber;

    if (numbersCount % numbersCountInLine == 0) {
      cout << "\n";
    } else {
      cout << " ";
    }

    if ((currentNumber + lastNumber) > numeric_limits<int>::max()) {
      cout << "Next Number overflow. Program has to stop.";
      return false;
    }
    currentNumber += lastNumber;
    lastNumber = currentNumber - lastNumber;

    ++numbersCount;
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Invalid parameters count \n";
    return 1;
  }

  size_t max;
  size_t numberCountInLine = 5;
  try {
    max = stoi(argv[1]);

    if (argc == 3) {
      numberCountInLine = stoi(argv[2]);
    }
  } catch (const exception &e) {
    cout << e.what() << "\n";
    return 1;
  }

  if (max < 1) {
    cout << "Invalid MAX parameter. Max < 1 \n";
    return 1;
  }

  if (argc == 3) {
    if (numberCountInLine < 1 || numberCountInLine > 10) {
      cout << "Invalid number count in line. Allowable interval is from 1 to "
              "10 \n";
      return 1;
    }
  }

  if (!PrintFibonacci(max)) {
    cout << "can't output all numbers. Probably, it's because of numbers "
            "overflow. Try to set not so huge MAX argument.\n";
  }
  cout << endl;

  return 0;
}
