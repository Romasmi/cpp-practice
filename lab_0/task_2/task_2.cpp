#include "stdafx.h"
using namespace std;

int SumDigits(int i) {
  int sum = 0;

  while (i != 0) {
    sum += i % 10;
    i /= 10;
  }

  return sum;
}

void PrintMagicNumbers(const int min, const int max) {
  for (int i = min; i < max; ++i) {
    if (i % SumDigits(i) == 0) {
      cout << i << '\n';
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Invalid parameters count \n";
    return 1;
  }

  try {
    const int MIN = stoi(argv[1]);
    const int MAX = stoi(argv[2]);

    if (MAX < MIN || MIN < 1) {
      cout << "Error: please, follow next rules: MIN >= 1, MIN < MAX";
      return 1;
    }

    PrintMagicNumbers(MIN, MAX);
  } catch (exception e) {
    cout << e.what() << endl;
    return 1;
  }

  return 0;
}
