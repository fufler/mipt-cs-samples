cmake_minimum_required(VERSION 3.1)

set(
    PROJECTS
    "01-input-output"
)

foreach(project ${PROJECTS})
    add_subdirectory(${project})
endforeach(project)

