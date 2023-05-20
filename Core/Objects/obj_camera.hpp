#pragma once

#include "obj_base.hpp"

namespace flat::objects
{
    class Camera
    {
    private:
        Object<flat::Ball> obj;

    public:
        Camera();
        ~Camera();
    };
};