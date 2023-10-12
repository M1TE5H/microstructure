/*******************************************************************************
 * VMICROSTRUCTURE
 * -----------------------------------------------------------------------------
 *
 ******************************************************************************/

#ifndef __V_MICROSTRUCTURE_HPP__
#define __V_MICROSTRUCTURE_HPP__

#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <initializer_list>
#include <iostream>

#include <concepts>
#include <format>
#include <ranges>

/*******************************************************************************
 * VLOCATION
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {

template <std::floating_point NumericT = float, std::size_t DimensionN = 2,
          template <typename, std::size_t> class ContainerT = std::array>
class vlocation {
public:
  using value_type             = NumericT;
  using pointer                = NumericT*;
  using reference              = NumericT&;
  using const_pointer          = NumericT const*;
  using const_reference        = NumericT const&;
  using size_type              = std::size_t;
  using difference_type        = std::make_signed_t<size_type>;

  using container              = ContainerT<NumericT, DimensionN>;

  using iterator               = typename container::iterator;
  using const_iterator         = typename container::const_iterator;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  vlocation(std::initializer_list<NumericT> init) {
    std::ranges::copy(init, begin());
  }

public:
  constexpr auto
  operator+=(vlocation<NumericT, DimensionN, ContainerT> const& other)
      -> vlocation<NumericT, DimensionN, ContainerT>& {

    for (auto&& [a, b] : std::views::zip(m_coordinate, other.m_coordinate))
      a += b;

    return *this;
  }

  constexpr auto
  operator-=(vlocation<NumericT, DimensionN, ContainerT> const& other)
      -> vlocation<NumericT, DimensionN, ContainerT>& {

    for (auto&& [a, b] : std::views::zip(m_coordinate, other.m_coordinate))
      a -= b;

    return *this;
  }

public:
  [[nodiscard]] constexpr auto operator[](std::size_t index) noexcept
      -> NumericT& {
    return m_coordinate[index];
  }

  [[nodiscard]] constexpr auto operator[](std::size_t index) const noexcept
      -> NumericT const& {
    return m_coordinate[index];
  }

  [[nodiscard]] constexpr auto coordinate(std::size_t index) noexcept
      -> NumericT& {
    return m_coordinate[index];
  }

  [[nodiscard]] constexpr auto coordinate(std::size_t index) const noexcept
      -> NumericT const& {
    return m_coordinate[index];
  }

public:
  constexpr auto begin() noexcept -> iterator { return m_coordinate.begin(); }

  constexpr auto begin() const noexcept -> const_iterator {
    return m_coordinate.begin();
  }

  constexpr auto end() noexcept -> iterator { return m_coordinate.end(); }

  constexpr auto end() const noexcept -> const_iterator {
    return m_coordinate.end();
  }

  constexpr auto rbegin() noexcept -> reverse_iterator {
    return m_coordinate.rbegin();
  }

  constexpr auto rbegin() const noexcept -> const_reverse_iterator {
    return m_coordinate.rbegin();
  }

  constexpr auto rend() noexcept -> reverse_iterator {
    return m_coordinate.rend();
  }

  constexpr auto rend() const noexcept -> const_reverse_iterator {
    return m_coordinate.rend();
  }

  constexpr auto cbegin() const noexcept -> const_iterator {
    return m_coordinate.cbegin();
  }

  constexpr auto cend() const noexcept -> const_iterator {
    return m_coordinate.cend();
  }

  constexpr auto crbegin() const noexcept -> const_reverse_iterator {
    return m_coordinate.crbegin();
  }

  constexpr auto crend() const noexcept -> const_reverse_iterator {
    return m_coordinate.crend();
  }

private:
  ContainerT<NumericT, DimensionN> m_coordinate;
};

// =============================================================================

template <std::floating_point NumericT, std::size_t DimensionN,
          template <typename, std::size_t> class ContainerT>
[[nodiscard]] constexpr auto
operator+(vlocation<NumericT, DimensionN, ContainerT> const& a,
          vlocation<NumericT, DimensionN, ContainerT> const& b)
    -> vlocation<NumericT, DimensionN, ContainerT> {
  auto t{a};
  t += b;
  return t;
}

template <std::floating_point NumericT, std::size_t DimensionN,
          template <typename, std::size_t> class ContainerT>
[[nodiscard]] constexpr auto
operator-(vlocation<NumericT, DimensionN, ContainerT> const& a,
          vlocation<NumericT, DimensionN, ContainerT> const& b)
    -> vlocation<NumericT, DimensionN, ContainerT> {
  auto t{a};
  t -= b;
  return t;
}

// =============================================================================

template <std::floating_point NumericT, std::size_t DimensionN,
          template <typename, std::size_t> class ContainerT>
auto operator<<(std::ostream&                                      os,
                vlocation<NumericT, DimensionN, ContainerT> const& location)
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

namespace vmicrostructure {} // namespace vmicrostructure

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
 * VCANVAS
 * -----------------------------------------------------------------------------
 * @todo ...
 ******************************************************************************/

namespace vmicrostructure {} // namespace vmicrostructure

#endif // !__V_MICROSTRUCTURE_HPP__