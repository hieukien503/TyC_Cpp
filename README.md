# TyC Compiler Project (C++ version)

A comprehensive compiler implementation for **TyC**, a simple C-like programming language with complete type inference, using the ANTLR4 parser generator.

[![CMake](https://img.shields.io/badge/CMake-3.5+-yellow.svg)](https://cmake.org/)
[![MinGW](https://img.shields.io/badge/MinGW-w64-blue.svg)](https://www.mingw-w64.org/)
[![ANTLR](https://img.shields.io/badge/ANTLR-4.13.2-orange.svg)](https://www.antlr.org/)
[![License](https://img.shields.io/badge/License-Academic-green.svg)](LICENSE)

## Overview

This is a C++ version of **TyC's compiler**, a custom C-like language designed for educational purposes.

📋 **For detailed language specification, see [TyC Specification](tyc_specification.md)**

The project demonstrates fundamental concepts of compiler construction including:

- **Lexical Analysis**: Tokenization and error handling for invalid characters, unclosed strings, and illegal escape sequences
- **Syntax Analysis**: Grammar-based parsing using ANTLR4 (ANother Tool for Language Recognition)
- **AST Generation**: Building abstract syntax trees from parse trees
- **Semantic Analysis**: Complete type inference system with static type checking
- **Code Generation**: Generating target code from validated AST
- **Error Handling**: Comprehensive error reporting for all compilation phases
- **Testing Framework**: Will be updated later

---

## Phase 1: Lexical and Syntax Analysis

### Required Tasks to Complete

1. **Read the specification carefully**

   - Study the detailed [TyC Specification](tyc_specification.md) document
   - Understand the syntax and semantics of the TyC language
   - Master the lexical and syntax rules

2. **Implement the TyC.g4 file**

   - Complete the ANTLR4 grammar file in `Grammar/src/TyC.g4`
   - Define lexical rules (tokens)
   - Define parser rules (grammar rules)
   - Handle precedence and associativity of expressions

3. **Write test cases for lexer and parser**
   - **Test cases for lexer** in `tests/src/LexerSuite.cpp`
     - Test valid and invalid tokens
     - Test error handling (unclosed strings, illegal escape sequences, etc.)
     - Test edge cases and boundary conditions
   - **Test cases for parser** in `tests/src/ParserSuite.cpp`
     - Test valid grammar structures
     - Test syntax errors and error recovery
     - Test nested structures and complex expressions

### Lexical Error Handling

For lexical errors, the lexer will return the following tokens with specific lexemes:

- **ERROR_TOKEN** with `<unrecognized char>` lexeme: when the lexer detects an unrecognized character.

- **UNCLOSE_STRING** with `<unclosed string>` lexeme: when the lexer detects an unterminated string. The `<unclosed string>` lexeme does not include the opening quote.

- **ILLEGAL_ESCAPE** with `<wrong string>` lexeme: when the lexer detects an illegal escape in string. The wrong string is from the beginning of the string (without the opening quote) to the illegal escape.

### Outcome

- **Grammar Implementation**: Accuracy and completeness of the `TyC.g4` file
- **Test Coverage**: Quantity and quality of test cases
- **Error Handling**: Capability to handle lexical and syntax errors

---

## Phase 2: AST Generation

### Required Tasks to Complete

1. **Study the AST Node Structure**

   - Read carefully all node classes in `AST/headers/AST.hpp` and `AST/src/AST.cpp`
   - Understand the AST node hierarchy and their properties
   - Master how different language constructs map to AST nodes
   - Study case: How Visitor design pattern is applied to real-world project

2. **Implement the ASTGeneration Class**

   - Implement a class `ASTGeneration` in `AST/headers/ASTGeneration.hpp` and `AST/src/ASTGeneration.cpp`, which inherits from `TyCVisitor` (generated from ANTLR4)
   - Override visitor methods to construct appropriate AST nodes
   - Handle all language constructs defined in the TyC specification

3. **Write AST Generation Test Cases**
   - Implement test cases in `tests/src/ASTGenSuite.cpp`
   - Test AST generation for all language features
   - Verify correct node types and structure
   - Test edge cases and complex nested structures

### Requirements

The `ASTGeneration` class must:

- **Inherit from TyCVisitor**: Use the visitor pattern to traverse parse trees
- **Return AST nodes**: Each visit method should return appropriate node objects from `nodes.py`
- **Handle all constructs**: Support all language features defined in the grammar
- **Maintain structure**: Preserve the logical structure and relationships between language elements

### Outcome

- **AST Implementation**: Correctness and completeness of the `ASTGeneration` class
- **Node Usage**: Proper utilization of node classes from `AST/headers/AST.hpp` and `AST/src/AST.cpp`
- **Test Coverage**: Quality and comprehensiveness of AST generation test cases
- **Structure Accuracy**: AST must correctly represent the source program structure

---

## Project Structure

```
.
├── Makefile                    # Cross-platform build automation
├── CMakeLists.txt              # CMake's configuration file to build the project
├── main.cpp                    # Main project entrypoint
├── main.hpp                    # Main project libraries, used in the project
├── README.md                   # Project documentation
├── tyc_specification.md        # Language specification
├── external/                   # External dependencies
│   ├── jar_file
│   │   └──antlr-4.13.2-complete.jar
│   └── antlr4-cpp-runtime 
├── Grammar/                    # Grammar definitions
│   ├── src/                    # Grammar source code
│   │   ├── TyC.g4              # ANTLR4 grammar specification
│   │   ├── lexererr.hpp        # Custom lexer error class definitions
│   │   └── lexererr.cpp        # Implementation for custom lexer error class
│   ├── target/                 # Generated file by ANTLR4
├── AST/                        # AST definitions
│   ├── headers/                # AST headers
│   │   ├── AST.hpp             # AST node class definitions
│   │   └── ASTGeneration.hpp   # ASTGeneration class definitions
│   ├── src/                    # AST source code
│   │   ├── AST.cpp             # Implementation of AST node class and Base Visitor
│   │   └── ASTGeneration.cpp   # Implementation of ASTGeneration class
├── Checker/                    # Static Checker definitions
│   ├── headers/                # Static Checker headers
│   │   ├── StaticChecker.hpp   # StaticChecker class definitions
│   │   └── StaticError.hpp     # StaticError class definitions
│   ├── src/                    # Static Checker source code
│   │   ├── StaticChecker.cpp   # Implementation of StaticChecker class
│   │   └── StaticError.cpp     # Implementation of StaticError class
├── CodeGenerator/              # Code Generator definitions
│   ├── headers/                # Code Generator headers
│   │   ├── MachineCode.hpp     # MachineCode and JasminCode class definitions
│   │   ├── Emitter.hpp         # Emitter class definitions
│   │   ├── Frame.hpp           # Frame class definitions
│   │   ├── CodeGenerator.hpp   # CodeGenerator class definitions
│   │   └── CodeGenError.hpp    # CodeGenError class definitions
│   ├── src/                    # Static Checker source code
│   │   ├── MachineCode.cpp     # Implementation of MachineCode and JasminCode class
│   │   ├── Emitter.cpp         # Implementation of Emitter class
│   │   ├── Frame.cpp           # Implementation of Frame class
│   │   ├── CodeGenerator.cpp   # Implementation of CodeGenerator class
│   │   └── CodeGenError.cpp    # Implementation of CodeGenError class
└── tests/                      # Test suite
    ├── headers/                # headers for testing
    │   ├── LexerSuite.hpp      # LexerSuite class definitions
    │   ├── ParserSuite.hpp     # ParserSuite class definitions
    │   ├── ASTGenSuite.hpp     # ASTGenSuite class definitions
    │   ├── CheckerSuite.hpp    # CheckerSuite class definitions
    │   ├── CodeGenSuite.hpp    # CodeGenSuite class definitions
    │   └── TestUtils.hpp       # Testing utilities class definitions
    ├── src/                    # source code for testing
    │   ├── LexerSuite.cpp      # Implementation of LexerSuite class
    │   ├── ParserSuite.cpp     # Implementation of ParserSuite class
    │   ├── ASTGenSuite.cpp     # Implementation of ASTGenSuite class
    │   ├── CheckerSuite.cpp    # Implementation of CheckerSuite class
    │   ├── CodeGenSuite.cpp    # Implementation of CodeGenSuite class
    │   └── TestUtils.cpp       # Implementation of Testing utilities class
    ├── testcases/              # Testcases folder
    └── solutions/              # Solutions folder
```

## Quick Start

### Prerequisites

- **CMake** (recommended for building and compiling the project)
- **MinGW-w64** (recommended for C++17)
- **Java Runtime Environment (JRE) 8+** (required for ANTLR4)

### Setup

1. **Clone the repository:**
   ```bash
   cd TyC_CPP
   ```

2. **Generate MinGW-compatible Makefiles:**
   ```bash
   cmake -G "MinGW Makefiles" .
   ```

3. **Build the target**
   ```bash
   make
   ```

4. **Check for dependencies**
   ```bash
   ./main check
   ```

5. **Compile ANTLR grammar files**
   ```bash
   ./main gen
   ```

5. **Run the code with file main.tyc in the root directory**
   ```bash
   ./main run
   ```

6. **Run tests (update later):**
    ```bash
   ./main test <TestSuite>
   ```

Where `<TestSuite>` is one of the following:
- `LexerSuite`
- `ParserSuite`
- `ASTGenSuite`
- `CheckerSuite`
- `CodeGenSuite`

## Available Commands (after generating MinGW-compatible Makefiles and building the target):

- `./main check`                - Check for dependencies
- `./main gen`                  - Install dependencies and set up environment
- `./main run`                  - Run the project (with a custom main.tyc file in the root directory)
- `./main test <TestSuite>`     - Run the test cases

## License

This project is developed for educational purposes as part of the **Principles of Programming Languages** course.

**Author for the custom language**: MEng. Trần Ngọc Bảo Duy

**Author for the source code**:
  - **Orginal source file (in Python)**: MEng. Trần Ngọc Bảo Duy
  - **Source file in C++**: Đoàn Hồng Hiếu Kiên

**Institution**: Faculty of Computer Science and Engineering, Ho Chi Minh City University of Technology, VNU-HCM
