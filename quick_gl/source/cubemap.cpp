#include <iostream>
#include <quick_gl/cubemap.hpp>

quick3d::gl::CubeMap::CubeMap(GLenum cubemap_format, uint32_t w, uint32_t h) noexcept
    : cubemap_format(cubemap_format), width(w), height(h)
{
    pre_alloc_cubemap();
}

quick3d::gl::CubeMap::CubeMap(GLenum cubemap_format, GLenum pre_alloc_format, uint32_t w, uint32_t h) noexcept
    : cubemap_format(cubemap_format), width(w), height(h)
{
    pre_alloc_cubemap(pre_alloc_format);
}

quick3d::gl::CubeMap::~CubeMap() noexcept
{
    glDeleteTextures(1, &cubemap_id);
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

void quick3d::gl::CubeMap::pre_alloc_cubemap(GLenum pre_alloc_format) noexcept
{
    glGenTextures(1,&cubemap_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubemap_id);
    // must pre-set the size of each texture2d in cubemap
    // or the fbo that this cubemap binding to will be incompete
    for (int i = 0; i < 6; i++)
    {
        if(pre_alloc_format == GL_DEPTH_COMPONENT)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, cubemap_format, width, height, 0, pre_alloc_format, GL_FLOAT, nullptr);
        else
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, cubemap_format, width, height, 0, pre_alloc_format, GL_UNSIGNED_BYTE, nullptr);
    }
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

quick3d::gl::ColorCubeMap::ColorCubeMap(GLenum format, uint32_t w, uint32_t h) noexcept
    : CubeMap(format, w, h)
{
}

void quick3d::gl::ColorCubeMap::generate_texture(GLenum location,unsigned char* img_data,uint32_t img_channels) noexcept
{
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP,cubemap_id);

    GLenum img_format;
    switch (img_channels)
    {
    case 1: img_format = GL_LUMINANCE;    break;
    case 3: img_format = GL_RGB;  break;
    case 4: img_format = GL_RGBA; break;
    }

    glTexImage2D(location,0,cubemap_format,width,height,0,img_format,GL_UNSIGNED_BYTE,img_data);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    mark_as_loaded(location);
}

quick3d::gl::DepthCubeMap::DepthCubeMap(uint32_t w, uint32_t h) noexcept
    : CubeMap(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, w, h)
{
}