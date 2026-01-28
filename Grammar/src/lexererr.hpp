#ifndef LEXERERR_HPP
#define LEXERERR_HPP

#include <iostream>

class LexerError: public std::exception {
public:
    virtual const char* what () const throw() = 0;
};

class ErrorToken: public LexerError {
private:
    std::string msg;

public:
    ErrorToken(std::string msg);
    const char* what () const throw();
};

class UncloseString: public LexerError {
private:
    std::string msg;

public:
    UncloseString(std::string msg);
    const char* what () const throw();
};

class IllegalEscape: public LexerError {
private:
    std::string msg;

public:
    IllegalEscape(std::string msg);
    const char* what () const throw();
};

#endif