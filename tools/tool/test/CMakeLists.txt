# ------------------------------------------------------------------------------
# CMAKE
# ------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    TOOL_TEST_NAME
    tool_test
)

set (
    TOOL_TEST_SOURCE
    tool.test.cpp
)

project ( ${TOOL_TEST_NAME} )

enable_testing ()

if ( NOT ( TARGET gtest AND TARGET gtest_main ) )

    # TODO: address this fatal error
    message ( FATAL_ERROR "Missing Targets: gtest and gtest_main" )

endif ()

add_executable (
    ${TOOL_TEST_NAME}
    ${TOOL_TEST_SOURCE}
)

target_link_libraries (
    ${TOOL_TEST_NAME}
    gtest
    gtest_main
    ${TOOL_NAME}
)

add_test (
    ${TOOL_TEST_NAME}
    ${TOOL_TEST_NAME}
)