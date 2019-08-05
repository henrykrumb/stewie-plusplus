project(stewie++)

cmake_minimum_required(VERSION 3.1)

set(CXX_STANDARD 17)

if (UNIX)
	add_compile_options("-std=c++14")
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR})
elseif (WIN32)
	add_compile_options("/std:c++latest")
	set(LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/lib" CACHE STRING "additional library dir")
	link_directories("${LIBS_PATH}/pdcurses/wincon")
	include_directories("${LIBS_PATH}/pdcurses")
endif ()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include(src/CMakeLists.txt)
include(include/CMakeLists.txt)


if (UNIX)
	add_library(stewie++ SHARED ${SOURCES})
	target_link_libraries(stewie++ ncurses pthread)
elseif (WIN32)
	add_library(stewie++ STATIC ${SOURCES})
	target_link_libraries(stewie++ pdcurses.lib)
endif ()

include(examples/CMakeLists.txt)

if (UNIX)
	add_executable(examples ${EXAMPLE_SOURCES})
	target_link_libraries(examples stewie++ ncurses pthread)
elseif (WIN32)
	add_executable(examples ${SOURCES} ${EXAMPLE_SOURCES})
	target_link_libraries(examples stewie++ pdcurses.lib)
endif ()
