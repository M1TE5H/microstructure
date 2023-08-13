/*******************************************************************************
 * ZLOCATION
 * -----------------------------------------------------------------------------
 *
 * \file       zlocation.hpp
 * \brief      Two-Dimensional Euclidean Coordinate Position
 *
 * \code       HTTPS://GITHUB.COM/M1TE5H/MICROSTRUCTURE
 *
 * \author     M1TE5H
 * \date       2022-12-31
 * \copyright  COPYRIGHT (C) 2022--PRESENT BY M1TE5H
 * \link       HTTPS://WWW.M1TE5H.COM
 *
 * \version    0.0.0
 *
 * =============================================================================
 * @details Design Rationale
 *
 * The \b zlocation class is low-lying data structure used to represent
 * two-dimensional positions of microstructural features, simulation events and
 * visualisation avatars.
 *
 * - Generalisability: templated for \e measurable types
 * - Various Kernels: cartesian, circular, curvilinear, canonical
 * - Intuitive Usage: arithmetic and relational overloads
 * - Modern C++20/23: best practices, compile-time computations
 * - Inspirations: std::complex and std::pair, Boost.Geometry and CGAL
 * - Extensions: see checklist at end for additional kernels
 *
 * =============================================================================
 * @example User Guide (Desired Interface and Recommend Use) [UPDATED]
 * @todo Address Unit Dimension Inconsistencies
 * @todo Address Multi-Dimensional Extensions
 * @todo Address Multi-Scale Generalisations
 *
 * @attention Under Construction:
 *
 * using namespace zmicrostructure;
 *
 * // note: concept arithmetical for ring number types
 * // note: concept unit for physical standards
 * // xmeasurement<arithmetical, unit>
 * using distance    = xmeasurement< double, meter >;
 * using orientation = xmeasurement< rational, radian >;
 *
 * // zlocation < LocationModel< xmeasurement,... > >
 * using xcartesian = zlocation< xcartesian< distance > >;
 * using xcircular  = zlocation< xcircular< distance, orientation > >;
 *
 * // xmetric< MetrixModel< arithmetical T = float, unit = meter > >
 * using xeuclidean = xmetric< xeuclidean<> >;
 *
 * // template< xlocatable LocationT1, xlocatable LocationT2 = LocationT1 >
 * // xdistance< xmetric >( LocationT1 const&, locationT2 const& );
 * constexpr d { xdistance< xeuclidean >( xcartesian { 1., 1.},
 *                                      xcircular { 1., 0. } ) };
 *
 * std::array< xcartesian, 1024 > lattice;
 * auto distortion = [](auto x, auto y){ return ( x * x ) + ( y * y ); };
 * std::array< xcartesian::value_type, 1024 > field {
 *     std::ranges::transform ( lattice, ScalarFunctor< distortion > );
 * };
 *
 *
 * =============================================================================
 * @example User Guide (Desired API and Recommended Use) [DEPRECATED]
 *
 * // pollution for demonstration purposes:
 * using namespace zmicrostructure;
 * using namespace zmicrostructure::zdetail::zlocation
 *
 * // aliases for convenience:
 * using zcartesian_float = zlocation< zmeasure<float>, zkernel::cartesian >;
 * using zcircular_float  = zlocation< zmeasure<float>, zkernel::circular >;
 *
 * // check functionalities as needed:
 * static_assert ( zlocatable< zcartesian_float > );
 * static_assert ( zlocatable< zcircular_float > );
 *
 * // define two cartesian coordinates:
 * constexpr zcartesian_float a { 42.f, 24.f };
 * constexpr zcartesian_float b { 24.f, 42.f };
 *
 * // compile-time use of accessors
 * static_assert ( a.horizontal () == b.vertical () );
 *
 * // standard arithmetic operations:
 * constexpr auto summation  = a + b;
 * constexpr auto difference = a - b;
 *
 * // define two circular coordinates
 * constexpr zcircular_float c { 100.0f, 0.f };
 * constexpr zcircular_float  d { 100.0f, std::numbers::pi / 2.f };
 *
 * // scalar transformation: lambda into functor
 * auto distortion = [](auto x, auto y){ return x * x + y * y; };
 *
 * auto constexpr distortion_at_a { ScalarFunctor<distortion>(a) };
 *
 * =============================================================================
 *
 ******************************************************************************/

#ifndef __Z_MICROSTRUCTURE_Z_LOCATION_HPP__
#define __Z_MICROSTRUCTURE_Z_LOCATION_HPP__

#pragma once

// =============================================================================

/// @note not standard/common use but convenient in this isolation code
#ifdef Z_MICROSTRUCTURE_NAMESPACE

#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_NAME()                           \
  Z_MICROSTRUCTURE_NAMESPACE(NAME)
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_BEGIN()                          \
  Z_MICROSTRUCTURE_NAMESPACE(BEGIN)
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_END()                            \
  Z_MICROSTRUCTURE_NAMESPACE(END)
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_SCOPE()                          \
  ::Z_MICROSTRUCTURE_NAMESPACE(SCOPE)
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE(TOGGLE)                          \
  Z_MICROSTRUCTURE_NAMESPACE(TOGGLE)

#else

#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_NAME() zmicrostructure
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_BEGIN()                          \
  namespace Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_NAME() {
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_END() }
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_SCOPE()                          \
  ::Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_NAME()
#define Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE(TOGGLE)                          \
  Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_##TOGGLE()
#endif

#ifdef Z_MICROSTRUCTURE_CONSTSPEC
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(SPEC, TYPE)                      \
  Z_MICROSTRUCTURE_CONSTSPEC(SPEC, TYPE)
#else
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(SPEC, TYPE)                      \
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_##SPEC##_##TYPE()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_CTOR() consteval
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_CTOR() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_CTOR()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_OLOP() consteval
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_OLOP() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_OLOP()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_MTHD() consteval
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_MTHD() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_MTHD()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_FUNC() consteval
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_FUNC() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_FUNC()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_ITER() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_ITER()

#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_INIT_VRBL() constinit
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_VRBL() constexpr
#define Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_VRBL()

#endif

// =============================================================================

// C Headers
#include <cmath>

// C++98/03/11/14/17 Headers
#include <array>
#include <iostream>
#include <limits>
#include <string_view>

// C++20/23 Headers
#include <concepts>
#include <format>
#include <numbers>

// #include "zdefinition.hpp"
// #include "zkernel.hpp"
// #include "zmeasure.hpp"

// =============================================================================

/// @note Macro Categorisation for Accessors
#define Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD(METHOD)                    \
  Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_##METHOD()

/// @note Modern Accessor: constexpr support
#define Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_MODERN() 1

/// @note Macro Categorisation for Arithmetic/Stream Overloads
#define Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(METHOD)                    \
  Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_##METHOD()

#define Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_GLOBAL() 1
#define Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_FRIEND() 0

/// @note Macro Categorisation for Relational Operators
#define Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(METHOD)                  \
  Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_##METHOD()

/// @note Modern Relational Operations: Class Members
#define Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_MODERN() 1

// =============================================================================
// =============================================================================
Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE(BEGIN)
// =============================================================================
// =============================================================================

// template <zarithmetical ArithmeticT, zunit UnitE> class LocationModel;

/// @brief Provisional Definitions
template <typename MeasureT>
concept zmeasurable = requires(MeasureT m) {
                        { std::is_arithmetic_v<MeasureT> };
                      };

enum class zkernel {
  cartesian,
  circular,
  curvilinear,
  canonical,
  affine,
  slant,
  skew,
};

template <std::floating_point NumberT> using zmeasure = NumberT;

/// @brief Forward Declarations

template <zmeasurable MeasureT, zkernel KernE> class zlocation;

template <zmeasurable MeasureT> class zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT> class zlocation<MeasureT, zkernel::circular>;

/// @todo Template Specialisation for Curvilinear Coordinates
// template< zmeasurable MeasureT >
// class zlocation< MeasureT, zkernel::curvilinear >;

