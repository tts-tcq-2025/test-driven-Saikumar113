#include "StringCalculator.h"

#include <cassert>
#include <iostream>

void runTests() {
  StringCalculator calc;

  assert(calc.Add("") == 0);
  assert(calc.Add("1") == 1);
  assert(calc.Add("1,2") == 3);
  assert(calc.Add("1,2,3,4") == 10);
  assert(calc.Add("1\n2,3") == 6);
  assert(calc.Add("//;\n1;2") == 3);
  assert(calc.Add("2,1001") == 2);
  assert(calc.Add("//[***]\n1***2***3") == 6);
  assert(calc.Add("//[*][%]\n1*2%3") == 6);

  bool thrown = false;
  try {
    calc.Add("1,-2,3,-4");
  } catch (const std::invalid_argument& e) {
    thrown = true;
  }
  assert(thrown);

  std::cout << "✅ All tests passed!" << std::endl;
}

int main() {
  runTests();
  return 0;
}
