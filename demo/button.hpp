#pragma once
#include "../utils/gameobj.hpp"
#include "../utils/timer.hpp"
#include "../flat/text_renderer.hpp"
#include "../utils/opengl_texture.hpp"
#include "../utils/opengl_shader.hpp"
#include "../utils/opengl_vao.hpp"
#include "../utils/image.hpp"
#include "text.hpp"
#include <functional>
#include <memory>
#include <string>
#include <string_view>

namespace Flat
{
    using ni::utils::Font;
    using ni::utils::TimeRecorder;
    using ni::utils::MilliSeconds;
    using ni::utils::opengl::ShaderProgram;
    using ni::utils::opengl::GLBufferType;
    using ni::utils::opengl::RectVertexArray;
    using ni::flat::TextRenderer;

    using Texture = ni::utils::opengl::Texture<ni::utils::opengl::ColorChannelType::RGBA,ni::utils::opengl::ColorChannelType::RGBA>;
    using Camera = ni::utils::opengl::FPSCamera;

    class Button : public ni::utils::GameObject
    {
    protected:
        float width,height;
        bool actived;
        ShaderProgram& shader;
        TextRenderer& ren;
        Camera& cam;
        Font& font;
        RectVertexArray<GLBufferType::Static> vao;
        std::function<void(void)> callback;
        Text text{ren,font,U""};
        inline static std::unique_ptr<Texture> blackTex;

    public:
        Button(const float& w,const float h,ShaderProgram& shader,TextRenderer& texRen,Camera& cam,Font& font,std::u32string_view str,std::function<void(void)> callback);
        ~Button() = default;
        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onRender() override;
        virtual void onEvent(ni::core::Event& e) override;

        void active() {actived = true;}
        void inactive() {actived = false;}
    };

    class BlinkingButton : public Button
    {
    private:
        TimeRecorder recoder;
        MilliSeconds interval;

    public:
        BlinkingButton(const float& w,const float h,ShaderProgram& shader,TextRenderer& texRen,Camera& cam,Font& font,const MilliSeconds& interval,std::u32string_view str,std::function<void(void)> callback);
        ~BlinkingButton() = default;
        void onUpdate() override;
    };
}