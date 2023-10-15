#pragma once

#include <format>
#include <memory>
#include <cstdint>
#include <cstring>
#include <concepts>
#include <stdexcept>
#include <functional>
#include <glad/glad.h>

#include <iostream>

namespace quick3d::gl
{
    // [√] VBO,EBO
    // [ ] UBO,SSBO,TBO
    // [√] 从OpenGL 3.3迁移到~~OpenGL4.3~~ OpenGL ES 3.2
    // [ ] 考虑：PBO,ACB
    // [ ] FBO（和RBO）从frame.hpp移动到这里
    // [√] 预分配
    // [√] 一次性写入和分段写入（内存映射）

    struct Buffer
    {
    protected:
        GLuint buffer_id;

        void create_ogl_buffer() noexcept
        {
            glGenBuffers(1,&buffer_id);
        }

        template <GLenum buffer_target, GLenum buffer_usage>
        void pre_allocate_mem(uint32_t size) noexcept
        {
            glBindBuffer(buffer_target, buffer_id);
            glBufferData(buffer_target,size,nullptr,buffer_usage);
            glBindBuffer(buffer_target,0);
        }

        void delete_buffer() noexcept
        {
            glDeleteBuffers(1,&buffer_id);
        }
        
    public:
        GLuint get_buffer_id() noexcept
        {
            return buffer_id;
        }

        virtual constexpr GLenum get_buffer_target() noexcept = 0;
        virtual constexpr GLenum get_buffer_usage() noexcept = 0;
        virtual GLsizei get_buffer_size() noexcept = 0;
    };

    struct NoneDMABuffer : public Buffer
    {
        virtual void set_buffer_data(GLvoid* data,GLsizei size) noexcept = 0;
        virtual void set_buffer_sub_data(GLvoid* data,GLsizei size,GLsizei offset) noexcept = 0;   
    };

    template <GLenum buffer_target,GLenum buffer_usage>
    class __Buffer : public NoneDMABuffer
    {
    public:
        __Buffer(uint32_t size) noexcept
        {
            create_ogl_buffer();
            pre_allocate_mem<buffer_target, buffer_usage>(size);
        }

        __Buffer(__Buffer&) = delete;

        ~__Buffer() noexcept
        {
            delete_buffer();
        }

        constexpr GLenum get_buffer_target() noexcept
        {
            return buffer_target;
        }

        constexpr GLenum get_buffer_usage() noexcept
        {
            return buffer_usage;
        }

        GLsizei get_buffer_size() noexcept
        {
            GLsizei size;
            glBindBuffer(buffer_target, buffer_id);
            glGetBufferParameteriv(buffer_target, GL_BUFFER_SIZE, &size);
            glBindBuffer(buffer_target, 0);
            return size;
        }

        template <typename T>
        requires requires(T t)
        {
            std::convertible_to<std::remove_cvref<T>, GLvoid*>;
        }
        void set_buffer_data(T data, GLsizei size) noexcept
        {
            set_buffer_sub_data(data, size, 0);
        }

        void set_buffer_data(GLvoid* data, GLsizei size) noexcept
        {
            set_buffer_sub_data(data, size, 0);
        }

        template <typename T>
        requires requires(T t)
        {
            std::convertible_to<std::remove_cvref<T>, GLvoid*>;
        }
        void set_buffer_sub_data(T data, GLsizei size, GLsizei offset) noexcept
        {
            glBindBuffer(buffer_target, buffer_id);
            glBufferSubData(buffer_target, offset, size, data);
            glBindBuffer(buffer_target, 0);
        }

        void set_buffer_sub_data(GLvoid* data, GLsizei size, GLsizei offset) noexcept
        {
            set_buffer_sub_data(data, size, offset);
        }
    };

    using VBO_Static   =   __Buffer<GL_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using VBO_Dynamic   =   __Buffer<GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using VBO_Stream   =   __Buffer<GL_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using EBO_Static   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using EBO_Dynamic   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using EBO_Stream   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using TBO_Static   =   __Buffer<GL_TEXTURE_BUFFER,GL_STATIC_DRAW>;
    using TBO_Dynamic   =   __Buffer<GL_TEXTURE_BUFFER,GL_DYNAMIC_DRAW>;
    using TBO_Stream   =   __Buffer<GL_TEXTURE_BUFFER,GL_STREAM_DRAW>;

    using UBO_Static   =   __Buffer<GL_UNIFORM_BUFFER,GL_STATIC_DRAW>;
    using UBO_Dynamic   =   __Buffer<GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW>;
    using UBO_Stream   =   __Buffer<GL_UNIFORM_BUFFER,GL_STREAM_DRAW>;

    using PackPBO_Static   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_STATIC_DRAW>;
    using PackPBO_Dynamic   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_DYNAMIC_DRAW>;
    using PackPBO_Stream   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_STREAM_DRAW>;

