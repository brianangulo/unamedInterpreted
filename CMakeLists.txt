cmake_minimum_required(VERSION 3.23)
project(interpreter_c C)

set(CMAKE_C_STANDARD 99)

add_executable(interpreter_c main.c lexer/tokens.c file/file.c)
