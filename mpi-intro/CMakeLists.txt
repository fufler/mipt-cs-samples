cmake_minimum_required(VERSION 3.1)

set(
    PROJECTS
    01-hello-world
)

foreach(project ${PROJECTS})
    add_subdirectory(${project})
endforeach(project)

