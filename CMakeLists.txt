cmake_minimum_required(VERSION 3.15)
project(TyC LANGUAGES CXX)

# Install reproc++ and Catch2 using FetchContent
include(FetchContent)

# reproc++
set(REPROC++ ON)
FetchContent_Declare(
    reproc
    GIT_REPOSITORY https://github.com/DaanDeMeyer/reproc.git
    GIT_TAG        v14.2.4
)

# Catch2
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)

FetchContent_MakeAvailable(reproc Catch2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
# ANTLR4 runtime
add_subdirectory(
    ${PROJECT_SOURCE_DIR}/external/antlr4-cpp-runtime
)

# Required for static runtime on MinGW
target_compile_definitions(antlr4_static PUBLIC ANTLR4CPP_STATIC)

# Grammar (generated files)
add_library(grammar
    ${PROJECT_SOURCE_DIR}/Grammar/src/lexererr.cpp
    ${PROJECT_SOURCE_DIR}/Grammar/target/TyCBaseVisitor.cpp
    ${PROJECT_SOURCE_DIR}/Grammar/target/TyCVisitor.cpp
    ${PROJECT_SOURCE_DIR}/Grammar/target/TyCLexer.cpp
    ${PROJECT_SOURCE_DIR}/Grammar/target/TyCParser.cpp
)

target_include_directories(grammar PUBLIC
    ${PROJECT_SOURCE_DIR}/Grammar/src
    ${PROJECT_SOURCE_DIR}/Grammar/target
)

target_link_libraries(grammar PUBLIC antlr4_static)

# AST
add_library(ast
    ${PROJECT_SOURCE_DIR}/AST/src/AST.cpp
    ${PROJECT_SOURCE_DIR}/AST/src/ASTGeneration.cpp
)

target_include_directories(ast PUBLIC
    ${PROJECT_SOURCE_DIR}/AST/headers
)

# Static Checker
add_library(checker
    ${PROJECT_SOURCE_DIR}/StaticChecker/src/StaticChecker.cpp
    ${PROJECT_SOURCE_DIR}/StaticChecker/src/StaticError.cpp
)

target_include_directories(checker PUBLIC
    ${PROJECT_SOURCE_DIR}/StaticChecker/headers
)

# Code Generator
add_library(codegen
    ${PROJECT_SOURCE_DIR}/CodeGenerator/src/CodeGenerator.cpp
    ${PROJECT_SOURCE_DIR}/CodeGenerator/src/CodeGenError.cpp
    ${PROJECT_SOURCE_DIR}/CodeGenerator/src/Emitter.cpp
    ${PROJECT_SOURCE_DIR}/CodeGenerator/src/Frame.cpp
    ${PROJECT_SOURCE_DIR}/CodeGenerator/src/MachineCode.cpp
)

target_include_directories(codegen PUBLIC
    ${PROJECT_SOURCE_DIR}/CodeGenerator/headers
)

# Testing (optional)
add_executable(compiler_tests
    test/src/LexerSuite.cpp
    test/src/ParserSuite.cpp
    test/src/ASTGenSuite.cpp
    test/src/CheckerSuite.cpp
    test/src/CodeGenSuite.cpp
    test/src/TestUtils.cpp
)

target_include_directories(compiler_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/test/headers
)

target_link_libraries(compiler_tests PRIVATE
    Catch2::Catch2WithMain
    grammar
    ast
    checker
    codegen
)

# CTest + Catch2 integration
include(CTest)
include(Catch)

catch_discover_tests(compiler_tests)

# Executable
add_executable(main
    main.cpp
)

target_link_libraries(main
    ast
    checker
    codegen
    grammar
    reproc++
)