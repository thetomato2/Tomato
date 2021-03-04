#  _______                    _        
# |__   __|                  | |       
#    | | ___  _ __ ___   __ _| |_ ___  
#    | |/ _ \| '_ ` _ \ / _` | __/ _ \ 
#    | | (_) | | | | | | (_| | || (_) |
#    |_|\___/|_| |_| |_|\__,_|\__\___/ 
#
# Derek Nord
# derekj.nord@gmail.com
# github.com/thetomato2
#-----------------------------------------------------
cmake_minimum_required (VERSION 3.8)

# Use ROOT variables in find_package
cmake_policy(SET CMP0014 NEW)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
##################################################################
# Initialize Project
project (Tomato)


##################################################################
# Global Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Global compile definitions since add_definitions() adds for all.
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
  $<$<CONFIG:Debug>:DEBUG;_DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
  $<$<CONFIG:MinSizeRel>:NDEBUG>
  $<$<CONFIG:RelWithDebInfo>:NDEBUG>
)

##################################################################
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}")

# Include sub-projects.
add_subdirectory ("TomatoDX")
add_subdirectory("App")

# Pre-Compiled HEaders
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
	target_precompile_headers("${PROJECT_NAME}" PUBLIC 
		<iostream> <memory> <utility> <algorithm> <functional> <sstream>
		<vector> <string> <unordered_map> <unordered_set>)
endif()
