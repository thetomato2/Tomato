#TomatoUtils conatain many helper classes

cmake_minimum_required (VERSION 3.8)

project(TomatoUtils VERSION 0.1 LANGUAGES CXX)

# set sources variable
set(TomatoUtils_SRCS
	"src/TomatoException.cpp"
	"src/Log.cpp"
	"src/ServiceLocator.cpp"
	"src/StringConverter.cpp"
)

set(TomatoUtils_HDRS
	"src/TomatoException.h"
	"src/Log.h"
	"src/ServiceLocator.h"
	"src/StringConverter.h"
)

add_library(TomUtils ${TomatoUtils_SRCS} ${TomatoUtils_HDRS})

target_include_directories(TomUtils
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	)