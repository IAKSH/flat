#include <iostream>
#include <quick_gl/texture.hpp>

quick3d::gl::Texture::Texture(GLenum tex_format,uint32_t tex_width,uint32_t tex_height,bool enable_rtti) noexcept
    : enable_rtti(enable_rtti)
{
    set_tex_format(tex_format);
    generate_texture(GL_RGBA,nullptr,tex_width,tex_height);
}

quick3d::gl::Texture::Texture(GLenum tex_format,GLuint tex_id,bool enable_rtti) noexcept
    : tex_id(tex_id),enable_rtti(enable_rtti)
{
    set_tex_format(tex_format);
}

quick3d::gl::Texture::Texture(GLenum tex_format,GLenum img_format,unsigned char* img_data,uint32_t img_width,uint32_t img_height,bool enable_rtti) noexcept
    : enable_rtti(enable_rtti)
{
    set_tex_format(tex_format);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,tex_id);

    glTexImage2D(GL_TEXTURE_2D,0,tex_format,img_width,img_height,0,img_format,GL_UNSIGNED_BYTE,img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);
}

void quick3d::gl::Texture::delete_texture() noexcept
{
    glDeleteTextures(1,&tex_id);
}

void quick3d::gl::Texture::set_tex_format(GLenum format) noexcept
{
    switch (format)
    {
    case GL_RED:
    case GL_RGB:
    case GL_RGBA:
        tex_format = format;
        break;

    default:
        std::cerr << "invalid texture foramt" << std::endl;
        std::terminate();
    }
}

GLint quick3d::gl::Texture::get_tex_width() const noexcept
{
    GLint width;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    return width;
}

GLint quick3d::gl::Texture::get_tex_height() const noexcept
{
    GLint height;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    return height;
}

GLenum quick3d::gl::Texture::get_tex_format() const noexcept
{
    GLenum format;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, reinterpret_cast<GLint*>(&format));
    return format;
}

