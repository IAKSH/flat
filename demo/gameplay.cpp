#include "gameplay.hpp"

flappy::BackGround::BackGround()
{
}

flappy::Pipe::Pipe()
{
}

flappy::Bird::Bird()
    : velocityY(0.0f)
{
}

void flappy::GamePlay::initWindow()
{
    window.initWindow();
    window.setWindowTitle("flappy bird");
}

void flappy::GamePlay::initListener()
{
    listener.initAudioListner();
    listener.setAudioListenerGain(1.0f);
    bgm.loadAudioFromFile("../../demo/sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
}

void flappy::GamePlay::initBird()
{
    bird.rectangle.x = -0.8f;
    bird.rectangle.w = 0.25f;
    bird.rectangle.h = 0.25f;
    bird.hitbox.setWidth(0.25f);
    bird.hitbox.setHeight(0.25f);
    bird.hitbox.setPosX(-0.8f);
    bird.source.initAudioSource();
    bird.source.setAudioSourceLooping(false);
    bird.source.setAudioSourceGain(0.5f);
    bird.texture0.initTexture();
    bird.texture0.loadTextureFromFile("../../demo/images/bird0_0.png");
    bird.texture1.loadTextureFromFile("../../demo/images/bird0_1.png");
    bird.texture2.loadTextureFromFile("../../demo/images/bird0_2.png");
}

void flappy::GamePlay::initPipes()
{
    // TODO
}

void flappy::GamePlay::initBackGround()
{
    background.rectangle.w = 1.0f;
    background.rectangle.h = 1.0f;
    background.source.initAudioSource();
    background.source.setAudioSourceLooping(true);
    background.source.setAudioSourceGain(0.5f);
    background.texture.initTexture();
    background.texture.loadTextureFromFile("../../demo/images/bg_day.png");
}

void flappy::GamePlay::start()
{
    background.source.playAudio(bgm.getAudioId());

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;
        if(kbInput.checkKeyboardDown(GLFW_KEY_D))
            bird.velocityY = 0.05f;

        bird.rectangle.y += bird.velocityY * 0.1f;
        bird.hitbox.setPosY(bird.rectangle.y);

        bird.velocityY -= 0.005f;

        // draw
        renderer.drawRectangle(background.rectangle);
        renderer.drawRectangle(bird.rectangle);
    }
}

flappy::GamePlay::GamePlay()
{
    initWindow();
    initListener();
    initBackGround();
    initPipes();
    initBird();
}
