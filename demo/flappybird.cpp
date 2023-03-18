#include <thread>
#include <iostream>

#include "audio_alsoft.hpp"
#include "keyboard_glfw.hpp"
#include "mouse_glfw.hpp"
#include "renderer_glcore.hpp"
#include "window_glfw.hpp"

struct obj
{
    float x, y, z, r, w, h;
    obj() : x(0.0f), y(0.0f), z(0.0f), r(0.0f), w(0.5f), h(0.5f) {}
    ~obj() {}
};

int main()
{
    flat::Window<flat::imp::window::glfw::Window>&& win = flat::imp::window::glfw::Window();
    flat::Renderer<flat::imp::renderer::glcore::Renderer>&& ren = flat::imp::renderer::glcore::Renderer();
    flat::KeyboardSource<flat::imp::keyboard::glfw::KeyboardSource>&& keyboard = flat::imp::keyboard::glfw::KeyboardSource();
    flat::MouseSource<flat::imp::mouse::glfw::MouseSource>&& mouse = flat::imp::mouse::glfw::MouseSource();
    flat::AudioMixer<flat::imp::audio::alsoft::AudioMixer>&& mixer = flat::imp::audio::alsoft::AudioMixer();

    auto source = mixer.genAudioSource();
    auto mp3 = mixer.genAudio("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

    auto birdTex1 = ren.genTexture("../../demo/images/bird0_0.png");
    auto birdTex2 = ren.genTexture("../../demo/images/bird0_1.png");
    auto birdTex3 = ren.genTexture("../../demo/images/bird0_2.png");

    (*source)[flat::AudioAttribType::looping](true);
    mixer << flat::AudioAttrib(flat::AudioAttribType::gain,0.2f) << (*source)(*mp3);

    obj bird;
    bird.x = -0.8f;
    bird.w = 0.09f;
    bird.h = 0.1f;

    float birdVelocity = 0.0f;

    while(true)
    {
        if(keyboard.checkKey(GLFW_KEY_ESCAPE))
            break;
        if(keyboard.checkKey(GLFW_KEY_SPACE))
            birdVelocity = 0.05f;
        if(mouse.checkMouseLeft())
            mixer << flat::StopFlag(*source);
        if(mouse.checkMouseRight())
            mixer << flat::ResumeFlag(*source);

        ren << flat::Color(1.0f,1.0f,1.0f,1.0f) << flat::TextureOffset(0.0f,0.0f,1.0f,1.0f) << *birdTex1 << flat::Rectangle(bird.x,bird.y,bird.z,bird.w,bird.h,bird.r);

        bird.y += birdVelocity;
        if(birdVelocity > -0.075f)
            birdVelocity -= 0.005f;
        
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(12));

        win.updateWindow();
    }

    return 0;
}