#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "../../Grammar/src/lexererr.hpp"
#include "../../Grammar/target/TyCLexer.h"
#include "../../Grammar/target/TyCParser.h"
#include <fstream>

const std::string TEST_DIR = "./test/testcases/";
const std::string SOL_DIR = "./test/solutions/";

class TestUtils {
public:
    static antlr4::ANTLRInputStream makeSource(
        const std::string& inputFile,
        const int& num
    );
};

class TestLexer {
public:
    static bool test(
        const std::string& input,
        const std::string& expect,
        const int& num
    );

    static void check(
        const std::string& sol_dir,
        antlr4::ANTLRInputStream& inputFile,
        const int& num
    ); 

    static void printLexeme(
        std::fstream& destFile,
        TyCLexer* lexer
    );
};

class SyntaxException: public std::exception {
private:
    std::string msg;
public:
    SyntaxException(std::string msg);
    const char* what() const throw();
};

class NewErrorListener: public antlr4::ConsoleErrorListener {
public:
    void syntaxError(
        antlr4::Recognizer *recognizer,
        antlr4::Token * offendingSymbol,
        size_t line, size_t charPositionInLine,
        const std::string &msg, std::exception_ptr e
    );
};

class TestParser {
public:
    static void check(
        const std::string& sol_dir,
        antlr4::ANTLRInputStream& inputFile,
        const int& num
    );

    static bool test(
        const std::string& input,
        const std::string& expect,
        const int& num
    );
};

#endif // TEST_UTILS_HPP