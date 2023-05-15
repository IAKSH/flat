#pragma once

#include <concepts>
#include <type_traits>

namespace flat::misc::ctti
{
    // Check type equality while compiling (ignore const and reference)
    template <typename T,typename U>
    constexpr bool is_same()
    {
        using Type = std::remove_cvref<T>;
        return std::is_same<Type,U>();
    }

    template <typename T,typename... Args>
    constexpr bool any_same()
    {
        if constexpr(sizeof...(Args) == 0)
            return false;
        else
            return (is_same<T,Args> || ...) || is_same<Args...>();
    }
}