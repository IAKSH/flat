#pragma once

#include "OpenGL/opengl_shader.hpp"
#include "object.hpp"
#include <memory>

namespace flat
{
    class RenderPipe
    {
    private:
        opengl::ShaderProgram shader;

    public:
        RenderPipe();
        ~RenderPipe();

        std::unique_ptr<Frame> ren_texture(const Texture& texture);
        std::unique_ptr<Frame> ren_frame(const Frame& frame);
    };

    class MixPipe
    {

    };
}