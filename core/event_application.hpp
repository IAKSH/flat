#pragma once

#include "event.hpp"

namespace ni::core
{
    class AppShutdownEvent : public Event
    {
    public:
        AppShutdownEvent()
        {
            setType(EventType::AppShutdown);
        }
        virtual ~AppShutdownEvent() override = default;
    };

    // abandoned
    class AppStartupEvent : public Event
    {
    public:
        AppStartupEvent()
        {
            setType(EventType::AppStartup);
        }
        virtual ~AppStartupEvent() override = default;
    };
}