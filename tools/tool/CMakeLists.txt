# ----------------------------------------------------------------
# CMAKE
# ----------------------------------------------------------------
cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    CMAKE_CXX_STANDARD
    20
)

set (
    PROJECT_NAME
    tool
)

set (
    TOOL_NAME
    tool
)

# ----------------------------------------------------------------
# HEADERS
# ----------------------------------------------------------------

set (
    TOOL_HEADERS_DIR
    include/${TOOL_NAME}
)

set (
    TOOL_HEADERS
    ${TOOL_HEADERS_DIR}/tool.hpp
)

# ----------------------------------------------------------------
# SOURCE
# ----------------------------------------------------------------

set (
    TOOL_SOURCE_DIR
    src
)

set (
    TOOL_SOURCE
    ${TOOL_SOURCE_DIR}/tool.cpp
)

# ----------------------------------------------------------------
# VERSION
# ----------------------------------------------------------------

file (
    READ
    ${TOOL_HEADERS_DIR}/version.hpp
    TOOL_VERSION_FILE
)

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_TOOLS_TOOL_VERSION_MAJOR ([0-9]*)"
    _MICROSTRUCTURE_TOOLS_TOOL_VERSION_MAJOR
    ${TOOL_VERSION_FILE}
)

set ( MICROSTRUCTURE_TOOLS_TOOL_VERSION_MAJOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_TOOLS_TOOL_VERSION_MINOR ([0-9]*)"
    _MICROSTRUCTURE_TOOLS_TOOL_VERSION_MINOR
    ${TOOL_VERSION_FILE}
)

set ( MICROSTRUCTURE_TOOLS_TOOL_VERSION_MINOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_TOOLS_TOOL_VERSION_PATCH ([0-9]*)"
    _MICROSTRUCTURE_TOOLS_TOOL_VERSION_PATCH
    ${TOOL_VERSION_FILE}
)

set ( MICROSTRUCTURE_TOOLS_TOOL_VERSION_PATCH ${CMAKE_MATCH_1} )

# ----------------------------------------------------------------
# UTILITIES
# ----------------------------------------------------------------

set (
    MICROSTRUCTURE_UTILITIES
    utl
)

# ----------------------------------------------------------------
# PROJECT
# ----------------------------------------------------------------

project (
    ${PROJECT_NAME}
    VERSION
        "${MICROSTRUCTURE_TOOLS_TOOL_VERSION_MAJOR}.${MICROSTRUCTURE_TOOLS_TOOL_VERSION_MINOR}.${MICROSTRUCTURE_TOOLS_TOOL_VERSION_PATCH}"
    DESCRIPTION
        "Tailored Toolkits"
    LANGUAGES
        C CXX
)

message (
    STATUS
    "${MICROSTRUCTURE_FRAMEWORK_NAME}|${PROJECT_NAME} ${PROJECT_VERSION}"
)

add_library (
    ${TOOL_NAME} STATIC
    ${TOOL_HEADERS}
    ${TOOL_SOURCE}
)

target_include_directories (
    ${TOOL_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${TOOL_NAME}>
    $<INSTALL_INTERFACE:include/${TOOL_NAME}>
)

target_include_directories (
    ${TOOL_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries (
    ${TOOL_NAME} PUBLIC
    ${MICROSTRUCTURE_UTILITIES}
)

# ----------------------------------------------------------------
# TESTING
# ----------------------------------------------------------------

if ( ${ENABLE_TESTS} )

    add_subdirectory ( test )

endif ( ${ENABLE_TESTS} )