#pragma once

#include "event.hpp"

namespace ni::core
{
    class MouseButtonEvent : public Event
    {
    private:
        int buttonCode;

    protected:
        void setButtonCode(const int& code) { buttonCode = code; }

    public:
        virtual ~MouseButtonEvent() override = default;
    };

    class MousePressEvent : public MouseButtonEvent
    {
    public:
        MousePressEvent(const int& code)
        {
            setType(EventType::MousePress);
            setButtonCode(code);
        }
        virtual ~MousePressEvent() override = default;
    };

    class MouseReleaseEvent : public MouseButtonEvent
    {
    public:
        MouseReleaseEvent(const int& code)
        {
            setType(EventType::MouseRelease);
            setButtonCode(code);
        }
       virtual ~MouseReleaseEvent() override = default;
    };

    class MousePositionEvent : public Event
    {
    private:
        int x,y;

    protected:
        void setX(const int& x) { this->x = x; }
        void setY(const int& y) { this->y = y; }

    public:
        virtual ~MousePositionEvent() override = default;
        const int& getX() const { return x; } 
        const int& getY() const { return y; } 
    };

    class MouseScrollEvent : public MousePositionEvent
    {
    public:
        MouseScrollEvent(const int& dx,const int& dy)
        {
            setType(EventType::MouseScroll);
            setX(dx);
            setY(dy);
        }
        virtual ~MouseScrollEvent() override = default;
    };

    class MouseMoveEvent : public MousePositionEvent
    {
    public:
        MouseMoveEvent(const int& x,const int& y)
        {
            setType(EventType::MouseMove);
            setX(x);
            setY(y);
        }
        virtual ~MouseMoveEvent() override = default;
    };
}