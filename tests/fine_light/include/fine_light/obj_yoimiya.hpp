#pragma once

#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/model.hpp>
#include <fine_light/object.hpp>
#include <fine_light/obj_light_ball.hpp>

namespace quick3d::test::fine_light
{
    class Yoimiya : public Object
    {
    private:
        inline static std::shared_ptr<gl::Program> program;
        inline static std::shared_ptr<gl::Model> model;
        inline static std::vector<LightBall*> light_balls;

        glm::vec3 position;
        glm::mat4 rotate;

        void try_load_program(std::string_view vs,std::string_view fs) noexcept(false);
        void try_load_model(std::string_view path) noexcept(false);

        void on_create() noexcept(false);
        void on_destroy() noexcept(false);

    public:
        Yoimiya() noexcept(false);
        Yoimiya(Yoimiya&) = delete;
        ~Yoimiya() noexcept(false);

        void on_tick(double delta_time) noexcept(false);
        void on_draw(const gl::FPSCamera& camera) noexcept(false);

        void on_load() noexcept(false);
        void on_unload() noexcept(false);

        static void add_light_ball(LightBall* light_ball) noexcept;
    };
}