#include <benchmark/benchmark.h>

#include <microstructure/microstructure.hpp>

static void BM_MicrostructureMethod ( benchmark::State& state ) {
    for ( auto _ : state ) {
        microstructure::method (); // method to be timed
    }
}

BENCHMARK ( BM_MicrostructureMethod );

BENCHMARK_MAIN ();