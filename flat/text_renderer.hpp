#pragma once

#include "color.hpp"
#include "scale.hpp"
#include "../utils/font.hpp"
#include "../utils/physics.hpp"
#include "../core/template.hpp"
#include "../utils/opengl_shader.hpp"
#include "../utils/opengl_camera.hpp"
#include "../utils/opengl_vao.hpp"
#include <string>
#include <string_view>

namespace ni::flat
{
    template<typename... Args>
    struct ContainsU32string_view : std::false_type {};

    template<typename T, typename... Rest>
    struct ContainsU32string_view<T, Rest...> : 
        std::conditional_t<std::is_same_v<T, std::u32string_view>, std::true_type, ContainsU32string_view<Rest...>> {};

    template <typename T>
    concept DrawTextArg = ::ni::core::anySame<T,Color,ni::utils::Point,
        ni::utils::Point,std::u32string_view,utils::Font*,ni::utils::opengl::FPSCamera>() ;

    class TextRenderer : public ::ni::core::DisableCopy
    {
        using Font = ::ni::utils::Font;
        using ShaderProgram = ::ni::utils::opengl::ShaderProgram;
        using CharTexture = ::ni::utils::CharTexture;
        using Camera = ::ni::utils::opengl::FPSCamera;
        using GLBufferType = ::ni::utils::opengl::GLBufferType;
        using Point = ::ni::utils::Point;
        template <GLBufferType T>
        using RectVertexArray = ::ni::utils::opengl::RectVertexArray<T>;

    private:
        float x,y,scale;
        float viewWidth,viewHeight;
        Font* font;
        Camera* cam;
        ShaderProgram shader;
        RectVertexArray<GLBufferType::Dynamic> vao;
        std::u32string str;
        std::array<float,36> vertices;
        std::array<unsigned int, 6> indices;
        static constexpr std::string_view const vshaderSource =
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
        static constexpr std::string_view const fshaderSource =
            "#version 330 core\n"
            "uniform sampler2D texture0;\n"
            "in vec2 aTexCoordOut;\n"
            "in vec4 aColorOut;\n"
            "out vec4 FragColor;\n"
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