/// @todo Template Specialisation for Canonical Coordinates
// template< zmeasurable MeasureT >
// class zlocation< MeasureT, zkernel::canonical >;

/// @todo Template Specialisation for Affine Coordinates
// template< zmeasurable MeasureT >
// class zlocation< MeasureT, zkernel::affine >;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @brief Forward Declarations for Overloaded Operators (Global)

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, KernE> const&, MeasureT const&)
    -> zlocation<MeasureT, KernE>;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, KernE> const&, MeasureT const&)
    -> zlocation<MeasureT, KernE>;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, KernE> const&, zlocation<MeasureT, KernE> const&)
    -> zlocation<MeasureT, KernE>;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, KernE> const&, zlocation<MeasureT, KernE> const&)
    -> zlocation<MeasureT, KernE>;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator*(zlocation<MeasureT, KernE> const&, MeasureT const&)
    -> zlocation<MeasureT, KernE>;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator/(zlocation<MeasureT, KernE> const&, MeasureT const&)
    -> zlocation<MeasureT, KernE>;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, KernE> const&, zlocation<MeasureT, KernE> const&)
    -> bool;

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator<=>(zlocation<MeasureT, KernE> const&,
            zlocation<MeasureT, KernE> const&) -> std::partial_ordering;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <zmeasurable MeasureT, zkernel KernE>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
std::ostream& operator<<(std::ostream&, zlocation<MeasureT, KernE> const&);

// -----------------------------------------------------------------------------

/// @brief  Forward Declarations: Cartesian Kernel Partial Specialisation

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const&,
          zlocation<MeasureT, zkernel::cartesian> const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const&,
          zlocation<MeasureT, zkernel::circular> const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const&,
          zlocation<MeasureT, zkernel::cartesian> const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const&,
          zlocation<MeasureT, zkernel::circular> const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator*(zlocation<MeasureT, zkernel::cartesian> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator/(zlocation<MeasureT, zkernel::cartesian> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::cartesian>;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::cartesian> const&,
           zlocation<MeasureT, zkernel::cartesian> const&) -> bool;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::cartesian> const&,
           zlocation<MeasureT, zkernel::circular> const&) -> bool;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator<=>(zlocation<MeasureT, zkernel::cartesian> const&,
            zlocation<MeasureT, zkernel::cartesian> const&)
    -> std::partial_ordering;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator<=>(zlocation<MeasureT, zkernel::cartesian> const&,
            zlocation<MeasureT, zkernel::circular> const&)
    -> std::partial_ordering;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
std::ostream& operator<<(std::ostream&,
                         zlocation<MeasureT, zkernel::cartesian> const&);

// -----------------------------------------------------------------------------

/// @brief  Forward Declarations: Circular Kernel Partial Specialisation

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const&,
          zlocation<MeasureT, zkernel::circular> const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const&,
          zlocation<MeasureT, zkernel::cartesian> const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const&,
          zlocation<MeasureT, zkernel::circular> const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const&,
          zlocation<MeasureT, zkernel::cartesian> const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator*(zlocation<MeasureT, zkernel::circular> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::circular>;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator/(zlocation<MeasureT, zkernel::circular> const&, MeasureT const&)
    -> zlocation<MeasureT, zkernel::circular>;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::circular> const&,
           zlocation<MeasureT, zkernel::circular> const&) -> bool;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::circular> const&,
           zlocation<MeasureT, zkernel::cartesian> const&) -> bool;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator<=>(zlocation<MeasureT, zkernel::circular> const&,
            zlocation<MeasureT, zkernel::circular> const&)
    -> std::partial_ordering;

template <zmeasurable MeasureT>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator<=>(zlocation<MeasureT, zkernel::circular> const&,
            zlocation<MeasureT, zkernel::cartesian> const&)
    -> std::partial_ordering;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto operator<<(std::ostream&, zlocation<MeasureT, zkernel::circular> const&)
    -> std::ostream&;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( GLOBAL )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// =============================================================================

/// @brief Parameters, Helpers and Wrappers

namespace zdetail::zlocation {
/// @todo  internal constants
/// @todo  use k_{lowercase} for constants (avoid macro conflicts)

/// @brief c.f. std::numbers
class zconstant final {
public:
  template <zmeasurable MeasureT>
  static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, VRBL) std::floating_point
      auto k_machine_resolution_v{std::numeric_limits<MeasureT>::epsilon()};

  template <zmeasurable MeasureT>
  static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, VRBL) std::floating_point
      auto k_location_resolution_v{std::numeric_limits<MeasureT>::min()};

  // --------------------------------

  static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, VRBL) std::floating_point
      auto k_machine_resolution{k_machine_resolution_v<zmeasure<float>>};

  static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, VRBL) std::floating_point
      auto k_location_resolution{k_location_resolution_v<zmeasure<float>>};

  // --------------------------------

  static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, VRBL) std::integral
      auto k_unit_in_last{5};

private:
  /// @note Private Constructor: Non-Instantiable Class
  zconstant() = default;
};

// -----------------------------------------------------------------------------

/// @todo  tolerance-based three-coordinate < helper

template <zmeasurable MeasureT>
[[deprecated("")]] [[nodiscard(
    "same/"
    "boo"
    "l")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                        FUNC) auto same(MeasureT const&
                                                                            a,
                                                                        MeasureT const&
                                                                            b)
    -> typename std::enable_if<!std::numeric_limits<MeasureT>::is_integer,
                               bool>::type {
  return std::fabs(a - b) <= std::fabs(a + b) *
                                 zconstant::k_machine_resolution_v<MeasureT> *
                                 zconstant::k_unit_in_last ||
         std::fabs(a - b) < zconstant::k_location_resolution_v<MeasureT>;
}

/// @note helper (h_ prefix)
template <zmeasurable MeasureT>
[[deprecated("outdated method")]] [[nodiscard(
    "use "
    "resul"
    "t")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                        FUNC) auto h_near(MeasureT const&
                                                                              a,
                                                                          MeasureT const&
                                                                              b)
    -> bool {
  return std::fabs(a - b) <= zconstant::k_location_resolution_v<MeasureT>;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard("use result")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR,
    FUNC) auto near(Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_SCOPE()::
                        zlocation<MeasureT, KernE> const& a,
                    Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_SCOPE()::zlocation<
                        MeasureT, KernE> const& b) -> bool {
  return h_near(a.first(), b.first()) && h_near(a.second(), b.second());
}

// -----------------------------------------------------------------------------

/// @note uc (under construction)
template <template <zmeasurable, zkernel> class LocationT, typename MeasureT,
          zkernel KernE>
concept uc_zlocatable =
    requires(LocationT<MeasureT, KernE> l) {
      typename LocationT<MeasureT, KernE>::value_type;

      {
        l.first()
        } -> std::same_as<typename LocationT<MeasureT, KernE>::value_type>;

      {
        l.second()
        } -> std::same_as<typename LocationT<MeasureT, KernE>::value_type>;
    };

// -----------------------------------------------------------------------------

template <typename GenericT>
concept zarithmetical = requires(GenericT a, GenericT b) {
                          { a + b } -> std::same_as<GenericT>;
                          { a - b } -> std::same_as<GenericT>;
                        };

/*
template< typename GenericT >
concept zscalable = requires ( GenericT v, std::floating_point auto s ) {
                      { ( v * s ) } -> std::same_as< GenericT >;
                      { ( v / s ) } -> std::same_as< GenericT >;
                    };
*/

template <typename GenericT>
concept zrelatable = requires(GenericT a, GenericT b) {
                       { a == b } -> std::same_as<bool>;
                       { a <=> b } -> std::same_as<std::partial_ordering>;
                     };

template <typename LocationT>
concept zlocatable = requires(LocationT l) {
                       typename LocationT::value_type;

                       {
                         l.first()
                         } -> std::same_as<typename LocationT::value_type>;

                       {
                         l.second()
                         } -> std::same_as<typename LocationT::value_type>;

                       { l.kernel() };

                       requires zarithmetical<LocationT>;
                       requires zrelatable<LocationT>;
                     };

template <zlocatable LocationT> class znear {
public:
  using value_type = typename LocationT::value_type;

public:
  [[nodiscard("use result")]] static Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, FUNC) auto
  operator()(LocationT const& a, LocationT const& b) -> bool {
    return h_near<value_type>(a.first(), b.first()) &&
           h_near<value_type>(a.second(), b.second());
  }

private:
  znear() = default;
};

// -----------------------------------------------------------------------------

/// @todo  variadic scalar functor idiom
/// @todo  desired API: ScalarFunctor<F>(zlocation const&)

class functor;

class scalar;

template <std::invocable TransformationF, typename... ExtraP>
class ScalarFunctor {

public:
  template <zmeasurable MeasureT, zkernel KernE>
  zmeasurable auto operator()() -> MeasureT {
    return MeasureT();
  }
};
} // namespace zdetail::zlocation

