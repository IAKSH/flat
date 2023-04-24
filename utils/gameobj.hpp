#pragma once

#include "physics.hpp"
#include "../core/event.hpp"

namespace ni::utils
{
    class GameObject : public Point
    {
    public:
        virtual void onAttach() = 0;
        virtual void onDetach() = 0;
        virtual void onUpdate() = 0;
        virtual void onRender() = 0;
        virtual void onEvent(ni::core::Event& e) = 0;
    };
}