#ifndef COMMON_UTILITY_ENUM_HPP_
#define COMMON_UTILITY_ENUM_HPP_

#include <concepts>
#include <type_traits>

#include <common/utility/format.hpp>

namespace common::utility {

template<typename Enum>
requires (std::is_enum_v<Enum>)
constexpr auto to_underlying(const Enum value) -> std::underlying_type_t<Enum> {
  return static_cast<std::underlying_type_t<Enum>>(value);
}

template<typename Enum>
requires (std::is_enum_v<Enum>)
constexpr auto from_underlying(const std::underlying_type_t<Enum> value) -> Enum {
  return static_cast<Enum>(value);
}

} // namespace common::utility

#endif // COMMON_UTILITY_ENUM_HPP_
