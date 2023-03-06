cmake_minimum_required(VERSION 3.23)
project(interpreter_c LANGUAGES CXX C)

set(CMAKE_C_STANDARD 99)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        b796f7d44681514f58a683a3a71ff17c94edb0c1 # release-1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(interpreter_c main.c lexer/tokens.c file/file.c)

add_executable(interpreter_tests tests/lexer_tests.cc lexer/tokens.c)

target_link_libraries(
        interpreter_tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(interpreter_tests)
