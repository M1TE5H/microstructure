/*******************************************************************************
 * \section   ZMICROSTRUCTURE
 * -----------------------------------------------------------------------------
 *
 * \file      zmicrostructure.hpp
 * \brief     Main Header for the Zeroth-Iteration Research Code
 *
 * \code      HTTPS://WWW.GITHUB.COM/M1TE5H/MICROSTRUCTURE
 *
 * \author    M1TE5H
 * \date      2022-01-13--PRESENT
 * \copyright COPYRIGHT (C) 2022--PRESENT BY M1TE5H
 * \link      HTTPS://WWW.M1TE5H.COM
 *
 * \version   0.0.0
 *
 * -----------------------------------------------------------------------------
 *
 * \subsection STATEMENT
 *
 * \attention  Under Construction
 *
 * This software is under construction. Please contact the author for futher
 * details.
 *
 * -----------------------------------------------------------------------------
 *
 * \subsection GUIDE
 *
 * \todo Recommend Use and Desired Interface
 *
 ******************************************************************************/

#ifndef __Z_MICROSTRUCTURE_HPP__
#define __Z_MICROSTRUCTURE_HPP__

#pragma once

#if (defined(_MSVC_LANG) && _MSVC_LANG < 202002L) ||                           \
    ((!defined(_MSVC_LANG)) && __cplusplus < 202002L)
#error "ZMICROSTRUCTURE REQUIRES A C++20-COMPLIANT COMPILER"
#else
#ifndef Z_MICROSTRUCTURE_CXX_STANDARD
/// @note Latest C++20/23 Features: disable (0) and enable (1)
#define Z_MICROSTRUCTURE_CXX_STANDARD() 1
#endif // !Z_MICROSTRUCTURE_CXX_STANDARD
#endif

#if (!defined(_MSVC_LANG))
/// @note GCC13 or clang
#warning "under construction"
#endif

/*******************************************************************************
 * \subsection PREPROCESSOR
 * -----------------------------------------------------------------------------
 * \note Recommended Choices: disable (0) and enable (1) for most directives
 * \todo Additional Macros: compiler selection for clang, gcc, msvc
 ******************************************************************************/

#define Z_MICROSTRUCTURE_MODERN_CXX_STANDARD_23()                              \
  Z_MICROSTRUCTURE_CXX_STANDARD()

#define Z_MICROSTRUCTURE_OPERATING_SYSTEM_LINUX()   0
#define Z_MICROSTRUCTURE_OPERATING_SYSTEM_MAC()     0
#define Z_MICROSTRUCTURE_OPERATING_SYSTEM_WINDOWS() 0
#define Z_MICROSTRUCTURE_OPERATING_SYSTEM_DOCKER()  1

#define Z_MICROSTRUCTURE_BUILD_DEBUG()              1
#define Z_MICROSTRUCTURE_BUILD_TEST()               1
#define Z_MICROSTRUCTURE_BUILD_RELEASE()            0

/// @note Clash Prevention
#define Z_MICROSTRUCTURE_NAMESPACE_NAME()           zmicrostructure

#define Z_MICROSTRUCTURE_ANSI()                     0
#define Z_MICROSTRUCTURE_D3JS()                     0
#define Z_MICROSTRUCTURE_GNUPLOT()                  1
#define Z_MICROSTRUCTURE_JULIA()                    0
#define Z_MICROSTRUCTURE_MATLAB()                   0
#define Z_MICROSTRUCTURE_MATPLOTLIB()               0
#define Z_MICROSTRUCTURE_PGF()                      0
#define Z_MICROSTRUCTURE_TIKZ()                     1
#define Z_MICROSTRUCTURE_SVG()                      0
#define Z_MICROSTRUCTURE_EPS()                      0
#define Z_MICROSTRUCTURE_PPM()                      1
#define Z_MICROSTRUCTURE_XELATEX()                  1

/*******************************************************************************
 * \subsection HEADERS
 * -----------------------------------------------------------------------------
 * \todo Fine Tune: remove headers that are not needed
 ******************************************************************************/

// C Headers
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

// C++98/03/11/14/17 Headers
#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

// C++20/23 Headers
#include <concepts>
#include <coroutine>
#include <format>
#include <ranges>
#include <source_location>

// Local Headers

/*******************************************************************************
 * \subsection MACROS
 * -----------------------------------------------------------------------------
 * \note Definitions: exclusive for internal use
 * \todo
 ******************************************************************************/

#define Z_MICROSTRUCTURE_VERSION(NUMBER) Z_MICROSTRUCTURE_VERSION_##NUMBER()

// -----------------------------------------------------------------------------

#define Z_MICROSTRUCTURE_OPERATING_SYSTEM(TARGET)                              \
  Z_MICROSTRUCTURE_OPERATING_SYSTEM_##TARGET()

// -----------------------------------------------------------------------------

#define Z_MICROSTRUCTURE_BUILD(MODE) Z_MICROSTRUCTURE_BUILD_##MODE()

