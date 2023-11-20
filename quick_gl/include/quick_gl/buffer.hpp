#pragma once

#include <format>
#include <memory>
#include <cstdint>
#include <cstring>
#include <concepts>
#include <stdexcept>
#include <functional>
#include <glad/gles2.h>

namespace quick3d::gl
{
    class Buffer
    {
    private:
        GLuint buffer_id;
        GLenum buffer_target;
        GLenum buffer_usage;

        bool verifiy_target(GLenum target) const noexcept;
        bool verifiy_usage(GLenum usage) const noexcept;

        void gen_buffer_id() noexcept;
        void pre_allocate_mem(GLsizeiptr size) noexcept;
        void delete_buffer() noexcept;

    public:
        Buffer(GLenum target, GLenum usage, GLsizeiptr size) noexcept(false);
        Buffer(Buffer& src, GLsizeiptr new_size = 0) noexcept;
        ~Buffer() noexcept;

        GLuint get_buffer_id() const noexcept;
        GLsizeiptr get_buffer_size() const noexcept;
        GLenum get_buffer_target() const noexcept;
        GLenum get_buffer_usage() const noexcept;
        void set_buffer_target(GLenum new_target) noexcept(false);

        // this will not check if out of range
        void write_buffer_data(const void* data, GLintptr offset, GLsizeiptr size) noexcept;
        // this will not check if out of range
        void dma_do(std::function<void(void* data)> callback, GLintptr offset, GLsizeiptr length, GLbitfield access) noexcept;
        void dma_do(std::function<void(void* data)> callback) noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.size()} -> std::same_as<std::size_t>;
            {t.data()} -> std::convertible_to<void*>;
        }
        void write_buffer_data(const T& t, std::size_t size = 0) noexcept
        {
            if (size)
                write_buffer_data(t.data(), 0, size);
            else
                write_buffer_data(t.data(), 0, t.size() * sizeof(float));
        }
    };
}