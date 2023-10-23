cmake_minimum_required(VERSION 3.5)

project(yandex_pay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yandex_pay main.cpp
    base64.cpp base64.h)

include(GNUInstallDirs)
install(TARGETS yandex_pay
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
