#include <iostream>
#include <memory>
#include "../core/application.hpp"
#include "../core/object.hpp"
#include "../core/pipe.hpp"

std::unique_ptr<flat::Image> my_image;
std::unique_ptr<flat::Texture> my_texture;
std::unique_ptr<flat::Camera> camera;
std::unique_ptr<flat::RenderPipe> pip;

//struct TestLayer : public flat::Layer
//{
//    TestLayer()
//        : flat::Layer("Test Layer")
//    {
//    }
//
//    virtual void on_attach() override
//    {
//        std::cout << "hello!\n";
//    }
//
//    virtual void on_detach() override
//    {
//        std::cout << "bye!\n";
//    }
//
//    virtual void on_update() override
//    {
//
//    }
//
//    virtual void on_render() override
//    {
//
//    }
//
//    virtual void on_event(const flat::Event& event) override
//    {
//        if(event.get_type() == flat::EventType::KeyPress)
//        {
//            if(reinterpret_cast<const flat::KeyPressEvent*>(&event)->get_keycode() == flat::misc::KeyCode::ESCAPE)
//                flat::Application::get_instance().exit();
//            else if(reinterpret_cast<const flat::KeyPressEvent*>(&event)->get_keycode() == flat::misc::KeyCode::Z)
//                my_texture->rotate(1.5f,0.5f,1.0f);
//        }
//    }
//};
//
//struct TestDrawLayer : public flat::Layer
//{
//    TestDrawLayer()
//        : flat::Layer("Test Draw Layer")
//    {
//    }
//
//    virtual void on_attach() override
//    {
//        std::cout << "test draw!\n";
//        camera = std::make_unique<flat::Camera>(800,600);
//
//        my_image = std::make_unique<flat::Image>("E:\\Programming-Playground\\flat2\\red.png");
//        my_texture = my_image->gen_texture(0,0,1024,576);
//
//        pip = std::make_unique<flat::RenderPipe>(flat::default_vertex_shader,flat::default_fragment_shader);
//    }
//
//    virtual void on_detach() override
//    {
//        std::cout << "bye!\n";
//    }
//
//    virtual void on_update() override
//    {
//        my_texture->set_position_x(my_texture->get_position_x() + sin(glfwGetTime()) * 0.0025f);
//        my_texture->set_position_y(my_texture->get_position_y() + cos(glfwGetTime()) * 0.001f);
//    }
//
//    virtual void on_render() override
//    {
//        glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        my_texture->flat::RenableObject::flush_to_screen();
//        //pip->ren_texture(*my_texture)->flat::RenableObject::flush_to_screen();
//    }
//
//    virtual void on_event(const flat::Event& event) override
//    {
//         std::cout << "event type: " << static_cast<int>(event.get_type()) << '\n';
//    }
//};

int main()
{
    auto my_test_layer {std::make_unique<flat::Layer>()};
    my_test_layer->set_attach_func([](){std::cout << "hello world!\n";});
    my_test_layer->set_detach_func([](){std::cout << "byebye!\n";});
    my_test_layer->set_event_func([](const flat::Event& event)
    {
        if(event.get_type() == flat::EventType::KeyPress)
        {
            if(reinterpret_cast<const flat::KeyPressEvent*>(&event)->get_keycode() == flat::misc::KeyCode::ESCAPE)
                flat::Application::get_instance().exit();
        }
    });

    flat::Application::get_instance().push_layer(std::move(my_test_layer));
    flat::Application::get_instance().run();
}