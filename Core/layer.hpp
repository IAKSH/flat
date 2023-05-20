#pragma once

#include "event.hpp"
#include "../../misc/disable_copy.hpp"
#include <string>

namespace flat
{
    class Layer : misc::DisableCopy
    {
    private:
        std::string layer_name;

    public:
        Layer(std::string_view name = "Unnamed Layer")
            : layer_name(name)
        {}

        ~Layer() = default;

        std::string_view get_name() {return layer_name;}
        virtual void on_attach() = 0;
        virtual void on_detach() = 0;
        virtual void on_update() = 0;
        virtual void on_render() = 0;
        virtual void on_event(const Event& event) = 0;
    };
}