// =============================================================================
/// zlocation
// =============================================================================

/// @class  zlocation
/// @brief  Main Template Class for Two-Dimensional Coordinate Position
/// @tparam MeasureT: zmeasurable type with physics-based arithmetic properties
/// @tparam KernE: zkernel enumerate for various coordinate systems
template <zmeasurable MeasureT, zkernel KernE> class zlocation final {
public:
  using value_type = MeasureT;

public:
  /// @brief  Default Constructor c.f. libstdc++ <complex>
  explicit Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
      zlocation(MeasureT const& i_first  = MeasureT(),
                MeasureT const& i_second = MeasureT())
      : m_first{i_first}, m_second{i_second} {}

  /// @brief  Compiler-Synthesised Copy Constructor
  /// @tparam MeasureU (can differ from MeasureT but kernels must match)
  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
  zlocation(zlocation<MeasureU, KernE> const& i_zlocation)
      : m_first{i_zlocation.first()}, m_second{i_zlocation.second()} {}

  // ---------------------------------------------------------------------------

  /// @brief Accessor Methods (constexpr support)

#if Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD(MODERN)

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) zmeasurable auto first() const noexcept -> MeasureT {
    return m_first;
  }

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) zmeasurable auto second() const noexcept -> MeasureT {
    return m_second;
  }

#else

  MeasureT&       first() { return m_first; }

  MeasureT&       second() { return m_second; }

  MeasureT const& first() const { return m_first; }

  MeasureT const& second() const { return m_second; }

