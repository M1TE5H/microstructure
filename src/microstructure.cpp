/**
 * \file  microstructure/src/microstructure.cpp
 * \brief Main Definitions
 * \todo  add license matter
 *
 * MICROSTRUCTURE (C) 2022--PRESENT // DR. MITESH PATEL @M1TE5H
 *
 */

#include "microstructure.hpp"

void microstructure::version() {
  printf("microstructure\tversion %d.%d.%d\n", MICROSTRUCTURE_VERSION_MAJOR,
         MICROSTRUCTURE_VERSION_MINOR, MICROSTRUCTURE_VERSION_PATCH);

  // utilities
  microstructure::utilities::utl::version();
  
  // tools
  microstructure::tools::tool::version();

  // libraries
  microstructure::libraries::learner::version();
  microstructure::libraries::solver::version();
  microstructure::libraries::subroutine::version();
}

// default method for microbenchmarking
void microstructure::method () {}