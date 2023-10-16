#include <array>
#include <iostream>
#include <quick_gl/context.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/buffer.hpp>
#include <quick_gl/vao.hpp>
#include <quick_gl/debug.hpp>
#include <quick_al/device.hpp>
#include <quick_al/context.hpp>
#include <quick_al/listener.hpp>
#include <quick_al/source.hpp>
#include <quick_al/buffer.hpp>
#include <quick_al/sample.hpp>

#define BGM_PATH "../../../../tests/oal_test/audio/heart.wav"
#define MODEL_PATH "../../../../tests/outer_glsl/model/yae/yae.obj"
#define IMAGE_FOLDER "../../../../tests/outer_glsl/image/"
#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

using namespace quick3d;

constexpr std::string_view model_vertex_strange_glsl{
    R"(
#version 320 es
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 randomVertexOffset(vec3 vertexPosition, vec3 vertexNormal, float delta)
{
    vec3 randomVector = normalize(vec3(rand(vec2(gl_VertexID, 0.0)), 
                                       rand(vec2(gl_VertexID, 1.0)), 
                                       rand(vec2(gl_VertexID, 2.0))));

    vec3 offsetPosition = vertexPosition + delta * randomVector;

    return offsetPosition;
}

void main()
{
    TexCoords = aTexCoords;
    vec3 offsetPosition = randomVertexOffset(aPos, aNormal, 0.1);
    gl_Position = projection * view * model * vec4(offsetPosition, 1.0);
}

//void main()
//{
//    TexCoords = aTexCoords;    
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
//}
    )"};

constexpr std::string_view model_vertex_glsl{
    R"(
#version 320 es
precision mediump float;

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
#version 320 es
precision mediump float;

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
            #version 320 es
            precision mediump float;

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
            #version 320 es
            precision mediump float;

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
        gl::Context context("yae", SCR_WIDTH, SCR_HEIGHT);
        glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        al::Device al_device(NULL);
        al::Context al_context(al_device);

        gl::Program skybox_program(skybox_vertex_glsl, skybox_fragment_glsl);

        gl::Buffer skybox_vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, skybox_vertices.size() * sizeof(float));
        skybox_vbo.write_buffer_data(skybox_vertices);
        gl::VertexArray skybox_vao;
        skybox_vao.add_attrib(skybox_vbo, 0, 3, 3, 0);

        gl::CubeMap skybox_cubemap(GL_RGBA,2048,2048);

        std::array<std::string,6> skybox_texture_pathes
        {
            std::format("{}/{}", IMAGE_FOLDER, "right.jpg"),
            std::format("{}/{}", IMAGE_FOLDER, "left.jpg"),
            std::format("{}/{}", IMAGE_FOLDER, "top.jpg"),
            std::format("{}/{}", IMAGE_FOLDER, "bottom.jpg"),
            std::format("{}/{}", IMAGE_FOLDER, "front.jpg"),
            std::format("{}/{}", IMAGE_FOLDER, "back.jpg"),
        };

        //gl::TextureRenderer ren(2048, 2048);
        for(int i = 0;i < 6;i++)
            skybox_cubemap.generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,gl::Image(skybox_texture_pathes[i],false));
            
        gl::Program model_program(model_vertex_glsl, model_fragment_glsl);
        gl::Model model(MODEL_PATH);
        gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

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

        // load audio
        al::Sample bgm_sample(BGM_PATH);
        al::Buffer bgm(bgm_sample);
        al::Source source(bgm);
        source.set_source_looping(true);
        source.set_source_gain(1.0f);
        al::Listener::set_gain(1.0f);
        source.play_sound();

        std::cout << "finish loading!\n";

        gl::check_ogl_error();

        auto win{context.get_window(0).get_glfw_window()};
        while (!glfwWindowShouldClose(win))
        {
            current_frame = glfwGetTime();
            delta_time = current_frame - last_frame;
            last_frame = current_frame;

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CW);
            glCullFace(GL_FRONT);

            camera.on_tick(static_cast<float>(delta_time));

            // draw skybox
            skybox_program.set_uniform("projection",camera.get_projection_matrix());
            skybox_program.set_uniform("view",glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f) + camera.get_front_vec(), camera.get_up_vec()));
            glBindTexture(GL_TEXTURE_CUBE_MAP,skybox_cubemap.get_cubemap_id());
            skybox_vao.draw(skybox_program,GL_TRIANGLES,0,36);
            glBindTexture(GL_TEXTURE_CUBE_MAP,0);

            // draw model
            glEnable(GL_DEPTH_TEST);
            glm::mat4 model_matrix = glm::mat4(1.0f);
            model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
            model_matrix = glm::scale(model_matrix, glm::vec3(1.5f, 1.5f, 1.5f));
            model_program.set_uniform("model", model_matrix);
            model_program.set_uniform("view", camera.get_view_matrix());
            model_program.set_uniform("projection", camera.get_projection_matrix());
            model.draw_model(model_program);

            glfwSwapBuffers(win);
            glfwPollEvents();

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