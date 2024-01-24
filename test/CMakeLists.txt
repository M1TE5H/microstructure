# ------------------------------------------------------------------------------
# CMAKE
# ------------------------------------------------------------------------------

cmake_minimum_required ( VERSION 3.14..3.25 FATAL_ERROR )

set (
    MICROSTRUCTURE_TEST_NAME
    microstructure_test
)

set (
    MICROSTRUCTURE_TEST_SOURCE
    microstructure.test.cpp
)

project ( ${MICROSTRUCTURE_TEST_NAME} )

enable_testing ()

if ( NOT ( TARGET gtest AND TARGET gtest_main ) )

    message ( FATAL_ERROR "Missing Targets: gtest and gtest_main" )

endif ()

add_executable (
    ${MICROSTRUCTURE_TEST_NAME}
    ${MICROSTRUCTURE_TEST_SOURCE}
)

target_link_libraries (
    ${MICROSTRUCTURE_TEST_NAME}
    gtest
    gtest_main
    ${MICROSTRUCTURE_FRAMEWORK_NAME}
)

add_test (
    ${MICROSTRUCTURE_TEST_NAME}
    ${MICROSTRUCTURE_TEST_NAME}
)