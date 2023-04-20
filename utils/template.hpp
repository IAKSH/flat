#pragma once

#include <concepts>
#include <type_traits>

namespace ni::utils
{
    template <typename T,typename U>
    constexpr bool isSame()
    {
        using Type = std::remove_cvref_t<T>;
        return std::is_same_v<Type,U>;
    }

    template <typename T, typename... Args>
    constexpr bool anySame()
    {
        if constexpr (sizeof...(Args) == 0)
            return false;
        else
            return (std::same_as<std::remove_reference_t<T>, Args> || ...) || any_same<Args...>();
    }

    template <typename T>
    class __Enchased
	{
	private:
		T t;

	public:
		__Enchased(const T& t) : t(t) {}
		~__Enchased() = default;
        operator T() const { return t; }
		operator T& () { return t; }
	};
}