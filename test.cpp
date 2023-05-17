#include <iostream>
#include <memory>
#include "Core/application.hpp"
#include "Core/object.hpp"

std::unique_ptr<flat::Image> my_image;

struct TestLayer : public flat::Layer
{
    TestLayer()
        : flat::Layer("Test Layer")
    {
    }

    virtual void on_attach() override
    {
        std::cout << "hello!\n";
        my_image = std::make_unique<flat::Image>("red.png");
    }

    virtual void on_detach() override
    {
        std::cout << "bye!\n";
    }

    virtual void on_update() override
    {

    }

    virtual void on_render() override
    {

    }

    virtual void on_event(const flat::Event& event) override
    {
        if(auto ptr = dynamic_cast<const flat::KeyPressEvent*>(&event);ptr != nullptr)
        {
            if(ptr->get_keycode() == flat::misc::KeyCode::ESCAPE)
                flat::Application::get_instance().exit();
        }
    }
};

int main()
{
    std::cout << "hello world!\n";
    flat::Application::get_instance().push_layer(std::make_unique<TestLayer>());
    flat::Application::get_instance().run();
}