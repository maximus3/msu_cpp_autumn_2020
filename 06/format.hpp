#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

class format_out_of_range_error: public std::out_of_range {
private:
    std::string msg;
public:
    explicit format_out_of_range_error(const std::string& what)
    : std::out_of_range(what)
    , msg(what) {}

    const char* what() const noexcept {
        return msg.c_str();
    }
};

class format_invalid_argument_error: public std::invalid_argument {
private:
    std::string msg;
public:
    explicit format_invalid_argument_error(const std::string& what)
    : std::invalid_argument(what)
    , msg(what) {}

    const char* what() const noexcept {
        return msg.c_str();
    }
};

class format_syntax_error: public std::runtime_error {
private:
    std::string msg;
public:
    explicit format_syntax_error(const std::string& what)
    : std::runtime_error(what)
    , msg(what) {}

    const char* what() const noexcept {
        return msg.c_str();
    }
};

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
                    throw format_out_of_range_error(error_str.str());
                }
                format_ss << str_args[num];
                is_num = false;
                continue;
            }
            if (!std::isdigit(c)) {
                std::stringstream error_str;
                error_str << c;
                throw format_invalid_argument_error(error_str.str());
            }
            num = num * 10 + (c - '0');
        }
        else if (c == '{') {
            is_num = true;
            num = 0;
        } else if (c == '}') {
            throw format_syntax_error("Unexpected symbol '}'");
        } else {
            format_ss << c;
        }
    }
    if (is_num) {
        throw format_syntax_error("Unexpected symbol '{'");
    }
    return format_ss.str();
}