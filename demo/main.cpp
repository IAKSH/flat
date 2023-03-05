#include <iostream>

#include "../source/flat.hpp"

class Demo : public flat::GamePlay
{
public:
    Demo();
    ~Demo() = default;
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
    
}