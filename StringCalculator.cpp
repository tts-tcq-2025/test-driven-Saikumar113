#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

bool StringCalculator::startsWith(const std::string &str, const std::string &prefix) const {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

void StringCalculator::replaceAll(std::string &s, const std::string &from, const std::string &to) const {
    if (from.empty()) return;
    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos) {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }
}

std::vector<std::string> StringCalculator::split(const std::string &s, char delim) const {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) elems.push_back(item);
    return elems;
}

std::vector<std::string> StringCalculator::parseDelimiters(std::string &input) const {
    std::vector<std::string> delimiters = {",", "\n"};
    if (!startsWith(input, "//")) return delimiters;

    size_t newlinePos = input.find('\n');
    if (newlinePos == std::string::npos)
        throw std::runtime_error("Invalid input: Missing newline after delimiter declaration.");

    std::string decl = input.substr(2, newlinePos - 2);
    input = input.substr(newlinePos + 1);

    if (!decl.empty() && decl.front() == '[') {
        size_t pos = 0;
        while (pos < decl.size()) {
            size_t start = decl.find('[', pos);
            size_t end = decl.find(']', start);
            if (start == std::string::npos || end == std::string::npos) break;
            delimiters.push_back(decl.substr(start + 1, end - start - 1));
            pos = end + 1;
        }
    } else {
        delimiters.push_back(decl);
    }
    return delimiters;
}

std::string StringCalculator::normalizeInput(const std::string &numbersPart, const std::vector<std::string> &delimiters) const {
    std::string result = numbersPart;
    for (const auto &d : delimiters)
        replaceAll(result, d, ",");
    return result;
}

std::vector<int> StringCalculator::extractNumbers(const std::string &normalized) const {
    std::vector<int> numbers;
    for (const auto &t : split(normalized, ',')) {
        if (t.empty()) continue;
        try {
            numbers.push_back(std::stoi(t));
        } catch (...) {
            // ignore invalid entries
        }
    }
    return numbers;
}

void StringCalculator::validateNegatives(const std::vector<int> &numbers) const {
    std::vector<int> negatives;
    for (int n : numbers)
        if (n < 0) negatives.push_back(n);

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << negatives[i];
        }
        throw std::runtime_error(oss.str());
    }
}

int StringCalculator::sumNumbers(const std::vector<int> &numbers) const {
    int sum = 0;
    for (int n : numbers)
        if (n <= 1000) sum += n;
    return sum;
}

int StringCalculator::Add(const std::string &input) {
    if (input.empty()) return 0;

    std::string mutableInput = input;
    auto delimiters = parseDelimiters(mutableInput);
    auto normalized = normalizeInput(mutableInput, delimiters);
    auto numbers = extractNumbers(normalized);
    validateNegatives(numbers);
    return sumNumbers(numbers);
}
