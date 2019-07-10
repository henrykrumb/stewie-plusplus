project(stewie++)

cmake_minimum_required(VERSION 3.1)

set(CXX_STANDARD 17)

IF (UNIX)
	#	add_compile_options("-std=c++17")
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR})
ELSE (WIN32)
	#	add_compile_options(/std:c++17)
	set(LIBS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
	link_directories("${LIBS_PATH}/pdcurses/wincon")
	include_directories("${LIBS_PATH}/pdcurses")
ENDIF (UNIX)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include(src/CMakeLists.txt)

IF (UNIX)
	add_library(stewie++ SHARED ${SOURCES})
	target_link_libraries(stewie++ ncurses pthread)
ELSE (WIN32)
	add_library(stewie++ STATIC ${SOURCES})
	target_link_libraries(stewie++ pdcurses.lib)
ENDIF (UNIX)

include(examples/CMakeLists.txt)

IF (UNIX)
	add_executable(examples ${EXAMPLE_SOURCES})
	target_link_libraries(examples stewie++ ncurses pthread)
ELSE (WIN32)
	add_executable(examples ${SOURCES} ${EXAMPLE_SOURCES})
	target_link_libraries(examples pdcurses.lib)
ENDIF (UNIX)
