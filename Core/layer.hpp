#pragma once

#include "event.hpp"
#include "../../misc/disable_copy.hpp"
#include <functional>
#include <string>

namespace flat
{
    class Layer : misc::DisableCopy
    {
    private:
        std::string layer_name;
        std::function<void()> callback_attach;
        std::function<void()> callback_detach;
        std::function<void()> callback_update;
        std::function<void()> callback_render;
        std::function<void(const Event& event)> callback_on_event;

    public:
        Layer(std::string_view name) : layer_name(name) {}
        Layer() : layer_name("Unnamed Layer") {}
        ~Layer() = default;

        std::string_view get_name() {return layer_name;}
        void on_attach() {if(callback_attach) callback_attach();}
        void on_detach() {if(callback_detach) callback_detach();}
        void on_update() {if(callback_update) callback_update();}
        void on_render() {if(callback_render) callback_render();}
        void on_event(const Event& event) {if(callback_on_event) callback_on_event(event);}
        void set_attach_func(std::function<void()> func) {callback_attach = func;}
        void set_detach_func(std::function<void()> func) {callback_detach = func;}
        void set_update_func(std::function<void()> func) {callback_update = func;}
        void set_render_func(std::function<void()> func) {callback_render = func;}
        void set_event_func(std::function<void(const Event&)> func) {callback_on_event = func;}
    };
}