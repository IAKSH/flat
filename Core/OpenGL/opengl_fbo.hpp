#pragma once

#include "../../misc/disable_copy.hpp"
#include "../../misc/logger.hpp"
#include "opengl_texture.hpp"
#include "opengl_scope.hpp"
#include <glad/glad.h>

namespace flat::opengl
{
    class FrameBuffer : misc::DisableCopy
    {
    private:
        unsigned int fbo;
        unsigned int rbo;
        unsigned int texture;

    public:
        FrameBuffer(int w,int h);
        ~FrameBuffer();
        void use() const;
        void use_as_out() const;
        void use_as_read() const;
        unsigned int get_fbo_id() const;
        unsigned int get_texture_id() const;
    };
}