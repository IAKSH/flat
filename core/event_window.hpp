#pragma once

#include <string>
#include <string_view>

#include "event.hpp"

namespace ni::core
{
    class WindowEvent : public Event
    {
    private:
        std::string_view windowName;

    protected:
        void setWindowName(std::string_view name) { windowName = name; }

    public:
        virtual ~WindowEvent() override = default;
    };

    class WindowCloseEvent : public WindowEvent
    {
    public:
        WindowCloseEvent(std::string_view name)
        {
            setType(EventType::WindowClose);
            setWindowName(name);
        }
        virtual ~WindowCloseEvent() override = default;
    };

    class WindowFocusEvent : public WindowEvent
    {
    public:
        WindowFocusEvent(std::string_view name)
        {
            setType(EventType::WindowFocus);
            setWindowName(name);
        }
        virtual ~WindowFocusEvent() override = default;
    };

    class WindowLostFocusEvent : public WindowEvent
    {
    public:
        WindowLostFocusEvent(std::string_view name)
        {
            setType(EventType::WindowLostFocus);
            setWindowName(name);
        }
        virtual ~WindowLostFocusEvent() override = default;
    };

    class WindowResizeEvent : public WindowEvent
    {
    public:
        WindowResizeEvent(std::string_view name)
        {
            setType(EventType::WindowResize);
            setWindowName(name);
        }
        virtual ~WindowResizeEvent() override = default;
    };

    class WindowMoveEvent : public WindowEvent
    {
    public:
        WindowMoveEvent(std::string_view name)
        {
            setType(EventType::WindowMove);
            setWindowName(name);
        }
        virtual ~WindowMoveEvent() override = default;
    };
}