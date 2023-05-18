#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../physics.hpp"
#include <array>

namespace flat::openal
{
    class Listener : virtual public flat::Rotatable, virtual public flat::Velocitor, misc::DisableCopy
    {
    public:
        Listener();
        ~Listener();

        // TODO:
        void update_listener();
    };
}