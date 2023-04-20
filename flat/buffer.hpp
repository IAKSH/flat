#pragma once

#include <deque>
#include <concepts>
#include <memory>

#include "../utils/animation.hpp"
#include "../utils/gameobj.hpp"
#include "../utils/logger.hpp"
#include "../utils/audio.hpp"
#include "../utils/camera.hpp"
#include "../utils/font.hpp"
#include "../flat/shader.hpp"
#include "../flat/text_renderer.hpp"

namespace ni::flat
{
    using ni::utils::Animation;
    using ni::utils::GameObject;
    using ni::utils::Logger;
    using ni::utils::Audio;
    using ni::utils::Camera2D;
    using ni::utils::Font;
    using ni::flat::Shader;
    using ni::flat::TextRenderer;

    class Buffer
    {
    public:
        virtual ~Buffer() {}
    };

    template <typename T>
    class SpecificBuffer : public Buffer
    {
    private:
        T t;

    public:
        template <typename... Args>
        SpecificBuffer(Args&&... args) : t(std::forward<Args>(args)...) {}
        virtual ~SpecificBuffer() override = default;
        operator T&() const {return t;}
    };

    class ResourceManager
    {
        using storage = std::deque<std::unique_ptr<Buffer>>;

    private:
        static storage animations;
        static storage gameobjects;
        static storage loggers;
        static storage audios;
        static storage soundEffects;
        static storage cameras;
        static storage fonts;
        static storage shader;
        static storage textRenderer;

    public:
        ResourceManager();
        ~ResourceManager();
    };
}