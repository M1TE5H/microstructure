#pragma once

namespace xmicrostructure {

	// PATTERN
	template<typename ArithmeticT> inline constexpr ArithmeticT elastic_stiffness_maximum_v = 0;
    template<std::floating_point FloatT> inline constexpr FloatT elastic_stiffness_maximum_v<FloatT> = 0;
    inline constexpr float elastic_stiffness_maximum = elastic_stiffness_maximum_v<float>;

} // namespace xmicrostructure