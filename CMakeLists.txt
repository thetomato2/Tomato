cmake_minimum_required(VERSION 3.23)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/msvc_toolchain.cmake)

project ("Tomato Engine"
        VERSION 0.1
        DESCRIPTION "Graphics renderer/game engine"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_UNITY_BUILD OFF)

set(BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(BUILD_DIR ${CMAKE_CURRENT_LIST_DIR}/build)
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

find_package(Vulkan REQUIRED)

set(ASSET_DIR ${CMAKE_CURRENT_LIST_DIR}/assets)

file(GLOB_RECURSE ASSETS
    ${ASSET_DIR}/*.*
    )



if(MSVC)
list(APPEND COMPILE_FLAGS  
    -Gr
    /EHsc
    /MP8
    # /W4
    /WX
    /GR-
    /FC
    -fp:fast
    -fp:except-
    )

list(APPEND LINKER_FLAGS
    -incremental:no
    )

else()
list(APPEND COMPILE_FLAGS 
        -fno-exceptions
        -fno-rtti
        # -Wall
        # -Wextra
        # -Wpedantic
        # -Werror
        -fms-extensions
        -Wno-gnu-anonymous-struct 
        -Wno-nested-anon-types
        -Wno-missing-braces

        -Wno-unused-variable
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-missing-field-initializers
    )
endif()

add_executable(Tomato WIN32
    src/core/Core.h
    src/main.cpp
)

target_include_directories(Tomato PUBLIC src)

target_link_options(Tomato PRIVATE
    ${LINKER_FLAGS}
    # -NODEFAULTLIB
)

# add_dependencies(Tomato Shaders)

target_compile_options(Tomato PUBLIC ${COMPILE_FLAGS})
target_compile_definitions(Tomato PUBLIC 
    $<$<CONFIG:Debug>:TOM_DEBUG>
    $<$<CONFIG:Release>:TOM_RELEASE>
    )

# add_custom_command(
#     TARGET Tomato POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSET_DIR} $<TARGET_FILE_DIR:Tomato>/assets DEPENDS ${ASSETS}
# )

add_custom_command(
    TARGET Tomato PRE_BUILD
    COMMAND ctime -begin ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tomato.ctm
)

add_custom_command(
    TARGET Tomato POST_BUILD
    COMMAND ctime -end ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Tomato.ctm
    )


# find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)
# ## find all the shader files under the shaders folder
# file(GLOB_RECURSE GLSL_SOURCE_FILES
#     "${PROJECT_SOURCE_DIR}/shaders/*.frag.glsl"
#     "${PROJECT_SOURCE_DIR}/shaders/*.vert.glsl"
#     "${PROJECT_SOURCE_DIR}/shaders/*.comp.glsl"
#     )
#
# ## iterate each shader
# foreach(GLSL ${GLSL_SOURCE_FILES})
#   message(STATUS "BUILDING SHADER")
#   get_filename_component(FILE_NAME ${GLSL} NAME)
#   set(SPIRV "${BUILD_DIR}/bin/shaders/${FILE_NAME}.spv")
#   message(STATUS ${GLSL})
#   ##execute glslang command to compile that specific shader
#   add_custom_command(
#     OUTPUT ${SPIRV}
#     COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
#     DEPENDS ${GLSL})
#   list(APPEND SPIRV_BINARY_FILES ${SPIRV})
# endforeach(GLSL)
#
# add_custom_target(
#     Shaders 
#     DEPENDS ${SPIRV_BINARY_FILES}
#     )
#
#
