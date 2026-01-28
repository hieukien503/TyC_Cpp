#include "../headers/TestUtils.hpp"

antlr4::ANTLRInputStream TestUtils::makeSource(
    const std::string& inputFile,
    const int& num
) {
    const std::string fileName = TEST_DIR + std::to_string(num) + ".txt";
    std::ofstream srcFile(fileName, std::ios::out);
    if (!srcFile.is_open()) {
        throw std::runtime_error("Could not open source file: " + fileName);
    }

    srcFile << inputFile;
    srcFile.close();
    return antlr4::ANTLRInputStream(inputFile);
}

bool TestLexer::test(
    const std::string& input,
    const std::string& expect,
    const int& num
) {
    antlr4::ANTLRInputStream inputFile = TestUtils::makeSource(input, num);
    TestLexer::check(SOL_DIR, inputFile, num);
    std::fstream destFile(SOL_DIR + std::to_string(num) + ".txt", std::ios::in);
    const std::string line {
        std::istreambuf_iterator<char>(destFile),
        std::istreambuf_iterator<char>()
    };

    destFile.close();
    return line == expect;
}

void TestLexer::check(
    const std::string& sol_dir,
    antlr4::ANTLRInputStream& inputFile,
    const int& num
) {
    std::fstream destFile(SOL_DIR + std::to_string(num) + ".txt", std::ios::out);
    auto lexer = TyCLexer(&inputFile);
    try {
        TestLexer::printLexeme(destFile, &lexer);
    }

    catch (LexerError& e) {
        destFile << std::string(e.what());
    }

    destFile.close();
}

void TestLexer::printLexeme(
    std::fstream& destFile,
    TyCLexer* lexer
) {
    auto token = lexer->nextToken();
    if (token.get()->getType() == TyCLexer::EOF) {
        destFile << "<EOF>";
        return;
    }

    destFile << token.get()->getText() << ",";
    TestLexer::printLexeme(destFile, lexer);
}

SyntaxException::SyntaxException(std::string msg) {
    this->msg = msg;
}

const char* SyntaxException::what() const throw() {
    return this->msg.c_str();
}

void NewErrorListener::syntaxError(
    antlr4::Recognizer *recognizer,
    antlr4::Token * offendingSymbol,
    size_t line, size_t charPositionInLine,
    const std::string &msg, std::exception_ptr e
) {
    throw SyntaxException("Error on line " + std::to_string(line) + ", col " + std::to_string(charPositionInLine) + ": " + offendingSymbol->getText());
}

void TestParser::check(
    const std::string& sol_dir,
    antlr4::ANTLRInputStream& inputFile,
    const int& num
) {
    std::fstream destFile(SOL_DIR + std::to_string(num) + ".txt", std::ios::out);
    auto lexer = TyCLexer(&inputFile);
    antlr4::CommonTokenStream tokens(&lexer);
    auto parser = TyCParser(&tokens);
    NewErrorListener listener = NewErrorListener();
    parser.removeErrorListeners();
    parser.addErrorListener(&listener);
    try {
        parser.program();
        destFile << "Success";
    }

    catch (const SyntaxException& e) {
        destFile << e.what();
    }

    catch(const std::exception& e) {
        destFile << e.what();
    }

    destFile.close();
}

bool TestParser::test(
    const std::string& input,
    const std::string& expect,
    const int& num
) {
    antlr4::ANTLRInputStream inputFile = TestUtils::makeSource(input, num);
    TestParser::check(SOL_DIR, inputFile, num);
    std::fstream destFile(SOL_DIR + std::to_string(num) + ".txt", std::ios::in);
    const std::string line {
        std::istreambuf_iterator<char>(destFile),
        std::istreambuf_iterator<char>()
    };

    destFile.close();
    return line == expect;
}