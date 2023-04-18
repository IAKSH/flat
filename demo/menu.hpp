#pragma once

#include "../core/layer.hpp"
#include "../core/event_keyboard.hpp"
#include "../core/application.hpp"
#include "../utils/camera.hpp"
#include "../utils/font.hpp"
#include "../utils/timer.hpp"
#include "../utils/shader.hpp"
#include "../utils/rectangle_vao.hpp"
#include "../flat/text_renderer.hpp"

#include "text.hpp"

namespace Flat
{
    using ni::core::Event;
    using ni::utils::Camera2D;
    using ni::utils::Font;
    using ni::utils::Color;
    using ni::utils::Texture;
    using ni::utils::GLBufferType;
    using ni::utils::VertexBuffer;
    using ni::utils::TimeRecorder;
    using ni::flat::Shader;
    using ni::flat::UniformArg;
    using ni::flat::TextRenderer;

    inline static const char* vshader =
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
        "    gl_Position =  camTrans * transform * vec4(aPos, 1.0f);\n"
        "    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
        "    aColorOut = aColor;\n"
        "}\0";

    inline static const char* fshader =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 aTexCoordOut;\n"
        "in vec4 aColorOut;\n"
        "uniform sampler2D texture0;\n"
        "void main()\n"
        "{\n"
        "    vec4 texColor = texture(texture0,aTexCoordOut);\n"
        "    FragColor = texColor * aColorOut;\n"
        "}\n\0";

    class MenuLayer : public ni::core::Layer
    {
    private:
        Shader shader;
        Font unifont;
        TextRenderer texRen;
        Camera2D cam;
        Texture background;
        Texture selectIcon;
        TimeRecorder recoder;
        VertexBuffer<ni::utils::GLBufferType::Dynamic> vao;
        Text gameTitle{texRen,MilliSeconds(100),U"Flat: a brief demo of engineNI's FLAT framework"};

    public:
        MenuLayer();
        ~MenuLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onRender() override;
        virtual void onEvent(Event& e) override;
    };
}