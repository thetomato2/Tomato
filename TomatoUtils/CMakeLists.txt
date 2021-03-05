#TomatoDX is my personal DIRECT3D implemenation files

cmake_minimum_required (VERSION 3.8)

project(TomatoUtils VERSION 0.1 LANGUAGES CXX)

# set sources variable
set(TomatoUtils_SRCS
	src/Test.cpp
)

set(TomatoUtils_HDRS
	src/Console.h
	src/Test.h
)

add_library(TomUtils ${TomatoUtils_SRCS} ${TomatoUtils_HDRS})

target_include_directories(TomUtils
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	)