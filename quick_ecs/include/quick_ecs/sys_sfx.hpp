#pragma once

#include <string_view>
#include <quick_ecs/ecs.hpp>
#include <quick_al/context.hpp>

namespace quick3d::ecs
{
    class SfxSystem : public System
    {
    private:
        al::Device device;
        al::Context context;

        virtual void on_create() noexcept(false) override final;
        virtual void on_destroy() noexcept(false) override final;

    public:
        SfxSystem() noexcept;
        SfxSystem(std::string_view device_name) noexcept;
        SfxSystem(SfxSystem&) = delete;
        ~SfxSystem() noexcept;

        virtual void on_attach() noexcept(false) override final;
        virtual void on_disattach() noexcept(false) override final;
        virtual void on_tick(float delta_ms) noexcept(false) override final;
    };
}