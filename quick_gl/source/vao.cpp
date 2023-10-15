#include <quick_gl/vao.hpp>

void quick3d::gl::VertexArray::create_vao() noexcept
{
	glGenVertexArrays(1, &vao_id);
}

void quick3d::gl::VertexArray::delete_vao() noexcept
{
	glDeleteVertexArrays(1, &vao_id);
}

quick3d::gl::VertexArray::VertexArray() noexcept
	: has_ebo(false)
{
	create_vao();
}

quick3d::gl::VertexArray::~VertexArray() noexcept
{
	delete_vao();
}

GLuint quick3d::gl::VertexArray::get_vao_id() const noexcept
{
	return GLuint();
}

void quick3d::gl::VertexArray::bind_ebo(GLuint ebo_id) noexcept
{
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	// unbind vao before you unbind ebo
	// because the binding vao will record any bind/unbind on GL_ELEMENT_ARRAY_BUFFER
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	has_ebo = true;
}

void quick3d::gl::VertexArray::add_attrib(GLenum buffer_target, uint32_t buffer_id,
	uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized) noexcept(false)
{
	//if (buffer_target != GL_ARRAY_BUFFER)
	//	throw std::runtime_error("invalid buffer target given to VAO");

	glBindBuffer(buffer_target, buffer_id);
	glBindVertexArray(vao_id);

	glVertexAttribPointer(index, len, GL_FLOAT, normalized, vertex_len * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(index);

	glBindBuffer(buffer_target, 0);
	glBindVertexArray(0);
}

void quick3d::gl::VertexArray::draw(GLuint program_id, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance) noexcept
{
	glUseProgram(program_id);
	glBindVertexArray(vao_id);

	// no need to bind vbo(s) and ebo here
	// because vao had recorded them before

	if (has_ebo)
		if (instance)
			glDrawElementsInstanced(primitive, vertex_count, GL_UNSIGNED_INT, 0, instance);
		else
			glDrawElements(primitive, vertex_count, GL_UNSIGNED_INT, 0);
	else
		if (instance)
			glDrawArraysInstanced(primitive, first, vertex_count, instance);
		else
			glDrawArrays(primitive, first, vertex_count);

	glBindVertexArray(0);
	glUseProgram(0);
}
