# ------------------------------------------------------------------------------
# UTL | CMAKE
# ------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

set (
    CMAKE_CXX_STANDARD
    23
)

set (
    PROJECT_NAME
    utl
)

set (
    UTILITY_NAME
    utl
)

# ------------------------------------------------------------------------------
# HEADERS
# ------------------------------------------------------------------------------

set (
    UTILITY_HEADERS_DIR
    include/${UTILITY_NAME}
)

set (
    UTILITY_HEADERS
    ${UTILITY_HEADERS_DIR}/utl.hpp
)

# ------------------------------------------------------------------------------
# SOURCE
# ------------------------------------------------------------------------------

set (
    UTILITY_SOURCE_DIR
    src
)

set (
    UTILITY_SOURCE
    ${UTILITY_SOURCE_DIR}/utl.cpp
)

# ------------------------------------------------------------------------------
# VERSION
# ------------------------------------------------------------------------------

file (
    READ
    ${UTILITY_HEADERS_DIR}/version.hpp
    UTILITY_VERSION_FILE
)

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_UTILITIES_UTL_VERSION_MAJOR ([0-9]*)"
    _MICROSTRUCTURE_UTILITIES_UTL_VERSION_MAJOR
    ${UTILITY_VERSION_FILE}
)

set ( MICROSTRUCTURE_UTILITIES_UTL_VERSION_MAJOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_UTILITIES_UTL_VERSION_MINOR ([0-9]*)"
    _MICROSTRUCTURE_UTILITIES_UTL_VERSION_MINOR
    ${UTILITY_VERSION_FILE}
)

set ( MICROSTRUCTURE_UTILITIES_UTL_VERSION_MINOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_UTILITIES_UTL_VERSION_PATCH ([0-9]*)"
    _MICROSTRUCTURE_UTILITIES_UTL_VERSION_PATCH
    ${UTILITY_VERSION_FILE}
)

set ( MICROSTRUCTURE_UTILITIES_UTL_VERSION_PATCH ${CMAKE_MATCH_1} )

# ------------------------------------------------------------------------------
# PROJECT
# ------------------------------------------------------------------------------

project (
    ${PROJECT_NAME}
    VERSION
        "${MICROSTRUCTURE_UTILITIES_UTL_VERSION_MAJOR}.${MICROSTRUCTURE_UTILITIES_UTL_VERSION_MINOR}.${MICROSTRUCTURE_UTILITIES_UTL_VERSION_PATCH}"
    DESCRIPTION
        "Generalised Utilities Suite"
    LANGUAGES
        C CXX
)

message (
    STATUS
    "${MICROSTRUCTURE_FRAMEWORK_NAME}|${PROJECT_NAME} ${PROJECT_VERSION}"
)

add_library (
    ${UTILITY_NAME} STATIC
    ${UTILITY_HEADERS}
    ${UTILITY_SOURCE}
)

target_include_directories (
    ${UTILITY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${UTILITY_NAME}>
    $<INSTALL_INTERFACE:include/${UTILITY_NAME}>
)

target_include_directories (
    ${UTILITY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ------------------------------------------------------------------------------
# TESTING
# ------------------------------------------------------------------------------

if ( ${ENABLE_TESTS} )

    add_subdirectory ( test )

endif ( ${ENABLE_TESTS} )