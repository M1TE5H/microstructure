# ================================================================
# MICROSTRUCTURE | CMAKE
# ================================================================
cmake_minimum_required( VERSION 3.14..3.25 )

# ================================================================
# OPTIONS
# ================================================================

# TODO: Compiler Options / Flags / Extensions

# Note: directories:
#   external for submodule (.gitmodules)
#   exclude for local
option ( ENABLE_LOCAL "Enable Local Development Environment" ON )

if ( ${ENABLE_LOCAL} )
    set ( EX_DIR exclude )
else ()
    set ( EX_DIR external )
endif ( ${ENABLE_LOCAL} )


option ( ENABLE_TESTS "Conduct Tests" OFF )
option ( ENABLE_BENCHMARKS "Conduct Benchmarks" OFF )

option ( ENABLE_BOOST "Enable Boost" OFF )
option ( ENABLE_FORMAT "Enable Format" OFF )
option ( ENABLE_DOXYGEN "Enable Doxygen" OFF )

# ================================================================
# COMPILATION
# ================================================================

# Note: C++20
set (
    CMAKE_CXX_STANDARD
    20
)

set (
    CMAKE_CXX_EXTENSIONS
    OFF
)

set (
    COMPILE_FLAGS
    -Wall
    -Wextra
    -pendantic
)

set ( GLOBAL PROPERTY USE_FOLDERS ON )

# ================================================================
# FRAMEWORK
# ================================================================

set (
    MICROSTRUCTURE_PROJECT_NAME
    "microstructure"
)

set (
    MICROSTRUCTURE_FRAMEWORK_NAME
    "microstructure"
)

# ----------------------------------------------------------------
# HEADERS
# ----------------------------------------------------------------
set (
    MICROSTRUCTURE_HEADERS_DIR
    include/${MICROSTRUCTURE_FRAMEWORK_NAME}
)

set (
    MICROSTRUCTURE_HEADERS
    ${MICROSTRUCTURE_HEADERS_DIR}/microstructure.hpp
)

# ----------------------------------------------------------------
# SOURCE
# ----------------------------------------------------------------

set (
    MICROSTRUCTURE_SOURCE_DIR
    src
)

set (
    MICROSTRUCTURE_SOURCE
    ${MICROSTRUCTURE_SOURCE_DIR}/microstructure.cpp
)

# ----------------------------------------------------------------
# VERSION
# ----------------------------------------------------------------

file (
    READ
    ${MICROSTRUCTURE_HEADERS_DIR}/version.hpp
    MICROSTRUCTURE_VERSION_FILE
)

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_VERSION_MAJOR ([0-9]*)"
    _MICROSTRUCTURE_VERSION_MAJOR
    ${MICROSTRUCTURE_VERSION_FILE}
)

set ( MICROSTRUCTURE_VERSION_MAJOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_VERSION_MINOR ([0-9]*)"
    _MICROSTRUCTURE_VERSION_MINOR
    ${MICROSTRUCTURE_VERSION_FILE}
)

set ( MICROSTRUCTURE_VERSION_MINOR ${CMAKE_MATCH_1} )

string (
    REGEX MATCH
    "#define MICROSTRUCTURE_VERSION_PATCH ([0-9]*)"
    _MICROSTRUCTURE_VERSION_PATCH
    ${MICROSTRUCTURE_VERSION_FILE}
)

set ( MICROSTRUCTURE_VERSION_PATCH ${CMAKE_MATCH_1} )

# ----------------------------------------------------------------
# PROJECT
# ----------------------------------------------------------------

project (
    microstructure
    VERSION
        "${MICROSTRUCTURE_VERSION_MAJOR}.${MICROSTRUCTURE_VERSION_MINOR}.${MICROSTRUCTURE_VERSION_PATCH}"
    DESCRIPTION
        "Framework for Efficient Simulation and Beautified Visualisation of Multiscale Mesomechanics"
    LANGUAGES
        C CXX
)

message (
    STATUS
    "${MICROSTRUCTURE_FRAMEWORK_NAME} ${PROJECT_VERSION}"
)

# ----------------------------------------------------------------
# LIBRARY
# ----------------------------------------------------------------

