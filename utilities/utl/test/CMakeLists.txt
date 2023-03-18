# ----------------------------------------------------------------
# CMAKE
# ----------------------------------------------------------------
cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    UTILITY_TEST_NAME
    utl_test
)

set (
    UTILITY_TEST_SOURCE
    utl_test.cpp
)

project ( ${UTILITY_TEST_NAME} )

enable_testing ()

if ( NOT ( TARGET gtest AND TARGET gtest_main ) )
    # TODO: address this fatal error
    message ( FATAL_ERROR "Missing Targets: gtest and gtest_main" )
endif ()

add_executable (
    ${UTILITY_TEST_NAME}
    ${UTILITY_TEST_SOURCE}
)

target_link_libraries (
    ${UTILITY_TEST_NAME}
    gtest
    gtest_main
    ${UTILITY_NAME}
)

add_test (
    ${UTILITY_TEST_NAME}
    ${UTILITY_TEST_NAME}
)