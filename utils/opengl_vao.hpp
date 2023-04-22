#pragma once

#include <glad/glad.h>
#include <array>

namespace ni::utils::opengl
{
    enum class GLBufferType : unsigned short
    {
        Static,Dynamic,Stream
    };

    template <size_t verticesLen,size_t indicesLen,GLBufferType Type>
    class VertexArray
    {
    private:
        GLuint vao,vbo,ebo;

        std::array<float,verticesLen> storagedVertices;
        std::array<unsigned int,indicesLen> storagedIndices;

        void create(const std::array<float,verticesLen>& vertices,const std::array<unsigned int,indicesLen>& indices)
        {
            static_assert(verticesLen % 9 == 0, "illegal vertices length");
            static_assert(indicesLen % 2 == 0, "illegal indices length");

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

            storagedVertices = vertices;
            storagedIndices = indices;
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

            glBindBuffer(GL_ARRAY_BUFFER,vbo);
            glBufferData(GL_ARRAY_BUFFER,sizeof(storagedVertices),storagedVertices.data(),bufferType);
        }

    public:
        VertexArray(const std::array<float,verticesLen>& vertices,const std::array<unsigned int,indicesLen>& indices) : vao(0),vbo(0),ebo(0) {create(vertices,indices);}
        ~VertexArray()
        {
            glDeleteVertexArrays(1, &vao);
		    glDeleteBuffers(1, &vbo);
        }

        const GLuint& getVAO() const { return vao; }
        const GLuint& getVBO() const { return vbo; }
        const GLuint& getEBO() const { return ebo; }

        std::array<const float,3> getPosition(size_t i)
        {
            static_assert(i < verticesLen / 9, "out of range");
            return std::array<const float,3>{storagedVertices[i * 9],storagedVertices[i * 9 + 1],storagedVertices[i * 9 + 2]};
        }
        std::array<const float,4> getColor(size_t i)
        {
            static_assert(i < verticesLen / 9, "out of range");
            return std::array<const float,4>{storagedVertices[i * 9 + 3],storagedVertices[i * 9 + 4],storagedVertices[i * 9 + 5],storagedVertices[i * 9 + 6]};
        }
        std::array<const float,2> getTextureCoord(size_t i)
        {
            static_assert(i < verticesLen / 9, "out of range");
            return std::array<const float,2>{storagedVertices[i * 9 + 7],storagedVertices[i * 9 + 8]};
        }

        void setPosition(size_t i,const std::array<float,3>& arr)
        {
            for(int j = 0;j < 3;j++)
                storagedVertices[i * 9 + j] = arr[j];

            update();
        }

        void setColor(size_t i,const std::array<float,4>& arr)
        {
            for(int j = 0; j < 4; j++)
                storagedVertices[i * 9 + 3 + j] = arr[j];
    
            update();
        }

        void setTextureCoord(size_t i,const std::array<float,4>& arr)
        {
            for(int j = 0;j < 2;j++)
                storagedVertices[i * 9 + 7 + j] = arr[j];

            update();
        }
    };

    template <GLBufferType Type>
    class RectVertexArray : public VertexArray<36,6,Type>
    {
    private:
        static constexpr std::array<unsigned int,6> rectIndices
        {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        static constexpr std::array<float,36> rectVertices
        {
            1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
            1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
            -1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
            -1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
        };

    public:
        RectVertexArray() : VertexArray<36,6,Type>(rectVertices, rectIndices) {}
        ~RectVertexArray() = default;
    };
}