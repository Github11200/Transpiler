cmake_minimum_required(VERSION 4.0)
project(Transpiler LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Transpiler main.cpp src/lexer.cpp src/token.cpp src/utils.cpp)
target_include_directories(Transpiler
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
