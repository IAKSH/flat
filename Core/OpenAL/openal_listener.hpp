#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../physics.hpp"
#include <array>

namespace flat::openal
{
    class Listener : public flat::Rotatable, public flat::Velocitor, misc::DisableCopy
    {
    public:
        Listener();
        ~Listener();

        // TODO:
        void update();
    };
}