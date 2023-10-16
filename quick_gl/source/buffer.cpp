#include <quick_gl/buffer.hpp>

bool quick3d::gl::Buffer::verifiy_target(GLenum target) const noexcept
{
    bool flag{ true };
    switch (target)
    {
    case GL_ARRAY_BUFFER:           // VBO
    case GL_ELEMENT_ARRAY_BUFFER:   // EBO
    case GL_UNIFORM_BUFFER:         // UBO
    case GL_SHADER_STORAGE_BUFFER:  // SSBO
    case GL_PIXEL_PACK_BUFFER:      // pack PBO
    case GL_PIXEL_UNPACK_BUFFER:    // unpack PBO
    case GL_TEXTURE_BUFFER:         // TBO
        break;
    default:
        flag = false;
    }
    return flag;
}

bool quick3d::gl::Buffer::verifiy_usage(GLenum usage) const noexcept
{
    bool flag{ true };
    switch (usage)
    {
    case GL_STATIC_DRAW:
    case GL_DYNAMIC_DRAW:
    case GL_STREAM_DRAW:
        break;
    default:
        flag = false;
    }
    return flag;
}

quick3d::gl::Buffer::Buffer(GLenum target, GLenum usage, GLsizeiptr size) noexcept(false)
{
    if (!verifiy_target(target))
        throw std::invalid_argument(std::format("invalied buffer target: 0x{:X}", target));
    if (!verifiy_usage(usage))
        throw std::invalid_argument(std::format("invalied buffer usage: 0x{:X}", usage));

    gen_buffer_id();
    pre_allocate_mem(size);
}

quick3d::gl::Buffer::Buffer(Buffer& src, GLsizeiptr new_size) noexcept
{
    // TODO: copy
}

quick3d::gl::Buffer::~Buffer() noexcept
{
    delete_buffer();
}

void quick3d::gl::Buffer::gen_buffer_id() noexcept
{
    glGenBuffers(1, &buffer_id);
}

void quick3d::gl::Buffer::pre_allocate_mem(GLsizeiptr size) noexcept
{
    glBufferData(buffer_target, size, nullptr, buffer_usage);
}

void quick3d::gl::Buffer::delete_buffer() noexcept
{
    glDeleteBuffers(1, &buffer_id);
}

GLuint quick3d::gl::Buffer::get_buffer_id() const noexcept
{
    return buffer_id;
}

GLsizeiptr quick3d::gl::Buffer::get_buffer_size() const noexcept
{
    GLsizeiptr size;
    glBindBuffer(buffer_target, buffer_id);
    glGetBufferParameteri64v(buffer_target, GL_BUFFER_SIZE, &size);
    glBindBuffer(buffer_target, 0);
    return size;
}

GLenum quick3d::gl::Buffer::get_buffer_target() const noexcept
{
    return buffer_target;
}

GLenum quick3d::gl::Buffer::get_buffer_usage() const noexcept
{
    return buffer_usage;
}

void quick3d::gl::Buffer::set_buffer_target(GLenum new_target) noexcept(false)
{
    if (!verifiy_target(new_target))
        throw std::runtime_error(std::format("invalid new buffer target: 0x{:X}", new_target));

    buffer_target = new_target;
}

void quick3d::gl::Buffer::load_buffer_data(const void* data, GLintptr offset, GLsizeiptr size) noexcept
{
    glBindBuffer(buffer_target, buffer_id);
    glBufferSubData(buffer_target, offset, size, data);
    glBindBuffer(buffer_target, 0);
}

void quick3d::gl::Buffer::dma_do(std::function<void(void* data)> callback,GLintptr offset , GLsizeiptr length, GLbitfield access) noexcept
{
    glBindBuffer(buffer_target, buffer_id);
    GLvoid* mapping_ptr{ glMapBufferRange(buffer_target, offset, length, access) };
    callback(mapping_ptr);
    glUnmapBuffer(buffer_target);
    glBindBuffer(buffer_target, 0);
}

void quick3d::gl::Buffer::dma_do(std::function<void(void* data)> callback) noexcept
{
    dma_do(callback, 0, get_buffer_size(), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}