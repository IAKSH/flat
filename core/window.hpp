#pragma once

#include "event.hpp"
#include "template.hpp"
#include <string>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ni::core
{
    template <typename Diverse>
    struct Window : public DisableCopy
    {
        void update() {static_cast<Diverse*>(this)->imp_update();}
        void onEvent(Event& e) {static_cast<Diverse*>(this)->imp_onEvent(e);}
        void setPositionX(const int& x) {static_cast<Diverse*>(this)->imp_setPositionX(x);}
        void setPositionY(const int& y) {static_cast<Diverse*>(this)->imp_setPositionY(y);}
        void setHeight(const int& h) {static_cast<Diverse*>(this)->imp_setHeight(h);}
        void setWidth(const int& w) {static_cast<Diverse*>(this)->imp_setWidth(w);}
        void setTitle(std::string_view title) {static_cast<Diverse*>(this)->imp_setTitle(title);}
        void setEventCallbackFunc(const std::function<void(Event&)>& func) {static_cast<Diverse*>(this)->imp_setEventCallbackFunc(func);}
        int getPositionX() {return static_cast<Diverse*>(this)->imp_getPositionX();}
        int getPositionY() {return static_cast<Diverse*>(this)->imp_getPositionY();}
        int getHeight() {return static_cast<Diverse*>(this)->imp_getHeight();}
        int getWidth() {return static_cast<Diverse*>(this)->imp_getWidth();}
        std::string_view getName() {return static_cast<Diverse*>(this)->imp_getName();}
    };
}