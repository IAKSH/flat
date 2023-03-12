#pragma once

#include <array>
#include <iostream>

#include <flat_al/audio.hpp>
#include <flat_gl/window.hpp>
#include <flat_gjk/gjk.hpp>
#include <utility>

namespace flappy
{

    class BackGround
    {
    public:
        BackGround();
        ~BackGround() = default;
        flat::AudioSource&& source = std::move(flat::al::Source());
        flat::Texture&& texture =  std::move(flat::gl::Texture());
        flat::Rectangle&& rectangle = std::move(flat::gl::Rectangle());
        flat::Hitbox2D&& hitbox = std::move(flat::gjk::Hitbox2D());
    };

    class Pipe
    {
    public:
        Pipe();
        ~Pipe() = default;
        flat::Rectangle&& rectangle = std::move(flat::gl::Rectangle());
        flat::Hitbox2D&& hitbox = std::move(flat::gjk::Hitbox2D());
        flat::Texture&& texture =  std::move(flat::gl::Texture());
    };

    class Bird
    {
    public:
        Bird();
        ~Bird() = default;
        flat::AudioSource&& source = std::move(flat::al::Source());
        flat::Texture&& texture0 =  std::move(flat::gl::Texture());
        flat::Texture&& texture1 =  std::move(flat::gl::Texture());
        flat::Texture&& texture2 =  std::move(flat::gl::Texture());
        flat::Rectangle&& rectangle = std::move(flat::gl::Rectangle());
        flat::Hitbox2D&& hitbox = std::move(flat::gjk::Hitbox2D());
        float velocityY;
    };

    class GamePlay
    {
    private:
        flat::gl::FWWindow _window;
        flat::Window& window = _window;
        flat::KeyboardInputSource& kbInput = _window;
        flat::MouseInputSource& msInput = _window;
        flat::Renderer& renderer  = _window;

        flat::al::Listener _listener;
        flat::AudioListener& listener = _listener;
        flat::al::Audio bgm;
        //flat::al::Audio fly;
        //flat::al::Audio die;
        //flat::al::Audio scored;

        BackGround background;
        Bird bird;
        std::array<Pipe,4> pipes;

        void initWindow();
        void initListener();
        void initBird();
        void initPipes();
        void initBackGround();

    public:
        GamePlay();
        ~GamePlay() = default;
        void start();
    };
}