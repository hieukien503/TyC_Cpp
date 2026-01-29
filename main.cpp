#include "main.hpp"
#include <reproc++/reproc.hpp>
#include <reproc++/drain.hpp>

#include "./Grammar/target/TyCLexer.h"
#include "./Grammar/target/TyCParser.h"

class TerminalColor {
public:
    enum class Color {
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,
        RESET = 0
    };

    std::string colorize(const std::string& text, Color color) {
        std::ostringstream oss;
        oss << "\033[" << static_cast<int>(color) << "m" << text << "\033[0m";
        return oss.str();
    }
};

class TyCApp {
protected:
    std::string grammarDir, targetDir, rootDir, ANTLR_JAR;

public:
    TerminalColor terminalColor;
    TyCApp() {
        this->rootDir = "./";
        this->grammarDir = "Grammar/src/TyC.g4";
        this->targetDir = "Grammar/target/";
        auto antlr_jar = std::getenv("ANTLR_JAR");
        if (antlr_jar) {
            this->ANTLR_JAR = std::string(antlr_jar);
        }

        else {
            this->ANTLR_JAR = "./external/jar_file/antlr-4.13.2-complete.jar";
        }

        this->terminalColor = TerminalColor();
    }

    std::optional<std::string> runCommand(
        const std::vector<std::string>& args,
        std::optional<std::string> cwd = std::nullopt,
        bool check = true,
        bool captureOutput = false
    ) {
        const std::string cwdPath = cwd.value_or(this->rootDir);
        if (args.empty()) {
            throw std::runtime_error("args is empty");
        }

        reproc::process proc;
        reproc::options opts;
        opts.working_directory = cwdPath.c_str();

        if (captureOutput) {
            opts.redirect.out.type = reproc::redirect::pipe;
            opts.redirect.err.type = reproc::redirect::pipe;
        }

        std::error_code startError = proc.start(args, opts);
        if (startError) {
            throw std::system_error(startError);
        }

        std::string out, err;
        if (captureOutput) {
            std::error_code drainError;
            drainError = reproc::drain(
                proc,
                reproc::sink::string(out),
                reproc::sink::string(err)
            );

            if (drainError && drainError != reproc::error::broken_pipe) {
                throw std::system_error(drainError);
            }
        }

        auto [status, waitError] = proc.wait(reproc::infinite);
        if (waitError) {
            throw std::system_error(waitError);
        }

        if (check && status != 0) {
            throw std::runtime_error(err.empty() ? "Command failed" : err);
        }

        if (captureOutput && !out.empty()) {
            return out;
        }

        return std::nullopt;
    }

