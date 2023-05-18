#include <iostream>
#include <memory>
#include "Core/application.hpp"
#include "Core/object.hpp"

std::unique_ptr<flat::Image> my_image;
std::unique_ptr<flat::Texture> my_texture;
std::unique_ptr<flat::Camera> camera;

struct TestLayer : public flat::Layer
{
    TestLayer()
        : flat::Layer("Test Layer")
    {
    }

    virtual void on_attach() override
    {
        std::cout << "hello!\n";
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

struct TestDrawLayer : public flat::Layer
{
    TestDrawLayer()
        : flat::Layer("Test Draw Layer")
    {
    }

    virtual void on_attach() override
    {
        std::cout << "test draw!\n";
        camera = std::make_unique<flat::Camera>(800,600);

        my_image = std::make_unique<flat::Image>("red.png");
        my_texture = my_image->gen_texture(0,0,500,500);
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
        glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //my_texture->flat::RenableObject::flush_to_screen();
        my_texture->flush_to_screen(*camera);
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
    flat::Application::get_instance().push_layer(std::make_unique<TestDrawLayer>());
    flat::Application::get_instance().run();
}