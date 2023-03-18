/**
 * \file  microstructure/utilities/utl/src/utl.cpp
 * \brief Generalised Utilities Suite
 */

#include "utl.hpp"

void microstructure::utilities::utl::version() {
  printf("utl\tversion %d.%d.%d\n", MICROSTRUCTURE_UTILITIES_UTL_VERSION_MAJOR,
         MICROSTRUCTURE_UTILITIES_UTL_VERSION_MINOR,
         MICROSTRUCTURE_UTILITIES_UTL_VERSION_PATCH);
}