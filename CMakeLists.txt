cmake_minimum_required(VERSION 3.10)
project(StudentGradeCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include)

add_executable(StudentGradeCalculator 
    src/main.cpp 
    src/Student.cpp 
    src/Utils.cpp
)