#include <vector>
#include <iostream>
#include <quick_gl/frame.hpp>

quick3d::gl::ColorFramebuffer::ColorFramebuffer(GLint width, GLint height) noexcept(false)
{
    setup_rbo(width, height);
    bind_texture_to_fbo(0);
}

quick3d::gl::ColorFramebuffer::ColorFramebuffer(GLuint tex_id, GLint width, GLint height) noexcept(false)
    : tex_id(tex_id)
{
    setup_rbo(width,height);
    bind_texture_to_fbo(tex_id);
    //if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE))
    //    throw std::runtime_error(std::format("fbo {} incomplete", fbo_id));
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

void quick3d::gl::ColorFramebuffer::set_draw_targets(const std::initializer_list<GLenum>& targets) noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

    std::vector<GLenum> _targets(targets);
    glDrawBuffers(_targets.size(), _targets.data());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void quick3d::gl::ColorFramebuffer::bind_texture_to_fbo(GLuint id) noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    tex_id = id;
}

void quick3d::gl::ColorFramebuffer::bind_texture_to_fbo(GLenum target, GLuint id) noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D, id, 0);
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

void quick3d::gl::DepthFramebuffer::bind_cubemap_depth_attachment(GLuint depth_attachment_id) noexcept
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, depth_attachment_id);
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
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void quick3d::gl::DepthFramebuffer::bind_texture_depth_attachment(GLuint depth_attachment_id) noexcept
{
    glBindTexture(GL_TEXTURE_2D, depth_attachment_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_attachment_id, 0);
    GLenum flags[]{ GL_NONE };
    glDrawBuffers(1, flags);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}