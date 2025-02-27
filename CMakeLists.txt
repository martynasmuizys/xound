cmake_minimum_required(VERSION 3.21)
project(
    xound
    VERSION 0.1.0
    LANGUAGES CXX)

# set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
# set(CMAKE_DEFAULT_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui")
add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

set(UI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/ui.cpp)
set(AUDIO_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/soundboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio/effects.cpp)

add_executable(xound src/main.cpp ${UI_SOURCES} ${AUDIO_SOURCES})

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    message("-- Building for Windows")
    target_link_libraries(xound PRIVATE imgui SDL3::SDL3-static ${OPENGL_LIBRARY})
else()
    message("-- Building for Linux")
    target_link_libraries(xound PRIVATE imgui SDL3::SDL3 ${OPENGL_LIBRARY})
endif()

target_compile_options(
    xound PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=
    -fdiagnostics-color=always)
