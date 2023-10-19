/*******************************************************************************
 * VMICROSTRUCTURE
 * -----------------------------------------------------------------------------
 *
 ******************************************************************************/

#ifndef __V_MICROSTRUCTURE_HPP__
#define __V_MICROSTRUCTURE_HPP__

#pragma once
#warning "vmicrostructure | venture kickstarter"

#include <algorithm>
#include <array>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <thread>

#include <concepts>
#include <format>
#include <ranges>

#define V_MICROSTRUCTURE_CONST(SPEC, TYPE)                                     \
  V_MICROSTRUCTURE_CONST_##SPEC##_##TYPE()

#define V_MICROSTRUCTURE_CONST_NONE_CTOR()
#define V_MICROSTRUCTURE_CONST_EXPR_CTOR() constexpr
#define V_MICROSTRUCTURE_CONST_EVAL_CTOR() consteval

#define V_MICROSTRUCTURE_CONST_NONE_FUNC()
#define V_MICROSTRUCTURE_CONST_EXPR_FUNC() constexpr
#define V_MICROSTRUCTURE_CONST_EVAL_FUNC() consteval

#define V_MICROSTRUCTURE_CONST_NONE_ITER()
#define V_MICROSTRUCTURE_CONST_EXPR_ITER() constexpr
#define V_MICROSTRUCTURE_CONST_EVAL_ITER() consteval

#define V_MICROSTRUCTURE_CONST_NONE_MTHD()
#define V_MICROSTRUCTURE_CONST_EXPR_MTHD() constexpr
#define V_MICROSTRUCTURE_CONST_EVAL_MTHD() consteval

#define V_MICROSTRUCTURE_CONST_NONE_OLOP()
#define V_MICROSTRUCTURE_CONST_EXPR_OLOP() constexpr
#define V_MICROSTRUCTURE_CONST_EVAL_OLOP() consteval

