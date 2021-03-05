cmake_minimum_required(VERSION 3.8)

project(App VERSION 1.0 LANGUAGES CXX)

add_executable(App WIN32 "src/WinMain.cpp" "src/Application.h" "src/Application.cpp")
target_include_directories(App PRIVATE src/)

target_link_libraries(App PRIVATE TDX)
target_link_libraries(App PRIVATE TomWin)
target_link_libraries(App PRIVATE TomUtils)
target_link_libraries(App PRIVATE Lua)
