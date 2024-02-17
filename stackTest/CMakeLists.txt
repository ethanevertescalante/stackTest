cmake_minimum_required(VERSION 3.25)
project(stackTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(stackTest main.cpp TraversableStack.cpp TraversableStack.hpp Token.cpp Token.hpp TagParser.cpp TagParser.hpp Tokenizer.cpp Tokenizer.hpp)
