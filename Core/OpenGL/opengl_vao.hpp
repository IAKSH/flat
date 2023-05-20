#pragma once

#include "../../misc/logger.hpp"
#include "../../misc/disable_copy.hpp"
#include "opengl_scope.hpp"
#include <exception>
#include <glad/glad.h>
#include <array>

namespace flat::opengl
{
    enum class BufferType : unsigned short
    {
        Static,Dynamic,Stream
    };

    template <size_t vertices_len,size_t indices_len,BufferType type>
    class VertexArray : misc::DisableCopy
    {
        static_assert(vertices_len % 9 == 0, "illegal vertices length");
        static_assert(indices_len % 2 == 0, "illegal indices length");

    private:
        GLuint vao,vbo,ebo;
        std::array<float,vertices_len> storaged_vertices;
        std::array<unsigned int,indices_len> storaged_indices;

        void create(const std::array<float,vertices_len>& vertices,const std::array<unsigned int,indices_len>& indices)
        {
            Scope scope;

            int buffer_type_flag;
            if constexpr(type == BufferType::Static)
                buffer_type_flag = GL_STATIC_DRAW;
            else if constexpr(type == BufferType::Dynamic)
                buffer_type_flag = GL_DYNAMIC_DRAW;
            else if constexpr(type == BufferType::Stream)
                buffer_type_flag = GL_STREAM_DRAW;

            glGenVertexArrays(1,&vao);
            glGenBuffers(1,&vbo);
            glGenBuffers(1,&ebo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices.data(),buffer_type_flag);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), buffer_type_flag);
            // position attribute
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,9 * sizeof(float),(void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,9 * sizeof(float),(void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // texture coord attribute
            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,9 * sizeof(float),(void*)(7 * sizeof(float)));
            glEnableVertexAttribArray(2);

            storaged_vertices = vertices;
            storaged_indices = indices;
        }

        void update()
        {
            Scope scope;

            GLuint buffer_type;
            if constexpr(type == BufferType::Static)
                buffer_type = GL_STATIC_DRAW;
            else if constexpr(type == BufferType::Dynamic)
                buffer_type = GL_DYNAMIC_DRAW;
            else if constexpr(type == BufferType::Stream)
                buffer_type = GL_STREAM_DRAW;
            
            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(storaged_vertices),storaged_vertices.data(),buffer_type);
        }

    public:
        VertexArray(const std::array<float,vertices_len>& vertices,const std::array<unsigned int,indices_len>& indices)
            : vao(0),vbo(0),ebo(0)
        {
            create(vertices,indices);
        }

        ~VertexArray()
        {
            glDeleteVertexArrays(1,&vao);
            glDeleteBuffers(1,&vbo);
        }

        GLuint getVAO() const {return vao;}
        GLuint getVBO() const {return vbo;}
        GLuint getEBO() const {return ebo;}

        std::array<const float,3> get_position(size_t i)
        {
            if(i < vertices_len / 9)
            {
                misc::main_logger->critical("VertexArray::get_position() out of range");
                std::terminate();
            }
            return std::array<const float,3>{storaged_vertices[i * 9],storaged_vertices[i * 9 + 1],storaged_vertices[i * 9 + 2]};
        }

        std::array<const float,4> get_color(size_t i)
        {
            if(i < vertices_len / 9)
            {
                misc::main_logger->critical("VertexArray::get_color() out of range");
                std::terminate();
            }
            return std::array<const float,4>{storaged_vertices[i * 9 + 3],storaged_vertices[i * 9 + 4],storaged_vertices[i * 9 + 5],storaged_vertices[i * 9 + 6]};
        }

        std::array<const float,2> get_texture_coord(size_t i)
        {
            if(i < vertices_len / 9)
            {
                misc::main_logger->critical("VertexArray::get_texture_coord() out of range");
                std::terminate();
            }
            return std::array<const float,2>{storaged_vertices[i * 9 + 7],storaged_vertices[i * 9 + 8]};
        }

        void set_position(size_t i,const std::array<float,3>& arr)
        {
            for(size_t j = 0;j < 3;j++)
                storaged_vertices[i * 9 + j] = arr[j];
            update();
        }

        void set_color(size_t i,const std::array<float,4>& arr)
        {
            for(size_t j = 0;j < 4;j++)
                storaged_vertices[i * 9 + 3 + j] = arr[j];
            update();
        }

        void set_texture_coord(size_t i,const std::array<float,4>& arr)
        {
            for(size_t j = 0;j < 2;j++)
                storaged_vertices[i * 9 + 7 + j] = arr[j];
            update();
        }
    };

    template <BufferType type>
    class RectangleVertexArray : public VertexArray<36,6,type>
    {
    private:
        inline static constexpr std::array<unsigned int,6> rect_indices
        {
            0,1,3,
            1,2,3
        };

        inline static constexpr std::array<float,36> rect_vertices
        {
            1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
            1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
            -1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
            -1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
        };

    public:
        RectangleVertexArray() : VertexArray<36, 6, type>(rect_vertices,rect_indices)
        {
        }

        ~RectangleVertexArray() = default;
    };
}