#pragma once

#include <string_view>
#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/camera.hpp>
#include <fine_light/object.hpp>

namespace quick3d::test::fine_light
{
    class Skybox : public Object
    {
    private:
        inline static std::shared_ptr<gl::VBO> vbo;
        inline static std::shared_ptr<gl::VAO> vao;
        inline static std::shared_ptr<gl::Program> program;
        inline static std::shared_ptr<gl::CubeMap> cubemap;

        void try_load_program(std::string_view vs,std::string_view fs) noexcept(false);
        void try_load_cubemap(std::string_view folder,
            const std::array<std::string_view, 6>& names,GLenum format,uint32_t w,uint32_t h) noexcept(false);
        void try_setup_vao() noexcept;

        void on_create() noexcept(false);
        void on_destroy() noexcept(false);

    public:
        Skybox() noexcept(false);
        Skybox(Skybox&) = delete;
        ~Skybox() noexcept(false);

        void on_tick(double delta_time) noexcept(false);
        void on_draw(const gl::FPSCamera& camera) noexcept(false);

        void on_load() noexcept(false);
        void on_unload() noexcept(false);
    };
}