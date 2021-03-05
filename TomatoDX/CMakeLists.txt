#TomatoDX is my personal DIRECT3D implemenation files

cmake_minimum_required (VERSION 3.8)

project(TomatoDX VERSION 0.1 LANGUAGES CXX)

# set sources variable
set(TomatoDX_SRCS
	"src/TomatoDX.cpp"
)

set(TomatoDX_HDRS
)

add_library(TDX ${TomatoDX_SRCS} ${TomatoDX_HDRS})

target_link_libraries(TDX PRIVATE "d3d11" "dxgi" "D3DCompiler" "Gdiplus")

target_include_directories(TDX 
	PUBLIC
	$<INSTALL_INTERFACE:include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	)
