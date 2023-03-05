#include <iostream>

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
    void customUpdateTick();
};

int main() noexcept
{
    std::cout << "hello\n";


    Demo demo;

    demo.runing = true;
    while(demo.runing)
    {
        demo.update();
    }
    return 0;
}

Demo::Demo()
{
    bird.loadNewAnimation("fly",250,{"../demo/images/bird0_0.png","../demo/images/bird0_1.png","../demo/images/bird0_2.png"});
    bird.loadAnimation("fly");
    bird.transform(glm::scale(bird.getPositionMat(),glm::vec3(0.5f,0.5f,0.5f)));
    bird.makeDrawMeta();
}

void Demo::customUpdateTick()
{
    camera.draw(bird);
}

Bird::Bird()
{

}