    using UnpackPBO_Static   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_STATIC_DRAW>;
    using UnpackPBO_Dynamic   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_DYNAMIC_DRAW>;
    using UnpackPBO_Stream   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_STREAM_DRAW>;

    using SSBO_Static   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_STATIC_DRAW>;
    using SSBO_Dynamic   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_DYNAMIC_DRAW>;
    using SSBO_Stream   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_STREAM_DRAW>;

    struct DMABuffer : public Buffer
    {
        virtual void buffer_mapping_do(std::function<void(GLvoid* mapping_ptr)> callback) noexcept = 0;
        virtual std::unique_ptr<unsigned char[]> copy_buffer_mem(GLsizei size,GLsizei offset) noexcept = 0;
        virtual void set_buffer_mem(GLvoid* data,GLsizei size,GLsizei offset) noexcept = 0;
    };

    template <GLenum buffer_target,GLenum buffer_usage>
    class __DMABuffer : public DMABuffer
    {
    public:
        __DMABuffer(uint32_t size) noexcept
        {
            create_ogl_buffer();
            pre_allocate_mem<buffer_target, buffer_usage>(size);
        }
        
        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_size()} -> std::same_as<GLsizei>;
            {t.buffer_mapping_do(std::declval<std::function<void(GLvoid*)>>())} -> std::same_as<void>;
        }
        __DMABuffer(T& t) noexcept
            : __DMABuffer(t.get_buffer_size())
        {
            // copy ogl buffer mem
            buffer_mapping_do([&](GLvoid* dest_mapping_ptr)
            {
                t.buffer_mapping_do([&](GLvoid* src_mapping_ptr)
                    {
                        std::memcpy(dest_mapping_ptr, src_mapping_ptr, get_buffer_size());
                    });
            });
        }

        ~__DMABuffer() noexcept
        {
            delete_buffer();
        }

        constexpr GLenum get_buffer_target() noexcept
        {
            return buffer_target;
        }

        constexpr GLenum get_buffer_usage() noexcept
        {
            return buffer_usage;
        }

        GLsizei get_buffer_size() noexcept
        {
            GLsizei size;
            glBindBuffer(buffer_target, buffer_id);
            glGetBufferParameteriv(buffer_target, GL_BUFFER_SIZE, &size);
            glBindBuffer(buffer_target, 0);
            return size;
        }

        template <typename T>
        requires requires(T t)
        {
            std::convertible_to<std::remove_cvref<T>, GLvoid*>;
        }
        void buffer_mapping_do(std::function<void(T mapping_ptr)> callback) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr{ glMapBufferRange(buffer_target,0,get_buffer_size(), GL_MAP_READ_BIT) };
            callback(mapping_ptr);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }

        void buffer_mapping_do(std::function<void(GLvoid* mapping_ptr)> callback) noexcept
        {
            buffer_mapping_do(callback);
        }

        std::unique_ptr<unsigned char[]> copy_buffer_mem(GLsizei size,GLsizei offset) noexcept
        {
            // no any check, for better performance

            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr{ glMapBufferRange(buffer_target,0,get_buffer_size(),GL_MAP_READ_BIT) };
            auto copied_ptr = std::make_unique<unsigned char[]>(size);
            std::memcpy(copied_ptr.get(), reinterpret_cast<int*>(mapping_ptr) + offset, size);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
            return copied_ptr;
        }

        template <typename T>
        requires requires(T t)
        {
            std::convertible_to<std::remove_cvref<T>, GLvoid*>;
        }
        void set_buffer_mem(T data,GLsizei size,GLsizei offset) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr{ glMapBufferRange(buffer_target, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT) };
            std::memcpy(reinterpret_cast<int*>(mapping_ptr) + offset, data, size);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }

        void set_buffer_mem(GLvoid* data, GLsizei size, GLsizei offset) noexcept
        {
            set_buffer_mem(data, size, offset);
        }
    };

    using DirectVBO_Static   =   __DMABuffer<GL_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using DirectVBO_Dynamic   =   __DMABuffer<GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectVBO_Stream   =   __DMABuffer<GL_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using DirectEBO_Static   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using DirectEBO_Dynamic   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectEBO_Stream   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using DirectTBO_Static   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_STATIC_DRAW>;
    using DirectTBO_Dynamic   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectTBO_Stream   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_STREAM_DRAW>;

    using DirectUBO_Static   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_STATIC_DRAW>;
    using DirectUBO_Dynamic   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectUBO_Stream   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_STREAM_DRAW>;

    using DirectPackPBO_Static   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_STATIC_DRAW>;
    using DirectPackPBO_Dynamic   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectPackPBO_Stream   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_STREAM_DRAW>;

    using DirectUnPackPBO_Static   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_STATIC_DRAW>;
    using DirectUnPackPBO_Dynamic   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectUnPackPBO_Stream   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_STREAM_DRAW>;

    using DirectSSBO_Static   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_STATIC_DRAW>;
    using DirectSSBO_Dynamic   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectSSBO_Stream   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_STREAM_DRAW>;
}