#pragma once

#include "physics.hpp"
#include "../core/event.hpp"

namespace ni::utils
{
    class [[deprecated("abandoned after the commit 0ca8f18")]] GameObject : public Point
    {
    public:
        virtual void onAttach() = 0;
        virtual void onDetach() = 0;
        virtual void onUpdate() = 0;
        virtual void onRender() = 0;
        virtual void onEvent(ni::core::Event& e) = 0;
    };
}