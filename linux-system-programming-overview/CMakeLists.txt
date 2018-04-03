cmake_minimum_required(VERSION 3.1)

set(
    PROJECTS
    "00-intro"
    "01-fork"
    "02-argc-argv-envp"
    "03-files"
    "04-pipes"
    "05-sysv-ipc"
    "06-posix-threads"
    "07-sockets"
)

foreach(project ${PROJECTS})
    add_subdirectory(${project})
endforeach(project)

