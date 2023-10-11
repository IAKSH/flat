#include <array>
#include <iostream>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/vertex.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/outer_glsl/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../../tests/outer_glsl/model";
static constexpr std::string_view IMAGE_FOLDER = "../../../../../tests/outer_glsl/image";

static constexpr int SCR_WIDTH = 1920;
static constexpr int SCR_HEIGHT = 1080;

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
     1.0f, -1.0f, 1.0f
};

void run() noexcept(false)
{
    quick3d::gl::Context context("outer glsl test", SCR_WIDTH, SCR_HEIGHT);
    glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    quick3d::gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

    std::array<std::string, 6> skybox_texture_pathes
    {
        std::format("{}/{}", IMAGE_FOLDER, "right.jpg"),
        std::format("{}/{}", IMAGE_FOLDER, "left.jpg"),
        std::format("{}/{}", IMAGE_FOLDER, "top.jpg"),
        std::format("{}/{}", IMAGE_FOLDER, "bottom.jpg"),
        std::format("{}/{}", IMAGE_FOLDER, "front.jpg"),
        std::format("{}/{}", IMAGE_FOLDER, "back.jpg")
    };

    quick3d::gl::Program skybox_program(
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_vs.glsl")).get_glsl(),
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_fs.glsl")).get_glsl());

    quick3d::gl::CubeMap skybox_cubemap(GL_RGBA, 2048, 2048);
    for (int i = 0; i < skybox_texture_pathes.size(); i++)
        skybox_cubemap.generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, quick3d::gl::Image(skybox_texture_pathes[i], false));

    quick3d::gl::VBO skybox_vbo(skybox_vertices);
    quick3d::gl::VAO skybox_vao(skybox_vbo);
    skybox_vao.enable_attrib(0, 3, 3, 0);

    quick3d::gl::Program model_program(
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_vs.glsl")).get_glsl(),
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl")).get_glsl());

    quick3d::gl::Model tree_model(std::format("{}/{}", MODEL_FOLDER, "Tree 02/Tree.obj"));
    std::clog << "tree model loadded!" << std::endl;
    quick3d::gl::Model yae_model(std::format("{}/{}", MODEL_FOLDER, "yae/yae.obj"));
    std::clog << "yae model loadded!" << std::endl;
    quick3d::gl::Model nanosuit_model(std::format("{}/{}", MODEL_FOLDER, "nanosuit/nanosuit.obj"));
    std::clog << "nanosuit model loadded!" << std::endl;
    quick3d::gl::Model earth_model(std::format("{}/{}", MODEL_FOLDER, "earth/Earth 2K.obj"));
    std::clog << "town model loadded!" << std::endl;

    context.get_window(0).set_mouse_callback([&](GLFWwindow* win, double x, double y) { camera.process_mouse_input(win, x, y); });
    context.get_window(0).set_keybord_callback([&](GLFWwindow* win, int key, int scancode, int action, int mods)
        {
            camera.process_keyboard_input(win, 0.01f);

            if (action == GLFW_PRESS)
            {
                switch (key)
                {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(win, true);
                    break;

                default:
                    break;
                }
            } });

    double delta_time{ 0 };
    double last_frame{ 0 };
    double current_frame{ 0 };

    auto win{ context.get_window(0).get_glfw_window() };
    while (!glfwWindowShouldClose(win))
    {
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        camera.on_tick(static_cast<float>(delta_time));

        // draw skybox
        skybox_program.set_uniform("projection", camera.get_projection_matrix());
        skybox_program.set_uniform("view", glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + camera.get_front_vec(), camera.get_up_vec()));
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_cubemap.get_cubemap_id());
        skybox_vao.draw(skybox_program, GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);

        // draw model
        model_program.set_uniform("view", camera.get_view_matrix());
        model_program.set_uniform("projection", camera.get_projection_matrix());

        glm::mat4 model_matrix;

        model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, -10.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
        model_program.set_uniform("model", model_matrix);
        earth_model.draw_model(model_program);

        for (int i = 0; i < 100; i++)
        {
            model_matrix = glm::mat4(1.0f);
            model_matrix = glm::translate(model_matrix, glm::vec3(i * 1.5f, (i % 3) * 1.5f, -0.5f));
            model_matrix = glm::scale(model_matrix, glm::vec3(1.5f, 1.5f, 1.5f));
            model_matrix = glm::rotate(model_matrix, static_cast<float>(cos(glfwGetTime())), glm::vec3(sin(glfwGetTime()), 0.2f, 0.5f));
            model_program.set_uniform("model", model_matrix);
            yae_model.draw_model(model_program);
        }

        model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(-10.0f, 0.0f, 0.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(0.5f, 0.5f, 0.5f));
        model_program.set_uniform("model", model_matrix);
        nanosuit_model.draw_model(model_program);

        model_matrix = glm::mat4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(-5.0f, 0.0f, 0.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(1.5f, 1.5f, 1.5f));
        model_program.set_uniform("model", model_matrix);
        tree_model.draw_model(model_program);

        glfwSwapBuffers(win);
        glfwPollEvents();

        glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
    }
}

int main() noexcept
{
    try
    {
        run();
    }
    catch (std::exception& e)
    {
        std::cerr << std::format("Exception: {}", e.what()) << std::endl;
    }
}