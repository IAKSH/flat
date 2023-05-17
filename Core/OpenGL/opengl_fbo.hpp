#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/logger.hpp"
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
        void use();
        void use_as_out();
        void use_as_read();
        unsigned int get_fbo_id() const;
        unsigned int get_texture_id() const;
    };
}