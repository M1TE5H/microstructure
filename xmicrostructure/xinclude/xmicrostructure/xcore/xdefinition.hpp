#pragma once

// Arithmetic Quantities
template<typename GenericT>
concept arithmetical = requires ( GenericT v ) {
    { std::is_arithmetic_v<GenericT> };
};

// Tensor-Like Quantities
template<typename GenericT>
concept measurable = requires ( GenericT l, GenericT r ) {
 { l + r } -> std::same_as<GenericT>; // summation (overload +)
 { l - r } -> std::same_as<GenericT>; // subtraction (overload -)
 // other constraints here ...
};