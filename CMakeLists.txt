cmake_minimum_required(VERSION 3.16)

project(ProyectoLamarquesina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProyectoLamarquesina main.cpp
    Clases.h
    Clases.cpp)

include(GNUInstallDirs)
install(TARGETS ProyectoLamarquesina
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
