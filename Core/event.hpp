#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/keycode.hpp"
#include "../../Misc/rtti.hpp"

namespace flat
{
    // base event
    struct Event : misc::DisableCopy
    {
        virtual ~Event() = default;
    };

    // keyboard event
    struct KeyboardEvent : public Event
    {
    private:
        misc::KeyCode keycode;
    protected:
        void set_keycode(misc::KeyCode code) {keycode = code;}
    public:
        virtual ~KeyboardEvent() override = default;
        misc::KeyCode get_keycode() const {return keycode;}
    };

    struct KeyPressEvent : KeyboardEvent
    {
        KeyPressEvent(misc::KeyCode keycode) {set_keycode(keycode);}
        virtual ~KeyPressEvent() override = default;
    };

    struct KeyReleaseEvent : public KeyboardEvent
    {
        KeyReleaseEvent(misc::KeyCode keycode) {set_keycode(keycode);}
        virtual ~KeyReleaseEvent() override = default;
    };

    // mouse event
    struct MouseEvent : public Event
    {
        virtual ~MouseEvent() override = default;
    };

    struct MouseButtonEvent : public MouseEvent
    {
        virtual ~MouseButtonEvent() override = default;
    };

    struct MousePressEvent : public MouseButtonEvent
    {
        virtual ~MousePressEvent() override = default;
    };

    struct MouseReleaseEvent : public MouseButtonEvent
    {
        virtual ~MouseReleaseEvent() override = default;
    };

    struct MouseLeftPressEvent : public MousePressEvent
    {
        virtual ~MouseLeftPressEvent () override = default;
    };

    struct MouseLeftReleaseEvent : public MouseReleaseEvent
    {
        virtual ~MouseLeftReleaseEvent() override = default;
    };

    struct MouseRightPressEvent : public MousePressEvent
    {
        virtual ~MouseRightPressEvent () override = default;
    };

    struct MouseRightReleaseEvent : public MouseReleaseEvent
    {
        virtual ~MouseRightReleaseEvent() override = default;
    };

    struct MouseMiddlePressEvent : public MousePressEvent
    {
        virtual ~MouseMiddlePressEvent () override = default;
    };

    struct MouseMiddleReleaseEvent : public MouseReleaseEvent
    {
        virtual ~MouseMiddleReleaseEvent() override = default;
    };

    struct MouseMoveEvent : public MouseEvent
    {
    private:
        int position_x,position_y;
    public:
        MouseMoveEvent(int x,int y)
            : position_x(x),position_y(y)
        {}

        virtual ~MouseMoveEvent() override = default;
        int get_position_x() const {return position_x;}
        int get_position_y() const {return position_y;}
    };

    class MouseScrollEvent : public MouseEvent
    {
    private:
        int scroll_x,scroll_y;
    public:
        MouseScrollEvent(int x,int y)
            : scroll_x(x),scroll_y(y)
        {}

        virtual ~MouseScrollEvent() override = default;
        int get_scroll_x() const {return scroll_x;}
        int get_scroll_y() const {return scroll_y;}
    };

    // window event
    struct WindowEvent : public Event
    {
        virtual ~WindowEvent() override = default;
    };

    struct WindowCloseEvent : public WindowEvent
    {
        virtual ~WindowCloseEvent() override = default;
    };

    struct WindowFocusEvent : public WindowEvent
    {
        virtual ~WindowFocusEvent() override = default;
    };

    struct WindowLostFocusEvent : public WindowEvent
    {
        virtual ~WindowLostFocusEvent() override = default;
    };

    struct WindowResizeEvent : public WindowEvent
    {
        virtual ~WindowResizeEvent() override = default;
    };

    struct WindowMoveEvent : public WindowEvent
    {
        virtual ~WindowMoveEvent() override = default;
    };
}