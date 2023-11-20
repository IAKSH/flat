#pragma once

#include <concepts>
#include <stdexcept>
#include <glad/gles2.h>

namespace quick3d::gl
{
	class VertexArray
	{
	private:
		GLuint vao_id;
		bool has_ebo;

		void create_vao() noexcept;
		void delete_vao() noexcept;

	public:
		VertexArray() noexcept;
		VertexArray(VertexArray&) = delete;
		~VertexArray() noexcept;

		GLuint get_vao_id() const noexcept;

		void bind_ebo(GLuint ebo_id) noexcept;

		template <typename T>
			requires requires(T t)
		{
			{t.get_buffer_id()} -> std::same_as<GLuint>;
			{t.get_buffer_target()} -> std::same_as<GLenum>;
		}
		void bind_ebo(const T& t) noexcept(false)
		{
			if (t.get_buffer_target() != GL_ELEMENT_ARRAY_BUFFER)
				throw std::runtime_error("invalid buffer target for vao::bind_ebo()");

			bind_ebo(t.get_buffer_id());
		}

		// TODO: 需要开放更多API，比如参数的具体类型，主要是确定VAO属性的大小，详见glVertexAttribPointer的参数列表
		// 也许可以用模板实现
		void add_attrib(GLenum buffer_target, uint32_t buffer_id,
			uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized = false) noexcept(false);

		template <typename T>
		requires requires(T t)
		{
			{t.get_buffer_id()} -> std::same_as<GLuint>;
			{t.get_buffer_target()} -> std::same_as<GLenum>;
		}
		void add_attrib(T& t, uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized = false) noexcept(false)
		{
			add_attrib(t.get_buffer_target(), t.get_buffer_id(), index, len, vertex_len, offset, normalized);
		}

		void draw(GLuint program_id, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance = 0) noexcept;

		template <typename T>
			requires requires(T t)
		{
			{t.get_program_id()} -> std::same_as<GLuint>;
		}
		void draw(const T& t, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance = 0) noexcept
		{
			draw(t.get_program_id(), primitive, first, vertex_count, instance);
		}
	};
}