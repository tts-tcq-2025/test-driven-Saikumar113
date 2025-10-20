#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string &input);

private:
    bool startsWith(const std::string &str, const std::string &prefix) const;
    void replaceAll(std::string &s, const std::string &from, const std::string &to) const;
    std::vector<std::string> split(const std::string &s, char delim) const;
    std::vector<std::string> parseDelimiters(std::string &input) const;
    std::string normalizeInput(const std::string &numbersPart, const std::vector<std::string> &delimiters) const;
    std::vector<int> extractNumbers(const std::string &normalized) const;
    void validateNegatives(const std::vector<int> &numbers) const;
    int sumNumbers(const std::vector<int> &numbers) const;
};
