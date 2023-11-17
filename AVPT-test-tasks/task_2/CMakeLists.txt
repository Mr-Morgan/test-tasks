cmake_minimum_required(VERSION 3.5)

project(task_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task_2 main.cpp
    readme.md
    iobuffer.h iobuffer.cpp)

include(GNUInstallDirs)
install(TARGETS task_2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
