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
    std::string trim(const std::string &s) const;
};
