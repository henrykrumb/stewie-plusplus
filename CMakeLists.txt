project(stewie++)

cmake_minimum_required(VERSION 3.1)

set(CXX_STANDARD 17)
add_compile_options(-std=c++17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


include(src/CMakeLists.txt)

add_library(stewie++ SHARED ${SOURCES})
target_link_libraries(stewie++
		curses
		pthread)


include(examples/CMakeLists.txt)

add_executable(examples ${EXAMPLE_SOURCES})
target_link_libraries(examples
		stewie++
		pthread)
