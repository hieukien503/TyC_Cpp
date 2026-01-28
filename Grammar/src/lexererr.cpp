#include "lexererr.hpp"

ErrorToken::ErrorToken(std::string msg) {
    this->msg = "Error Token: " + msg;
}

const char* ErrorToken::what() const throw() {
    return this->msg.c_str();
}

UncloseString::UncloseString(std::string msg) {
    this->msg = "Unclosed String: " + msg;
}

const char* UncloseString::what() const throw() {
    return this->msg.c_str();
}

IllegalEscape::IllegalEscape(std::string msg) {
    this->msg = "Illegal Escape In String: " + msg;
}

const char* IllegalEscape::what() const throw() {
    return this->msg.c_str();
}