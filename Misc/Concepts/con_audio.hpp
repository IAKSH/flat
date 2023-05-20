#pragma once

#include "con_physics.hpp"

namespace flat::misc::concepts
{
    template <typename T>
    concept Listener2D = requires(T t)
    {
        requires(Velocitor2D<T>);
        requires(Rotator2D<T>);
    };

    template <typename T>
    concept Listener3D = requires(T t)
    {
        requires(Velocitor3D<T>);
        requires(Rotator3D<T>);
    };
}