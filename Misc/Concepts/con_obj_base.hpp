#pragma once

#include "con_physics.hpp"
#include "con_audio.hpp"

namespace flat::misc::concepts
{
    template <typename T>
    concept Object = requires(T t)
    {
        requires(PhysicsModel<T>);
        {t.get_obj_id()} -> std::same_as<unsigned long long>;
    };
}