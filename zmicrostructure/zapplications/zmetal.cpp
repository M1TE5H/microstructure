#include <zmicrostructure/zmicrostructure.hpp>

/// @note pollution for convenience
using namespace zmicrostructure;

int main() {

  static_assert(zlocatable<zlocation<int>>);
  constexpr zlocation<int> a{42, 24};
  constexpr zlocation<int> b{24, 42};
  constexpr auto           c1{a + b};
  constexpr zlocation<int> c2{a.horizontal() + b.horizontal(),
                              a.vertical() + b.vertical()};
  static_assert(c1 == c2);
}