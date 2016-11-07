cmake_minimum_required(VERSION 2.8)

project(parallel_sort)

find_package(OpenMP REQUIRED)

list( APPEND CMAKE_MODULE_PATH 
  "${CMAKE_SOURCE_DIR}/../cmake/Modules")

find_package(TBB REQUIRED)
include_directories( ${TBB_INCLUDE_DIRS} )

add_subdirectory(src)


