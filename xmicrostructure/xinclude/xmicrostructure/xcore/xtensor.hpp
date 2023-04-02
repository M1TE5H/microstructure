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

struct formation_across; // l-to-r stride

// ================================

/**
 * \class tensor
 * \brief Generic Tensor
 * \todo  overload,...
 */

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol = formation_across>
class tensor;

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol>
std::ostream& operator<< ( std::ostream&, tensor<ArithmeticT, R, D, FormationPol> const& );

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol>
class tensor {

public:
  using tensor_type = tensor<ArithmeticT, R, D, FormationPol>;
  using value_type = ArithmeticT;
  using pointer = ArithmeticT*;
  using const_pointer = ArithmeticT const*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using difference_type = std::make_signed_t<size_type>;
  // using iterator = [?]
  // using const_iterator = [?]
  // using reverse_iterator = std::reverse_iterator<iterator>;
  // using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using index_t = std::size_t;

  // --------------------------------

public:

    // CONSTRUCTORS
  tensor () {}

public:
  // ASSIGNMENT: COPY, MOVE, ...

  tensor_type& operator=(tensor_type const& other) {
    // TODO
    return *this;
  }

  // ARITHMETIC OVERLOADS

  tensor_type& operator+=(tensor_type const& rhs) {
    // TODO
    return *this;
  }

  tensor_type& operator-=(tensor_type const& rhs) {
    // TODO
    return *this;
  }

  tensor_type& operator*=(ArithmeticT const& s) {
    // TODO
    return *this;
  }

  tensor_type& operator/=(ArithmeticT const& s) {
    // TODO
    return *this;
  }

  // BITSHIFT

  friend std::ostream& operator<< <ArithmeticT,R,D,FormationPol> ( std::ostream&, tensor_type const& );

  // --------------------------------

public:
  ArithmeticT& operator[](index_t i) { return value[i]; }

  ArithmeticT const operator[](index_t i) const { return value[i]; }

  // --------------------------------

public:
  std::array<ArithmeticT, tensor_t(R, D)> value;
};

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol>
inline constexpr auto
operator+(tensor<ArithmeticT, R, D, FormationPol>& lhs,
          tensor<ArithmeticT, R, D, FormationPol> const& rhs) {
  lhs += rhs;
  return lhs;
}

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol>
inline constexpr auto
operator-(tensor<ArithmeticT, R, D, FormationPol>& lhs,
          tensor<ArithmeticT, R, D, FormationPol> const& rhs) {
  lhs -= rhs;
  return lhs;
}

template <arithmetical ArithmeticT, rank R, dimension D,
          class FormationPol>
std::ostream& operator<< ( std::ostream& os, tensor<ArithmeticT, R, D, FormationPol> const& a_tensor ) {
    
    for ( auto const& v : a_tensor.value ) {
        os << v << '\t';
    }
    
    return os;
}

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