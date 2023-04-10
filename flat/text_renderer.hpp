#pragma once

#include <string>

#include "../utils/shader.hpp"
#include "../utils/font.hpp"
#include "../utils/vao.hpp"

namespace ni::flat
{

    class TextRenderer
    {
        using Font = ::ni::utils::Font;
        using Shader = ::ni::utils::Shader;
        using VertexBuffer = ::ni::utils::VertexArrayObj;
        using CharTexture = ::ni::utils::CharTexture;

    private:
        Shader shader;
        VertexBuffer vao;
        std::array<float,36> vertices;
        std::array<unsigned int, 6> indices;
        const char* const vshaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
            "out vec2 TexCoords;\n"
            "\n"
            "uniform mat4 projection;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
            "    TexCoords = vertex.zw;\n"
            "}\0";
        const char* const fshaderSource =
            "#version 330 core\n"
            "in vec2 TexCoords;\n"
            "out vec4 color;\n"
            "\n"
            "uniform sampler2D text;\n"
            "uniform vec3 textColor;\n"
            "\n"
            "void main()\n"
            "{    \n"
            "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
            "    color = vec4(textColor, 1.0) * sampled;\n"
            "}\0";

        void initialize();

    public:
        TextRenderer();
        TextRenderer(TextRenderer&) = delete;
        ~TextRenderer() = default;

        void drawText(std::u32string_view str,const float& x,const float& y,const float& z,const float& r,const float& g,const float& b,const float& a,const float& scale,Font& font);
    };
}