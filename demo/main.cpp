#include <iostream>
#include <climits>

#include "../source/flat.hpp"

class Bird : public flat::GameObject
{
public:
    Bird();
    ~Bird() = default;
};

class Background : public flat::GameObject
{
public:
    Background();
    ~Background() = default;
};

class Pipe : public flat::GameObject
{
public:
    Pipe();
    ~Pipe() = default;
};

class Demo : public flat::GamePlay
{
private:
    Bird birds[5];
    Pipe pipe;
    Background background;

public:
    Demo();
    ~Demo() = default;
    void initializeDemo()
    {
        flat::windowSizeW = 800;
        flat::windowSizeH = 600;
        flat::windowTitle = "FLAT Demo";

        camera.loadVShaderFromFile("../demo/shader/vshader.glsl");
        camera.loadFShaderFromFile("../demo/shader/fshader.glsl");
        camera.initializePainter();
        camera.initializeListener();

        for(int i = 0;i < 5;i++)
        {
            Bird& bird = birds[i];
            bird.loadNewAnimation("stop", 100, {"../demo/images/bird0_0.png"});
            bird.loadNewAnimation("fly", 125, {"../demo/images/bird0_0.png", "../demo/images/bird0_1.png", "../demo/images/bird0_2.png"});
            bird.loadAnimation("stop");
            bird.setSizeH(0.25f);
            bird.setSizeW(0.25f);
            bird.setPosition(glm::vec3(-0.8f + 0.001f * i, 0.0f, 0.0f));
            bird.setHitboxScale(0.8f);
            bird.setHitboxOffset(glm::vec3(-0.25f,0.0f,0.0f));
            bird.makeDrawMeta();
        }

        pipe.loadNewAnimation("up",1000,{"../demo/images/pipe_up.png"});
        pipe.loadAnimation("up");
        pipe.setSizeH(1.0f);
        pipe.setSizeW(0.2f);
        pipe.setPosition(glm::vec3(0.5f, 0.0f, 0.0f));
        pipe.setHitboxScale(0.8f);
        pipe.makeDrawMeta();

        background.loadNewAnimation("day",1000,{"../demo/images/bg_day.png"});
        background.loadAnimation("day");
        background.setPosition(glm::vec3(0.0f,0.0f,0.0f));
        background.setSizeH(2.0f);
        background.setSizeW(2.0f);
        background.makeDrawMeta();

        background.initializeSoundSource();
        background.setSoundLoopable(true);
        background.setSoundVolume(0.1f);
        flat::Audio testBgm;
        testBgm.load("../demo/sounds/relaxed-vlog-night-street-131746.mp3");
        background.playSound(testBgm);

        //bird.initializeSoundSource();
        //bird.setSoundLoopable(true);
    }
    void customUpdateTick();
    void customUpdateInput();
};

int main() noexcept
{
    Demo demo;
    demo.initializeDemo();
    demo.runing = true;
    while (demo.runing)
    {
        demo.update();
    }

    //demo.destroyGLFW();
    return 0;
}

Demo::Demo()
{

}

void Demo::customUpdateTick()
{
    camera.draw(background);
    for(auto bird : birds)
        camera.draw(bird);
    camera.draw(pipe);

    background.addTexOffset(glm::vec2(0.001f,0.0f));

    for(auto bird : birds)
    {
        bird.addVelocity(glm::vec3(0.0f,-0.005f,0.0f));
        bird.updatePosition(1);

        if(bird.getPosY() >= 1.0f)
        bird.setPosition(glm::vec3(-0.8f,0.99f,0.0f));

        if(bird.GJKCollisionCheck(pipe))
        {
            std::cout << "game over!" << std::endl;
            abort();
        }
    }
}

void Demo::customUpdateInput()
{
    runing = !checkKey(GLFW_KEY_ESCAPE);

    if(checkKey(GLFW_KEY_SPACE))
    {
        for(auto bird : birds)
        {
            bird.setVelocity(glm::vec3(0.0f,0.05f,0.0f));
            bird.loadAnimation("fly");
        }
    }

    if(checkMouseLeftClick())
    {
        std::cout << "right click at (" << getMousePosX() << "," << getMousePosY() << ")" << std::endl;
    }
}

Bird::Bird()
{
}

Background::Background()
{

}

Pipe::Pipe()
{

}
