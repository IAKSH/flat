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

    private:
        Shader shader;
        VertexBuffer vao;
        std::array<float,36> vertices;
        std::array<unsigned int, 6> indices;
        const char* const vshaderSource = 
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec4 aColor;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "uniform mat4 projTrans;\n"
            "out vec2 aTexCoordOut;\n"
            "out vec4 aColorOut;\n"
            "void main()\n"
            "{\n"
            "    gl_Position =  projTrans * vec4(aPos, 1.0f);\n"
            "    aTexCoordOut = vec2(aTexCoord.x - 1.0, 1.0f - aTexCoord.y);\n"
            "    aColorOut = aColor;\n"
            "}\n";
        const char* const fshaderSource = "#version 330 core\n"
            "uniform sampler2D texture0;\n"
            "in vec4 aColorOut;\n"
            "in vec2 aTexCoordOut;\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    float alpha = texture(texture0, aTexCoordOut).r;\n"
            "    vec3 grayScale = vec3(alpha);\n"
            "    FragColor = vec4(aColorOut.rgb * grayScale, alpha * aColorOut.a);\n"
            "}\n";

        void initialize();

    public:
        TextRenderer();
        TextRenderer(TextRenderer&) = delete;
        ~TextRenderer() = default;

        void drawText(std::u32string_view str,const float& x,const float& y,const float& r,const float& g,const float& b,const float& a,const float& z,const float& scale,Font& font);
    };
}