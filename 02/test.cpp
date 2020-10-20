#include <sstream>

#include "test_runner.h"
#include "TokenParser.h"

void
tests_consructor() {                                  
    std::stringstream out;
    
    Callback start_callback = [&out]() {
        out << "START";
    };

    Callback finish_callback = [&out]() {
        out << "END";
    };

    DigitTokenCallback digit_callback = [&out](const int& token) {
        out << token << "-DIGIT";
    };

    StringTokenCallback string_callback = [&out](const std::string& token) {
        out << token << "-STRING";
    };
    
    TokenParser parser = TokenParser(start_callback
                                     , finish_callback
                                     , digit_callback
                                     , string_callback);
                                     
    
    parser.parse("token token2 323 123token4 token5 6token 75435");
    
    Assert(out.str() == "STARTtoken-STRINGtoken2-STRING323-DIGIT123token4-STRINGtoken5-STRING6token-STRING75435-DIGITEND"
           , "test_constr: output <<" + out.str() + ">>");
}

void
tests_set() {                                  
    std::stringstream out;
    
    Callback start_callback = [&out]() {
        out << "START";
    };

    Callback finish_callback = [&out]() {
        out << "END";
    };

    DigitTokenCallback digit_callback = [&out](const int& token) {
        out << token << "-DIGIT";
    };

    StringTokenCallback string_callback = [&out](const std::string& token) {
        out << token << "-STRING";
    };
    
    TokenParser parser = TokenParser();
    
    parser.SetStartCallback(start_callback);
    parser.SetFinishCallback(finish_callback);
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
                                     
    
    parser.parse("fdsfe 123456 323 123fsdsd 435");
    
    Assert(out.str() == "STARTfdsfe-STRING123456-DIGIT323-DIGIT123fsdsd-STRING435-DIGITEND"
           , "test_set: output <<" + out.str() + ">>");
}

void
tests_any() {                                  
    std::stringstream out;
    
    Callback start_callback = [&out]() {
        out << "START";
    };

    Callback finish_callback = [&out]() {
        out << "END";
    };

    DigitTokenCallback digit_callback = [&out](const int& token) {
        out << token << "-DIGIT";
    };

    StringTokenCallback string_callback = [&out](const std::string& token) {
        out << token << "-STRING";
    };
    
    TokenParser parser = TokenParser(start_callback, finish_callback);
    
    parser.SetDigitTokenCallback(digit_callback);
    parser.SetStringTokenCallback(string_callback);
                                    
    
    parser.parse("fdsfe 123456 323 123fsdsd 435");
    
    Assert(out.str() == "STARTfdsfe-STRING123456-DIGIT323-DIGIT123fsdsd-STRING435-DIGITEND"
           , "test_any: output <<" + out.str() + ">>");
}

int
main(void) {
    TestRunner runner = TestRunner();
    runner.RunTest(tests_consructor, "Callbacks from constructor");
    runner.RunTest(tests_set, "By set callbacks");
    runner.RunTest(tests_any, "Any");
    
    std::cout << "All tests passes successfully!\n";
    return 0;
}
