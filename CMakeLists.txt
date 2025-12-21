cmake_minimum_required(VERSION 3.15)
project(XSmall-HMI-Player VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

message(STATUS "Downloading SFML...")

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW TRUE
)

set(SFML_STATIC_LIBRARIES ON CACHE BOOL "Build static libraries" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "Disable audio" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Disable network" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Disable examples" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "Disable docs" FORCE)

FetchContent_MakeAvailable(sfml)
message(STATUS "SFML downloaded (static)")

message(STATUS "Downloading Google Test...")

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
    GIT_SHALLOW TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
message(STATUS "Google Test downloaded")

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${PROJECT_ROOT}/include
    ${sfml_SOURCE_DIR}/include
)

set(SOURCES
    src/main.cpp
    src/VariableDatabase.cpp
    src/VisualObject.cpp
    src/Rectangle.cpp
    src/Text.cpp
    src/Line.cpp
    src/Polyline.cpp
    src/InputField.cpp
    src/Button.cpp
    src/Image.cpp
    src/HistoryGraph.cpp
    src/SceneFactory.cpp
    src/HmiPlayer.cpp
    src/JSONSceneLoader.cpp  
)

add_executable(HMI_Player ${SOURCES})

target_compile_definitions(HMI_Player PRIVATE SFML_STATIC)

target_link_libraries(HMI_Player PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

if(WIN32)
    target_link_libraries(HMI_Player PRIVATE
        opengl32
        winmm
        gdi32
    )
endif()

file(COPY ${PROJECT_ROOT}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "Main app configured (static)")


add_subdirectory(tests)