    bool checkCommandExists(const std::string& cmd) {
        try {
            this->runCommand({cmd, "--version"}, std::nullopt, true, false);
            return true;
        } 
        
        catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    bool checkJavaExists() {
        return this->checkCommandExists("java");
    }

    bool checkJavaVersionAtLeast(int major=17) {
        if (!this->checkJavaExists()) {
            return false;
        }

        try {
            const std::string out = this->runCommand(
                {"java", "--version"},
                std::nullopt,
                true,
                true
            ).value();

            std::istringstream iss(out);
            std::string line;
            std::getline(iss, line);
            std::istringstream lineStream(line);
            std::string javaStr, versionStr;
            lineStream >> javaStr >> versionStr; // Skip 'java'
            int foundMajor = 0;
            if (versionStr.find('.') != std::string::npos) {
                std::replace(versionStr.begin(), versionStr.end(), '.', ' ');
                std::istringstream versionStream(versionStr);
                versionStream >> foundMajor;
            } 
            
            else {
                foundMajor = std::stoi(versionStr);
            }

            return foundMajor >= major;
        }

        catch (const std::exception& e) {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    void checkDependencies() {
        bool javaOk = this->checkJavaVersionAtLeast(17);
        bool antlrJarExists = std::filesystem::exists(this->ANTLR_JAR);
        if (!javaOk) {
            std::cout << this->terminalColor.colorize("Some dependencies are missing or do not meet the required versions:\n", TerminalColor::Color::RED);
            std::cout << this->terminalColor.colorize("- Java 17 or higher is required.\n", TerminalColor::Color::RED);
        }
        
        if (!antlrJarExists) {
            std::cout << this->terminalColor.colorize("- ANTLR JAR file not found at path: " + this->ANTLR_JAR + "\n", TerminalColor::Color::RED);
        }
        
        else {
            std::cout << this->terminalColor.colorize("All dependencies are satisfied.\n", TerminalColor::Color::GREEN);
        }
    }

    void showHelp() {
        std::cout << this->terminalColor.colorize("TyC Project in C++ - Available Commands:\n", TerminalColor::Color::BLUE);
        std::cout << this->terminalColor.colorize("-----------------------Setup and Build------------------------\n", TerminalColor::Color::GREEN);
        std::cout << this->terminalColor.colorize("cmake -G \"MinGW Makefiles\" .\t\t-Generate MinGW-compatible CMake files\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("make\t\t\t\t\t-Compile the project\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main check\t\t\t\t-Check dependencies\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main gen\t\t\t\t-Generate ANTLR files\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main run\t\t\t\t-Run the project with file \"main.tyc\" in the source directory\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("-----------------------Testing--------------------------------\n", TerminalColor::Color::GREEN);
        std::cout << this->terminalColor.colorize("./main test LexerSuite\t\t\t-Run lexer tests\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main test ParserSuite\t\t\t-Run parser tests\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main test ASTGenSuite\t\t\t-Run ast tests\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main test CheckerSuite\t\t-Run static checker tests\n", TerminalColor::Color::YELLOW);
        std::cout << this->terminalColor.colorize("./main test CodeGenSuite\t\t-Run code generation tests\n", TerminalColor::Color::YELLOW);
    }

    void generateANTLRFiles() {
        std::cout << "Generating ANTLR files...\n";
        try {
            this->runCommand(
                {
                    "java",
                    "-jar",
                    this->ANTLR_JAR,
                    "-o",
                    this->targetDir,
                    "-no-listener",
                    "-visitor",
                    this->grammarDir
                }
            );

            std::cout << this->terminalColor.colorize("ANTLR files generated successfully in " + this->targetDir + "\n", TerminalColor::Color::GREEN);
        }
        
        catch(const std::exception& e) {
            std::cout << this->terminalColor.colorize("Error generating ANTLR files: " + std::string(e.what()) + "\n", TerminalColor::Color::RED);
        }
    }
};

int main(int argc, char** argv) {
    TyCApp* app = new TyCApp();
    if (argc < 2) {
        app->showHelp();
    }

    else {
        std::string command = argv[1];
        if (command == "check") {
            app->checkDependencies();
        }

        else if (command == "help") {
            app->showHelp();
        }

        else if (command == "gen") {
            app->generateANTLRFiles();
        }

        else if (command == "run") {
            bool exists = std::filesystem::exists("main.tyc");
            if (!exists) {
                std::cout << app->terminalColor.colorize("Source file 'main.tyc' not found in the current directory.\n", TerminalColor::Color::RED);
            } 
            
            else {
                std::cout << app->terminalColor.colorize("Running the project...\n", TerminalColor::Color::GREEN);
                class SyntaxException: public std::exception {
                private:
                    std::string msg;
                public:
                    SyntaxException(std::string msg) {
                        this->msg = msg;
                    }

                    const char* what() const throw() {
                        return this->msg.c_str();
                    }
                };

                class NewErrorListener: public antlr4::ConsoleErrorListener {
                public:
                    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
                        throw SyntaxException("Error on line " + std::to_string(line) + ", col " + std::to_string(charPositionInLine) + ": " + offendingSymbol->getText());
                    }
                };

                std::ifstream sourceFile("main.tyc");
                antlr4::ANTLRInputStream input(sourceFile);
                try {
                    TyCLexer lexer(&input);
                    antlr4::CommonTokenStream tokens(&lexer);
                    TyCParser parser(&tokens);
                    NewErrorListener errorListener;
                    parser.removeErrorListeners();
                    parser.addErrorListener(&errorListener);
                    antlr4::tree::ParseTree* tree = parser.program();
                    std::cout << app->terminalColor.colorize("Parsing completed successfully.\n", TerminalColor::Color::GREEN);
                } 
                
                catch (const std::exception& e) {
                    std::cout << app->terminalColor.colorize("Error during parsing: " + std::string(e.what()) + "\n", TerminalColor::Color::RED);
                }
            }
        }

        else if (command == "test") {
            if (argc < 3) {
                std::cout << app->terminalColor.colorize("Please specify a test suite to run.\n", TerminalColor::Color::RED);
            } 
            
            else {
                std::string suite = argv[2];
                std::cout << app->terminalColor.colorize("Running test suite: " + suite + "\n", TerminalColor::Color::GREEN);
                if (suite != "LexerSuite" && suite != "ParserSuite" && suite != "ASTGenSuite" && suite != "CheckerSuite" && suite != "CodeGenSuite") {
                    std::cout << app->terminalColor.colorize("Unknown test suite: " + suite + "\n", TerminalColor::Color::RED);
                    app->showHelp();
                    delete app;
                    return 0;
                }

                try {
                    std::optional<std::string> res = app->runCommand(
                        {
                            "./compiler_tests",
                            "--verbosity",
                            "high",
                            "--name",
                            suite,
                            "-s",
                            "--colour-mode",
                            "ansi",
                            [&]() {
                                if (suite == "LexerSuite") return "[lexer]";
                                if (suite == "ParserSuite") return "[parser]";
                                if (suite == "ASTGenSuite") return "[ast]";
                                if (suite == "CheckerSuite") return "[checker]";
                                if (suite == "CodeGenSuite") return "[codegen]";
                                return "";
                            }()
                        },
                        std::nullopt,
                        false,
                        true
                    );

                    std::string result = res.value_or(app->terminalColor.colorize("Test suite '" + suite + "' executed successfully.\n", TerminalColor::Color::GREEN));
                    std::cout << result;
                }
                
                catch (const std::exception& e) {
                    std::cout << app->terminalColor.colorize("Error running test suite '" + suite + "': " + std::string(e.what()) + "\n", TerminalColor::Color::RED);
                }
            }
        }

        else {
            std::cout << app->terminalColor.colorize("Unknown command: " + command + "\n", TerminalColor::Color::RED);
            app->showHelp();
        }
    }

    delete app;
    return 0;
}