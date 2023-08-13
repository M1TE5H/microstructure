# ==============================================================================
# ZMICROSTRUCTURE | CMAKE
# ==============================================================================

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

# ==============================================================================
# COMPILATION
# ==============================================================================

set ( CMAKE_CXX_STANDARD 23 )

# ==============================================================================
# LIBRARY
# ==============================================================================

set (
    ZMICROSTRUCTURE_PROJECT_NAME
    zmicrostructure
)


set (
    ZMICROSTRUCTURE_LIBRARY_NAME
    zmicrostructure
)


project ( zmicrostructure )


set (
    ZMICROSTRUCTURE_HEADERS_DIR
    zinclude/${ZMICROSTRUCTURE_LIBRARY_NAME}
)

set (
    ZMICROSTRUCTURE_HEADERS
    ${ZMICROSTRUCTURE_HEADERS_DIR}/zmicrostructure.hpp
)


set (
    ZMICROSTRUCTURE_SOURCE_DIR
    zsrc
)

set (
    ZMICROSTRUCTURE_SOURCE
    ${ZMICROSTRUCTURE_SOURCE_DIR}/zmicrostructure.cpp
)


add_library (
    ${ZMICROSTRUCTURE_LIBRARY_NAME} STATIC
    ${ZMICROSTRUCTURE_HEADERS}
    ${ZMICROSTRUCTURE_SOURCE}
)


target_include_directories (
    ${ZMICROSTRUCTURE_LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/zinclude/${ZMICROSTRUCTURE_LIBRARY_NAME}>
    $<INSTALL_INTERFACE:zinclude/${ZMICROSTRUCTURE_LIBRARY_NAME}>
)

target_include_directories (
    ${ZMICROSTRUCTURE_LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/zinclude>
    $<INSTALL_INTERFACE:zinclude>
)

target_compile_definitions (
    ${ZMICROSTRUCTURE_LIBRARY_NAME} PRIVATE
    ZMICROSTRUCTURE_CXX_STANDARD=${ZMICROSTRUCTURE_CXX_STANDARD}
)

# ==============================================================================
# TESTS
# ==============================================================================

add_subdirectory ( ztest )


# ==============================================================================
# APPLICATIONS
# ==============================================================================

# add_subdirectory ( zapplications )