add_library (
    ${MICROSTRUCTURE_FRAMEWORK_NAME} STATIC
    ${MICROSTRUCTURE_HEADERS}
    ${MICROSTRUCTURE_SOURCE}
)

target_include_directories (
    ${MICROSTRUCTURE_FRAMEWORK_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${MICROSTRUCTURE_FRAMEWORK_NAME}>
    $<INSTALL_INTERFACE:include/${MICROSTRUCTURE_FRAMEWORK_NAME}>
)

target_include_directories (
    ${MICROSTRUCTURE_FRAMEWORK_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ================================================================
# TESTING
# ================================================================

include ( CTest )

if ( ${ENABLE_TESTS} )

    enable_testing ()
    add_subdirectory ( ${EX_DIR}/googletest )
    include_directories (
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
    )

    add_subdirectory ( test )

endif ( ${ENABLE_TESTS} )

# ================================================================
# BENCHMARKS
# ================================================================

if ( ${ENABLE_BENCHMARKS} )

    add_subdirectory ( ${EX_DIR}/benchmark )
    include_directories (
        ${benchmark_SOURCE_DIR}/include
        ${benchmark_SOURCE_DIR}
    )

    add_subdirectory ( benchmarks )

endif ()

# ================================================================
# DOCUMENTATION
# ================================================================

if ( ${ENABLE_DOXYGEN} )

    find_package( Doxygen )
    
    if ( Doxygen_FOUND )
        add_subdirectory ( doc )
    else ()
        message ( STATUS "Doxygen not found so documentation will not be built." )
    endif ()

endif ( ${ENABLE_DOXYGEN} )

# ================================================================
# DEPENDENCIES
# ================================================================

# Note: Third-Parties

# ----------------------------------------------------------------
# BOOST
# ----------------------------------------------------------------

if ( ${ENABLE_BOOST} )
    find_package ( Boost REQUIRED )
endif ( ${ENABLE_BOOST} )

# ----------------------------------------------------------------
# FORMAT
# ----------------------------------------------------------------

if ( ${ENABLE_FORMAT} )

    include ( FetchContent )

    FetchContent_Declare (
        fmtlib
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 5.3.0
    )

endif ( ${ENABLE_FORMAT} )

# ================================================================
# UTILITIES
# ================================================================
set (
    MICROSTRUCTURE_UTILITIES_DIR
    utilities
)

set (
    MICROSTRUCTURE_UTILITIES
    utl
)

foreach ( UTILITY ${MICROSTRUCTURE_UTILITIES} )
    add_subdirectory ( ${MICROSTRUCTURE_UTILITIES_DIR}/${UTILITY} )
endforeach ( UTILITY ${MICROSTRUCTURE_UTILITIES} )

# ================================================================
# TOOLS
# ================================================================
set (
    MICROSTRUCTURE_TOOLS_DIR
    tools
)

set (
    MICROSTRUCTURE_TOOLS
    tool
)

foreach ( TOOL ${MICROSTRUCTURE_TOOLS} )
    add_subdirectory ( ${MICROSTRUCTURE_TOOLS_DIR}/${TOOL} )
endforeach ( TOOL ${MICROSTRUCTURE_TOOLS} )

# ================================================================
# LIBRARIES
# ================================================================
set (
    MICROSTRUCTURE_LIBRARIES_DIR
    lib
)

set (
    MICROSTRUCTURE_LIBRARIES
    subroutine
)

foreach ( LIBRARY ${MICROSTRUCTURE_LIBRARIES} )
    add_subdirectory ( ${MICROSTRUCTURE_LIBRARIES_DIR}/${LIBRARY} )
endforeach ( LIBRARY ${MICROSTRUCTURE_LIBRARIES} )



# ================================================================
# LINKAGE
# ================================================================

# Note: Link Boost and fmtlib as needed i.e.
# target_link_libraries (
#    ${MICROSTRUCTURE_FRAMEWORK} Boost fmtlib
# )

target_link_libraries (
    ${MICROSTRUCTURE_FRAMEWORK_NAME}
    ${MICROSTRUCTURE_UTILITIES}
    ${MICROSTRUCTURE_TOOLS}
    ${MICROSTRUCTURE_LIBRARIES}
)

# ================================================================
# APPLICATIONS
# ================================================================
add_subdirectory ( applications)