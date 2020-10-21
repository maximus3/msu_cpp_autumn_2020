#pragma once

#include <string>
#include <functional>

using Callback = std::function<void()>;
using DigitTokenCallback = std::function<void(const int)>;
using StringTokenCallback = std::function<void(const std::string&)>;

class TokenParser
{
private:
    Callback start_callback;
    Callback finish_callback;
    DigitTokenCallback digit_callback;
    StringTokenCallback string_callback;
public:
    TokenParser(const Callback& start_callback_=[]() {}
                , const Callback& finish_callback_=[]() {}
                , const DigitTokenCallback& digit_callback_=[](const int) {}
                , const StringTokenCallback& string_callback_=[](const std::string&) {});
        
    void SetStartCallback(const Callback& callback);
    void SetFinishCallback(const Callback& callback);
    void SetDigitTokenCallback(const DigitTokenCallback& callback);
    void SetStringTokenCallback(const StringTokenCallback& callback);
    
    void Parse(const std::string& text);
};
