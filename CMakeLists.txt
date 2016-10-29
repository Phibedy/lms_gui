project(LMS_GUI C CXX)

cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    "src/qt_visulation.cpp"
    "src/main_window.cpp"
    "src/main.cpp"
    "src/overview.cpp"
    "src/logging.cpp"
    "src/profiling.cpp"
    "src/graph.cpp"
    "src/data_collector.cpp"
)

set(HEADERS
    "include/qt_visulation.h"
    "include/main_window.h"
    "include/overview.h"
    "include/logging.h"
    "include/profiling.h"
    "include/graph.h"
    "include/data_collector.h"
)

#set compiler flags
if((${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wreturn-type -Wpedantic ")
endif()

#QT
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Charts)

include_directories(include)
add_executable(qt_visulation ${SOURCES} ${HEADERS})
target_link_libraries(qt_visulation PRIVATE ${CONAN_LIBS} Qt5::Widgets Qt5::Charts Qt5Core)
