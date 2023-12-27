cmake_minimum_required (VERSION 3.5)

project (GridSnake)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -pthread")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (include_dir "${source_dir}/include/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (GridSnake ${source_files})

target_include_directories(GridSnake PUBLIC /usr/include/SFML)
target_include_directories(GridSnake PUBLIC ${include_dir})
target_link_libraries(GridSnake sfml-system sfml-window sfml-graphics)

