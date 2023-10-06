#pragma once

#include <cstdint>
#include <concepts>
#include <string_view>
#include <glad/glad.h>

namespace quick3d::gl
{
    template <GLenum buffer_type>
    class VertexBuffer
    {
    private:
        GLenum store_mode;
        GLuint buffer_id;
        std::size_t buffer_size;

    public:
        VertexBuffer() noexcept
            : store_mode(GL_STATIC_DRAW),buffer_size(0)
        {
            glGenBuffers(1,&buffer_id);
        }

        template <typename T>
        requires requires(T t)
        {
            { t.size() } -> std::convertible_to<std::size_t>;
            { t.data() } -> std::convertible_to<const void*>;
        }
        VertexBuffer(const T& t,GLenum store_mode = GL_STATIC_DRAW) noexcept
            : store_mode(store_mode),buffer_size(0)
        {
            glGenBuffers(1,&buffer_id);
            write_to_buffer(t,store_mode);
        }

        VertexBuffer(VertexBuffer&) = delete;

        ~VertexBuffer() noexcept
        {
            glDeleteBuffers(1,&buffer_id);
        }

        GLuint get_buffer_id() const noexcept
        {
            return buffer_id;
        } 

        template <typename T>
        requires requires(T t)
        {
            { t.size() } -> std::convertible_to<std::size_t>;
            { t.data() } -> std::convertible_to<const void*>;
        }
        void write_to_buffer(const T& t,GLenum mode) noexcept
        {
            store_mode = mode;

            auto write_buffer = [&]()
			{
				glBindBuffer(buffer_type, buffer_id);
				glBufferData(buffer_type, sizeof(t), t.data(), static_cast<GLenum>(store_mode));
			};

			if (buffer_size == t.size())
				write_buffer();
			else
			{
				glDeleteBuffers(1, &buffer_id);
				glGenBuffers(1, &buffer_id);
				write_buffer();
				buffer_size = t.size();
			}
            glBindBuffer(buffer_type, 0);
        }

        GLenum get_store_mode() const noexcept
        {
            return store_mode;
        }
    };

    using VBO = VertexBuffer<GL_ARRAY_BUFFER>;
    using EBO = VertexBuffer<GL_ELEMENT_ARRAY_BUFFER>;

    class VAO
    {
    private:
        GLuint vao_id;
        VBO* vbo;
        EBO* ebo;

    public:
        VAO(VBO& vbo) noexcept;
        VAO(VBO& vbo,EBO& ebo) noexcept;
        VAO(VAO&) = delete;
        ~VAO() noexcept;

        GLuint get_vao_id() const noexcept;
        void enable_attrib(uint32_t index,uint32_t len,uint32_t vertex_len,uint32_t offset,bool normalized = false) const noexcept;
        VBO* get_binding_vbo() const noexcept;
        EBO* get_binding_ebo() const noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
            {t.set_uniform(std::declval<std::string_view>(),
                std::declval<int>())} -> std::same_as<void>;
        }
        void draw(const T& t,GLenum primitive,GLint first,GLsizei vertex_count) noexcept
        {
            glUseProgram(t.get_program_id());

            glBindVertexArray(vao_id);
            glBindBuffer(GL_ARRAY_BUFFER,vbo->get_buffer_id());

            if (!ebo)
                glDrawArrays(primitive, first, vertex_count);
            else
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
                glDrawElements(primitive, vertex_count, GL_UNSIGNED_INT, 0);
            }

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
            glUseProgram(0);
        }
    };
}