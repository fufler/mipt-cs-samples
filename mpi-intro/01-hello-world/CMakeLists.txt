cmake_minimum_required(VERSION 3.1)

# This causes compilation error in Travis CI due to
# invalid suffix on literal; C++11 requires a space between literal and string macro [-Werror=literal-suffix]
#
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})

add_executable("hello" "hello.cpp")

target_link_libraries("hello" ${MPI_CXX_LIBRARIES})

