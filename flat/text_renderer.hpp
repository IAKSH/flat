#pragma once

#include <string>
#include <string_view>

#include "../utils/shader.hpp"
#include "../utils/font.hpp"
#include "../utils/vao.hpp"
#include "../utils/camera.hpp"
#include "any_same.hpp"
#include "dtype.hpp"

namespace ni::flat
{
    template<typename... Args>
    struct ContainsU32string_view : std::false_type {};

    template<typename T, typename... Rest>
    struct ContainsU32string_view<T, Rest...> : 
        std::conditional_t<std::is_same_v<T, std::u32string_view>, std::true_type, ContainsU32string_view<Rest...>> {};

    template <typename T>
    concept DrawTextArg = any_same<T,Color,Point,Scale,std::u32string_view,utils::Font*,utils::Camera2D*>() ;

    class TextRenderer
    {
        using Font = ::ni::utils::Font;
        using Shader = ::ni::utils::Shader;
        using VertexBuffer = ::ni::utils::VertexArrayObj;
        using CharTexture = ::ni::utils::CharTexture;
        using Camera = ::ni::utils::Camera2D;

    private:
        float x,y,scale;
        Font* font;
        Camera* cam;
        Shader shader;
        VertexBuffer vao;
        std::u32string str;
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
        void setDrawColor(const Color& color);
        void setDrawPosition();

        template <typename T>
        void drawTextHelper(T&& arg);
        void drawTextHelper(Color&& color);
        void drawTextHelper(Point&& point);
        void drawTextHelper(Scale&& scale);
        void drawTextHelper(Font* font);
        void drawTextHelper(Camera* cam);
        void drawTextHelper(std::u32string_view str);
        void _drawText();

    public:
        TextRenderer();
        TextRenderer(TextRenderer&) = delete;
        ~TextRenderer() = default;

        template <DrawTextArg... Args>
        void drawText(Args... args)
        {
            (drawTextHelper(std::forward<Args>(args)), ...);
            if constexpr (ContainsU32string_view<Args...>::value)
                _drawText();
        }
    };
}