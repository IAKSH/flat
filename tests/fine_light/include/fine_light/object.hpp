#pragma once

#include <quick_gl/camera.hpp>

namespace quick3d::test::fine_light
{
    // 古典object的尝试
    // 实际引擎应该使用ECS架构

    struct Object
    {
        virtual void on_tick(double delta_time) noexcept(false) = 0;
        virtual void on_draw(const gl::FPSCamera& camera) noexcept(false) = 0;
        virtual void on_create() noexcept(false) = 0;
        virtual void on_destroy() noexcept(false) = 0;
        virtual void on_load() noexcept(false) = 0;
        virtual void on_unload() noexcept(false) = 0;
    };
}