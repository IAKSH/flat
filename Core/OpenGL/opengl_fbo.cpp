#include "opengl_fbo.hpp"
#include <exception>

flat::opengl::FrameBuffer::FrameBuffer(int w,int h)
{
    Scope scope;

    glGenFramebuffers(1,&fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);

    // create texture
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,nullptr);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    // bind texture to fbo
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture,0);

    // create rbo
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,w,h);
    // bind rbo to fbo
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);

    // check framebuffer
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        misc::main_logger->critical("OpenGL framebuffer not complete");
        std::terminate();
    }
}

flat::opengl::FrameBuffer::~FrameBuffer()
{
    glDeleteTextures(1,&texture);
    glDeleteRenderbuffers(1,&rbo);
    glDeleteFramebuffers(1,&fbo);
}

void flat::opengl::FrameBuffer::use() const
{
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
}

void flat::opengl::FrameBuffer::use_as_out() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,fbo);
}

void flat::opengl::FrameBuffer::use_as_read() const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER,fbo);
}

unsigned int flat::opengl::FrameBuffer::get_fbo_id() const
{
    return fbo;
}

unsigned int flat::opengl::FrameBuffer::get_texture_id() const
{
    return texture;
}