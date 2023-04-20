#pragma once

#include <array>
#include <exception>
#include <glad/glad.h>
#include "../logger.hpp"
#include "../template.hpp"
#include "../physics/common.hpp"

namespace ni::opengl
{
    struct VertexArrayObjID : public utils::__Enchased<GLuint>
    {
        VertexArrayObjID(const GLuint& id = 0) : __Enchased(id) {}
    };

    struct VertexBufferObjID : public utils::__Enchased<GLuint>
    {
        VertexBufferObjID(const GLuint& id = 0) : __Enchased(id) {}
    };

    struct ElementBufferObjID : public utils::__Enchased<GLuint>
    {
        ElementBufferObjID(const GLuint& id = 0) : __Enchased(id) {}
    };

    template <typename T>
    concept VertexArrayReturnType = utils::anySame<T,VertexArrayObjID,VertexBufferObjID,ElementBufferObjID>();

    enum class GLBufferType : unsigned short
    {
        Static,Dynamic,Stream
    };

    template <GLBufferType Type>
    class VertexArray
    {
    private:
        GLuint vao,vbo,ebo;

        void release()
        {
            glDeleteVertexArrays(1, &vao);
		    glDeleteBuffers(1, &vbo);
        }

        template <size_t verticesLen,size_t indicesLen>
        void create(const std::array<float,verticesLen>& vertices,const std::array<unsigned int,indicesLen>& indices)
        {
            static_assert(verticesLen % 9 == 0, "illegal vertices length");
            static_assert(indicesLen % 2 == 0, "illegal indices length");

            if(vao)
            {
                ni::utils::coreLogger->critical("OpenGL Vertex Array Object re-allocated (vao = {})",vao);
                std::terminate();
            }

            int glBufferTypeFlag;
            if constexpr(Type == GLBufferType::Static)
                glBufferTypeFlag = GL_STATIC_DRAW;
            else if constexpr(Type == GLBufferType::Dynamic)
                glBufferTypeFlag = GL_DYNAMIC_DRAW;
            else if constexpr(Type == GLBufferType::Stream)
                glBufferTypeFlag = GL_STREAM_DRAW;

            glGenVertexArrays(1, &vao);
		    glGenBuffers(1, &vbo);
		    glGenBuffers(1, &ebo);
		    glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
		    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), glBufferTypeFlag);

		    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), glBufferTypeFlag);
        
            // position attribute
		    (0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		    glEnableVertexAttribArray(0);
            // color attribute
		    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		    glEnableVertexAttribArray(1);
		    // texture coord attribute
		    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		    glEnableVertexAttribArray(2);

		    glBindBuffer(GL_ARRAY_BUFFER, 0);
		    glBindVertexArray(0);
        }

    protected:
        // no check of out-of-range, be careful
        void create(const float* const vertices,const unsigned int* const indices)
        {
            if(vao)
            {
                ni::utils::coreLogger->critical("OpenGL Vertex Array Object re-allocated (vao = {})",vao);
                std::terminate();
            }

            int glBufferTypeFlag;
            if constexpr(Type == GLBufferType::Static)
                glBufferTypeFlag = GL_STATIC_DRAW;
            else if constexpr(Type == GLBufferType::Dynamic)
                glBufferTypeFlag = GL_DYNAMIC_DRAW;
            else if constexpr(Type == GLBufferType::Stream)
                glBufferTypeFlag = GL_STREAM_DRAW;

            glGenVertexArrays(1, &vao);
		    glGenBuffers(1, &vbo);
		    glGenBuffers(1, &ebo);
		    glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
		    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, vertices, glBufferTypeFlag);

		    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, glBufferTypeFlag);
        
            // position attribute
		    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		    glEnableVertexAttribArray(0);
            // color attribute
		    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		    glEnableVertexAttribArray(1);
		    // texture coord attribute
		    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		    glEnableVertexAttribArray(2);

		    glBindBuffer(GL_ARRAY_BUFFER, 0);
		    glBindVertexArray(0);
        }

    public:
        template <size_t verticesLen,size_t indicesLen>
        VertexArray(const std::array<float,verticesLen>& vertices,const std::array<unsigned int,indicesLen>& indices)
        {
            create(vertices,indices);
        }
        ~VertexArray()
        {
            release();
        }

        const GLuint& getVAO() const { return vao; }
        const GLuint& getVBO() const { return vbo; }
        const GLuint& getEBO() const { return ebo; }

        template <VertexArrayReturnType T>
        T get() const
        {
            if constexpr (utils::isSame<T,VertexArrayObjID>())
                return VertexArrayObjID(vao);
            else if constexpr (utils::isSame<T,VertexBufferObjID>())
                return VertexBufferObjID(vbo);
            else if constexpr (utils::isSame<T,ElementBufferObjID>())
                return ElementBufferObjID(ebo);
        }

        template <VertexArrayReturnType T>
        void set(T&& t)
        {
            if constexpr (utils::isSame<T,VertexArrayObjID>())
                vao = t;
            else if constexpr (utils::isSame<T,VertexBufferObjID>())
                vbo = t;
            else if constexpr (utils::isSame<T,ElementBufferObjID>())
                ebo = t;
        }
    };

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
    concept VerticesComponent = any_same<T,utils::Point,TextureCoord,Color,Red,Green,Blue,Alpha>();

    template <GLBufferType Type>
    class RectangleVertexArray : public VertexArray<Type>
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
        RectangleVertexArray()
        {
            this->create(getVerticesPtr(),rectangleIndices.data());
        }
        ~RectangleVertexArray() = default;

        template <VerticesComponent T>
        void set(size_t i,const T& t) override
        {
            if(i >= vertices.size())
            {
                ni::utils::coreLogger->critical(
                    "VertexBuffer set(..) out of range: vertices.size() = {} but i = {}",vertices.size(),i);
                std::terminate();
            }

            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,utils::Point>)
            {
                auto& xyz = vertices[i].xyz;
                xyz[0] = ((utils::Point&)t).get<utils::AxisCoordinateX>();
                xyz[1] = static_cast<utils::Point>(t).getPosY();
                xyz[2] = static_cast<utils::Point>(t).getPosZ();
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
        const T& get(size_t i) const override
        {
            if(i >= vertices.size())
            {
                ni::utils::coreLogger()->critical(
                    "VertexBuffer get(..) out of range: vertices.size() = {} but i = {}",vertices.size(),i);
                std::terminate();
            }

            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,utils::Point>)
            {
                auto& buffer = vertices[i].xyz;
                return utils::Point({buffer[0],buffer[1],buffer[2]});
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