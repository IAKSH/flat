#pragma once

#include "con_audio.hpp"
#include <concepts>

namespace flat::misc::concepts
{
    template <typename T>
    concept Camera2D = requires(T t)
    {
        requires(Listener2D<T>);
    };

    template <typename T>
    concept Camera3D = requires(T t)
    {
        requires(Listener3D<T>);
    };
}