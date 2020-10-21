#include "TokenParser.h"

#define CHECK_ALL_DIGITS  all_digits ? digit_callback(std::stoi(token)) : string_callback(token)

TokenParser::TokenParser(const Callback& start_callback_
        , const Callback& finish_callback_
        , const DigitTokenCallback& digit_callback_
        , const StringTokenCallback& string_callback_)
        : start_callback(start_callback_)
        , finish_callback(finish_callback_)
        , digit_callback(digit_callback_)
        , string_callback(string_callback_) {}


void TokenParser::SetStartCallback(const Callback& callback) {
    start_callback = callback;
}

void TokenParser::SetFinishCallback(const Callback& callback) {
    finish_callback = callback;
}

void TokenParser::SetDigitTokenCallback(const DigitTokenCallback& callback) {
    digit_callback = callback;
}

void TokenParser::SetStringTokenCallback(const StringTokenCallback& callback) {
    string_callback = callback;
}

void TokenParser::Parse(const std::string& text) {
    start_callback();
    
    std::string token = "";
    bool all_digits = true;
    
    for(const auto& c: text) {
        if (std::isspace(c) && token.length()) {
            CHECK_ALL_DIGITS;
            token = "";
            all_digits = true;
            continue;
        }
        if (!std::isdigit(c)) {
            all_digits = false;
        }
        token += c;
    }
    if (token.length()) {
        CHECK_ALL_DIGITS;
    }
    
    finish_callback();
}