#endif // !Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD ( MODERN )

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) auto kernel() const noexcept -> zkernel {
    return KernE;
  }

  // ---------------------------------------------------------------------------

  /// @brief Modifier Methods

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto first(MeasureT const& i_first) -> void { m_first = i_first; }

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto second(MeasureT const& i_second) -> void { m_second = i_second; }

  // ---------------------------------------------------------------------------

  /// @brief Overloaded Operators for Basic Arithmetic

  /// @brief Unary Operators
  /// @note  unary + is identity for this class so no need to overload

  [[nodiscard("use result from arithmetic "
              "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
      zlocation
      operator-() const;

  /// @brief Basic Arithmetic: Uniform Translation

  template <zmeasurable MeasureU>
  [[nodiscard("use result from arithmetic "
              "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
      zlocation&
      operator+=(MeasureU const&);

  template <zmeasurable MeasureU>
  [[nodiscard("use result from arithmetic "
              "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
      zlocation&
      operator-=(MeasureU const&);

  /// @brief Basic Arithmetic: Addition and Subtraction

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
  zlocation& operator+=(zlocation<MeasureU, KernE> const&);

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
  zlocation& operator-=(zlocation<MeasureU, KernE> const&);

  /// @brief Basic Arithmetic: Rescale

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
  zlocation& operator*=(MeasureU const&);

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
  zlocation& operator/=(MeasureU const&);

  ///@todo check if definition belongs here
  [[nodiscard("use result from relational "
              "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                  OLOP) auto
  operator==(zlocation<MeasureT, KernE> const&) const -> bool;

  [[nodiscard("use result from relational "
              "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                  OLOP) auto
  operator<=>(zlocation<MeasureT, KernE> const&) const -> std::partial_ordering;

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /// @note no code to avoid friend declarations/definitions

#elif Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(FRIEND)

  /// @brief friend versions of the overloaded arithmetic operators
  /// @note  friend definitions are automatically inlined

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator+(zlocation<MeasureT, KernE> const& a_zlocation,
            MeasureU const&                   a_shift) {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      += a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator-(zlocation<MeasureU, KernE> const& a_zlocation,
            MeasureT const&                   a_shift) {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      -= a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator+(zlocation<MeasureT, KernE> const& lhs_zlocation,
            zlocation<MeasureU, KernE> const& rhs_zlocation) {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      += rhs_zlocation;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator-(zlocation<MeasureT, KernE> const& lhs_zlocation,
            zlocation<MeasureU, KernE> const& rhs_zlocation) {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      -= rhs_zlocation;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator*(zlocation<MeasureT, KernE> const& a_zlocation,
            MeasureU const&                   a_scale) {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      *= a_scale;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "use result from arithmetic "
      "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) zlocation
  operator/(zlocation<MeasureT, KernE> const& a_zlocation,
            MeasureU const&                   a_scale) {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      /= a_scale;
    return interim_zlocation;
  }

  friend
      [[nodiscard("use result from relational "
                  "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                      OLOP) bool
      operator==(zlocation<MeasureT, KernE> const& lhs_zlocation,
                 zlocation<MeasureT, KernE> const& rhs_zlocation) {
    return (lhs_zlocation.m_first == rhs_zlocation.m_first &&
            lhs_zlocation.m_second == rhs_zlocation.m_second);
  }

  friend
      [[nodiscard("use result from relational "
                  "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                      OLOP) bool
      operator!=(zlocation<MeasureT, KernE> const& lhs_zlocation,
                 zlocation<MeasureT, KernE> const& rhs_zlocation) {
    return !operator==(lhs_zlocation, rhs_zlocation);
  }

  /// @brief Standard Stream

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP) std::ostream&
  operator<<(std::ostream& os, zlocation<MeasureT, KernE> const& a_zlocation) {
    os << std::format("({}\t{})", a_zlocation.m_first, a_zlocation.m_second);
    return os;
  };

#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( FRIEND )

  // ---------------------------------------------------------------------------

private:
  MeasureT m_first{MeasureT()};
  MeasureT m_second{MeasureT()};
};

// =============================================================================

/// @brief Defintions for Class Member Unary Overloads (-)

template <zmeasurable MeasureT, zkernel KernE>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, KernE>::operator-() const
    -> zlocation<MeasureT, KernE> {
  return zlocation<MeasureT, KernE>{-m_first, -m_second};
}

/// @brief Definitions for Class Member Overloads (+=, -=, *=, /=)

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto zlocation<MeasureT, KernE>::operator+=(MeasureU const& a_shift)
    -> zlocation<MeasureT, KernE>& {
  m_first  += a_shift;
  m_second += a_shift;
  return *this;
}

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto zlocation<MeasureT, KernE>::operator-=(MeasureU const& a_shift)
    -> zlocation<MeasureT, KernE>& {
  m_first  -= a_shift;
  m_second -= a_shift;
  return *this;
}

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto zlocation<MeasureT, KernE>::operator+=(
    zlocation<MeasureU, KernE> const& other_zlocation)
    -> zlocation<MeasureT, KernE>& {
  m_first  += other_zlocation.first();
  m_second += other_zlocation.second();
  return *this;
}

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto zlocation<MeasureT, KernE>::operator-=(
    zlocation<MeasureU, KernE> const& other_zlocation)
    -> zlocation<MeasureT, KernE>& {
  m_first  -= other_zlocation.first();
  m_second -= other_zlocation.second();
  return *this;
}

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
auto zlocation<MeasureT, KernE>::operator*=(MeasureU const& a_scale)
    -> zlocation<MeasureT, KernE>& {
  m_first  *= a_scale;
  m_second *= a_scale;
  return *this;
}

template <zmeasurable MeasureT, zkernel KernE>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto zlocation<MeasureT, KernE>::operator/=(MeasureU const& a_scale)
    -> zlocation<MeasureT, KernE>& {
  m_first  /= a_scale;
  m_second /= a_scale;
  return *this;
}

/// @todo Tolerance Correction
template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                        OLOP) auto zlocation<MeasureT,
                                                                             KernE>::
operator==(zlocation<MeasureT, KernE> const& other_zlocation) const -> bool {
  return (m_first == other_zlocation.first() &&
          m_second == other_zlocation.second());
};

/// @todo Tolerance Correction
template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                        OLOP) auto zlocation<MeasureT,
                                                                             KernE>::
operator<=>(zlocation<MeasureT, KernE> const& other_zlocation) const
    -> std::partial_ordering {
  return (m_first <=> other_zlocation.first() &&
          m_second <=> other_zlocation.second());
};

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @brief Definitions for Global Overloads ( +, -, *, \ )

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, KernE> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, KernE> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      += a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, KernE> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, KernE> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      -= a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, KernE> const& lhs_zlocation,
          zlocation<MeasureT, KernE> const& rhs_zlocation)
    -> zlocation<MeasureT, KernE> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      += rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, KernE> const& lhs_zlocation,
          zlocation<MeasureT, KernE> const& rhs_zlocation)
    -> zlocation<MeasureT, KernE> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      -= rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator*(zlocation<MeasureT, KernE> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, KernE> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      *= a_scale;
  return interim_zlocation;
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from arithmetic "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator/(zlocation<MeasureT, KernE> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, KernE> {
  [[assume(a_scale != MeasureT(0))]];
  auto interim_zlocation = a_zlocation;
  interim_zlocation      /= a_scale;
  return interim_zlocation;
}

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

/// @brief Definitions for Non-Class Member Boolean Overloads (==, !=)
/// @note  machine level nearness is used

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, KernE> const& lhs_zlocation,
           zlocation<MeasureT, KernE> const& rhs_zlocation) -> bool {

  auto machine_level_nearness = [](MeasureT const& a,
                                   MeasureT const& b) -> bool {
    return fabs(a - b) < std::numeric_limits<MeasureT>::min();
  };

  return machine_level_nearness(lhs_zlocation.first(), rhs_zlocation.first()) &&
         machine_level_nearness(lhs_zlocation.second(), rhs_zlocation.second());
}

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard(
    "use result from relational "
    "overload")]] inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator!=(zlocation<MeasureT, KernE> const& lhs_zlocation,
           zlocation<MeasureT, KernE> const& rhs_zlocation) -> bool {
  return !operator==(lhs_zlocation, rhs_zlocation);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// -----------------------------------------------------------------------------

/// @brief Definitions for Standard Stream Overloads

template <zmeasurable MeasureT, zkernel KernE>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto operator<<(std::ostream& os, zlocation<MeasureT, KernE> const& a_zlocation)
    -> std::ostream& {
  os << std::format("{}\t{}", a_zlocation.first(), a_zlocation.second());
  return os;
}

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( GLOBAL )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// =============================================================================

/// @brief Partial Template Specialisation for Cartesian Kernel

template <zmeasurable MeasureT>
class zlocation<MeasureT, zkernel::cartesian> final {
public:
  using value_type = MeasureT;

public:
  // explicit zlocation () = default;

  /// @brief Default Constructor c.f. libdstdc++ <complex>
  explicit Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
      zlocation(MeasureT const& i_horizontal = MeasureT(),
                MeasureT const& i_vertical   = MeasureT())
      : m_horizontal{i_horizontal}, m_vertical{i_vertical} {}

  /// @brief  Compiler-Synthesised Copy Constructors
  /// @tparam MeasureU (can differ from MeasureT and kernels must not match)
  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
  zlocation(zlocation<MeasureU, zkernel::cartesian> const& i_zlocation)
      : m_horizontal{i_zlocation.horizontal()}, m_vertical{
                                                    i_zlocation.vertical()} {}

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, CTOR)
  zlocation(zlocation<MeasureU, zkernel::circular> const& i_zlocation)
      : m_horizontal{i_zlocation.radial() * cos(i_zlocation.azimuthal())},
        m_vertical{i_zlocation.radial() * sin(i_zlocation.azimuthal())} {}

  // ---------------------------------------------------------------------------

  /// @brief Accessor Methods (constexpr support)

#if Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD(MODERN)

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) zmeasurable auto horizontal() const noexcept -> MeasureT {
    return m_horizontal;
  }

  [[nodiscard("use accessed member")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) zmeasurable auto vertical() const noexcept -> MeasureT {
    return m_vertical;
  }

  [[deprecated("accessor: first/horizontal")]] [[nodiscard(
      "access method")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                               MTHD) zmeasurable
      auto first() const noexcept -> MeasureT {
    return m_horizontal;
  }

  [[deprecated("accessor: second/vertical")]] [[nodiscard(
      "access method")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                               MTHD) zmeasurable
      auto second() const noexcept -> MeasureT {
    return m_vertical;
  }

#else

  MeasureT&       horizontal() { return m_horizontal; }

  MeasureT&       vertical() { return m_vertical; }

  MeasureT const& horizontal() const { return m_horizontal; }

  MeasureT const& vertical() const { return m_vertical; }

#endif // !Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD( MODERN )

  [[nodiscard("kernel")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) auto kernel() const noexcept -> zkernel {
    return zkernel::cartesian;
  }

  // ---------------------------------------------------------------------------

  /// @brief Modifier Methods

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto horizontal(MeasureT const& i_horizontal) -> void {
    m_horizontal = i_horizontal;
  }

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto vertical(MeasureT const& i_vertical) -> void { m_vertical = i_vertical; }

  [[deprecated(
      "modifier: "
      "first/horizontal")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE,
                                                                  MTHD) auto first(MeasureT const&
                                                                                       i_horizontal)
      -> void {
    m_horizontal = i_horizontal;
  }

  [[deprecated(
      "modifier: "
      "second/vertical")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE,
                                                                 MTHD) auto second(MeasureT const&
                                                                                       i_vertical)
      -> void {
    m_vertical = i_vertical;
  }

  // ---------------------------------------------------------------------------

  /// @brief Overloaded Operators for Arithmetic Operations

  /// @brief Unary Operators

  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-() const -> zlocation;

  /// @brief Basic Arithmetic: Uniform Translation

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator+=(MeasureU const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-=(MeasureU const&) -> zlocation&;

  /// @brief Basic Arithmetic: Addition and Subtraction
  /// @note  Specialised for Cartesian and Circular Interactions

  /// @todo  Removal of the [nodiscard("")] attribute
  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator+=(zlocation<MeasureU, zkernel::cartesian> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator+=(zlocation<MeasureU, zkernel::circular> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator-=(zlocation<MeasureU, zkernel::cartesian> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator-=(zlocation<MeasureU, zkernel::circular> const&) -> zlocation&;

  /// @brief Basic Arithmetic: Rescale

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator*=(MeasureU const&) -> zlocation&;

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
  auto operator/=(MeasureU const&) -> zlocation&;

  /// @brief Relational Operators

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator==(zlocation<MeasureT, zkernel::cartesian> const&) const -> bool;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator==(zlocation<MeasureT, zkernel::circular> const&) const -> bool;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator<=>(zlocation<MeasureT, zkernel::cartesian> const&) const
      -> std::partial_ordering;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator<=>(zlocation<MeasureT, zkernel::circular> const&) const
      -> std::partial_ordering;

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /// @note no code to avoid friend definitions/declarations

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#elif Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(FRIEND)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /// @brief Friend Functions for Basic Arithmetic
  /// @note Added the [[nodiscard("")]] attribute here

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator+(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
            MeasureU const&                                a_shift)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      += a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator-(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
            MeasureU const&                                a_shift)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      -= a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator+(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
            zlocation<MeasureU, zkernel::cartesian> const& rhs_zlocation)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      += rhs_zlocation;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator-(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
            zlocation<MeasureU, zkernel::cartesian> const& rhs_zlocation)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      -= rhs_zlocation;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator*(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
            MeasureU const&                                a_scale)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      *= a_scale;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend [[nodiscard(
      "overloaded "
      "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator/(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
            MeasureU const&                                a_scale)
      -> zlocation<MeasureT, zkernel::cartesian> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      /= a_scale;
    return interim_zlocation;
  }

  friend [[nodiscard(
      "overloaded "
      "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator==(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
      -> bool {
    /*
    return ( lhs_zlocation.m_horizontal == rhs_zlocation.m_horizontal &&
             lhs_zlocation.m_vertical == rhs_zlocation.m_vertical );
    */
    return xdetail::zlocation::near(lhs_location, rhs_zlocation);
  }

  /// @todo check conversion from circular to cartesian
  friend [[nodiscard(
      "overloaded "
      "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator==(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
      -> bool {
    return operator==(lhs_zlocation,
                      zlocation<MeasureT, zkernel::cartesian>(rhs_zlocation));
  }

  friend [[nodiscard(
      "overloaded "
      "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator!=(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
      -> bool {
    return !operator==(lhs_zlocation, rhs_zlocation);
  }

  friend [[nodiscard(
      "overloaded "
      "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator!=(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
      -> bool {
    return !operator==(lhs_zlocation, rhs_zlocation);
  }

  // ---------------------------------------------------------------------------

  /// @brief Standard Stream

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP) auto
  operator<<(std::ostream&                                  os,
             zlocation<MeasureT, zkernel::cartesian> const& a_zlocation)
      -> std::ostream& {
    os << std::format("({},{})", a_zlocation.m_horizontal,
                      a_zlocation.m_vertical);
    return os;
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD()
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /// @brief General Methods

  /// @note included for consistency
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, MTHD)
  zmeasurable auto radial() const -> MeasureT {
    return std::hypot(m_horizontal, m_vertical);
  }

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, MTHD)
  zmeasurable auto azimuthal() const -> MeasureT {
    return std::atan2(m_vertical, m_horizontal);
  }

private:
  /// @brief Cartesian Conventions
  MeasureT m_horizontal{MeasureT()};
  MeasureT m_vertical{MeasureT()};
};

// =============================================================================

/// @brief Defintions for Class Member Unary Overloads (-)

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator-() const
    -> zlocation<MeasureT, zkernel::cartesian> {
  return zlocation<MeasureT, zkernel::cartesian>{-m_horizontal, -m_vertical};
}

/// @brief Definitions for Class Member Overloads (+=, -=, *=, /=)

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator+=(
    MeasureU const& a_shift) -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal += a_shift;
  m_vertical   += a_shift;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator-=(
    MeasureU const& a_shift) -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal -= a_shift;
  m_vertical   -= a_shift;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator+=(
    zlocation<MeasureU, zkernel::cartesian> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal += other_zlocation.horizontal();
  m_vertical   += other_zlocation.vertical();
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator+=(
    zlocation<MeasureU, zkernel::circular> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal += other_zlocation.radial() * cos(other_zlocation.azimuthal());
  m_vertical   += other_zlocation.radial() * sin(other_zlocation.azimuthal());
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator-=(
    zlocation<MeasureU, zkernel::cartesian> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal -= other_zlocation.horizontal();
  m_vertical   -= other_zlocation.vertical();
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator-=(
    zlocation<MeasureU, zkernel::circular> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal -= other_zlocation.radial() * cos(other_zlocation.azimuthal());
  m_vertical   -= other_zlocation.radial() * sin(other_zlocation.azimuthal());
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator*=(
    MeasureU const& a_scale) -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal *= a_scale;
  m_vertical   *= a_scale;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::cartesian>::operator/=(
    MeasureU const& a_scale) -> zlocation<MeasureT, zkernel::cartesian>& {
  m_horizontal /= a_scale;
  m_vertical   /= a_scale;
  return *this;
}

/// @brief Member Relational Overloads (== and <=>)

/// @todo  Tolerance Correction
template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, FUNC) auto zlocation<MeasureT, zkernel::cartesian>::
operator==(zlocation<MeasureT, zkernel::cartesian> const& other_zlocation) const
    -> bool {
  /*
  return ( m_horizontal == other_zlocation.horizontal () &&
           m_vertical == other_zlocation.vertical () );
  */

  return zdetail::zlocation::near(*this, other_zlocation);
};

/// @todo  Tolerance Correction
/// @note  Cirular-Cartesian API (horizontal() and vertical())
template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, OLOP) auto zlocation<MeasureT, zkernel::cartesian>::
operator==(zlocation<MeasureT, zkernel::circular> const& other_zlocation) const
    -> bool {
  return (m_horizontal == other_zlocation.horizontal() &&
          m_vertical == other_zlocation.vertical());
};

/// @todo  Tolerance Correction
template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, OLOP) auto zlocation<MeasureT, zkernel::cartesian>::
operator<=>(zlocation<MeasureT, zkernel::cartesian> const& other_zlocation)
    const -> std::partial_ordering {
  return (m_horizontal <=> other_zlocation.horizontal() &&
          m_vertical <=> other_zlocation.vertical());
};

/// @todo  Tolerance Correction
/// @note  Cirular-Cartesian API (horizontal() and vertical())
template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, FUNC) auto zlocation<MeasureT, zkernel::cartesian>::
operator<=>(zlocation<MeasureT, zkernel::circular> const& other_zlocation) const
    -> std::partial_ordering {
  return (m_horizontal <=> other_zlocation.horizontal() &&
          m_vertical <=> other_zlocation.vertical());
};

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @brief Definitions for Global Overloads ( +, -, *, \ )

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      += a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      -= a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      += rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator+(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      += rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      -= rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator-(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
    -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      -= rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator*(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, zkernel::cartesian> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      *= a_scale;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator/(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, zkernel::cartesian> {
  [[assume(a_scale != MeasureT(0))]];
  auto interim_zlocation = a_zlocation;
  interim_zlocation      /= a_scale;
  return interim_zlocation;
}

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

/// @brief Non-Class Member Boolean Overloads (==, !=)
/// @note  machine level nearness is used
/// @todo  update with internal::zlocation functionalities

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator==(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> bool {
  auto machine_level_nearness = [](MeasureT const& a,
                                   MeasureT const& b) -> bool {
    return fabs(a - b) < std::numeric_limits<MeasureT>::min();
  };

  return machine_level_nearness(lhs_zlocation.horizontal(),
                                rhs_zlocation.horizontal()) &&
         machine_level_nearness(lhs_zlocation.vertical(),
                                rhs_zlocation.vertical());
}

/// @todo  correct for to_cartesian

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator==(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
    -> bool {
  return operator==(lhs_zlocation,
                    zlocation<MeasureT, zkernel::cartesian>{rhs_zlocation});
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator!=(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> bool {
  return !operator==(lhs_zlocation, rhs_zlocation);
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC) auto
operator!=(zlocation<MeasureT, zkernel::cartesian> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::circular> const&  rhs_zlocation)
    -> bool {
  return operator!=(lhs_zlocation, zlocation < MeasureT,
                    zkernel::cartesian{rhs_zlocation});
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// -----------------------------------------------------------------------------

/// @brief Definition for Standard Stream (Cartesian Conventions)

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto operator<<(std::ostream&                                  os,
                zlocation<MeasureT, zkernel::cartesian> const& a_zlocation)
    -> std::ostream& {
  return os << std::format("({},{})", a_zlocation.horizontal(),
                           a_zlocation.vertical());
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( GLOBAL )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// =============================================================================

/// @brief Partial Template Specialisation for Circular Kernel

template <zmeasurable MeasureT>
class zlocation<MeasureT, zkernel::circular> final {
public:
  using value_type = MeasureT;

public:
  /// @brief  Default Constructor c.f. stdlibc++ <complex>
  explicit Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
      zlocation(MeasureT const& i_radial    = MeasureT(),
                MeasureT const& i_azimuthal = MeasureT())
      : m_radial{i_radial}, m_azimuthal{i_azimuthal} {}

  /// @brief  Compiler-Synthesised Copy Constructors
  /// @tparam MeasureU (can differ from MeasureT and kernels must not match)
  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
  zlocation(zlocation<MeasureU, zkernel::circular> const& i_zlocation)
      : m_radial{i_zlocation.radial()}, m_azimuthal{i_zlocation.azimuthal()} {}

  template <zmeasurable MeasureU>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EVAL, CTOR)
  zlocation(zlocation<MeasureU, zkernel::cartesian> const& i_zlocation)
      : m_radial{std::hypot(i_zlocation.horizontal(), i_zlocation.vertical())},
        m_azimuthal{
            std::atan2(i_zlocation.vertical(), i_zlocation.horizontal())} {}

  // ---------------------------------------------------------------------------

  /// @brief Accessor Methods (constexpr support)

#if Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD(MODERN)

  [[nodiscard("accessor")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, MTHD)
      zmeasurable auto radial() const noexcept -> MeasureT {
    return m_radial;
  }

  [[nodiscard("accessor")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, MTHD)
      zmeasurable auto azimuthal() const noexcept -> MeasureT {
    return m_azimuthal;
  }

  [[deprecated("first/radial")]] [[nodiscard(
      "accessor")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                          MTHD) zmeasurable
      auto first() const noexcept -> MeasureT {
    return m_radial;
  }

  [[deprecated("second/azimuthal")]] [[nodiscard(
      "accessor")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                          MTHD) zmeasurable
      auto second() const noexcept -> MeasureT {
    return m_azimuthal;
  }

#else

  MeasureT&       radial() { return m_radial; }

  MeasureT&       azimuthal() { return m_azimuthal; }

  MeasureT const& radial() const { return m_radial; }

  MeasureT const& azimuthal() const { return m_azimuthal; }

#endif // !Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD( MODERN )

  [[nodiscard("kernel")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      EXPR, MTHD) auto kernel() const noexcept -> zkernel {
    return zkernel::circular;
  }

  // ---------------------------------------------------------------------------

  /// Modifier Methods

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto radial(MeasureT const& i_radial) -> void { m_radial = i_radial; }

  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, MTHD)
  auto azimuthal(MeasureT const& i_azimuthal) -> void {
    m_azimuthal = i_azimuthal;
  }

  [[deprecated("first/radial")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      NONE, MTHD) auto first(MeasureT const& i_radial) -> void {
    m_radial = i_radial;
  }

  [[deprecated("first/radial")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
      NONE, MTHD) auto second(MeasureT const& i_azimuthal) -> void {
    m_azimuthal = i_azimuthal;
  }

  // ---------------------------------------------------------------------------

  /// @brief Overloaded Operators for Arithmetic Operations
  /// @note  Circular Convetions and Circular-Cartesian Interactions

  /// @brief Unary Operators
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-() const -> zlocation;

  /// @brief Basic Arithmetic: Radial Translation

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator+=(MeasureU const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-=(MeasureU const&) -> zlocation&;

  /// @brief Basic Arithmetic: Addition and Subtraction

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator+=(zlocation<MeasureU, zkernel::circular> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator+=(zlocation<MeasureU, zkernel::cartesian> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-=(zlocation<MeasureU, zkernel::circular> const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator-=(zlocation<MeasureU, zkernel::cartesian> const&) -> zlocation&;

  /// @brief Basic Arithmetic: Rescale

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator*=(MeasureU const&) -> zlocation&;

  template <zmeasurable MeasureU>
  [[nodiscard("overloaded "
              "arithmetic")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator/=(MeasureU const&) -> zlocation&;

  /// @brief Overloaded Relational

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator==(zlocation<MeasureT, zkernel::circular> const&) const -> bool;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator==(zlocation<MeasureT, zkernel::cartesian> const&) const -> bool;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator<=>(zlocation<MeasureT, zkernel::circular> const&) const
      -> std::partial_ordering;

  [[nodiscard("overloaded "
              "relational")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                    OLOP) auto
  operator<=>(zlocation<MeasureT, zkernel::cartesian> const&) const
      -> std::partial_ordering;

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /// @note no code to avoid friend declarations/definitions

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#elif Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(FRIEND)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /// @brief Overloaded Friends

  template <zmeasurable MeasureU>
  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator+(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
            MeasureU const& a_shift) -> zlocation<MeasureT, zkernel::circular> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      += a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator-(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
            MeasureU const& a_shift) -> zlocation<MeasureT, zkernel::circular> {
    auto interim_zlocation = a_zlocation;
    interim_zlocation      -= a_shift;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator+(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
            zlocation<MeasureU, zkernel::circular> const& rhs_zlocation)
      -> zlocation<MeasureT, zkernel::circular> {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      += rhs_zlocation;
    return interim_zlocation;
  }

  template <zmeasurable MeasureU>
  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator-(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
            zlocation<MeasureU, zkernel::circular> const& rhs_zlocation)
      -> zlocation<MeasureT, zkernel::circular> {
    auto interim_zlocation = lhs_zlocation;
    interim_zlocation      -= rhs_zlocation;
    return interim_zlocation;
  }

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator==(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
      -> bool {
    return (lhs_zlocation.m_radial == rhs_zlocation.m_radial &&
            lhs_zlocation.m_azimuthal == rhs_zlocation.m_azimuthal);
  }

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator==(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
             zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
      -> bool {
    return operator==(lhs_zlocation,
                      zlocation<MeasureT, zkernel::circular>(rhs_zlocation));
  }

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator!=(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
             zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
      -> bool {
    return !operator==(lhs_zlocation, rhs_zlocation);
  }

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
  operator!=(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
             zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
      -> bool {
    return !operator==(lhs_zlocation, rhs_zlocation);
  };

  /// @brief Standard Stream

  friend Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP) auto
  operator<<(std::ostream&                                 os,
             zlocation<MeasureT, zkernel::circular> const& a_zlocation)
      -> std::ostream& {
    os << std::format("({}:{}*PI)", a_zlocation.m_radial,
                      a_zlocation.m_azimuthal / std::numbers::pi);
    return os;
  }

  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( GLOBAL )
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // ---------------------------------------------------------------------------

  /// @brief Generic Methods

  [[nodiscard("")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                          MTHD) zmeasurable
      auto horizontal() const -> MeasureT {
    return m_radial * cos(m_azimuthal);
  }

  [[nodiscard("")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                          MTHD) zmeasurable
      auto vertical() const -> MeasureT {
    return m_radial * sin(m_azimuthal);
  }

  // ---------------------------------------------------------------------------

private:
  /// @brief Circular Conventions
  MeasureT m_radial{MeasureT()};
  MeasureT m_azimuthal{MeasureT()};
};

// =============================================================================

/// @brief Definitions for Unary Operators (-)

/// @todo  check consistency with bounds of (radial,azimuthal)
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator-() const
    -> zlocation<MeasureT, zkernel::circular> {
  return zlocation<MeasureT, zkernel::circular>{m_radial,
                                                m_azimuthal + std::numbers::pi};
}

/// @brief Definitions for Class Member Overloads (+=, -=, *=, /=)

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator+=(MeasureU const& a_shift)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial += a_shift;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator-=(MeasureU const& a_shift)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial -= a_shift;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator+=(
    zlocation<MeasureU, zkernel::circular> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial    += other_zlocation.radial();
  m_azimuthal += other_zlocation.azimuthal();
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator+=(
    zlocation<MeasureU, zkernel::cartesian> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial +=
      std::hypot(other_zlocation.horizontal(), other_zlocation.vertical());
  m_azimuthal +=
      std::atan2(other_zlocation.vertical(), other_zlocation.horizontal());
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator-=(
    zlocation<MeasureU, zkernel::circular> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial    -= other_zlocation.radial();
  m_azimuthal -= other_zlocation.azimuthal();
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator-=(
    zlocation<MeasureU, zkernel::cartesian> const& other_zlocation)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial -=
      std::hypot(other_zlocation.horizontal(), other_zlocation.vertical());
  m_azimuthal -=
      std::atan2(other_zlocation.vertical(), other_zlocation.horizontal());
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator*=(MeasureU const& a_scale)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial *= a_scale;
  return *this;
}

template <zmeasurable MeasureT>
template <zmeasurable MeasureU>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator/=(MeasureU const& a_scale)
    -> zlocation<MeasureT, zkernel::circular>& {
  m_radial /= a_scale;
  return *this;
}

/// @brief Relational Overloads

/// @todo  Tolerance Correction
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator==(
    zlocation<MeasureT, zkernel::circular> const& other_zlocation) const
    -> bool {
  return (m_radial == other_zlocation.radial() &&
          m_azimuthal == other_zlocation.azimuthal());
};

/// @todo  Tolerance Correction
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator==(
    zlocation<MeasureT, zkernel::cartesian> const& other_zlocation) const
    -> bool {
  return (m_radial == other_zlocation.radial() &&
          m_azimuthal == other_zlocation.azimuthal());
};

/// @todo  Tolerance Correction
/// @note  Incorrect Defintion
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator<=>(
    zlocation<MeasureT, zkernel::circular> const& other_zlocation) const
    -> std::partial_ordering {
  return (m_radial <=> other_zlocation.radial() &&
          m_azimuthal <=> other_zlocation.azimuthal());
};

/// @todo  Tolerance Correction
/// @note  Incorrect Defintion
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP)
auto zlocation<MeasureT, zkernel::circular>::operator<=>(
    zlocation<MeasureT, zkernel::cartesian> const& other_zlocation) const
    -> std::partial_ordering {
  return (m_radial <=> other_zlocation.radial() &&
          m_azimuthal <=> other_zlocation.azimuthal());
};

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD(GLOBAL)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @brief Definitions for Non-Class Member Overloads ( +, -, *, \ )

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      += a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
          MeasureT const& a_shift) -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      -= a_shift;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      += rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator+(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
          zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      += rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
          zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      -= rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator-(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
          zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = lhs_zlocation;
  interim_zlocation      -= rhs_zlocation;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator*(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      *= a_scale;
  return interim_zlocation;
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator/(zlocation<MeasureT, zkernel::circular> const& a_zlocation,
          MeasureT const& a_scale) -> zlocation<MeasureT, zkernel::circular> {
  auto interim_zlocation = a_zlocation;
  interim_zlocation      /= a_scale;
  return interim_zlocation;
}

// -----------------------------------------------------------------------------

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD(MODERN)
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/// @note Class Members for Relational Overloads in Modern C++20

#else

/// @brief Definitions for Non-Class Member Boolean Overloads (==, !=)
/// @note  machine level nearness is used

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
    -> bool {
  auto machine_level_nearness = [](MeasureT const& a,
                                   MeasureT const& b) -> bool {
    return fabs(a - b) < std::numeric_limits<MeasureT>::min();
  };

  return machine_level_nearness(lhs_zlocation.radial(),
                                rhs_zlocation.radial()) &&
         machine_level_nearness(lhs_zlocation.azimuthal(),
                                rhs_zlocation.azimuthal());
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator==(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
           zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> bool {
  return operator==(lhs_zlocation, to_circular(rhs_zlocation));
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator!=(zlocation<MeasureT, zkernel::circular> const& lhs_zlocation,
           zlocation<MeasureT, zkernel::circular> const& rhs_zlocation)
    -> bool {
  return !operator==(lhs_zlocation, rhs_zlocation);
}

template <zmeasurable MeasureT>
inline Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, OLOP) auto
operator!=(zlocation<MeasureT, zkernel::circular> const&  lhs_zlocation,
           zlocation<MeasureT, zkernel::cartesian> const& rhs_zlocation)
    -> bool {
  return !operator==(lhs_zlocation, to_circular(rhs_zlocation));
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_RELATIONAL_METHOD( MODERN )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// -----------------------------------------------------------------------------

/// @brief Definition for Standard Stream
/// @note  Azimuthal Representation in PI-based Units

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(NONE, OLOP)
auto operator<<(std::ostream&                                 os,
                zlocation<MeasureT, zkernel::circular> const& a_zlocation)
    -> std::ostream& {

  auto const radian_format = [](MeasureT const& a_radian) {
    return a_radian / std::numbers::pi;
  };

  return os << std::format("({}:{}*PI)", a_zlocation.radial(),
                           radian_format(a_zlocation.azimuthal()));
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif // !Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD( GLOBAL )
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// =============================================================================

/**
 * \class convert
 * \brief Kernel Conversion Functors
 * \todo  Desired API: convert<KernE2>(zlocation<MeasureT, KernE1> const&)
 */

template <zkernel KernE> class [[nodiscard]] convert final {
public:
  template <zmeasurable MeasureT>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto operator()(zlocation<MeasureT, zkernel::cartesian> const&) const
      -> zlocation<MeasureT, KernE>;

  template <zmeasurable MeasureT>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto operator()(zlocation<MeasureT, zkernel::circular> const&) const
      -> zlocation<MeasureT, KernE>;
};

template <zkernel KernE>
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
auto convert<KernE>::operator()(
    zlocation<MeasureT, zkernel::cartesian> const& a_zlocation) const
    -> zlocation<MeasureT, KernE> {
  return zlocation<MeasureT, KernE>{a_zlocation.horizontal(),
                                    a_zlocation.vertical()};
}

template <zkernel KernE>
template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
auto convert<KernE>::operator()(
    zlocation<MeasureT, zkernel::circular> const& a_zlocation) const
    -> zlocation<MeasureT, KernE> {
  return zlocation<MeasureT, KernE>{a_zlocation.radial(),
                                    a_zlocation.azimuthal()};
}

// -----------------------------------------------------------------------------

template <> class [[nodiscard]] convert<zkernel::cartesian> final {
public:
  template <zmeasurable MeasureT>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto operator()(zlocation<MeasureT, zkernel::circular> const&) const
      -> zlocation<MeasureT, zkernel::cartesian>;
};

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
auto convert<zkernel::cartesian>::operator()(
    zlocation<MeasureT, zkernel::circular> const& a_zlocation) const
    -> zlocation<MeasureT, zkernel::cartesian> {
  return zlocation<MeasureT, zkernel::cartesian>{a_zlocation.horizontal(),
                                                 a_zlocation.vertical()};
}

// -----------------------------------------------------------------------------

template <> class [[nodiscard]] convert<zkernel::circular> final {
public:
  template <zmeasurable MeasureT>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto operator()(zlocation<MeasureT, zkernel::cartesian> const&) const
      -> zlocation<MeasureT, zkernel::circular>;
};

template <zmeasurable MeasureT>
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
auto convert<zkernel::circular>::operator()(
    zlocation<MeasureT, zkernel::cartesian> const& a_zlocation) const
    -> zlocation<MeasureT, zkernel::circular> {
  return zlocation<MeasureT, zkernel::circular>{a_zlocation.radial(),
                                                a_zlocation.azimuthal()};
}

// =============================================================================

/// @name  norm
/// @brief Euclidean Metric

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard("norm")]] zmeasurable auto
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
    norm(zlocation<MeasureT, KernE> const& a_zlocation) -> MeasureT {
  return std::hypot(a_zlocation.first(), a_zlocation.second());
}

/// @brief Partial Specialisation for Cartesian and Circular Kernels

template <zmeasurable MeasureT>
[[nodiscard("norm")]] zmeasurable auto
Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
    norm(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation)
        -> MeasureT {
  return std::hypot(a_zlocation.horizontal(), a_zlocation.vertical());
}

template <zmeasurable MeasureT>
[[nodiscard("norm")]] auto Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
    norm(zlocation<MeasureT, zkernel::circular> const& a_zlocation) {
  return a_zlocation.radial();
}

// =============================================================================

/// @name  orientation
/// @brief Radians Relative to the Horizontal Axis

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard("orientation")]] auto Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                        FUNC)
    orientation(zlocation<MeasureT, KernE> const& a_zlocation) {
  return std::atan2(a_zlocation.second(), a_zlocation.first());
}

/// @brief Partial Specialisation for Cartesian and Circular Kernels

template <zmeasurable MeasureT>
[[nodiscard("orientation")]] auto Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                        FUNC)
    orientation(zlocation<MeasureT, zkernel::cartesian> const& a_zlocation) {
  return std::atan2(a_zlocation.vertical(), a_zlocation.horizontal());
}

template <zmeasurable MeasureT>
[[nodiscard("orientation")]] auto Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR,
                                                                        FUNC)
    orientation(zlocation<MeasureT, zkernel::circular> const& a_zlocation) {
  return a_zlocation.azimuthal();
}

// =============================================================================

/// @name  invert
/// @brief ...
/// @todo  ...

template <zmeasurable MeasureT, zkernel KernE>
[[nodiscard("invert")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, FUNC) auto invert(zlocation<MeasureT, KernE> const& a_zlocation) {
  return zlocation<MeasureT, KernE>{a_zlocation.second(), a_zlocation.first()};
}

template <zmeasurable MeasureT>
[[nodiscard("invert")]] Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(
    EXPR, FUNC) auto invert(zlocation<MeasureT, zkernel::cartesian> const&
                                a_zlocation) {
  return zlocation<MeasureT, zkernel::cartesian>{a_zlocation.vertical(),
                                                 a_zlocation.horizontal()};
}

// =============================================================================
// =============================================================================
Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE(END)
// =============================================================================
// =============================================================================

/// @name  Custom Formatter
/// @brief Strategy Design Pattern (tikz, matlab, etc)
/// @note  Must be struct std::formatter (not class std::formatter)
/// @note  std namespace
/// @todo  ...

// =============================================================================

template <zmicrostructure::zmeasurable MeasureT, zmicrostructure::zkernel KernE,
          class CharT>
struct std::formatter<zmicrostructure::zlocation<MeasureT, KernE>, CharT>
    : std::formatter<MeasureT, CharT> {
  template <class FormatContext>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto format(zmicrostructure::zlocation<MeasureT, KernE> const& a_zlocation,
              FormatContext& format_context) const {
    return std::format_to(format_context.out(), "({}\t{})", a_zlocation.first(),
                          a_zlocation.second());
  }
};

template <zmicrostructure::zmeasurable MeasureT, class CharT>
struct std::formatter<
    zmicrostructure::zlocation<MeasureT, zmicrostructure::zkernel::cartesian>,
    CharT> : std::formatter<MeasureT, CharT> {
  template <class FormatContext>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto format(
      zmicrostructure::zlocation<
          MeasureT, zmicrostructure::zkernel::cartesian> const& a_zlocation,
      FormatContext& format_context) const {
    return std::format_to(format_context.out(), "({},{})",
                          a_zlocation.horizontal(), a_zlocation.vertical());
  }
};

template <zmicrostructure::zmeasurable MeasureT, class CharT>
struct std::formatter<
    zmicrostructure::zlocation<MeasureT, zmicrostructure::zkernel::circular>,
    CharT> : std::formatter<MeasureT, CharT> {
  template <class FormatContext>
  Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC(EXPR, FUNC)
  auto format(
      zmicrostructure::zlocation<
          MeasureT, zmicrostructure::zkernel::circular> const& a_zlocation,
      FormatContext& format_context) const {
    return std::format_to(format_context.out(), "({}:{}*PI)",
                          a_zlocation.radial(),
                          a_zlocation.azimuthal() / std::numbers::pi);
  }
};

// =============================================================================

/// @todo Potential Generalisation (Unfinished)
/// @attention Under Construction
// ring: +, -, *,
// field: +, -, *, /
// zlocation< zkernel<xcoordinate,xcoordinate> cartesian >
// concept locatable = requires () {}
// locatable LocationT
// xdistance< xmetric > ( zlocation const&, zlocation const& );

// Intention: an array of points with different models and units
// Loop over such an array in a lattice structure for transform_reduce

namespace zmicrostructure::zsandbox {

template <typename GenericT>
concept coordinate = requires(GenericT a, GenericT b) {
                       typename GenericT::value_type;
                       { a + b } -> std::same_as<GenericT>;
                       { a - b } -> std::same_as<GenericT>;
                     };

template <coordinate CoordinateT> class cartesian final {
public:
  using value_type = CoordinateT::value_type;

private:
  CoordinateT m_coordinate;
};

template <coordinate CoordinateT1, coordinate CoordinateT2> class kernel {
private:
  CoordinateT1 m_first;
  CoordinateT2 m_second;
};

template <template <coordinate CoordinateT1, coordinate CoordinateT2>
          class Kernel>
class zlocation {};

}; // namespace zmicrostructure::zsandbox

// =============================================================================

/// @brief Macro Cleanse

#undef Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE
#undef Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_BEGIN
#undef Z_MICROSTRUCTURE_Z_LOCATION_NAMESPACE_END

#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_CTOR
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_CTOR
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_CTOR
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_OLOP
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_OLOP
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_OLOP
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_MTHD
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_MTHD
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_MTHD
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EVAL_FUNC
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_FUNC
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_FUNC
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_ITER
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_ITER
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_INIT_VRBL
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_EXPR_VRBL
#undef Z_MICROSTRUCTURE_Z_LOCATION_CONSTSPEC_NONE_VRBL

#undef Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_METHOD
#undef Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_GLOBAL
#undef Z_MICROSTRUCTURE_Z_LOCATION_OVERLOAD_FRIEND

#undef Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_METHOD
#undef Z_MICROSTRUCTURE_Z_LOCATION_ACCESSOR_MODERN

// =============================================================================

/// @brief Kernel Checklist (Partial Specialisation)
///        - [] forward declaration: template<> class<>;
///        - [] forward declarations: overloads (global + friends)
///        - [] class members: first/second, horizontal/vertical
///        - [] overload definitions: +=, -=, *=, /= as methods
///        - [] overload definitions: +, -, *, / as global/friend
///        - [] comparison: ==, != and <=>
///        - [] functionalities: comparison, inversion, etc.

/// \todo Corrections and Revisions (Unfinished Draft)
/// @todo relax the constexpr and consteval specification
/// @todo access methods need corrections
/// @todo -> decltype () and -> decltype(auto)
/// @todo enum class angle { deg, rad }
/// @todo same, concindental, near: comparison idiom
/// @todo copy/move semantics to be defaulted
/// @todo remove some [[nodiscard]] and [[deprecated]]
/// @todo check transform_reduce lambda implementation for functor
/// @todo internal testing for debug build
/// @todo debug messages for debug build
/// @todo clang-tidy and clang-format
/// @todo multi-scale and multi-dimensional extension
/// @todo major revision: use std::array and specialise for N=2

#endif // !__Z_MICROSTRUCTURE_Z_LOCATION_HPP__