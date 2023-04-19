#pragma once

#include "vao.hpp"
#include "color.hpp"
#include "logger.hpp"
#include "texture.hpp"
#include "mass_point.hpp"
#include "any_same.hpp"

#include <array>
#include <type_traits>
#include <variant>
#include <exception>

namespace ni::utils
{
    inline static std::array<unsigned int,6> rectangleIndices
    {
        0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
    };

    struct Vertex
    {
        std::array<float,3> xyz;
        std::array<float,4> rgba;
        std::array<float,2> textCoord;
    };

    template <typename T>
    concept VerticesComponent = any_same<T,Point,TextureCoord,Color,Red,Green,Blue,Alpha>();

    template <GLBufferType Type>
    class VertexBuffer : public VertexArrayObj<Type>
    {
    private:
        std::array<Vertex,4> vertices
        {
            1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
			1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
			-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
			-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
        };

        const float* const getVerticesPtr() const
        {
            return reinterpret_cast<const float* const>(vertices.data());
        }

        void update()
        {
            GLuint bufferType;
            if constexpr(Type == GLBufferType::Static)
                bufferType = GL_STATIC_DRAW;
            else if constexpr(Type == GLBufferType::Dynamic)
                bufferType = GL_DYNAMIC_DRAW;
            else if constexpr(Type == GLBufferType::Stream)
                bufferType = GL_STREAM_DRAW;

            glBindBuffer(GL_ARRAY_BUFFER,this->getVBO());
            glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices.data(),bufferType);
        }

    public:
        VertexBuffer()
        {
            this->create(getVerticesPtr(),rectangleIndices.data());
        }
        ~VertexBuffer() = default;

        template <VerticesComponent T>
        void set(size_t i,const T& t)
        {
            if(i >= vertices.size())
            {
                ni::utils::coreLogger()->critical(
                    "VertexBuffer set(..) out of range: vertices.size() = {} but i = {}",vertices.size(),i);
                std::terminate();
            }

            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,Point>)
            {
                auto& xyz = vertices[i].xyz;
                xyz[0] = static_cast<Point>(t).getPosX();
                xyz[1] = static_cast<Point>(t).getPosY();
                xyz[2] = static_cast<Point>(t).getPosZ();
            }
            else if constexpr(std::is_same_v<U,TextureCoord>)
            {
                auto& xy = vertices[i].textCoord;
                xy[0] = static_cast<TextureCoord>(t).getX();
                xy[1] = static_cast<TextureCoord>(t).getY();
            }
            else if constexpr(std::is_same_v<U,Color>)
            {
                Color&& color = static_cast<Color>(t);
                vertices[i].rgba[0] = static_cast<Red>(color);
                vertices[i].rgba[1] = static_cast<Green>(color);
                vertices[i].rgba[2] = static_cast<Blue>(color);
                vertices[i].rgba[3] = static_cast<Alpha>(color);
            }
            else if constexpr(std::is_same_v<U,Red>)
                vertices[i].rgba[0] = static_cast<Red>(t);
            else if constexpr(std::is_same_v<U,Green>)
                vertices[i].rgba[1] = static_cast<Green>(t);
            else if constexpr(std::is_same_v<U,Blue>)
                vertices[i].rgba[2] = static_cast<Blue>(t);
            else if constexpr(std::is_same_v<U,Alpha>)
                vertices[i].rgba[3] = static_cast<Alpha>(t);
            
            update();
        }

        template <VerticesComponent T>
        const T& get(size_t i) const
        {
            if(i >= vertices.size())
            {
                ni::utils::coreLogger()->critical(
                    "VertexBuffer get(..) out of range: vertices.size() = {} but i = {}",vertices.size(),i);
                std::terminate();
            }

            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,Point>)
            {
                auto& buffer = vertices[i].xyz;
                return Point({buffer[0],buffer[1],buffer[2]});
            }
            else if constexpr(std::is_same_v<U,TextureCoord>)
            {
                auto& buffer = vertices[i].textCoord;
                return TextureCoord(buffer[0],buffer[1]);
            }
            else if constexpr(std::is_same_v<U,Color>)
            {
                return Color(vertices[i].rgba[0],
                    vertices[i].rgba[1],vertices[i].rgba[2],vertices[i].rgba[3]);
            }
            else if constexpr(std::is_same_v<U,Red>)
                return Red(vertices[i].rgba[0] * 255);
            else if constexpr(std::is_same_v<U,Green>)
                return Green(vertices[i].rgba[1] * 255);
            else if constexpr(std::is_same_v<U,Blue>)
                return Blue(vertices[i].rgba[2] * 255);
            else if constexpr(std::is_same_v<U,Alpha>)
                return Alpha(vertices[i].rgba[3] * 255);

            update();
        }
    };
}