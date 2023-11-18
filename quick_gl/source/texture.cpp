#include <iostream>
#include <quick_gl/texture.hpp>

quick3d::gl::Texture::Texture(GLenum tex_format, uint32_t tex_width, uint32_t tex_height, bool enable_rtti) noexcept
    : tex_format(tex_format), enable_rtti(enable_rtti), tex_width(tex_width), tex_height(tex_height)
{
    GLenum img_format{ GL_RED };
    if (tex_format == GL_DEPTH_COMPONENT)
        img_format = GL_DEPTH_COMPONENT;
    else if (tex_format == GL_STENCIL_INDEX)
        img_format = GL_STENCIL_INDEX;
    generate_texture(img_format,nullptr,tex_width,tex_height);
}

quick3d::gl::Texture::Texture(GLenum tex_format, GLuint tex_id, bool enable_rtti) noexcept
    : tex_format(tex_format), tex_id(tex_id), enable_rtti(enable_rtti), tex_width(0), tex_height(0)
{
}

quick3d::gl::Texture::Texture(GLenum tex_format, GLenum img_format, unsigned char* img_data, uint32_t img_width, uint32_t img_height, bool enable_rtti) noexcept
    : tex_format(tex_format), enable_rtti(enable_rtti), tex_width(img_width), tex_height(img_height)
{
    generate_texture(img_format,img_data,img_width,img_height);
}

quick3d::gl::Texture::~Texture() noexcept
{
    if(enable_rtti)
        delete_texture();
}

void quick3d::gl::Texture::generate_texture(GLenum img_format,unsigned char* img_data,uint32_t img_width,uint32_t img_height) noexcept
{
    glGenTextures(1,&tex_id);
    glBindTexture(GL_TEXTURE_2D,tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,tex_format,img_width,img_height,0,img_format,GL_UNSIGNED_BYTE,img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);
}

void quick3d::gl::Texture::delete_texture() noexcept
{
    glDeleteTextures(1,&tex_id);
}

GLuint quick3d::gl::Texture::get_tex_id() const noexcept
{
    return tex_id;
}

GLint quick3d::gl::Texture::get_tex_width() const noexcept
{
    return tex_width;
}

GLint quick3d::gl::Texture::get_tex_height() const noexcept
{
    return tex_height;
}

GLenum quick3d::gl::Texture::get_tex_format() const noexcept
{
    return tex_format;
}

