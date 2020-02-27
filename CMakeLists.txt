cmake_minimum_required(VERSION 3.0)
project(Snake2)

set(CMAKE_CXX_STANDARD 11)

file(GLOB CPPS "*.cpp")
file(GLOB CPPS2 "source/*")
file(GLOB HS "header/*")

add_executable(${PROJECT_NAME} ${CPPS} ${CPPS2} ${HS})
