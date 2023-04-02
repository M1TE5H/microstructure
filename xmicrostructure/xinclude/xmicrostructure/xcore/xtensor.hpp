#pragma once

namespace xmicrostructure {

/**
 * \brief R-rank tensor label
 */

enum class rank { scalar = 0, vector = 1, tensor2 = 2, tensor4 = 4 };

// ================================

/**
 * \brief D-dimensional tensor label
 */

enum class dimension { one = 1, two = 2, three = 3 };

constexpr std::size_t dimension_t(dimension const& d) {
  switch (d) {
  case dimension::one:
    return 1;
    break;
  case dimension::two:
    return 2;
    break;
  case dimension::three:
    return 3;
    break;
  default:
    return 1;
    break;
  }
}

// ================================

/**
 * \brief R-Rank and D-Dimensional Tensor Size with Redundancies
 * \todo  Correction for Redundacies
 */

constexpr std::size_t tensor_t(rank const& r, dimension const& d) {
  switch (r) {
  case rank::scalar:
    return 1;
    break;
  case rank::vector:
    return dimension_t(d);
    break;
  case rank::tensor2:
    return dimension_t(d) * dimension_t(d);
  case rank::tensor4:
    return dimension_t(d) * dimension_t(d) * dimension_t(d) * dimension_t(d);
    break;
  default:
    return 1;
    break;
  }
}

// ================================

/**
 * \brief Default Formation Policies
 * \todo  <unfinished>
 */

struct formation_left;

// ================================

/**
 * \class tensor
 * \todo  overload,...
 */

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol = formation_left>
class tensor {

public:
  using index_t = std::size_t;

  // --------------------------------

public:
  ArithmeticT& operator()(index_t i) { return value[i]; }

  ArithmeticT const operator()(index_t i) const { return value[i]; }

  // --------------------------------

private:
  std::array<ArithmeticT, tensor_t(R, D)> value;
};

// ================================

/**
 * \brief Template Specialisations
 * \todo  <unfinished>
 */

// ================================

} // namespace xmicrostructure

// Material Tensor
// Rank-0 (Scalar)
// Rank-1 (Vector)
// Rank-2 (Tensor e.g. Distortion)
// Rank-4 (Tensor e.g. Constants)