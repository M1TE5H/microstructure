#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>

namespace front {

class test {
public:
  static inline constexpr auto i_matrix_vector_transformation{
      R"( auto transform ( Vector v ) with ( Matrix m ); )"};

  static inline constexpr auto o_matrix_vector_transformation{
      R"( auto transform@with ( Vector v, Matrix m ); )"};
};

} // namespace front

auto main(int argc, char* argv[]) -> int { return EXIT_SUCCESS; }