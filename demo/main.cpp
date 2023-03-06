#include <iostream>
#include <climits>

#include "../source/flat.hpp"

class Bird : public flat::GameObject
{
public:
    Bird();
    ~Bird() = default;
};

class Demo : public flat::GamePlay
{
private:
    Bird bird;

public:
    Demo();
    ~Demo() = default;
    void initializeDemo()
    {
        camera.loadVShaderFromFile("../demo/shader/vshader.glsl");
        camera.loadFShaderFromFile("../demo/shader/fshader.glsl");
        camera.initializePainter();

        bird.loadNewAnimation("fly", 250, {"../demo/images/bird0_0.png", "../demo/images/bird0_1.png", "../demo/images/bird0_2.png"});
        bird.loadAnimation("fly");
        bird.setSizeH(0.25f);
        bird.setSizeW(0.25f);
        bird.setPosition(glm::vec3(0.5f,0.5f,0.5f));
        bird.makeDrawMeta();
    }
    void customUpdateTick();
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
    return 0;
}

Demo::Demo()
{
}

void Demo::customUpdateTick()
{
    camera.draw(bird);
    // a float (rotate) too big will cause bug 
    bird.addRotate(0.01f);
}

Bird::Bird()
{
}