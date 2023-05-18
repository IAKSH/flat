#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/keycode.hpp"
#include "../../Misc/rtti.hpp"

namespace flat
{
    enum class EventType
    {
        KeyPress,KeyRelease,MousePress,MouseRelease,MouseMove,MouseScroll,
        WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMove
    };

    // base event
    class Event : misc::DisableCopy
    {
    private:
        const EventType type;
    public:
        Event(EventType type) : type(type) {}
        virtual ~Event() = default;
        EventType get_type() const {return type;}
    };

    // keyboard event
    class KeyboardEvent : public Event
    {
    private:
        misc::KeyCode keycode;
    protected:
        void set_keycode(misc::KeyCode code) {keycode = code;}
        KeyboardEvent(EventType type) : Event(type) {}
    public:
        virtual ~KeyboardEvent() override = default;
        misc::KeyCode get_keycode() const {return keycode;}
    };

    struct KeyPressEvent : KeyboardEvent
    {
        KeyPressEvent(misc::KeyCode keycode) : KeyboardEvent(EventType::KeyPress) {set_keycode(keycode);}
        virtual ~KeyPressEvent() override = default;
    };

    struct KeyReleaseEvent : public KeyboardEvent
    {
        KeyReleaseEvent(misc::KeyCode keycode) : KeyboardEvent(EventType::KeyRelease) {set_keycode(keycode);}
        virtual ~KeyReleaseEvent() override = default;
    };

    // mouse event
    class MouseButtonEvent : public Event
    {
    private:
        int keycode;
    protected:
        MouseButtonEvent(int keycode,EventType type) : keycode(keycode),Event(type) {}
    public:
        virtual ~MouseButtonEvent() override = default;
    };

    struct MousePressEvent : public MouseButtonEvent
    {
        MousePressEvent(int keycode) : MouseButtonEvent(keycode,EventType::MousePress) {}
        virtual ~MousePressEvent () override = default;
    };

    struct MouseReleaseEvent : public MouseButtonEvent
    {
        MouseReleaseEvent(int keycode) : MouseButtonEvent(keycode,EventType::MouseRelease) {}
        virtual ~MouseReleaseEvent () override = default;
    };

    struct MouseMoveEvent : Event
    {
    private:
        int position_x,position_y;
    public:
        MouseMoveEvent(int x,int y)
            : position_x(x),position_y(y),Event(EventType::MouseMove)
        {}

        virtual ~MouseMoveEvent() override = default;
        int get_position_x() const {return position_x;}
        int get_position_y() const {return position_y;}
    };

    class MouseScrollEvent : public Event
    {
    private:
        int scroll_x,scroll_y;
    public:
        MouseScrollEvent(int x,int y)
            : scroll_x(x),scroll_y(y),Event(EventType::MouseScroll)
        {}

        virtual ~MouseScrollEvent() override = default;
        int get_scroll_x() const {return scroll_x;}
        int get_scroll_y() const {return scroll_y;}
    };

    // window event
    struct WindowCloseEvent : public Event
    {
        WindowCloseEvent() : Event(EventType::WindowClose) {}
        virtual ~WindowCloseEvent() override = default;
    };

    struct WindowFocusEvent : public Event
    {
        WindowFocusEvent() : Event(EventType::WindowFocus) {}
        virtual ~WindowFocusEvent() override = default;
    };

    struct WindowLostFocusEvent : public Event
    {
        WindowLostFocusEvent() : Event(EventType::WindowLostFocus) {}
        virtual ~WindowLostFocusEvent() override = default;
    };

    struct WindowResizeEvent : public Event
    {
        WindowResizeEvent() : Event(EventType::WindowResize) {}
        virtual ~WindowResizeEvent() override = default;
    };

    struct WindowMoveEvent : public Event
    {
        WindowMoveEvent() : Event(EventType::WindowMove) {}
        virtual ~WindowMoveEvent() override = default;
    };
}