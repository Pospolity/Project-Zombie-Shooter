cmake_minimum_required(VERSION 3.10)
project(Project-Zombie-Shooter)

set(CMAKE_CXX_STANDARD 11)

add_executable(Project-Zombie-Shooter main.cpp GameResources.cpp GameResources.h IGameObject.h Protagonist.cpp Protagonist.h Background.cpp Background.h game.cpp mapEditor.cpp mapEditor.h game.h UI_Button.cpp UI_Button.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Project-Zombie-Shooter ${SFML_LIBRARIES})
endif()
