cmake_minimum_required(VERSION 3.10)
project(Project-Zombie-Shooter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project-Zombie-Shooter main.cpp MainResources.h Protagonist.cpp Protagonist.h Background.cpp Background.h Game.cpp MapEditor.cpp MapEditor.h Game.h UI_Button.cpp UI_Button.h MainWindow.cpp MainWindow.h MainMenu.cpp MainMenu.h colorPalette.h Tile.cpp Tile.h  fb_to_sfml.h GameResources.cpp GameResources.h Collision.cpp Collision.h Zombie.cpp Zombie.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Project-Zombie-Shooter ${SFML_LIBRARIES})
endif()
