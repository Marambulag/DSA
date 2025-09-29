cmake_minimum_required(VERSION 3.12)
project(VisualDSA LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

file(GLOB SRC_FILES
    src/*.cpp
)

add_executable(VisualDSA ${SRC_FILES})

target_include_directories(VisualDSA PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(VisualDSA PRIVATE sfml-graphics sfml-window sfml-system)
