cmake_minimum_required(VERSION 3.5)

project(prog_avanc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog_avanc main.cpp sculptor.h sculptor.cpp figurageometrica.h)

install(TARGETS prog_avanc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
