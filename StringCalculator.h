#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& input);

private:
    bool startsWith(const std::string& s, const std::string& prefix);
    std::string extractDelimiterSection(const std::string& input);
    std::vector<std::string> parseDelimiters(const std::string& section);
    std::string normalizeInput(const std::string& input, const std::vector<std::string>& delimiters);
    std::vector<int> extractNumbers(const std::string& input);
    void validateNegatives(const std::vector<int>& numbers);
    int sumNumbers(const std::vector<int>& numbers);
};

#endif
