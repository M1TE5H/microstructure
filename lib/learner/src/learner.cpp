/**
 * \file  microstructure/lib/learner/src/learner.cpp
 * \brief Learner
 */


#include "learner.hpp"

void microstructure::libraries::learner::version () {
    printf("learner\tversion %d.%d.%d\n", MICROSTRUCTURE_LIBRARIES_LEARNER_VERSION_MAJOR,
         MICROSTRUCTURE_LIBRARIES_LEARNER_VERSION_MINOR,
         MICROSTRUCTURE_LIBRARIES_LEARNER_VERSION_PATCH);
}