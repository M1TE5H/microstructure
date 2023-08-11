# ==============================================================================
# ZMICROSTRUCTURE : ZAPPLICATIONS | CMAKE
# ==============================================================================

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

# ==============================================================================
# COMPILATION
# ==============================================================================

set ( CMAKE_CXX_STANDARD 23 )

add_executable ( zmetal zmetal.cpp )

target_link_libraries ( zmetal zmicrostructure ) 