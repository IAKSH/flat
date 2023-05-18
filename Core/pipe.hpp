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
        RenderPipe(std::string_view vshader,std::string_view fshader);
        ~RenderPipe();

        std::unique_ptr<Frame> ren_texture(const Texture& texture) const;
        std::unique_ptr<Frame> ren_frame(const Frame& frame) const;
    };

    class MixPipe
    {

    };

    // TODO:
    constexpr std::string_view default_vertex_shader 
    {
        ""
    };

    // TODO:
    constexpr std::string_view default_fragment_shader
    {
        ""
    };

    extern std::unique_ptr<opengl::ShaderProgram> default_shader;
}