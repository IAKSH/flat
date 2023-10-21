#pragma once

#include <chrono>

namespace quick3d::ecs
{
    class Entity
    {
    protected:
        virtual void on_create() noexcept(false) = 0;
        virtual void on_destroy() noexcept(false) = 0;

    public:
        virtual void on_attach() noexcept(false) = 0;
        virtual void on_disattach() noexcept(false) = 0;
        virtual void on_tick(float delta_ms) noexcept(false) = 0;
    };

    class Component : public Entity
    {
    };

    class System : public Entity
    {
    private:
        bool running;

    protected:
        void system_stop() noexcept;
        void system_run() noexcept;

    public:
        bool is_running() noexcept;
    };

    class Action
    {
    public:
        virtual void execute(Entity* entity) noexcept(false) = 0;
    };
}