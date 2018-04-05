cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(
    TARGETS
    "threads"
    "mt-sort"
)

find_package (Threads)

foreach (target ${TARGETS})
    add_executable("${target}" "${target}.cpp")
    target_link_libraries("${target}" ${CMAKE_THREAD_LIBS_INIT})
endforeach(target)
