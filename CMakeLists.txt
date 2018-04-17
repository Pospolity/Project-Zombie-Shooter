cmake_minimum_required(VERSION 3.10)
project(Project-Zombie-Shooter)

set(CMAKE_CXX_STANDARD 11)

add_executable(Project-Zombie-Shooter main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Project-Zombie-Shooter ${SFML_LIBRARIES})
endif()
