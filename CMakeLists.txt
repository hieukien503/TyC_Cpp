cmake_minimum_required(VERSION 3.5.0)

project(TyC)

add_definitions(-DANTLR4CPP_STATIC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "C:\\MINGW\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\MINGW\\bin\\g++.exe")

include_directories(
  ${PROJECT_SOURCE_DIR}/AST/headers
  ${PROJECT_SOURCE_DIR}/Checker/headers
  ${PROJECT_SOURCE_DIR}/Grammar
  ${PROJECT_SOURCE_DIR}/Grammar/src
  ${PROJECT_SOURCE_DIR}/Grammar/src/atn
  ${PROJECT_SOURCE_DIR}/Grammar/src/dfa
  ${PROJECT_SOURCE_DIR}/Grammar/src/internal
  ${PROJECT_SOURCE_DIR}/Grammar/src/misc
  ${PROJECT_SOURCE_DIR}/Grammar/src/support
  ${PROJECT_SOURCE_DIR}/Grammar/src/tree
  ${PROJECT_SOURCE_DIR}/Grammar/src/tree/pattern
  ${PROJECT_SOURCE_DIR}/Grammar/src/tree/xpath
)

file(GLOB SOURCES
  "${PROJECT_SOURCE_DIR}/main.cpp"
  "${PROJECT_SOURCE_DIR}/AST/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/Checker/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/atn/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/dfa/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/internal/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/misc/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/support/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/tree/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/tree/pattern/*.cpp"
  "${PROJECT_SOURCE_DIR}/Grammar/src/tree/xpath/*.cpp"
)

add_executable(main ${SOURCES})
