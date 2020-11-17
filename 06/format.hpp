#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

template <class T>
std::string
make_string(const T& arg) {
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

template <class... Args>
std::string
format(const std::string& str, Args&&... args) {
    std::vector<std::string> str_args {make_string(std::forward<Args>(args))...};

    bool is_num = false;
    size_t num = 0;
    std::stringstream format_ss;
    for (const auto& c: str) {
        if (is_num) {
            if (c == '}') {
                if (num >= str_args.size()) {
                    std::stringstream error_str;
                    error_str << num << ">=" << str_args.size();
                    throw std::out_of_range(error_str.str());
                }
                format_ss << str_args[num];
                is_num = false;
                continue;
            }
            if (!std::isdigit(c)) {
                std::stringstream error_str;
                error_str << c;
                throw std::invalid_argument(error_str.str());
            }
            num = num * 10 + (c - '0');
        }
        else if (c == '{') {
            is_num = true;
            num = 0;
        } else if (c == '}') {
            throw std::runtime_error("Unexpected symbol '}'");
        } else {
            format_ss << c;
        }
    }
    if (is_num) {
        throw std::runtime_error("Unexpected symbol '{'");
    }
    return format_ss.str();
}