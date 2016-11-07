cmake_minimum_required(VERSION 2.8)

project(thrust_zip_iterator)

find_package(OpenMP REQUIRED)

list( APPEND CMAKE_MODULE_PATH 
  "${CMAKE_SOURCE_DIR}/../cmake/Modules")

find_package(Thrust REQUIRED)

include_directories( ${THRUST_INCLUDE_DIRS})
add_definitions(-DTHRUST_DEVICE_SYSTEM=THRUST_DEVICE_SYSTEM_OMP)

add_subdirectory(src)


