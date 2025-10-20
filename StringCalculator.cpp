#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>

bool StringCalculator::startsWith(const std::string& s, const std::string& prefix) {
    return s.rfind(prefix, 0) == 0;
}

std::string StringCalculator::extractDelimiterSection(const std::string& input) {
    if (!startsWith(input, "//")) return "";
    auto pos = input.find('\n');
    return input.substr(2, pos - 2);
}

std::vector<std::string> StringCalculator::parseDelimiters(const std::string& section) {
    if (section.empty()) return {",", "\n"};

    std::vector<std::string> delimiters;
    std::regex bracketed("\\[(.*?)\\]");
    std::smatch match;
    std::string temp = section;

    while (std::regex_search(temp, match, bracketed)) {
        delimiters.push_back(match[1]);
        temp = match.suffix();
    }

    if (delimiters.empty()) delimiters.push_back(std::string(1, section[0]));
    return delimiters;
}

std::string StringCalculator::normalizeInput(const std::string& input, const std::vector<std::string>& delimiters) {
    std::string data = input;
    for (const auto& d : delimiters) {
        std::regex r(std::regex_replace(d, std::regex(R"([-[\]{}()*+?.,\^$|#\s])"), R"(\$&)"));
        data = std::regex_replace(data, r, ",");
    }
    data = std::regex_replace(data, std::regex("\n"), ",");
    return data;
}

std::vector<int> StringCalculator::extractNumbers(const std::string& input) {
    std::vector<int> nums;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {
        if (token.empty()) continue;
        nums.push_back(std::stoi(token));
    }

    return nums;
}

void StringCalculator::validateNegatives(const std::vector<int>& numbers) {
    std::vector<int> negatives;
    for (int n : numbers) if (n < 0) negatives.push_back(n);

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) oss << ",";
            oss << negatives[i];
        }
        throw std::invalid_argument(oss.str());
    }
}

int StringCalculator::sumNumbers(const std::vector<int>& numbers) {
    int sum = 0;
    for (int n : numbers) if (n <= 1000) sum += n;
    return sum;
}

int StringCalculator::Add(const std::string& input) {
    if (input.empty()) return 0;

    std::string section = extractDelimiterSection(input);
    std::vector<std::string> delimiters = parseDelimiters(section);
    std::string data = startsWith(input, "//") ? input.substr(input.find('\n') + 1) : input;
    std::string normalized = normalizeInput(data, delimiters);
    std::vector<int> numbers = extractNumbers(normalized);
    validateNegatives(numbers);
    return sumNumbers(numbers);
}
