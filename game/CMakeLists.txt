cmake_minimum_required(VERSION 3.10)
project(BulletHell LANGUAGES CXX)

# Set C++ standard and build type
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set only for debugging / release
set(CMAKE_BUILD_TYPE Debug)

# Automatically collect all source and header files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h")

# Make sure CMAKE_SOURCE_DIR is correct
message("\t\t MEOW CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Platform-specific configuration for linking RayLib
if(WIN32)
    add_compile_options(/W0)
    # Windows-specific settings
    include_directories(${CMAKE_SOURCE_DIR}/../raylib-5.5_win64_msvc16/include)
    link_directories(${CMAKE_SOURCE_DIR}/../raylib-5.5_win64_msvc16/lib)
elseif(UNIX)
    # Linux-specific settings
    include_directories(${CMAKE_SOURCE_DIR}/../raylib-5.5_linux_amd64/include)
    link_directories(${CMAKE_SOURCE_DIR}/../raylib-5.5_linux_amd64/lib)
else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

# Add ImGui and rlImGui files
file(GLOB IMGUI_SRC_FILES
    "${CMAKE_SOURCE_DIR}/../imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/../rlImGui/rlImGui.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/../imgui/"
    "${CMAKE_SOURCE_DIR}/../rlImGui/"
)

# Add an executable target
add_executable(game ${SRC_FILES} ${HEADER_FILES} ${IMGUI_SRC_FILES})

# Include additional directories if needed
target_include_directories(game PRIVATE include)

# This links the raylib library to the game target
target_link_libraries(game PRIVATE raylib)

# If on windows, link winmm since raylib needs it
if(WIN32)
    target_link_libraries(game PRIVATE winmm)
endif()
