#include <iostream>
#include <quick_gl/frame.hpp>

quick3d::gl::Framebuffer::Framebuffer(GLint width, GLint height) noexcept(false)
    : Framebuffer(GL_TEXTURE_2D, 0, width, height)
{
}

quick3d::gl::Framebuffer::Framebuffer(GLenum texture_type,GLuint tex_id,GLint width,GLint height) noexcept(false)
{
    create_fbo_and_rbo(width,height);
    bind_texture_to_fbo(texture_type,tex_id);

    //glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    //if(!(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE))
    //    throw std::runtime_error(std::format("fbo {} incomplete",fbo_id));
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

quick3d::gl::Framebuffer::~Framebuffer() noexcept
{
    delete_fbo_and_rbo();
}

void quick3d::gl::Framebuffer::create_fbo_and_rbo(GLint width,GLint height) noexcept
{
    glGenFramebuffers(1, &fbo_id);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

	glGenRenderbuffers(1, &rbo_id);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void quick3d::gl::Framebuffer::bind_texture_to_fbo(GLenum texture_type,GLuint id) noexcept
{
    switch (texture_type)
    {
    case GL_TEXTURE_2D:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        break;

    default:
        std::cerr << "bind_texture_to_fbo(): invalid texture_type" << std::endl;
        std::terminate();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_type, id, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    tex_id = id;
}

void quick3d::gl::Framebuffer::delete_fbo_and_rbo() noexcept
{
    glDeleteRenderbuffers(1, &rbo_id);
	glDeleteFramebuffers(1, &fbo_id);
}

GLint quick3d::gl::Framebuffer::get_width() const noexcept
{
    GLint width;
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return width;
}

GLint quick3d::gl::Framebuffer::get_height() const noexcept
{
    GLint height;
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return height;
}

GLuint quick3d::gl::Framebuffer::get_fbo_id() const noexcept
{
    return fbo_id;
}

GLuint quick3d::gl::Framebuffer::get_binding_tex_id() const noexcept
{
    return tex_id;
}
