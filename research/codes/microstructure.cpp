#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <array>
#include <execution>
#include <iostream>
#include <mutex>
#include <thread>

#include <concepts>
#include <coroutine>
#include <format>
#include <ranges>
#include <span>

/// @note naive alternatives (not intended for actual use)
namespace nonstd {

template <class... Args>
void print(std::FILE* stream, std::format_string<Args...> fmt, Args&&... args) {
  stream << std::format(fmt, args...);
}

template <class... Args>
void print(std::format_string<Args...> fmt, Args&&... args) {
  std::cout << std::format(fmt, args...);
}

/// @todo "range"-based algorithms with parallel execution policies

} // namespace nonstd

/// @todo ...
namespace microstructure {

template <std::floating_point CoordinateT, std::size_t DimensionN>
class location {
public:
  using value_type             = CoordinateT;
  using pointer                = CoordinateT*;
  using reference              = CoordinateT&;
  using const_pointer          = CoordinateT const*;
  using const_reference        = CoordinateT const&;

  using container              = std::array<CoordinateT, DimensionN>;
  using iterator               = container::iterator;
  using const_iterator         = container::const_iterator;
  using reverse_iterator       = container::reverse_iterator;
  using const_reverse_iterator = container::const_reverse_iterator;

public:
public:
private:
  container m_coordinate;
};

} // namespace microstructure

int main(int argc, char* argv[], char* env[]) {
  nonstd::print("{}|{}\n", "microstructure", "research");
  std::exit(EXIT_SUCCESS);
}