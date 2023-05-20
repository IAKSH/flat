#pragma once

#include "obj_base.hpp"
#include "../physics.hpp"

namespace flat::objects
{
    class Drawable
    {
    private:
        Object<flat::Square> object;
    
    public:
        Drawable();
        ~Drawable();
        void flush_to_screen() const;
    };
};