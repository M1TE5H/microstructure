#include "xmicrostructure.hpp"

void xmicrostructure::version() {
  xmicrostructure::println(
      "xmicrostructure {}.{}.{}", X_MICROSTRUCTURE_VERSION_MAJOR,
      X_MICROSTRUCTURE_VERSION_MINOR, X_MICROSTRUCTURE_VERSION_PATCH);
}

int xmicrostructure::EntrancePoint(int argc, char *argv[]) {
  return EXIT_SUCCESS;
}