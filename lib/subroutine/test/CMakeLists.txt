# ------------------------------------------------------------------------------
# CMAKE
# ------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

set (
    LIBRARY_TEST_NAME
    subroutine_test
)

set (
    LIBRARY_TEST_SOURCE
    subroutine.test.cpp
)

project ( ${LIBRARY_TEST_NAME} )

enable_testing ()

if ( NOT ( TARGET gtest AND TARGET gtest_main ) )
    # TODO: address this fatal error
    message ( FATAL_ERROR "Missing Targets: gtest and gtest_main" )
endif ()

add_executable (
    ${LIBRARY_TEST_NAME}
    ${LIBRARY_TEST_SOURCE}
)

target_link_libraries (
    ${LIBRARY_TEST_NAME}
    gtest
    gtest_main
    ${LIBRARY_NAME}
)

add_test (
    ${LIBRARY_TEST_NAME}
    ${LIBRARY_TEST_NAME}
)