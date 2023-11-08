#include <iostream>
#include <quick_gl/frame.hpp>

quick3d::gl::ColorFramebuffer::ColorFramebuffer(GLint width, GLint height) noexcept(false)
    : ColorFramebuffer(GL_TEXTURE_2D, 0, width, height)
{
}

quick3d::gl::ColorFramebuffer::ColorFramebuffer(GLenum texture_type,GLuint tex_id,GLint width,GLint height) noexcept(false)
{
    setup_rbo(width,height);
    bind_texture_to_fbo(texture_type,tex_id);
}

quick3d::gl::ColorFramebuffer::~ColorFramebuffer() noexcept
{
    delete_rbo();
}

void quick3d::gl::Framebuffer::create_fbo() noexcept
{
    glGenFramebuffers(1, &fbo_id);
}

void quick3d::gl::Framebuffer::delete_fbo() noexcept
{
    glDeleteFramebuffers(1, &fbo_id);
}

quick3d::gl::Framebuffer::Framebuffer() noexcept
{
    create_fbo();
}

quick3d::gl::Framebuffer::~Framebuffer() noexcept
{
    delete_fbo();
}

void quick3d::gl::ColorFramebuffer::setup_rbo(GLint width,GLint height) noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

	glGenRenderbuffers(1, &rbo_id);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_id);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void quick3d::gl::ColorFramebuffer::bind_texture_to_fbo(GLenum texture_type,GLuint id) noexcept
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

void quick3d::gl::ColorFramebuffer::delete_rbo() noexcept
{
    glDeleteRenderbuffers(1, &rbo_id);
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

GLuint quick3d::gl::ColorFramebuffer::get_binding_tex_id() const noexcept
{
    return tex_id;
}

void quick3d::gl::DepthFramebuffer::bind_depth_attachment(GLuint depth_attachment_id) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment_id, 0);
    GLenum flags[]{ GL_NONE };
    glDrawBuffers(1, flags);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

quick3d::gl::DepthFramebuffer::DepthFramebuffer(GLuint depth_attachment_id) noexcept
{
    bind_depth_attachment(depth_attachment_id);
}
