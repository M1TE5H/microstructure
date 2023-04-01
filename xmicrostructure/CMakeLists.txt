cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

option ( ENABLE_TESTS "Enable Tests" ON )

set (
    CMAKE_CXX_STANDARD 20
)

project (
    xmicrostructure
    VERSION
        0.0.0
    DESCRIPTION
        "EXPERIMENTATION | PROOF-OF-CONCEPT & MINIMAL WORKING EXAMPLE"
    LANGUAGES
        C CXX
)

set (
    X_MICROSTRUCTURE_FRAMEWORK_NAME
    xmicrostructure
)

set (
    X_MICROSTRUCTURE_HEADER_DIR
    xinclude/xmicrostructure
)

set (
    X_MICROSTRUCTURE_UTILTIES
    xutilities/xformatter/xformatter.hpp
)

set (
    X_MICROSTRUCTURE_TOOLS
)

set (
    X_MICROSTRUCTURE_LIBRARIES
    xlib/xlearner/xlearner.hpp
    xlib/xsolver/xsolver.hpp
)

set (
    X_MICROSTRUCTURE_HEADERS
    ${X_MICROSTRUCTURE_HEADER_DIR}/xmicrostructure.hpp
    ${X_MICROSTRUCTURE_HEADER_DIR}/xcore.hpp
    ${X_MICROSTRUCTURE_HEADER_DIR}/xcore/xkernel.hpp
    ${X_MICROSTRUCTURE_HEADER_DIR}/xsimulation.hpp
    ${X_MICROSTRUCTURE_HEADER_DIR}/xvisualisation.hpp
)

set (
    X_MICROSTRUCTURE_SOURCE_DIR
    xsrc
)

set (
    X_MICROSTRUCTURE_SOURCE
    ${X_MICROSTRUCTURE_SOURCE_DIR}/xmicrostructure.cpp
    ${X_MICROSTRUCTURE_SOURCE_DIR}/xsimulation.cpp
    ${X_MICROSTRUCTURE_SOURCE_DIR}/xvisualisation.cpp
    ${X_MICROSTRUCTURE_UTILTIES}
    ${X_MICROSTRUCTURE_TOOLS}
    ${X_MICROSTRUCTURE_LIBRARIES}
)

add_library (
    ${X_MICROSTRUCTURE_FRAMEWORK_NAME} STATIC
    ${X_MICROSTRUCTURE_HEADERS}
    ${X_MICROSTRUCTURE_SOURCE}
)

target_include_directories (
    ${X_MICROSTRUCTURE_FRAMEWORK_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xinclude/${X_MICROSTRUCTURE_FRAMEWORK_NAME}>
    $<INSTALL_INTERFACE:include/${X_MICROSTRUCTURE_FRAMEWORK_NAME}>
)

target_include_directories (
    ${X_MICROSTRUCTURE_FRAMEWORK_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/xinclude>
    $<INSTALL_INTERFACE:xinclude>
)

find_package ( fmt )

target_link_libraries ( xmicrostructure fmt::fmt )

if ( ${ENABLE_TESTS} )
    add_subdirectory ( xtest )
endif ( ${ENABLE_TESTS} )

add_subdirectory ( xapplications )