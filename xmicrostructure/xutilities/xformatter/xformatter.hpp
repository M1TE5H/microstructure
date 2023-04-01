#pragma once

#include <iostream>

namespace xmicrostructure {

#ifdef X_MICROSTRUCTURE_FMTLIB

template <typename... GenericT>
using xmicrostructure_format_str = fmt::format_string<GenericT...>;

template <typename... GenericT>
auto inline print(xmicrostructure_format_str<GenericT...> fmt,
                  GenericT &&...args) {
  return fmt::print(fmt, std::forward<GenericT>(args)...);
}

template <typename... GenericT>
auto inline println(xmicrostructure_format_str<GenericT...> fmt,
                    GenericT &&...args) {
  return fmt::println(fmt, std::forward<GenericT>(args)...);
}

#else // |X_MICROSTRUCTURE_FMTLIB

template <typename... GenericT> auto inline print(GenericT &&...args) {
  std::cout << "fmtlib error\n";
}

template <typename... GenericT> auto inline println(GenericT &&...args) {
  std::cout << "fmtlib error\n";
}

#endif // !X_MICROSTRUCTURE_FMTLIB

} // namespace xmicrostructure