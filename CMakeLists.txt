cmake_minimum_required(VERSION 3.7)
project(minecraft_launch_proxy)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

aux_source_directory(src/ SOURCES)

find_package(Qt5 COMPONENTS Network REQUIRED)

add_executable(minecraft_launch_proxy ${SOURCES})

target_link_libraries(minecraft_launch_proxy Qt5::Network)