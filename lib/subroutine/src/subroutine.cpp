/**
 * \file  microstructure/lib/subroutine/src/subroutine.cpp
 * \brief 
 */


#include "subroutine.hpp"

void microstructure::libraries::subroutine::version () {
    printf("subroutine\tversion %d.%d.%d\n", MICROSTRUCTURE_LIBRARIES_SUBROUTINE_VERSION_MAJOR,
         MICROSTRUCTURE_LIBRARIES_SUBROUTINE_VERSION_MINOR,
         MICROSTRUCTURE_LIBRARIES_SUBROUTINE_VERSION_PATCH);
}