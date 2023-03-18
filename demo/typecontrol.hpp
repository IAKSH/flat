#pragma once

#include <concepts>

namespace flat
{
    template <typename T, typename... Args> constexpr bool is_same()
    {
        if constexpr(sizeof...(Args) == 0)
            return false;
        else
            return (std::same_as<std::remove_reference_t<T>, Args> || ...) || is_same<Args...>();
    }
}