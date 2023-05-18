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
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "out vec2 aTexCoordOut;\n"
        "out vec4 aColorOut;\n"
        "uniform mat4 transform;\n"
        "uniform mat4 camTrans;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = camTrans * transform * vec4(aPos, 1.0f);\n"
        "    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
        "    aColorOut = aColor;\n"
        "}\0"
    };

    // TODO:
    constexpr std::string_view default_fragment_shader
    {
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 aTexCoordOut;\n"
        "in vec4 aColorOut;\n"
        "uniform sampler2D texture0;\n"
        "void main()\n"
        "{\n"
        "    vec4 texColor = texture(texture0,aTexCoordOut);\n"
        "    FragColor = texColor * aColorOut;\n"
        "}\n\0"
    };

    extern std::unique_ptr<opengl::ShaderProgram> default_shader;
}