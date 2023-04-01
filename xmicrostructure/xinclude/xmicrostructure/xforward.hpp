#pragma once

#include "xversion.hpp"

#define X_MICROSTRUCTURE_NAMESPACE_BEGIN namespace xmicrostructure {
#define X_MICROSTRUCTURE_NAMESPACE_END   } // namespace xmicrostructure

X_MICROSTRUCTURE_NAMESPACE_BEGIN X_MICROSTRUCTURE_NAMESPACE_END

#include <cassert>
#include <cmath>
#include <cstddef>

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <concepts>
#include <ranges>
#include <span>

// #include <format>
#ifndef X_MICROSTRUCTURE_FMTLIB
	#define X_MICROSTRUCTURE_FMTLIB 1
#endif

#if X_MICROSTRUCTURE_FMTLIB > 0
	#include <fmt/format.h>
	#include <fmt/os.h>
#endif

#ifndef X_MICROSTRUCTURE_GNUPLOT
	#define X_MICROSTRUCTURE_GNUPLOT 1
#endif

#ifndef X_MICROSTRUCTURE_XELATEX
	#define X_MICROSTRUCTURE_XELATEX 1
#endif

#include "../../xutilities/xformatter/xformatter.hpp"

#include "../../xlib/xlearner/xlearner.hpp"
#include "../../xlib/xsolver/xsolver.hpp"

#include "xcore.hpp"
#include "xsimulation.hpp"
#include "xvisualisation.hpp"