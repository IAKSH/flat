#pragma once

#include <string>
#include <string_view>

#include "../utils/font.hpp"
#include "../utils/vao.hpp"
#include "../utils/camera.hpp"
#include "any_same.hpp"
#include "shader.hpp"
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
        using Shader = ::ni::flat::Shader;
        using VertexBuffer = ::ni::utils::VertexArrayObj;
        using CharTexture = ::ni::utils::CharTexture;
        using Camera = ::ni::utils::Camera2D;

    private:
        float x,y,scale;
        float viewWidth,viewHeight;
        Font* font;
        Camera* cam;
        Shader shader;
        VertexBuffer vao;
        std::u32string str;
        std::array<float,36> vertices;
        std::array<unsigned int, 6> indices;
        const char* const vshaderSource =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec4 aColor;\n"
            "layout (location = 2) in vec2 aTexCoord;\n"
            "\n"
            "uniform mat4 camTrans;\n"
            "out vec4 aColorOut;\n"
            "out vec2 aTexCoordOut;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position =  camTrans * vec4(aPos.xy,0.9f, 1.0f);\n"
            "    aColorOut = aColor;\n"
            "    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
            "}\0";
        const char* const fshaderSource =
            "#version 330 core\n"
            "uniform sampler2D texture0; // 纹理采样器\n"
            "in vec2 aTexCoordOut; // 输入的纹理坐标\n"
            "in vec4 aColorOut;\n"
            "out vec4 FragColor; // 输出的颜色\n"
            "\n"
            "void main()\n"
            "{\n"
            "    float alpha = texture(texture0, aTexCoordOut).r;\n"
            "    vec3 grayScale = vec3(alpha);\n"
            "    FragColor = vec4(aColorOut.rgb * grayScale, alpha * aColorOut.a);\n"
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

        void setViewWidth(const float& val) { viewWidth = val; }
        void setViewHeight(const float& val) { viewHeight = val; }
        const float& getViewWidth() { return viewWidth; }
        const float& getViewHeight() { return viewHeight; }

        template <DrawTextArg... Args>
        void drawText(Args... args)
        {
            (drawTextHelper(std::forward<Args>(args)), ...);
            if constexpr (ContainsU32string_view<Args...>::value)
                _drawText();
        }
    };
}