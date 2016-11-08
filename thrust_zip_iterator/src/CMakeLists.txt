

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
add_executable( zip_iterator_test main.cpp)

set_target_properties(zip_iterator_test PROPERTIES
  COMPILE_FLAGS "${OpenMP_CXX_FLAGS}")

set_target_properties(zip_iterator_test PROPERTIES
  LINK_FLAGS "${OpenMP_CXX_FLAGS}")