/*******************************************************************************
 * VLOCATION
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {

template <typename MeasureT>
concept vmeasurable = requires(MeasureT measure) {
                        { true };

                        // measure + measure;
                        // measure - measure;
                      };

template <typename LocationT>
concept vlocatable = requires(LocationT location) {
                       typename LocationT::value_type;
                       typename LocationT::pointer;
                       typename LocationT::reference;
                       typename LocationT::const_pointer;
                       typename LocationT::const_reference;
                       typename LocationT::size_type;
                       typename LocationT::difference_type;
                       typename LocationT::iterator;
                       typename LocationT::const_iterator;
                       typename LocationT::reverse_iterator;
                       typename LocationT::const_reverse_iterator;

                       location.begin();
                       location.end();
                       location.cbegin();
                       location.cend();

                       location.rbegin();
                       location.rend();
                       location.crbegin();
                       location.crend();

                       location[0];
                       location.coordinate[0];
                     };

template <vmeasurable MeasureT = float, std::size_t DimensionN = 2,
          template <typename, std::size_t> class CollectionC = std::array>
class vlocation {
public:
  using value_type             = MeasureT;
  using pointer                = MeasureT*;
  using reference              = MeasureT&;
  using const_pointer          = MeasureT const*;
  using const_reference        = MeasureT const&;
  using size_type              = std::size_t;
  using difference_type        = std::make_signed_t<size_type>;

  using container              = CollectionC<MeasureT, DimensionN>;

  using iterator               = typename container::iterator;
  using const_iterator         = typename container::const_iterator;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  V_MICROSTRUCTURE_CONST(EXPR, CTOR)
  vlocation(std::array<MeasureT, DimensionN> i_coordinate)
      : m_coordinate{i_coordinate} {}

  V_MICROSTRUCTURE_CONST(EXPR, CTOR)
  vlocation(std::initializer_list<MeasureT> i_coordinate) {
    std::ranges::copy_n(i_coordinate.begin(), DimensionN, m_coordinate.begin());
  }

public:
  V_MICROSTRUCTURE_CONST(EXPR, OLOP)
  auto operator+=(vlocation<MeasureT, DimensionN, CollectionC> const& other)
      -> vlocation<MeasureT, DimensionN, CollectionC>& {

    for (auto const& [a, b] :
         std::ranges::views::zip(m_coordinate, other.m_coordinate))
      a += b;

    return *this;
  }

  V_MICROSTRUCTURE_CONST(EXPR, OLOP)
  auto operator-=(vlocation<MeasureT, DimensionN, CollectionC> const& other)
      -> vlocation<MeasureT, DimensionN, CollectionC>& {

    for (auto const& [a, b] :
         std::ranges::views::zip(m_coordinate, other.m_coordinate))
      a -= b;

    return *this;
  }

public:
  [[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, MTHD) auto
  operator[](std::size_t index) noexcept -> MeasureT& {
    return m_coordinate[index];
  }

  [[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, MTHD) auto
  operator[](std::size_t index) const noexcept -> MeasureT const& {
    return m_coordinate[index];
  }

  [[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, MTHD) auto coordinate(
      std::size_t index) noexcept -> MeasureT& {
    return m_coordinate[index];
  }

  [[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, MTHD) auto coordinate(
      std::size_t index) const noexcept -> MeasureT const& {
    return m_coordinate[index];
  }

public:
  V_MICROSTRUCTURE_CONST(EXPR, ITER) auto begin() noexcept -> iterator {
    return m_coordinate.begin();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto begin() const noexcept -> const_iterator { return m_coordinate.begin(); }

  V_MICROSTRUCTURE_CONST(EXPR, ITER) auto end() noexcept -> iterator {
    return m_coordinate.end();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto end() const noexcept -> const_iterator { return m_coordinate.end(); }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto rbegin() noexcept -> reverse_iterator { return m_coordinate.rbegin(); }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto rbegin() const noexcept -> const_reverse_iterator {
    return m_coordinate.rbegin();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER) auto rend() noexcept -> reverse_iterator {
    return m_coordinate.rend();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto rend() const noexcept -> const_reverse_iterator {
    return m_coordinate.rend();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto cbegin() const noexcept -> const_iterator {
    return m_coordinate.cbegin();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto cend() const noexcept -> const_iterator { return m_coordinate.cend(); }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto crbegin() const noexcept -> const_reverse_iterator {
    return m_coordinate.crbegin();
  }

  V_MICROSTRUCTURE_CONST(EXPR, ITER)
  auto crend() const noexcept -> const_reverse_iterator {
    return m_coordinate.crend();
  }

  V_MICROSTRUCTURE_CONST(EXPR, MTHD) auto size() const noexcept -> std::size_t {
    return m_coordinate.size();
  }

private:
  CollectionC<MeasureT, DimensionN> m_coordinate;
};

// =============================================================================

template <vmeasurable MeasureT, std::size_t DimensionN,
          template <typename, std::size_t> class CollectionC>
[[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, OLOP) auto
operator+(vlocation<MeasureT, DimensionN, CollectionC> const& a,
          vlocation<MeasureT, DimensionN, CollectionC> const& b)
    -> vlocation<MeasureT, DimensionN, CollectionC> {
  auto t{a};
  t += b;
  return t;
}

template <vmeasurable MeasureT, std::size_t DimensionN,
          template <typename, std::size_t> class CollectionC>
[[nodiscard]] V_MICROSTRUCTURE_CONST(EXPR, OLOP) auto
operator-(vlocation<MeasureT, DimensionN, CollectionC> const& a,
          vlocation<MeasureT, DimensionN, CollectionC> const& b)
    -> vlocation<MeasureT, DimensionN, CollectionC> {
  auto t{a};
  t -= b;
  return t;
}

// =============================================================================

template <vmeasurable MeasureT, std::size_t DimensionN,
          template <typename, std::size_t> class CollectionC>
auto operator<<(std::ostream&                                       os,
                vlocation<MeasureT, DimensionN, CollectionC> const& location)
    -> std::ostream& {
  bool first{true};

  for (auto const& coordinate : location) {
    if (first)
      first = false;
    else
      os << '\t';
    os << coordinate;
  }

  return os;
}

} // namespace vmicrostructure

/*******************************************************************************
 * VLATTICE
 * -----------------------------------------------------------------------------
 *
 ******************************************************************************/

namespace vmicrostructure {

template <vlocatable LocationT, std::size_t... ExtentsN> class zlattice {
public:
private:
};

} // namespace vmicrostructure

/*******************************************************************************
 * VFIELD
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {} // namespace vmicrostructure

/*******************************************************************************
 * VFEATURE
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {} // namespace vmicrostructure

/*******************************************************************************
 * VCONTOUR
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {} // namespace vmicrostructure

/*******************************************************************************
 * VCANVAS
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {} // namespace vmicrostructure

#endif // !__V_MICROSTRUCTURE_HPP__