#include <quick_gl/vertex.hpp>

quick3d::gl::VAO::VAO(VBO& vbo) noexcept
    : vbo(&vbo),ebo(nullptr)
{
    glGenVertexArrays(1,&vao_id);
}

quick3d::gl::VAO::VAO(VBO& vbo,EBO& ebo) noexcept
    : vbo(&vbo),ebo(&ebo)
{
    glGenVertexArrays(1,&vao_id);
}

quick3d::gl::VAO::~VAO() noexcept
{
    glDeleteVertexArrays(1,&vao_id);
}

GLuint quick3d::gl::VAO::get_vao_id() const noexcept
{
    return vao_id;
}

void quick3d::gl::VAO::enable_attrib(uint32_t index,uint32_t len,uint32_t vertex_len,uint32_t offset,bool normalized) const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER,vbo->get_buffer_id());
    glBindVertexArray(vao_id);

	glVertexAttribPointer(index, len, GL_FLOAT, normalized, vertex_len * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(index);
            
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

quick3d::gl::VBO* quick3d::gl::VAO::get_binding_vbo() const noexcept
{
    return vbo;
}

quick3d::gl::EBO* quick3d::gl::VAO::get_binding_ebo() const noexcept
{
    return ebo;
}