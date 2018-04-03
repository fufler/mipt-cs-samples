cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    TARGETS
    "fork-and-wait"
    "fork-bomb"
    "fork"
    "pid"
    "several-forks-then-wait"
    "true-and-false"
)

foreach (target ${TARGETS})
    add_executable("${target}" "${target}.cpp")
endforeach(target)
