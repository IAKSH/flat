#pragma once

#include <string_view>
#include <quick_ecs/ecs.hpp>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>

namespace quick3d::ecs
{
    class GfxSystem : public System
    {
    private:
        gl::Context context;
        gl::FPSCamera camera;

        virtual void on_create() noexcept(false) override final;
        virtual void on_destroy() noexcept(false) override final;

        void bind_camera_to_context() noexcept;

    public:
        GfxSystem(int w,int h,std::string_view title = "Quick3D") noexcept;
        GfxSystem(GfxSystem&) = delete;
        ~GfxSystem() noexcept;

        virtual void on_attach() noexcept(false) override final;
        virtual void on_disattach() noexcept(false) override final;
        virtual void on_tick(float delta_ms) noexcept(false) override final;

        gl::FPSCamera& get_camera() noexcept;
        void capture_mouse() noexcept;
    };
}