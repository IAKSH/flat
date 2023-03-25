#pragma once

#include <concepts>

namespace stool
{
    template <typename T, typename... Args> constexpr bool same_type()
    {
        if constexpr(sizeof...(Args) == 0)
            return false;
        else
            return (std::same_as<std::remove_reference_t<T>, Args> || ...) || same_type<Args...>();
    }
}  // namespace stool