#pragma once

#include "../../misc/disable_copy.hpp"
#include "concepts.hpp"

namespace flat
{
    class Event
    {
    protected:
        Event() = default;
    public:
        virtual ~Event() = default;
    };

    class KeyButtomEvent : public Event
    {
    private:
        KeyButtonCode code;
        KeyButtonStatus status;

    public:
        KeyButtomEvent(KeyButtonCode code,KeyButtonStatus status) : code(code),status(status) {}
        virtual ~KeyButtomEvent() override = default;

        auto get_event_typemark() const {return CoreEventTypeMark::KeyButton;}
        auto get_key_button_code() const {return code;}
        auto get_key_button_status() const {return status;}
    };

    class MouseButtonEvent : public Event
    {
    private:
        MouseButtonCode code;
        MouseButtonStatus status;

    public:
        MouseButtonEvent(MouseButtonCode code,MouseButtonStatus status) : code(code),status(status) {}
        virtual ~MouseButtonEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::MouseButton;}
        auto get_mouse_button_code() const {return code;}
        auto get_mouse_button_status() const {return status;}
    };

    class MouseMoveEvent : public Event
    {
    private:
        double x;
        double y;

    public:
        MouseMoveEvent(double x,double y) : x(x),y(y) {}
        virtual ~MouseMoveEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::MouseMove;}
        auto get_mouse_movement() const {return std::array<double,2>{x,y};}
        auto get_mouse_movement_x() const {return x;}
        auto get_mouse_movement_y() const {return y;}
    };

    class MouseScrollEvent : public Event
    {
    private:
        double x;
        double y;

    public:
        MouseScrollEvent(double x,double y) : x(x),y(y) {}
        virtual ~MouseScrollEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::MouseScroll;}
        auto get_mouse_scroll() const {return std::array<double,2>{x,y};}
        auto get_mouse_scroll_x() const {return x;}
        auto get_mouse_scroll_y() const {return y;}
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;
        virtual ~WindowCloseEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::WindowClose;}
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent() = default;
        virtual ~WindowResizeEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::WindowResize;}
    };

    class WindowMoveEvent : public Event
    {
    public:
        WindowMoveEvent() = default;
        virtual ~WindowMoveEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::WindowMove;}
    };

    class WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() = default;
        virtual ~WindowFocusEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::WindowFocus;}
    };

    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() = default;
        virtual ~WindowLostFocusEvent() override = default;
        auto get_event_typemark() const {return CoreEventTypeMark::WindowLostFocus;}
    };

    static_assert(WithEventTypeMark<KeyButtomEvent> && WithKeyButtonCode<KeyButtomEvent> && WithKeyStatus<KeyButtomEvent>);
    static_assert(WithEventTypeMark<MouseButtonEvent> && WithMouseButtonCode<MouseButtonEvent> && WithMouseButtonStatus<MouseButtonEvent>);
    static_assert(WithEventTypeMark<MouseMoveEvent> && WithMouseMoveInfo<MouseMoveEvent>);
    static_assert(WithEventTypeMark<MouseScrollEvent> && WithMouseScrollInfo<MouseScrollEvent>);
    static_assert(WithEventTypeMark<WindowCloseEvent>);
    static_assert(WithEventTypeMark<WindowResizeEvent>);
    static_assert(WithEventTypeMark<WindowMoveEvent>);
    static_assert(WithEventTypeMark<WindowFocusEvent>);
    static_assert(WithEventTypeMark<WindowLostFocusEvent>);
}