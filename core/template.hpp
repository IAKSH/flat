#pragma once

#include <concepts>
#include <type_traits>

namespace ni::core
{
    template <typename T,typename U>
    constexpr bool isSame()
    {
        using Type = std::remove_cvref_t<T>;
        return std::is_same<Type,U>();
    }

    template <typename T, typename... Args>
    constexpr bool anySame()
    {
        if constexpr (sizeof...(Args) == 0)
            return false;
        else
            return (std::same_as<std::remove_reference_t<T>, Args> || ...) || anySame<Args...>();
    }

    struct DisableCopy
    {
        DisableCopy() = default;
        DisableCopy(DisableCopy&) = delete;
        ~DisableCopy() = default;
    };
}