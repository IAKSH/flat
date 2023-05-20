#pragma once

#include "con_obj_base.hpp"
#include "con_obj_camera.hpp"

namespace flat::misc::concepts
{
    template <typename T,typename U>
    concept Drawable2D = requires(T t,const U& u)
    {
        requires(Object<T>);
        requires(Camera2D<U>);
        {t.draw()} -> std::same_as<void>;
        {t.draw(u)} -> std::same_as<void>;
    };

    template <typename T,typename U>
    concept Drawable3D = requires(T t,const U& u)
    {
        requires(Object<T>);
        requires(Camera3D<U>);
        {t.draw()} -> std::same_as<void>;
        {t.draw(u)} -> std::same_as<void>;
    };
}