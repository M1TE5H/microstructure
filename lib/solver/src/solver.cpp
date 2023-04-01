/**
 * \file  microstructure/lib/solver/src/solver.cpp
 * \brief Solver
 */


#include "solver.hpp"

void microstructure::libraries::solver::version () {
    printf("solver\tversion %d.%d.%d\n", MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MAJOR,
         MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_MINOR,
         MICROSTRUCTURE_LIBRARIES_SOLVER_VERSION_PATCH);
}