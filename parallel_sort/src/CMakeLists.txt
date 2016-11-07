

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
add_executable( parallel_sort main.cpp )

target_link_libraries(parallel_sort ${TBB_LIBRARIES})

set_target_properties(parallel_sort PROPERTIES
    LINK_FLAGS "${OpenMP_CXX_FLAGS}")


