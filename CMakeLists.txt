cmake_minimum_required(VERSION 3.27)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        first_follow.cpp
        first_follow.h
        BaseLexicalAnalyzer.cpp
        BaseLexicalAnalyzer.h
        PythonLogicLA.cpp
        PythonLogicLA.h
        Tree.cpp
        Tree.h
        PythonLogicParser.cpp
        PythonLogicParser.h
)
