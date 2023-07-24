cmake_minimum_required(VERSION 3.15)

project(finance-lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

file(GLOB SOURCES "src/*.cpp")

add_executable(FINANCE-LIB main.cpp ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/eigen-3.4.0)


enable_testing()
add_test(NAME tests COMMAND tests)
