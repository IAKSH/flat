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

class Demo : public flat::GamePlay
{
private:
    Bird bird;
    Background background;

public:
    Demo();
    ~Demo() = default;
    void initializeDemo()
    {
        camera.loadVShaderFromFile("../demo/shader/vshader.glsl");
        camera.loadFShaderFromFile("../demo/shader/fshader.glsl");
        camera.initializePainter();
        camera.initializeListener();

        bird.loadNewAnimation("fly", 250, {"../demo/images/bird0_0.png", "../demo/images/bird0_1.png", "../demo/images/bird0_2.png"});
        bird.loadAnimation("fly");
        bird.setSizeH(0.25f);
        bird.setSizeW(0.25f);
        bird.setPosition(glm::vec3(0.5f, 0.5f, 0.5f));
        bird.makeDrawMeta();

        background.loadNewAnimation("day",1000,{"../demo/images/bg_day.png"});
        background.loadAnimation("day");
        background.setSizeH(2.0f);
        background.setSizeW(2.0f);
        background.makeDrawMeta();

        background.initializeSoundSource();
        background.setSoundLoopable(true);
        background.setSoundVolume(0.1f);
        flat::Audio testBgm;
        testBgm.load("../demo/sounds/relaxed-vlog-night-street-131746.mp3");
        background.playSound(testBgm);

        bird.initializeSoundSource();
        //bird.setSoundLoopable(true);
    }
    void customUpdateTick();
    void customUpdateInput();
};

int main() noexcept
{
    std::cout << "hello\n";

    Demo demo;
    demo.initializeDemo();
    demo.runing = true;
    while (demo.runing)
    {
        demo.update();
    }

    demo.destroyGLFW();
    return 0;
}

Demo::Demo()
{
}

void Demo::customUpdateTick()
{
    camera.draw(background);
    camera.draw(bird);
    // a float (rotate) too big will cause bug
    bird.addRotate(0.01f);
}

void Demo::customUpdateInput()
{
    runing = !checkKey(GLFW_KEY_ESCAPE);

    if(checkKey(GLFW_KEY_A))
        bird.addPosition(glm::vec3(-0.01f,0.0f,0.0f));
    if(checkKey(GLFW_KEY_S))
        bird.addPosition(glm::vec3(0.0f,-0.01f,0.0f));
    if(checkKey(GLFW_KEY_D))
        bird.addPosition(glm::vec3(0.01f,0.0f,0.0f));
    if(checkKey(GLFW_KEY_W))
        bird.addPosition(glm::vec3(0.0f,0.01f,0.0f));

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
