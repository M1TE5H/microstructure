# ------------------------------------------------------------------------------
# CMAKE
# ------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

set (
    CMAKE_CXX_STANDARD
    23
)

set (
    PROJECT_NAME
    solver
)

set (
    LIBRARY_NAME
    solver
)

# ------------------------------------------------------------------------------
# HEADERS
# ------------------------------------------------------------------------------

set (
    LIBRARY_HEADERS_DIR
    include/${LIBRARY_NAME}
)

set (
    LIBRARY_HEADERS
    ${LIBRARY_HEADERS_DIR}/solver.hpp
)

# ------------------------------------------------------------------------------
# SOURCE
# ------------------------------------------------------------------------------

set (
    LIBRARY_SOURCE_DIR
    src
)

set (
    LIBRARY_SOURCE
    ${LIBRARY_SOURCE_DIR}/solver.cpp
)

# ------------------------------------------------------------------------------
# VERSION
# ------------------------------------------------------------------------------

file (
    READ
    ${LIBRARY_HEADERS_DIR}/version.hpp
    LIBRARY_VERSION_FILE
)

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MAJOR ([0-9]*)"
    _MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MAJOR
    ${LIBRARY_VERSION_FILE}
)

set ( MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MAJOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MINOR ([0-9]*)"
    _MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MINOR
    ${LIBRARY_VERSION_FILE}
)

set ( MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MINOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_PATCH ([0-9]*)"
    _MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_PATCH
    ${LIBRARY_VERSION_FILE}
)

set ( MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_PATCH ${CMAKE_MATCH_1} )

# ------------------------------------------------------------------------------
# UTILITIES
# ------------------------------------------------------------------------------

set (
    MICROSTRUCTURE_UTILITIES
    utl
)

# ------------------------------------------------------------------------------
# TOOLS
# ------------------------------------------------------------------------------

set (
    MICROSTRUCTURE_TOOLS
    tool
)

# ------------------------------------------------------------------------------
# PROJECT
# ------------------------------------------------------------------------------

project (
    ${PROJECT_NAME}
    VERSION
        "${MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MAJOR}.${MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MINOR}.${MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_PATCH}"
    DESCRIPTION
        "Solver"
    LANGUAGES
        C CXX
)

message (
    STATUS
    "${MICROSTRUCTURE_FRAMEWORK_NAME}|${PROJECT_NAME} ${PROJECT_VERSION}"
)

add_library (
    ${LIBRARY_NAME} STATIC
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCE}
)

target_include_directories (
    ${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories (
    ${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries (
    ${LIBRARY_NAME} PUBLIC
    ${MICROSTRUCTURE_UTILITIES}
    ${MICROSTRUCTURE_TOOLS}
)

# ------------------------------------------------------------------------------
# TESTING
# ------------------------------------------------------------------------------

if ( ${ENABLE_TESTS} )

    add_subdirectory ( test )

endif ( ${ENABLE_TESTS} )