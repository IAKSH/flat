#pragma once

#include "../../misc/disable_copy.hpp"
#include "../physics.hpp"
#include <array>

namespace flat::openal
{
    class Listener
    {
    public:
        Listener();
        ~Listener();

        // TODO:
        void update_listener();
    };
}