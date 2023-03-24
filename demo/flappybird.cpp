#include <memory>
#include <thread>
#include <iostream>
#include <utility>

#include "audio_alsoft.hpp"
#include "keyboard_glfw.hpp"
#include "mouse_glfw.hpp"
#include "renderer_glcore.hpp"
#include "window_glfw.hpp"
#include "gameplay.hpp"

static flat::Window<flat::imp::window::glfw::Window>&& win = flat::imp::window::glfw::Window();
static flat::Renderer<flat::imp::renderer::glcore::Renderer>&& ren = flat::imp::renderer::glcore::Renderer();
static flat::KeyboardSource<flat::imp::keyboard::glfw::KeyboardSource>&& keyboard = flat::imp::keyboard::glfw::KeyboardSource();
static flat::MouseSource<flat::imp::mouse::glfw::MouseSource>&& mouse = flat::imp::mouse::glfw::MouseSource();
static flat::AudioMixer<flat::imp::audio::alsoft::AudioMixer>&& mixer = flat::imp::audio::alsoft::AudioMixer();

static std::unique_ptr<flat::Texture> birdTex0 = ren.genTexture("../../../../demo/images/bird0_0.png");
static std::unique_ptr<flat::Texture> birdTex1 = ren.genTexture("../../../../demo/images/bird0_1.png");
static std::unique_ptr<flat::Texture> birdTex2 = ren.genTexture("../../../../demo/images/bird0_2.png");
static std::unique_ptr<flat::Texture> pipeTexDown = ren.genTexture("../../../../demo/images/pipe_down.png");
static std::unique_ptr<flat::Texture> pipeTexUp = ren.genTexture("../../../../demo/images/pipe_up.png");

static flat::Animation birdAnimation(250, { birdTex0.get(), birdTex1.get(), birdTex2.get() });

class Bird : public flat::GameObject<Bird>
{
private:
    float velocityY;

public:
    Bird()
        : velocityY(0.0f)
    {
        
        bindAnimation("fly", birdAnimation);
        switchAnimationTo("fly");

        setPosX(-0.8f);
        setWidth(0.09f);
        setHeight(0.1f);
    }

    ~Bird() {}
    void imp_onTick()
    {
        if(keyboard.checkKey(GLFW_KEY_SPACE))
            velocityY = 0.05f;

        setPosY(getPosY() + velocityY);
        if(velocityY > -0.075f)
            velocityY -= 0.005f;
        
        ren << flat::Color(1.0f,1.0f,1.0f,1.0f) << flat::TextureOffset(0.0f,0.0f,1.0f,1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(),getPosY(),0.0f,getWidth(),getHeight(),getRotate());
    }
};

int main()
{
    auto source = mixer.genAudioSource();
    auto mp3 = mixer.genAudio("../../../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

    (*source)[flat::AudioAttribType::looping](true);
    (*source)[flat::AudioAttribType::gain](0.2f);
    mixer << flat::AudioAttrib(flat::AudioAttribType::gain,0.2f) << (*source)(*mp3);

    flat::GameObject<Bird>&& bird = Bird();

    while(true)
    {
        if(keyboard.checkKey(GLFW_KEY_ESCAPE))
            break;
        if(mouse.checkMouseLeft())
            mixer << flat::StopFlag(*source);
        if(mouse.checkMouseRight())
            mixer << flat::ResumeFlag(*source);

        bird.onTick();
        
        std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(12));

        win.updateWindow();
    }

    return 0;
}