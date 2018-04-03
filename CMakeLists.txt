cmake_minimum_required(VERSION 3.1)

set(
    PROJECTS
    "linux-system-programming-overview"
)

foreach(project ${PROJECTS})
    add_subdirectory(${project})
endforeach(project)

