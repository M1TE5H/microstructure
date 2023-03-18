/**
 * \file  microstructure/tools/tool/src/tool.cpp
 * \brief Tailored Toolkit
 */

#include "tool.hpp"

void microstructure::tools::tool::version() {
  printf("tool\tversion %d.%d.%d\n", MICROSTRUCTURE_TOOLS_TOOL_VERSION_MAJOR,
         MICROSTRUCTURE_TOOLS_TOOL_VERSION_MINOR,
         MICROSTRUCTURE_TOOLS_TOOL_VERSION_PATCH);
}