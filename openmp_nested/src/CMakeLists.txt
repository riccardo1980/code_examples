

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
add_executable( openmp_nested main.cpp)

set_target_properties(openmp_nested PROPERTIES
  COMPILE_FLAGS "${OpenMP_CXX_FLAGS}")

set_target_properties(openmp_nested PROPERTIES
  LINK_FLAGS "${OpenMP_CXX_FLAGS}")




