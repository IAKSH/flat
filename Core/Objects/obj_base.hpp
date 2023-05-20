#pragma once

#include "../physics.hpp"
#include "../../Misc/Concepts/con_physics.hpp"

namespace flat::objects
{
    inline static unsigned int object_count {0};

    template <misc::concepts::PhysicsModel Model>
    class Object
    {
    private:
        Model model;
        const unsigned int id;

    public:
        Object()
            : id(++object_count)
        {
        }

        unsigned int get_obj_id() const
        {
            return id;
        }
    };
}