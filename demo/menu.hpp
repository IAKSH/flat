#pragma once

#include "../core/layer.hpp"
#include "../core/event_keyboard.hpp"
#include "../core/application.hpp"
#include "../utils/font.hpp"
#include "../utils/timer.hpp"
#include "../utils/opengl_shader.hpp"
#include "../utils/opengl_camera.hpp"
#include "../utils/opengl_vao.hpp"
#include "../flat/text_renderer.hpp"
#include "text.hpp"
#include "button.hpp"
#include <string_view>

namespace Flat
{
    using ni::core::Event;
    using ni::utils::Font;
    using ni::utils::opengl::GLBufferType;
    using ni::utils::opengl::RectVertexArray;
    using ni::utils::TimeRecorder;
    using ni::utils::opengl::ShaderProgram;
    using ni::flat::Color;
    using ni::flat::TextRenderer;
    using Texture = ni::utils::opengl::Texture<ni::utils::opengl::ColorChannelType::RGBA,ni::utils::opengl::ColorChannelType::RGBA>;
    using Camera = ni::utils::opengl::Camera;

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
        ShaderProgram shader;
        Font unifont48;
        Font unifont16;
        TextRenderer texRen;
        Camera cam;
        float camRotateSpeedUp {0.0f};
        float camRotateSpeedRight {0.0f};
        float camRollSpeed {0.0f};
        float camMoveSpeedUp {0.0f};
        float camMoveSpeedRight {0.0f};
        std::unique_ptr<Texture> background;
        std::unique_ptr<Texture> selectIcon;
        TimeRecorder recoder;
        TimeRecorder fpsRecoder;
        RectVertexArray<GLBufferType::Dynamic> vao;
        RollingText gameTitle{texRen,unifont16,MilliSeconds(100),U"Flat: a brief demo of engineNI's FLAT framework"};
        RollingText info0{texRen,unifont16,MilliSeconds(150),U"这是我在使用C++（几乎）从零构建一个2D甚至3D游戏的实验，它可以说是一堆实验特性的集合。"};
        RollingText info1{texRen,unifont16,MilliSeconds(175),U"FLAT framework是engineNI的基础，也是实际上构成游戏的部分，它是一套能够重复利用的代码。"};
        Text fpsInfo{texRen,unifont16,U""};
        BlinkingButton startButton{150.0f,35.0f,shader,texRen,cam,unifont48,MilliSeconds(500),U"按'Z'开始...",[](){
            ni::core::otherLogger->warn("game start!");
            // TODO: ...
        }};

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