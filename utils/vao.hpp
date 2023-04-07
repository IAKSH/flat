#pragma once

#include <array>

#include <glad/glad.h>

namespace ni::utils
{
    enum class GLBufferType : unsigned short
    {
        Static,Dynamic,Stream
    };

    class VertexArrayObj
    {
    private:
        GLuint vao,vbo,ebo;
        void release()
        {
            glDeleteVertexArrays(1, &vao);
		    glDeleteBuffers(1, &vbo);
        }

    public:
        VertexArrayObj()
            : vao{0},vbo{0},ebo{0}
        {
        }
        ~VertexArrayObj()
        {
            release();
        }

        const GLuint& getVAO() const { return vao; }
        const GLuint& getVBO() const { return vbo; }
        const GLuint& getEBO() const { return ebo; }

        template <size_t verticesLen,size_t indicesLen>
        void create(GLBufferType type, const std::array<float,verticesLen>& vertices,const std::array<unsigned int,indicesLen>& indices)
        {
            static_assert(verticesLen % 9 == 0, "illegal vertices length");
            static_assert(indicesLen % 2 == 0, "illegal indices length");

            int glBufferTypeFlag;
            switch (type)
            {
                case GLBufferType::Static:
                    glBufferTypeFlag = GL_STATIC_DRAW;
                    break;
                case GLBufferType::Dynamic:
                    glBufferTypeFlag = GL_DYNAMIC_DRAW;
                    break;
                case GLBufferType::Stream:
                    glBufferTypeFlag = GL_STREAM_DRAW;
                    break;
            }

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
        }
    };
}