#if defined(Z_MICROSTRUCTURE_BUILD) && Z_MICROSTRUCTURE_BUILD(DEBUG) == 1
#define Z_MICROSTRUCTURE_DEBUG(MESSAGE)                                        \
  do {                                                                         \
    std::cerr << std::format("\x1B[97;44m{0:16}{1:64}\x1B[0m", "DEBUG",        \
                             MESSAGE)                                          \
              << std::endl;                                                    \
  } while (0)
#else
#define Z_MICROSTRUCTURE_DEBUG(MESSAGE)                                        \
  do {                                                                         \
  } while (0)
#endif

// -----------------------------------------------------------------------------

/// @note not standard/common use but for convenience in this isolated code
#define Z_MICROSTRUCTURE_NAMESPACE(TOGGLE) Z_MICROSTRUCTURE_NAMESPACE_##TOGGLE()

#define Z_MICROSTRUCTURE_NAMESPACE_BEGIN()                                     \
  namespace Z_MICROSTRUCTURE_NAMESPACE_NAME() {
#define Z_MICROSTRUCTURE_NAMESPACE_END()   }
#define Z_MICROSTRUCTURE_NAMESPACE_SCOPE() ::Z_MICROSTRUCTURE_NAMESPACE_NAME()

Z_MICROSTRUCTURE_NAMESPACE(BEGIN)
Z_MICROSTRUCTURE_NAMESPACE(END)

// -----------------------------------------------------------------------------

/// @todo consider improvements or alternatives to generalise
#define Z_MICROSTRUCTURE_CONSTSPEC(SPEC, TYPE)                                 \
  Z_MICROSTRUCTURE_CONSTSPEC_IMPL(SPEC, TYPE)

#define Z_MICROSTRUCTURE_CONSTSPEC_IMPL(SPEC, TYPE)                            \
  Z_MICROSTRUCTURE_CONSTSPEC_##SPEC##_##TYPE()

#define Z_MICROSTRUCTURE_CONSTSPEC_EVAL_CTOR() consteval
#define Z_MICROSTRUCTURE_CONSTSPEC_EXPR_CTOR() constexpr
#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_CTOR()

#define Z_MICROSTRUCTURE_CONSTSPEC_EVAL_MTHD() consteval
#define Z_MICROSTRUCTURE_CONSTSPEC_EXPR_MTHD() constexpr
#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_MTHD()

#define Z_MICROSTRUCTURE_CONSTSPEC_EVAL_OLOP() consteval
#define Z_MICROSTRUCTURE_CONSTSPEC_EXPR_OLOP() constexpr
#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_OLOP()

#define Z_MICROSTRUCTURE_CONSTSPEC_EVAL_FUNC() consteval
#define Z_MICROSTRUCTURE_CONSTSPEC_EXPR_FUNC() constexpr
#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_FUNC()

#define Z_MICROSTRUCTURE_CONSTSPEC_INIT_VRBL() constinit
#define Z_MICROSTRUCTURE_CONSTSPEC_EXPR_VRBL() constexpr
#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_VRBL()

#define Z_MICROSTRUCTURE_CONSTSPEC_NONE_ITER()

// =============================================================================
// =============================================================================
Z_MICROSTRUCTURE_NAMESPACE(BEGIN)
// =============================================================================
// =============================================================================

template <typename LocationT>
concept zlocatable = requires(LocationT l) {
                       typename LocationT::value_type;
                       l.horizontal();
                       l.vertical();
                     };

template <typename ContainerT>
concept zcontainer = requires(ContainerT c) {
                       typename ContainerT::value_type;
                       typename ContainerT::iterator;
                       typename ContainerT::const_iterator;
                       c.size();
                       c[0];
                     };

/// @class zlocation
/// @brief cartesian coordinate
template <std::integral NumberZ> class zlocation {
public:
  using value_type = NumberZ;

public:
  explicit Z_MICROSTRUCTURE_CONSTSPEC(EXPR, CTOR)
      zlocation(NumberZ h, NumberZ v)
      : m_horizontal{h}, m_vertical{v} {}

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_CONSTSPEC(
      EXPR, MTHD) std::integral auto horizontal() const noexcept -> NumberZ {
    return m_horizontal;
  }

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_CONSTSPEC(
      EXPR, MTHD) std::integral auto vertical() const noexcept -> NumberZ {
    return m_vertical;
  }

  auto horizontal(NumberZ const& h) -> void { m_horizontal = h; }
  auto vertical(NumberZ const& v) -> void { m_vertical = v; }

  Z_MICROSTRUCTURE_CONSTSPEC(EVAL, OLOP)
  auto operator+=(zlocation const& other) -> zlocation& {
    m_horizontal += other.horizontal();
    m_vertical   += other.vertical();
    return *this;
  }

  Z_MICROSTRUCTURE_CONSTSPEC(EVAL, OLOP)
  auto operator-=(zlocation const& other) -> zlocation& {
    m_horizontal -= other.horizontal();
    m_vertical   -= other.vertical();
    return *this;
  }

  Z_MICROSTRUCTURE_CONSTSPEC(EVAL, OLOP)
  auto operator*=(NumberZ const& scale) -> zlocation& {
    m_horizontal *= scale;
    m_vertical   *= scale;
    return *this;
  }

  Z_MICROSTRUCTURE_CONSTSPEC(EVAL, OLOP)
  auto operator/=(NumberZ const& scale) -> zlocation& {
    [[assume(!scale)]];
    m_horizontal /= scale;
    m_vertical   /= scale;
    return *this;
  }

public:
private:
  NumberZ m_horizontal{0};
  NumberZ m_vertical{0};
};

template <std::integral NumberZ>
[[nodiscard("use arithmetic overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL,
                                                                    OLOP) auto
operator+(zlocation<NumberZ> const& a, zlocation<NumberZ> const& b)
    -> decltype(auto) {
  auto t{a};
  t += b;
  return t;
}

template <std::integral NumberZ>
[[nodiscard("use arithmetic overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL,
                                                                    OLOP) auto
operator-(zlocation<NumberZ> const& a, zlocation<NumberZ> const& b)
    -> decltype(auto) {
  auto t{a};
  t -= b;
  return t;
}

template <std::integral NumberZ>
[[nodiscard("use arithmetic overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL,
                                                                    OLOP) auto
operator*(zlocation<NumberZ> const& zloc, NumberZ const& scale)
    -> decltype(auto) {
  auto t{zloc};
  t -= scale;
  return t;
}

template <std::integral NumberZ>
[[nodiscard("use arithmetic overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL,
                                                                    OLOP) auto
operator/(zlocation<NumberZ> const& zloc, NumberZ const& scale)
    -> decltype(auto) {
  [[assume(!scale)]];
  auto t{zloc};
  t /= scale;
  return t;
}

template <std::integral NumberZ>
[[nodiscard("use boolean overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL,
                                                                 OLOP) auto
operator==(zlocation<NumberZ> const& a, zlocation<NumberZ> const& b) -> bool {
  return a.horizontal() == b.horizontal() && a.vertical() == b.vertical();
}

template <std::integral NumberZ>
[[nodiscard("use order overload")]] Z_MICROSTRUCTURE_CONSTSPEC(EVAL, OLOP) auto
operator<=>(zlocation<NumberZ> const& a, zlocation<NumberZ> const& b)
    -> std::partial_ordering {
  auto norm_square = [&](auto h, auto v) { return h * h + v * v; };
  return norm_square(a.horizontal(), a.vertical()) <=>
         norm_square(b.horizontal(), b.vertical());
  // return a.horizontal() <=> b.horizontal() && a.vertical() <=> b.vertical();
}

/// @class zlattice
/// @brief Two-Dimensional Grid Container Data Structure

template <zlocatable LocationT, std::size_t RowsN = 1, std::size_t ColsN = 1,
          template <typename, std::size_t> class ContainerT = std::array>
  requires zcontainer<ContainerT<LocationT, ColsN>>
class zlattice;

template <typename LatticeT> class zlattice_const_iterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type        = typename LatticeT::value_type;
  using difference_type   = std::ptrdiff_t;
  using pointer           = value_type const*;
  using reference         = value_type const&;
  using iterator_type     = typename LatticeT::const_iterator;

public:
  zlattice_const_iterator() = default;

  Z_MICROSTRUCTURE_CONSTSPEC(NONE, CTOR)
  zlattice_const_iterator(iterator_type itr, zlattice<value_type> const* zltc)
      : m_iterator{itr}, m_zlattice{zltc} {}

  Z_MICROSTRUCTURE_CONSTSPEC(NONE, ITER)
  auto operator*() const -> reference { return *m_iterator; }

  Z_MICROSTRUCTURE_CONSTSPEC(NONE, ITER) auto operator->() const -> pointer {
    return &(*m_iterator);
  }

protected:
  friend class zlattice<value_type>;

protected:
  iterator_type               m_iterator;
  zlattice<value_type> const* m_zlattice{nullptr};
};

template <typename LatticeT>
class zlattice_iterator : public zlattice_const_iterator<LatticeT> {};

template <zlocatable LocationT, std::size_t RowsN, std::size_t ColsN,
          template <typename, std::size_t> class ContainerT>
  requires zcontainer<ContainerT<LocationT, ColsN>>
class zlattice {
public:
  using value_type      = LocationT;
  using pointer         = LocationT*;
  using reference       = LocationT&;
  using const_pointer   = LocationT const*;
  using const_reference = LocationT const&;
  using iterator        = zlattice_iterator<zlattice>;
  using const_iterator  = zlattice_const_iterator<zlattice>;

public:
  Z_MICROSTRUCTURE_CONSTSPEC(EXPR, CTOR) zlattice() {
    std::ranges::fill(*this, LocationT());
  }

  auto begin() noexcept -> iterator;
  auto end() noexcept -> iterator;

  auto begin() const noexcept -> const_iterator;
  auto end() const noexcept -> const_iterator;

  auto cbegin() const noexcept -> const_iterator;
  auto cend() const noexcept -> const_iterator;

private:
  ContainerT<ContainerT<LocationT, ColsN>, RowsN> m_site;
};

// =============================================================================
// =============================================================================
Z_MICROSTRUCTURE_NAMESPACE(END)
// =============================================================================
// =============================================================================

#endif // !__Z_MICROSTRUCTURE_HPP__