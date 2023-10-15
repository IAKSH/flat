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
    // [O] UBO,SSBO
    // [X] TBO
    // [√] 从OpenGL 3.3迁移到~~OpenGL4.3~~ OpenGL ES 3.2
    // [X] 考虑：PBO,ACB
    // [~] FBO（和RBO）从frame.hpp移动到这里 <驳回：不是同一种Buffer> 
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

        void pre_allocate_mem(GLenum buffer_target, GLenum buffer_usage, GLsizeiptr size) noexcept
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
        virtual GLint get_buffer_size() noexcept = 0;
    };

    template <GLenum buffer_target,GLenum buffer_usage>
    class __Buffer : public Buffer
    {
    public:
        __Buffer(GLsizeiptr size) noexcept
        {
            create_ogl_buffer();
            pre_allocate_mem(buffer_target, buffer_usage, size);
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
        
        GLint get_buffer_size() noexcept
        {
            GLint size;
            glBindBuffer(buffer_target, buffer_id);
            glGetBufferParameteriv(buffer_target, GL_BUFFER_SIZE, &size);
            glBindBuffer(buffer_target, 0);
            return size;
        }

        template <typename T>
        void set_buffer_data(T* data, GLsizeiptr size) noexcept
        {
            set_buffer_sub_data(data, size, 0);
        }

        template <typename T>
        void set_buffer_sub_data(T* data, GLsizeiptr size, GLsizeiptr offset) noexcept
        {
            glBindBuffer(buffer_target, buffer_id);
            glBufferSubData(buffer_target, offset, size, data);
            glBindBuffer(buffer_target, 0);
        }
    };

    using VBO_Static   =   __Buffer<GL_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using VBO_Dynamic   =   __Buffer<GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using VBO_Stream   =   __Buffer<GL_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using EBO_Static   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using EBO_Dynamic   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using EBO_Stream   =   __Buffer<GL_ELEMENT_ARRAY_BUFFER,GL_STREAM_DRAW>;

    // TODO: TBO is so strange, current API is not usable for sure
    //using TBO_Static   =   __Buffer<GL_TEXTURE_BUFFER,GL_STATIC_DRAW>;
    //using TBO_Dynamic   =   __Buffer<GL_TEXTURE_BUFFER,GL_DYNAMIC_DRAW>;
    //using TBO_Stream   =   __Buffer<GL_TEXTURE_BUFFER,GL_STREAM_DRAW>;

    // about UBO:
    // https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object
    // for more infomation, see the part of DirectUBO

    using UBO_Static   =   __Buffer<GL_UNIFORM_BUFFER,GL_STATIC_DRAW>;
    using UBO_Dynamic   =   __Buffer<GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW>;
    using UBO_Stream   =   __Buffer<GL_UNIFORM_BUFFER,GL_STREAM_DRAW>;

    //using PackPBO_Static   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_STATIC_DRAW>;
    //using PackPBO_Dynamic   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_DYNAMIC_DRAW>;
    //using PackPBO_Stream   =   __Buffer<GL_PIXEL_PACK_BUFFER,GL_STREAM_DRAW>;

    //using UnpackPBO_Static   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_STATIC_DRAW>;
    //using UnpackPBO_Dynamic   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_DYNAMIC_DRAW>;
    //using UnpackPBO_Stream   =   __Buffer<GL_PIXEL_UNPACK_BUFFER,GL_STREAM_DRAW>;

    // about SSBO:
    // https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object
    // for more infomation, see the part of DirectSSBO

    using SSBO_Static   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_STATIC_DRAW>;
    using SSBO_Dynamic   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_DYNAMIC_DRAW>;
    using SSBO_Stream   =   __Buffer<GL_SHADER_STORAGE_BUFFER,GL_STREAM_DRAW>;

    template <GLenum buffer_target,GLenum buffer_usage>
    class __DMABuffer : public Buffer
    {
    public:
        __DMABuffer(GLsizeiptr size) noexcept
        {
            create_ogl_buffer();
            pre_allocate_mem(buffer_target, buffer_usage, size);
        }
        
        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_size()} -> std::same_as<GLint>;
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

        GLint get_buffer_size() noexcept
        {
            GLint size;
            glBindBuffer(buffer_target, buffer_id);
            glGetBufferParameteriv(buffer_target, GL_BUFFER_SIZE, &size);
            glBindBuffer(buffer_target, 0);
            return size;
        }

        template <typename T>
        void buffer_mapping_do(std::function<void(T* mapping_ptr)> callback) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr{ glMapBufferRange(buffer_target,0,get_buffer_size(), GL_MAP_READ_BIT) };
            callback(mapping_ptr);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }

        std::unique_ptr<unsigned char[]> copy_buffer_mem(GLsizeiptr size, GLsizeiptr offset) noexcept
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
        void set_buffer_mem(T* data, GLsizeiptr size, GLsizeiptr offset) noexcept
        {
            glBindBuffer(buffer_target,buffer_id);

            GLvoid* mapping_ptr{ glMapBufferRange(buffer_target, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT) };
            std::memcpy(reinterpret_cast<int*>(mapping_ptr) + offset, data, size);

            glUnmapBuffer(buffer_target);
            glBindBuffer(buffer_target,0);
        }
    };

    using DirectVBO_Static   =   __DMABuffer<GL_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using DirectVBO_Dynamic   =   __DMABuffer<GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectVBO_Stream   =   __DMABuffer<GL_ARRAY_BUFFER,GL_STREAM_DRAW>;

    using DirectEBO_Static   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW>;
    using DirectEBO_Dynamic   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectEBO_Stream   =   __DMABuffer<GL_ELEMENT_ARRAY_BUFFER,GL_STREAM_DRAW>;

    // about TBO:
    // https://www.khronos.org/opengl/wiki/Buffer_Texture
    // TBO is useful when transport huge amount of texture data from CPU to GPU
    // with TBO, you can reduce calls of OpenGL ES API, which will increase your performance
    // and more, through DMA, you can update parts of the texture in a high performance way
    // there's a limit on texture size in legacy Texture, TBO can store more data than legacy Texture could
    // 
    // however TBOs are just Buffers, they can't create minimap for textures
    // 
    // TBO uses like VBO/EBO, you can create,fill and bind TBO like this:
    // glBindBuffer(GL_TEXTURE_BUFFER, tbo_id);
    // glBufferData(GL_TEXTURE_BUFFER, texture.size() * sizeof(float), texture.data(), GL_STATIC_DRAW);
    // (or you can use glBufferSubData to fill/update parts of the TBO)
    // 
    // as the steps upon, you have a Texture Buffer now, but things no end yet
    // before you use this TBO, you need to bind your Texture Buffer (a buffer) to a Buffer Texture (a texture)
    // do like this:
    // 
    // glGenTextures(1,&texture_id);
    // glbindTexture(GL_TEXTURE_BUFFER, texture);
    // glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo_id);
    // 
    // then the TBO was binded to a buffered texture, and the texture was binded to contex
    // next you may need to the set the filter of this buffered texture:
    // 
    // glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_BUFFER, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 
    // you can now use the binding TBO in GLSL like this:
    // 
    // #version 320 es
    // precision highp float;
    // 
    // uniform samplerBuffer tboSampler
    // void main()
    // {
    //     vec4 tboData = texelFetch(tboSampler,0);
    //     ...
    // }
    //
    // the '0' in 'texelFetch(tboSampler,0);' was the index of the TBO's element
    // which meas on 

    // TODO: TBO are not simply a buffer, but a combination of texture and buffer
    // need to create a single class for TBO

    // TODO: TBO is so strange, current API is not usable for sure
    //using DirectTBO_Static   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_STATIC_DRAW>;
    //using DirectTBO_Dynamic   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_DYNAMIC_DRAW>;
    //using DirectTBO_Stream   =   __DMABuffer<GL_TEXTURE_BUFFER,GL_STREAM_DRAW>;

    // about UBO:
    // https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object
    // UBO is global accessable (for shaders that have uniform block binding to it)
    // use UBO instead of a large number of plain uniforms can reduce calls of OpenGL ES API
    // which benefets alot on the performance
    // 
    // to bind a UBO to context's UBO binding point, use like this:
    // glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboExampleBlock); 
    // 
    // or:                                                 (offset)(size)
    // glBindBufferRange(GL_UNIFORM_BUFFER, 2, uboExampleBlock, 0, 152);
    // 
    // you can define a uniform block in GLSL to access the UBO binded
    //
    // layout(row_major) uniform MatrixBlock
    // {
    //     mat4 projection;
    //     mat4 modelview;
    // } matrices[3];
    // 
    // not finish yet, you need also bind GLSL's uniform block to the binding point, like below:
    // 
    // unsigned int lights_index = glGetUniformBlockIndex(shaderA.ID, "Lights");   
    // glUniformBlockBinding(shaderA.ID, lights_index, 2)
    //
    // this needs shader's id, so we put this API in shader.hpp
    // in most case, you don't need to bind shader's uniform block use plain OpenGL ES API

    using DirectUBO_Static   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_STATIC_DRAW>;
    using DirectUBO_Dynamic   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectUBO_Stream   =   __DMABuffer<GL_UNIFORM_BUFFER,GL_STREAM_DRAW>;

    //using DirectPackPBO_Static   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_STATIC_DRAW>;
    //using DirectPackPBO_Dynamic   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_DYNAMIC_DRAW>;
    //using DirectPackPBO_Stream   =   __DMABuffer<GL_PIXEL_PACK_BUFFER,GL_STREAM_DRAW>;

    //using DirectUnPackPBO_Static   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_STATIC_DRAW>;
    //using DirectUnPackPBO_Dynamic   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_DYNAMIC_DRAW>;
    //using DirectUnPackPBO_Stream   =   __DMABuffer<GL_PIXEL_UNPACK_BUFFER,GL_STREAM_DRAW>;

    // about SSBO:
    // https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object
    // SSBO is slower than UBO in most case
    // however, it can contains a variable-length array in the end of it's memory structure
    // 
    // SSBO uses like UBO, both are global accessable (also, you need to define the interface block before you access them)
    // SSBO has its own binding points that just like UBO's
    // to bind a SSBO to certain binding point, do like this:
    //
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);
    // 
    // or:                                            (offset)(size)
    // glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 2, ssbo, 0, 152);
    // 
    // the's one thing you need to pay attention to is that,
    // as SSBO needs to be updated in most case, and you might need to change the size of its buffer
    // when you glBufferData() SSBO into a bigger mem space, you actually create a new buffer
    // in that case, you need to rebind this buffer as a SSBO, and rebind this SSBO to former SSBO binding point
    // and, the one last thing is, you need to delete the former buffer, OpenGL ES context won't delete it automaticly
    // 
    // TODO: Buffer class need to do this (👆) automaticly
    //
    // you also need to define a buffer block in GLSL, so that you can access the binding SSBOs
    // your GLSL code may look like this:
    //
    // layout(std430, binding = 2) buffer anotherLayoutName
    // {
    //     int some_int;
    //     float fixed_array[42];
    //     float variable_array[];
    // };
    // 
    // as you can see, the binding point of GLSL's Buffer Block was defined while compiling shader program
    // you can not change this after it was compiled
    
    using DirectSSBO_Static   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_STATIC_DRAW>;
    using DirectSSBO_Dynamic   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_DYNAMIC_DRAW>;
    using DirectSSBO_Stream   =   __DMABuffer<GL_SHADER_STORAGE_BUFFER,GL_STREAM_DRAW>;
}