#pragma once

#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/camera.hpp>
#include <fine_light/object.hpp>

namespace quick3d::test::fine_light
{
    class Container : public Object
    {
    private:
        inline static std::shared_ptr<gl::VBO> vbo;
        inline static std::shared_ptr<gl::VAO> vao;
        inline static std::shared_ptr<gl::Texture> texture_diffuse;
        inline static std::shared_ptr<gl::Texture> texture_specular;
        inline static std::shared_ptr<gl::Program> program;

        glm::vec3 position;
        glm::vec3 rotate_axis;
        float rotate_speed;

        void try_load_program(std::string_view vs,std::string_view fs) noexcept(false);
        void try_load_texture(std::string_view diffuse_tex_folder,std::string_view specular_tex_folder,GLenum color_format) noexcept(false);
        void try_setup_vao() noexcept;

    public:
        Container(std::string_view vs,std::string_view fs,
            std::string_view diffuse_tex_folder,std::string_view specular_tex_folder,GLenum color_format) noexcept(false);

        Container(Container&) = delete;
        ~Container() = default;

        void on_tick(double delta_time) noexcept(false);
        void on_draw(const gl::FPSCamera& camera) noexcept(false);
        void on_create() noexcept(false);
        void on_destroy() noexcept(false);
        void on_load() noexcept(false);
        void on_unload() noexcept(false);
    };
}