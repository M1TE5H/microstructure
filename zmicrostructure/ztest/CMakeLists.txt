# ==============================================================================
# ZMICROSTRUCTURE : ZTEST | CMAKE
# ==============================================================================

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

# ==============================================================================
# COMPILATION
# ==============================================================================

set ( CMAKE_CXX_STANDARD 23 )

add_executable ( zlocation.test zlocation.test.cpp )
target_link_libraries ( zlocation.test zmicrostructure )

# add_executable ( zmicrostructure.test zmicrostructure.test.cpp )
# target_link_libraries ( zmicrostructure.test zmicrostructure )