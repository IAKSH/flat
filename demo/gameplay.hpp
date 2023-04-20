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
#include "button.hpp"
#include <string_view>

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
    
    class GamePlay : public ni::core::Layer
    {
    private:

    public:
        GamePlay();
        ~GamePlay() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onRender() override;
        virtual void onEvent(Event& e) override;
    };
}