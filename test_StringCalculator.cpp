#include "StringCalculator.h"
#include <cassert>
#include <iostream>

void runTests() {
    StringCalculator calc;

    // Step 1: Smallest failing test
    assert(calc.Add("") == 0);

    // Step 2: One number
    assert(calc.Add("1") == 1);

    // Step 3: Two numbers
    assert(calc.Add("1,2") == 3);

    // Step 4: Multiple numbers
    assert(calc.Add("1,2,3,4") == 10);

    // Step 5: Newline as delimiter
    assert(calc.Add("1\n2,3") == 6);

    // Step 6: Custom single delimiter
    assert(calc.Add("//;\n1;2") == 3);

    // Step 7: Ignore numbers > 1000
    assert(calc.Add("2,1001") == 2);

    // Step 8: Multi-length delimiters
    assert(calc.Add("//[***]\n1***2***3") == 6);

    // Step 9: Multiple delimiters
    assert(calc.Add("//[*][%]\n1*2%3") == 6);

    // Step 10: Negative number throws exception
    bool thrown = false;
    try { calc.Add("1,-2,3,-4"); }
    catch (const std::invalid_argument& e) { thrown = true; }
    assert(thrown);

    std::cout << "✅ All tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
