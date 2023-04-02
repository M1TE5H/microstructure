#pragma once

#include "xdefinition.hpp"
namespace xmicrostructure {

    enum class interlace {
        lattice,
        tessellation
    };

    template<interlace I>
    class mesh {};

} // namespace xmicrostructure