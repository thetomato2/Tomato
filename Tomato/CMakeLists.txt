# CMakeList.txt : CMake project for Tomato, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project("TomatoEngine" VERSION 0.01) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(TomatoConfig.h.in TomatoConfig.h)

# Add source to this project's executable.
add_executable (Tomato "Tomato.cpp"  )

# TODO: Add tests and install targets if needed.

target_include_directories(Tomato PUBLIC
							"${PROJECT_BINARY_DIR}"
							)
