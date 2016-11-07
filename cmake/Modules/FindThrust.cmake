# Try to find Thrust
# Once done, this will define
# THRUST_FOUND
# THRUST_INCLUDE_DIRS

find_path( THRUST_INCLUDE_DIR
  thrust/version.h
  HINTS
  /usr/include/cuda
  /usr/local/cuda/include
  DOC "Thrust headers"
  )

find_package_handle_standard_args(Thrust  DEFAULT_MSG THRUST_INCLUDE_DIR )
mark_as_advanced( THRUST_INCLUDE_DIR )
set( THRUST_INCLUDE_DIRS ${THRUST_INCLUDE_DIR} )

