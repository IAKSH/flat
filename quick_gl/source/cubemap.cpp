#include <iostream>
#include <quick_gl/cubemap.hpp>

quick3d::gl::CubeMap::CubeMap(GLenum format,uint32_t w,uint32_t h) noexcept
    : width(w),height(h)
{
    switch (format)
    {
    case GL_R:
    case GL_RGB:
    case GL_RGBA:
        cubmap_format = format;
        break;

    default:
        std::cerr << "invalid cubemap foramt" << std::endl;
        std::terminate();
    }

    setup_cubemap();
}

quick3d::gl::CubeMap::~CubeMap() noexcept
{
    glDeleteTextures(1,&cubemap_id);
}

void quick3d::gl::CubeMap::mark_as_loaded(GLenum location) noexcept
{
    switch(location)
    {
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:    positive_x_complete = true; break;
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:    positive_y_complete = true; break;
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:    positive_z_complete = true; break;
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:    negative_x_complete = true; break;
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:    negative_y_complete = true; break;
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:    negative_z_complete = true; break;
    }
}

void quick3d::gl::CubeMap::setup_cubemap() noexcept
{
    glGenTextures(1,&cubemap_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubemap_id);
    // must pre-set the size of each texture2d in cubemap
    // or the fbo that this cubemap binding to will be incompete
    for(int i = 0;i < 6;i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,cubmap_format,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,nullptr);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

GLuint quick3d::gl::CubeMap::get_cubemap_id() const noexcept
{
    return cubemap_id;
}

uint32_t quick3d::gl::CubeMap::get_cubemap_width() const noexcept
{
    return width;
}

uint32_t quick3d::gl::CubeMap::get_cubemap_height() const noexcept
{
    return height;
}

bool quick3d::gl::CubeMap::is_cubemap_complete() const noexcept
{
    return positive_x_complete &&
        negative_x_complete &&
        positive_y_complete &&
        negative_y_complete &&
        positive_z_complete &&
        negative_z_complete;
}

void quick3d::gl::CubeMap::generate_texture(GLenum location,unsigned char* img_data,uint32_t img_channels) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubemap_id);

    GLenum img_format;
    switch (img_channels)
    {
    case 1: img_format = GL_R;    break;
    case 3: img_format = GL_RGB;  break;
    case 4: img_format = GL_RGBA; break;
    }

    glTexImage2D(location,0,cubmap_format,width,height,0,img_format,GL_UNSIGNED_BYTE,img_data);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    mark_as_loaded(location);
}