#pragma once

#include <cstdint>
#include <concepts>
#include <string_view>
#include <glad/glad.h>

// TODO: 需要大改 【实例化，多VBO，预分配，分块写入，UBO，SSBO】
// 实现VAO的多VBO挂载，VAO不在构造时绑定VBO，VAO不管理VBO的内存
// 实现Buffer的预分配和分块写入，同时保留整块写入API
// 实现Uniform Buffer Object (UBO)
// Shader也需要修改，以支持Uniform块到UBO的绑定
// 实现SSBO，同样也需要改Shader

// 其他目标：减少不必要的模板，在高动态领域使用虚继承

// 比较糟糕的一点是，之前的测试也需要重写。
// 这也意味着在重构过程中会缺少有效的测试

/*
Uniform缓冲对象比起独立的uniform有很多好处。
第一，一次设置很多uniform会比一个一个设置多个uniform要快很多。
第二，比起在多个着色器中修改同样的uniform，在Uniform缓冲中修改一次会更容易一些。
最后一个好处可能不会立即显现，如果使用Uniform缓冲对象的话，你可以在着色器中使用更多的uniform。
OpenGL限制了它能够处理的uniform数量，这可以通过GL_MAX_VERTEX_UNIFORM_COMPONENTS来查询。
当使用Uniform缓冲对象时，最大的数量会更高。
所以，当你达到了uniform的最大数量时（比如再做骨骼动画(Skeletal Animation)的时候），你总是可以选择使用Uniform缓冲对象。
*/

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

        void write_to_buffer(float* data,std::size_t size,GLenum mode) noexcept
        {
            store_mode = mode;
            auto write_buffer = [&]()
	        {
	        	glBindBuffer(buffer_type, buffer_id);
	        	glBufferData(buffer_type, size, data, static_cast<GLenum>(store_mode));
	        };

	        if (buffer_size == size)
	        	write_buffer();
	        else
	        {
	        	glDeleteBuffers(1, &buffer_id);
	        	glGenBuffers(1, &buffer_id);
	        	write_buffer();
	        	buffer_size = size;
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

        void bind_instance_array(const VBO& vbo, GLuint index, GLuint len,
            GLuint vertex_size, GLuint offset_size, GLuint divisor) const noexcept;
        void bind_instance_array(GLuint instance_vbo_id, GLuint index, GLuint len,
            GLuint vertex_size, GLuint offset_size, GLuint divisor) const noexcept;

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