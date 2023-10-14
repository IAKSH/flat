#pragma once

#include <quick_gl/shader.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/model.hpp>
#include <fine_light/object.hpp>

namespace quick3d::test::fine_light
{
    class LightBall : public Object
    {
    private:
        inline static std::shared_ptr<gl::Model> model;
        inline static std::shared_ptr<gl::Program> program;

        glm::vec3 light_color;
        glm::vec3 position;
        glm::vec3 move_direction;

        void try_load_program(std::string_view vs,std::string_view fs) noexcept(false);
        void try_load_model(std::string_view path) noexcept(false);

        void on_create() noexcept(false);
        void on_destroy() noexcept(false);

    public:
        LightBall() noexcept(false);
        LightBall(LightBall&) = delete;
        ~LightBall() noexcept(false);

        void on_tick(double delta_time) noexcept(false);
        void on_draw(const gl::FPSCamera& camera) noexcept(false);

        void on_load() noexcept(false);
        void on_unload() noexcept(false);

        glm::vec3 get_light_color() const noexcept;
        glm::vec3 get_position() const noexcept;
    };
}