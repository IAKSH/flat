#pragma once

#include <array>
#include <vector>
#include <memory>
#include <quick_gl/window.hpp>

namespace quick3d::gl
{
    // Context类需要有一种好的全局可见方案
    // 最好不要用单例模式
    class Context
    {
    private:
        std::vector<std::unique_ptr<Window>> windows;

        void setup_context(std::string_view title,int w,int h) noexcept(false);
        void destroy_context() noexcept;

        GLuint get_binding_buffer(GLenum target) noexcept(false);
        GLuint get_binding_vao() noexcept;
        GLuint get_binding_shader() noexcept;
        GLuint get_binding_texture() noexcept;
        GLuint get_binding_cubemap() noexcept;
        GLuint get_binding_framebuffer() noexcept;

        void unbind_buffer(GLenum target) noexcept;
        void unbind_vao() noexcept;
        void unbind_shader() noexcept;
        void unbind_texture() noexcept;
        void unbind_cubemap() noexcept;
        void unbind_framebuffer() noexcept;

    public:
        Context(std::string_view title,int w,int h) noexcept(false);
        Context(Context&) = delete;
        ~Context() noexcept;

        Window& get_window(uint32_t index) noexcept(false);
        uint32_t add_new_window(std::string_view title,int w,int h) noexcept;
        void remove_window(uint32_t index) noexcept(false);

        // bind buffer (glBindBuffer)
        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_id()} -> std::same_as<GLuint>;
            {t.get_buffer_target()} -> std::same_as<GLenum>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glBindBuffer(t.get_buffer_target(), t.get_buffer_id());
        }

        // bind buffer (glBindBuffer & glBindBufferRange, for UBO/SSBO)
        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_id()} -> std::same_as<GLuint>;
            {t.get_buffer_target()} -> std::same_as<GLenum>;
        }
        void bind_to_context(const T& t,GLuint index,GLintptr offset = 0,GLsizeiptr size = 0) noexcept(false)
        {
            // you known, actually, glBindBufferRange is a variation of glBindBufferBase
            glBindBufferRange(t.get_buffer_target(), index, t.get_buffer_id(), offset, size);
        }

        // bind vao
        template <typename T>
        requires requires(T t)
        {
            {t.get_vao_id()} -> std::same_as<GLuint>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glBindVertexArray(t.get_vao_id());
        }

        // bind shader program
        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glUseProgram(t.get_program_id());
        }

        // bind texture
        template <typename T>
        requires requires(T t)
        {
            {t.get_texture_id()} -> std::same_as<GLuint>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glBindTexture(GL_TEXTURE_2D, t.get_texture_id());
        }

        // bind cubemap
        template <typename T>
        requires requires(T t)
        {
            {t.get_cubemap_id()} -> std::same_as<GLuint>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, t.get_cubemap_id());
        }

        // bind framebuffer
        template <typename T>
        requires requires(T t)
        {
            {t.get_fbo_id()} -> std::same_as<GLuint>;
        }
        void bind_to_context(const T& t) noexcept(false)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, t.get_fbo_id());
        }

        GLuint get_binding_obj_id(GLenum target) noexcept(false);
        void unbind_from_context(GLenum target) noexcept(false);

        void swap_window_buffers() noexcept;
        void poll_events() noexcept;
        void fill_frame_color(std::array<float,4> color) noexcept;
        void fill_frame_color(float r,float g,float b,float a) noexcept;
        void clean_frame_buffers() noexcept;
    };
}