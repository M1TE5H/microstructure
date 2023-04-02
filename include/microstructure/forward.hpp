/**
 * \file  microstructure/include/microstructure/forward.hpp
 * \brief Forward Declarations for the Main Header
 */

#pragma once

// ================================================================

// NAMESPACE RESERVATION

#define MICROSTRUCTURE_NAMESPACE_BEGIN namespace microstructure {
#define MICROSTRUCTURE_NAMESPACE_END   } // namespace microstructure

MICROSTRUCTURE_NAMESPACE_BEGIN MICROSTRUCTURE_NAMESPACE_END

// ================================================================

// STANDARD LIBRARY (2020)

// c headers
#include <cassert>
#include <cmath>
#include <cstddef>

// c++17 headers
#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <vector>

// c++20 headers
#include <concepts>
#include <coroutine>
#include <numbers>
#include <ranges>
#include <span>

// ================================================================

// STANDARD LIBRARY (2023)

// #include <format>

#ifndef MICROSTRUCTURE_FMTLIB
	#define MICROSTRUCTURE_FMTLIB 0
#endif

#if MICROSTRUCTURE_FMTLIB > 0
	#include <fmt/format.h>
	#include <fmt/os.h>
#endif

// ================================================================

// OUTPUT FLAGS

#ifndef MICROSTRUCTURE_D3JS
	#define MICROSTRUCTURE_D3JS 0
#endif

#ifndef MICROSTRUCTURE_GNUPLOT
	#define MICROSTRUCTURE_GNUPLOT 0
#endif

#ifndef MICROSTRUCTURE_JULIA
	#define MICROSTRUCTURE_JULIA 0
#endif

#ifndef MICROSTRUCTURE_MATLAB
	#define MICROSTRUCTURE_MATLAB 0
#endif

#ifndef MICROSTRUCTURE_MATPLOTLIB
	#define MICROSTRUCTURE_MATPLOTLIB 0
#endif

#ifndef MICROSTRUCTURE_PGF
	#define MICROSTRUCTURE_PGF 0
#endif

#ifndef MICROSTRUCTURE_TIKZ
	#define MICROSTRUCTURE_TIKZ 0
#endif

#ifndef MICROSTRUCTURE_SVG
	#define MICROSTRUCTURE_SVG 0
#endif

#ifndef MICROSTRUCTURE_XELATEX
	#define MICROSTRUCTURE_XELATEX 0
#endif

// ================================================================

// MICROSTRUCTURE INTERNALS

// microstructure utilities
#include <utl/utl.hpp>

// microstructure tools
#include <tool/tool.hpp>

// microstructure libraries
#include <learner/learner.hpp>
#include <solver/solver.hpp>
#include <subroutine/subroutine.hpp>

// local headers
#include "version.hpp"

