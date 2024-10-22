cmake_minimum_required(VERSION 3.20)

# Project info setup
project(game-of-life VERSION 2.0 LANGUAGES CXX)

# Compiler norm to use
set(CMAKE_CXX_STANDARD 17)

# External libs directory
set(EXTERNALS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)

# Add all source files in src/ excluding main.cpp
file(GLOB_RECURSE SOURCES_FILES src/*.cpp)

# Add include directory
set(HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Creating executable
add_executable(${PROJECT_NAME} ${SOURCES_FILES})

# Add headers to executable
target_include_directories(${PROJECT_NAME} PRIVATE
    ${HEADERS_DIR}
)

# Adding libs includes to project lib
add_subdirectory(externals/SDL)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${EXTERNALS_DIR}/SDL/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)

# if(WIN32)
# # If on win32 env, Copy SDL2.dll to the build folder after the executable is built
# add_custom_command(
# TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy_if_different
# "${CMAKE_BINARY_DIR}/externals/SDL/$<CONFIG>/$<IF:$<CONFIG:Debug>,SDL2d.dll,SDL2.dll>"
# "${CMAKE_BINARY_DIR}/$<CONFIG>/$<IF:$<CONFIG:Debug>,SDL2d.dll,SDL2.dll>"
# COMMENT "Copying SDL2 DLL to the build folder"
# )
# endif()
