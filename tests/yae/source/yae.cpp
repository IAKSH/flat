#include <array>
#include <iostream>
#include <quick_gl/context.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/texture_render.hpp>
#include <quick_gl/debug.hpp>

#define MODEL_PATH "D:/Programming-Playground/distort/test/model/yae_obj/yae.obj"
#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

using namespace quick3d::gl;

constexpr std::string_view model_vertex_glsl{
    R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
    )"};

constexpr std::string_view model_fragment_glsl{
    R"(
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}
    )"};

constexpr std::string_view skybox_vertex_glsl{
    R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            out vec3 texCoord;

            uniform mat4 projection;
            uniform mat4 view;

            void main()
            {
                texCoord = aPos;
                gl_Position = projection * view * vec4(aPos,1.0);
            }
        )"};

constexpr std::string_view skybox_fragment_glsl{
    R"(
            #version 330 core
            out vec4 fragColor;

            in vec3 texCoord;

            uniform samplerCube skybox_cubemap;

            void main()
            {
                fragColor = texture(skybox_cubemap,texCoord);
            }
        )"};

constexpr std::array<float, 108> skybox_vertices{
    // right
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,

    // left
    -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    // top
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    // bottom
    -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,

    // front
    -1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, -1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f,

    // back
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f};

int main() noexcept
{
    try
    {
        Context context("yae", SCR_WIDTH, SCR_HEIGHT);
        glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        check_ogl_error();

        Program skybox_program((GLSLString(skybox_vertex_glsl)), (GLSLString(skybox_fragment_glsl)));

        check_ogl_error();

        VBO skybox_vbo(skybox_vertices);

        check_ogl_error();

        VAO skybox_vao(skybox_vbo);

        check_ogl_error();

        skybox_vao.enable_attrib(0,3,3,0);

        check_ogl_error();

        CubeMap skybox_cubemap(GL_RGBA,2048,2048);

        check_ogl_error();

        constexpr std::array<std::string_view,6> skybox_texture_pathes
        {
            "D:\\Programming-Projects\\glbind\\tests\\img\\right.jpg",
            "D:\\Programming-Projects\\glbind\\tests\\img\\left.jpg",
            "D:\\Programming-Projects\\glbind\\tests\\img\\top.jpg",
            "D:\\Programming-Projects\\glbind\\tests\\img\\bottom.jpg",
            "D:\\Programming-Projects\\glbind\\tests\\img\\front.jpg",
            "D:\\Programming-Projects\\glbind\\tests\\img\\back.jpg"
        };

        check_ogl_error();

        TextureRenderer ren(2048, 2048);
        for(int i = 0;i < 6;i++)
            // TODO: TextureRenderer异常，Debugger看见管线里一个shader都没有
            ren.draw_to_cubemap(skybox_cubemap, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, Image(skybox_texture_pathes[i], false));
            //skybox_cubemap.generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,Image(skybox_texture_pathes[i],false));

        check_ogl_error();
            
        Program model_program((GLSLString(model_vertex_glsl)), (GLSLString(model_fragment_glsl)));
        Model model(MODEL_PATH);
        FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

        check_ogl_error();

        context.get_window(0).set_mouse_callback([&](GLFWwindow *win, double x, double y)
                                                 { camera.process_mouse_input(win, x, y); });
        context.get_window(0).set_keybord_callback([&](GLFWwindow *win, int key, int scancode, int action, int mods)
                                                   {
            camera.process_keyboard_input(win,0.01f);

            if(action == GLFW_PRESS)
            {
                switch (key)
                {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(win,true);
                    break;

                default:
                    break; 
                }
            } });

        double delta_time{0};
        double last_frame{0};
        double current_frame{0};

        std::cout << "finish loading!\n";

        check_ogl_error();

        auto win{context.get_window(0).get_glfw_window()};
        while (!glfwWindowShouldClose(win))
        {
            check_ogl_error();

            current_frame = glfwGetTime();
            delta_time = current_frame - last_frame;
            last_frame = current_frame;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CW);
            glCullFace(GL_FRONT);

            camera.on_tick(static_cast<float>(delta_time));

            check_ogl_error();

            // draw skybox
            skybox_program.set_uniform("projection",camera.get_projection_matrix());
            //skybox_program.set_uniform("view", camera.get_view_matrix());
            skybox_program.set_uniform("view",glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f) + camera.get_front_vec(), camera.get_up_vec()));
            glBindTexture(GL_TEXTURE_CUBE_MAP,skybox_cubemap.get_cubemap_id());
            skybox_vao.draw(skybox_program,GL_TRIANGLES,0,36);
            glBindTexture(GL_TEXTURE_CUBE_MAP,0);

            check_ogl_error();

            // draw model
            glEnable(GL_DEPTH_TEST);
            glm::mat4 model_matrix = glm::mat4(1.0f);
            model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
            model_matrix = glm::scale(model_matrix, glm::vec3(1.5f, 1.5f, 1.5f));
            model_program.set_uniform("model", model_matrix);
            model_program.set_uniform("view", camera.get_view_matrix());
            model_program.set_uniform("projection", camera.get_projection_matrix());
            model.draw_model(model_program);

            check_ogl_error();

            glfwSwapBuffers(win);
            glfwPollEvents();

            check_ogl_error();

            glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
}