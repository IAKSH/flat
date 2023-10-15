#pragma once

#include <format>
#include <concepts>
#include <stdexcept>
#include <glad/glad.h>

#ifdef _MSC_VER
#pragma deprecated(Framebuffer)
#endif

namespace quick3d::gl
{
    // this Framebuffer use Texture from outside
    // it won't manage the Texture
    class Framebuffer
    {
    private:
        GLuint fbo_id;
        GLuint rbo_id;
        GLuint tex_id;
        
        void create_fbo_and_rbo(GLint width,GLint height) noexcept;
        void delete_fbo_and_rbo() noexcept;
    
    public:
        Framebuffer(GLint width, GLint height) noexcept(false);
        Framebuffer(GLenum texture_type, GLuint tex_id, GLint width, GLint height) noexcept(false);

        template <typename T>
        requires requires(T t)
        {
            {t.get_tex_id()} -> std::same_as<GLuint>;
            {t.get_tex_width()} -> std::same_as<GLint>;
            {t.get_tex_height()} -> std::same_as<GLint>;
            {t.get_tex_format()} -> std::same_as<GLenum>;
        }
        Framebuffer(const T& t) noexcept(false)
            : tex_id(t.get_tex_id())
        {
            create_fbo_and_rbo(t.get_tex_width(),t.get_tex_height());
            bind_texture_to_fbo(t.get_tex_format(), tex_id);
            if(!(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE))
                throw std::runtime_error(std::format("fbo {} incomplete",fbo_id));
        }

        Framebuffer(Framebuffer&) = delete;

        ~Framebuffer() noexcept;

        GLint get_width() const noexcept;
        GLint get_height() const noexcept;
        GLuint get_fbo_id() const noexcept;
        GLuint get_binding_tex_id() const noexcept;

        void bind_texture_to_fbo(GLenum texture_type, GLuint id) noexcept;
    };
}