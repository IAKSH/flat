#pragma once

#include <array>
#include <format>
#include <stdexcept>
#include <string_view>
#include <glad/glad.h>
#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/frame.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/cubemap.hpp>

namespace quick3d::gl
{
	// this is a "factory class"(not really) that gen texture by off-screen rendering
	// this will offer better quality texture, and automaticly convert format
    class TextureRenderer
    {
    private:
        std::unique_ptr<Program> program;
        std::unique_ptr<VAO> vao;
        std::unique_ptr<VBO> vbo;
        std::unique_ptr<EBO> ebo;
        std::unique_ptr<Framebuffer> fbo;
        GLint width, height;

        void setup_program() noexcept(false);
        void setup_vao() noexcept;
        void setup_fbo_without_texture() noexcept(false);

    public:
        TextureRenderer(GLint w, GLint h) noexcept(false);
        TextureRenderer(TextureRenderer&) = delete;
        ~TextureRenderer() = default;

        void draw_to_texture(const Texture& output_texture, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false);
        void draw_to_texture(GLuint output_texture_id, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false);

        template <typename T>
        requires requires(T t)
        {
            { t.get_img_data() } -> std::convertible_to<const void*>;
            { t.get_img_channels() } -> std::same_as<int>;
            { t.get_img_width() } -> std::same_as<int>;
            { t.get_img_height() } -> std::same_as<int>;
        }
        void draw_to_texture(const Texture& output_texture, const T& t) noexcept(false)
        {
            draw_to_texture(output_texture.get_tex_id(), t.get_img_data(), t.get_img_channels(), t.get_img_width(), t.get_img_height());
        }

        void draw_to_cubemap(const CubeMap& output_cubemap, GLenum location,
            unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false);
        void draw_to_cubemap(GLuint output_cubemap_id, GLenum location,
            unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false);

        template <typename T>
            requires requires(T t)
        {
            { t.get_img_data() } -> std::convertible_to<const void*>;
            { t.get_img_channels() } -> std::same_as<int>;
            { t.get_img_width() } -> std::same_as<int>;
            { t.get_img_height() } -> std::same_as<int>;
        }
        void draw_to_cubemap(const CubeMap& output_cubemap, GLenum location, const T& t) noexcept(false)
        {
            draw_to_cubemap(output_cubemap.get_cubemap_id(), location, t.get_img_data(), t.get_img_channels(), t.get_img_width(), t.get_img_height());
        }
    };
}