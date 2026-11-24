cmake_minimum_required(VERSION 3.16)

project(LaMarquesina LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt genera código extra para Q_OBJECT (moc) y para los recursos .qrc (rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

qt_add_executable(LaMarquesina
    main.cpp
    Juego.h Juego.cpp
    Cuerpo.h Cuerpo.cpp
    Persona.h Persona.cpp
    Obstaculos.h Obstaculos.cpp
    Tiposagente.h Tiposagente.cpp

)

target_link_libraries(LaMarquesina PRIVATE Qt6::Widgets Qt6::Multimedia)

# En Windows: que no abra una consola negra junto al juego
set_target_properties(LaMarquesina PROPERTIES WIN32_EXECUTABLE ON)

