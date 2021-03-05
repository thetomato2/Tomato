#TomatoWin is used to handle Windows apps 

cmake_minimum_required (VERSION 3.8)

project(TomatoUtils VERSION 0.1 LANGUAGES CXX)

# set sources variable
set(TomatoWin_SRCS
	"src/Window.cpp"
	"src/Keyboard.cpp"
	"src/Mouse.cpp"
)

set(TomatoWin_HDRS
	"src/Window.h"
	"src/TomatoWindows.h"
	"src/Keyboard.h"
	"src/Mouse.h"
)

add_library(TomWin ${TomatoWin_SRCS} ${TomatoWin_HDRS})

target_link_libraries(TomWin PRIVATE TomUtils)

target_include_directories(TomWin
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	)