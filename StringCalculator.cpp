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
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::string StringCalculator::trim(const std::string &s) const {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    if (start == s.size()) return "";
    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) --end;
    return s.substr(start, end - start + 1);
}

int StringCalculator::Add(const std::string &input) {
    if (input.empty()) return 0;

    std::string numbersPart = input;
    std::vector<std::string> delimiters = {",", "\n"};

    // Handle custom delimiter
    if (startsWith(numbersPart, "//")) {
        size_t newlinePos = numbersPart.find('\n');
        if (newlinePos == std::string::npos)
            throw std::runtime_error("Invalid input: Missing newline after delimiter declaration.");

        std::string delimiterDecl = numbersPart.substr(2, newlinePos - 2);
        numbersPart = numbersPart.substr(newlinePos + 1);

        if (!delimiterDecl.empty() && delimiterDecl.front() == '[') {
            size_t pos = 0;
            while (pos < delimiterDecl.size()) {
                size_t start = delimiterDecl.find('[', pos);
                size_t end = delimiterDecl.find(']', start);
                if (start == std::string::npos || end == std::string::npos) break;
                std::string delim = delimiterDecl.substr(start + 1, end - start - 1);
                delimiters.push_back(delim);
                pos = end + 1;
            }
        } else {
            delimiters.push_back(delimiterDecl);
        }
    }

    // Normalize all delimiters to commas
    std::string normalized = numbersPart;
    for (const auto &d : delimiters)
        replaceAll(normalized, d, ",");

    std::vector<std::string> tokens = split(normalized, ',');
    std::vector<int> negatives;
    long long sum = 0;

    for (auto &t : tokens) {
        t = trim(t);
        if (t.empty()) continue;
        try {
            int num = std::stoi(t);
            if (num < 0) negatives.push_back(num);
            else if (num <= 1000) sum += num;
        } catch (...) {
            // Ignore invalid tokens
        }
    }

    if (!negatives.empty()) {
        std::ostringstream oss;
        oss << "negatives not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << negatives[i];
        }
        throw std::runtime_error(oss.str());
    }

    return static_cast<int>(sum);
}
