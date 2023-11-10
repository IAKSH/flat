#pragma once

#include <format>
#include <concepts>
#include <stdexcept>
#include <glad/glad.h>

namespace quick3d::gl
{
    // this FrameBuffer use Texture from outside
    // it won't manage the Texture
    class Framebuffer
    {
    protected:
        GLuint fbo_id;
        void create_fbo() noexcept;
        void delete_fbo() noexcept;
        
    public:
        Framebuffer() noexcept;
        Framebuffer(Framebuffer&) = delete;
        ~Framebuffer() noexcept;
        GLint get_width() const noexcept;
        GLint get_height() const noexcept;
        GLuint get_fbo_id() const noexcept;
    };

    class ColorFramebuffer : public Framebuffer
    {
    private:
        GLuint rbo_id;
        GLuint tex_id;
        void setup_rbo(GLint width, GLint height) noexcept;
        void delete_rbo() noexcept;

    public:
        ColorFramebuffer(GLint width, GLint height) noexcept(false);
        ColorFramebuffer(GLuint tex_id, GLint width, GLint height) noexcept(false);
        ColorFramebuffer(ColorFramebuffer&) = delete;
        ~ColorFramebuffer() noexcept;

        void set_draw_targets(const std::initializer_list<GLenum>& targets) noexcept;
        void bind_texture_to_fbo(GLuint id) noexcept;
        void bind_texture_to_fbo(GLenum target, GLuint id) noexcept;
        GLuint get_binding_tex_id() const noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_tex_id()} -> std::same_as<GLuint>;
            {t.get_tex_width()} -> std::same_as<GLint>;
            {t.get_tex_height()} -> std::same_as<GLint>;
            {t.get_tex_format()} -> std::same_as<GLenum>;
        }
        ColorFramebuffer(const T& t) noexcept(false)
            : tex_id(t.get_tex_id())
        {
            setup_rbo(t.get_tex_width(), t.get_tex_height());
            bind_texture_to_fbo(tex_id);
            //if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE))
            //    throw std::runtime_error(std::format("fbo {} incomplete", fbo_id));
        }
    };

    class DepthFramebuffer : public Framebuffer
    {
    private:
        void bind_depth_attachment(GLuint depth_attachment_id) noexcept;

    public:
        DepthFramebuffer(GLuint depth_attachment_id) noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_cubemap_id()} -> std::same_as<GLuint>;
        }
        DepthFramebuffer(const T& t) noexcept
        {
            bind_depth_attachment(t.get_cubemap_id());
        }

        DepthFramebuffer(DepthFramebuffer&) = delete;
        ~DepthFramebuffer() = default;
    };
}