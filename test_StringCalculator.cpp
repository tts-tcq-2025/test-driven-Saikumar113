#include <iostream>
#include <cassert>
#include "StringCalculator.h"

void runTests() {
    StringCalculator calc;

    // Basic and multiple number tests
    assert(calc.Add("") == 0);
    assert(calc.Add("1") == 1);
    assert(calc.Add("1,2") == 3);
    assert(calc.Add("1,2,3,4,5") == 15);

    // Newline support
    assert(calc.Add("1\n2,3") == 6);

    // Custom delimiters
    assert(calc.Add("//;\n1;2") == 3);
    assert(calc.Add("//[***]\n1***2***3") == 6);
    assert(calc.Add("//;\n1;2;3;4") == 10);
    assert(calc.Add("//;\n1;2\n3") == 6);
    assert(calc.Add("//[###]\n1###2###3###4") == 10);

    // Large numbers
    assert(calc.Add("2,1001") == 2);
    assert(calc.Add("1000,2") == 1002);

    // Multiple custom delimiters (optional extended)
    assert(calc.Add("//[*][%]\n1*2%3") == 6);

    // Exception for negative numbers
    try {
        calc.Add("1,-2,-3,4");
        assert(false); // should not reach here
    } catch (const std::runtime_error &ex) {
        std::string msg = ex.what();
        assert(msg.find("negatives not allowed") != std::string::npos);
        assert(msg.find("-2") != std::string::npos);
        assert(msg.find("-3") != std::string::npos);
    }

    std::cout << "✅ All tests passed successfully!" << std::endl;
}

int main() {
    runTests();
    return 0;
}
