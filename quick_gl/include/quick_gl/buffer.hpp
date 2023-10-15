#pragma once

#include <format>
#include <memory>
#include <cstdint>
#include <concepts>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <glad/glad.h>

namespace quick3d::gl
{
    // VBO,EBO
    // UBO,SSBO,TBO
    // 从OpenGL 3.3迁移到OpenGL4.3
    // 考虑：PBO,ACB
    // FBO（和RBO）从frame.hpp移动到这里
    // 预分配
    // 一次性写入和分段写入（内存映射）

    struct Buffer
    {
    protected:
        GLuint buffer_id;

        void create_ogl_buffer() noexcept
        {
            glGenBuffers(1,&buffer_id);
        }

        void pre_allocate_mem(GLenum buffer_target,GLenum buffer_usage, uint32_t size) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);
            glBufferData(buffer_target,size,nullptr,buffer_usage);
            glBindBuffer(buffer_target,0);
        }

        void delete_buffer() noexcept
        {
            glDeleteBuffers(1,&buffer_id);
        }
        
    public:
        virtual GLuint get_buffer_id() noexcept = 0;
        virtual constexpr GLenum get_buffer_target() noexcept = 0;
        virtual constexpr GLenum get_buffer_usage() noexcept = 0;
        virtual GLsizei get_buffer_size() noexcept = 0;
    };

    struct NoneDMABuffer : public Buffer
    {
        /*
        virtual void buffer_mapping_do(std::function<void(GLvoid* mapping_ptr)> callback) noexcept = 0;
        virtual std::unique_ptr<unsigned char[]> copy_buffer_mem(GLsizei size,GLsizei offset) noexcept = 0;
        virtual void set_buffer_mem(GLvoid* data,GLsizei size,GLsizei offset) noexcept = 0;
        */
    
        virtual void set_buffer_data(GLvoid* data,GLsizei size) noexcept = 0;
        virtual void set_buffer_sub_data(GLvoid* data,GLsizei size,GLsizei offset) noexcept = 0;   
        virtual std::unique_ptr<unsigned char[]> copy_buffer_data() noexcept = 0;
        virtual std::unique_ptr<unsigned char[]> copy_buffer_sub_data() noexcept = 0;
    };

    template <GLenum buffer_target,GLenum buffer_usage>
    class __Buffer : public NoneDMABuffer
    {
    private:
        

    public:
        __Buffer(uint32_t size)
        {
            create_ogl_buffer();
            pre_allocate_mem(buffer_target,buffer_usage,size);
        }
    };

    using VBO_Static   =   __Buffer<GL_VERTEX_ARRAY,GL_STATIC_DRAW>;
    using VBO_Dynamic   =   __Buffer<GL_VERTEX_ARRAY,GL_DYNAMIC_DRAW>;
    using VBO_Stream   =   __Buffer<GL_VERTEX_ARRAY,GL_STREAM_DRAW>;

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
            pre_allocate_mem(buffer_target,buffer_usage,size);
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
                        std::copy(src_mapping_ptr, src_mapping_ptr + get_buffer_size(), dest_mapping_ptr);
                    });
            });
        }

        ~__DMABuffer() noexcept
        {
            delete_buffer();
        }

        GLuint get_buffer_id() noexcept
        {
            return buffer_id;
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

        void buffer_mapping_do(std::function<void(GLvoid* mapping_ptr)> callback) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr {glMapBuffer(buffer_target,GL_READ_WRITE)};
            callback(mapping_ptr);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }

        std::unique_ptr<unsigned char[]> copy_buffer_mem(GLsizei size,GLsizei offset) noexcept
        {
            // no any check, for better performance

            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr {glMapBuffer(buffer_target,GL_READ_ONLY)};
            auto copied_ptr = std::make_unique<unsigned char[]>(size);
            std::copy(mapping_ptr + offset,mapping_ptr + offset + size,copied_ptr.get());

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
            return copied_ptr;
        }

        void set_buffer_mem(GLvoid* data,GLsizei size,GLsizei offset) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr {glMapBuffer(buffer_target,GL_WRITE_ONLY)};
            std::copy(data,data + size,mapping_ptr + offset);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }
    };

    using DirectVBO_Static   =   __DMABuffer<GL_VERTEX_ARRAY,GL_STATIC_DRAW>;
    using DirectVBO_Dynamic   =   __DMABuffer<GL_VERTEX_ARRAY,GL_DYNAMIC_DRAW>;
    using DirectVBO_Stream   =   __DMABuffer<GL_VERTEX_ARRAY,GL_STREAM_DRAW>;

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