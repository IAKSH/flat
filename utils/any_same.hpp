#pragma once

#include <concepts>

namespace ni::utils
{
    template <typename T, typename... Args> constexpr bool any_same()
    {
        if constexpr (sizeof...(Args) == 0)
            return false;
        else
            return (std::same_as<std::remove_reference_t<T>, Args> || ...) || any_same<Args...>();
    }
}