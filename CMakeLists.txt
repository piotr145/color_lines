cmake_minimum_required(VERSION 2.8)

project(color_lines)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -O2")
endif()

set(EXECUTABLE_NAME "color_lines")

set(sources
    "src/board.cpp"
    "src/main.cpp"
    "src/game.cpp"
    "src/config.cpp"
)

add_executable(${EXECUTABLE_NAME} ${sources})

# Detect and add SFML
set(CMAKE_MODULE_PATH "/usr/share/cmake-3.4/Modules" ${CMAKE_MODULE_PATH})

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

