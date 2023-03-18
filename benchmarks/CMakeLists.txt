# ----------------------------------------------------------------
# CMAKE
# ----------------------------------------------------------------
cmake_minimum_required ( VERSION 3.14..3.25 )

set (
    MICROSTRUCTURE_BENCHMARK_NAME
    microstructure_benchmark
)

set (
    MICROSTRUCTURE_BENCHMARK_SOURCE
    microstructure_benchmark.cpp
)

project ( ${MICROSTRUCTURE_BENCHMARK_NAME} )

add_executable (
    ${MICROSTRUCTURE_BENCHMARK_NAME}
    ${MICROSTRUCTURE_BENCHMARK_SOURCE}
)

target_link_libraries (
    ${MICROSTRUCTURE_BENCHMARK_NAME}
    benchmark::benchmark
    ${MICROSTRUCTURE_FRAMEWORK_NAME}
)

add_test (
    ${MICROSTRUCTURE_BENCHMARK_NAME}
    ${MICROSTRUCTURE_BENCHMARK_NAME}
)