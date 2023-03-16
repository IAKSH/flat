#pragma once

#include <algorithm>
#include <iostream>

#include "abstruct_api.hpp"
#include "glcore_imp.hpp"
#include "initialized.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace glcore
{
    class Renderer : public renapi::Renderer<Renderer>
    {
    private:
        uint32_t vao, vbo, ebo, shader;

        const char* vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\n\0";

        void initGLFW()
        {
            std::cerr << "warnning: glfw initialized by Renderer" << std::endl;

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            GLFWwindow* window = glfwCreateWindow(800, 600, "FLAT", NULL, NULL);
            if(window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                abort();
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
        }

        void initGLAD()
        {
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                abort();
            }
        }

        void initShader()
        {
            unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            // check for shader compile errors
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            // fragment shader
            unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            // check for shader compile errors
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            // link shaders
            shader = glCreateProgram();
            glAttachShader(shader, vertexShader);
            glAttachShader(shader, fragmentShader);
            glLinkProgram(shader);
            // check for linking errors
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        void makeDrawMeta()
        {
            float vertices[] = {
                0.5f,  0.5f,  0.0f,  // top right
                0.5f,  -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f, 0.5f,  0.0f   // top left
            };
            unsigned int indices[] = {
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
            };
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

    public:
        Renderer() : vao(0), vbo(0), ebo(0) {}

        ~Renderer()
        {
            glDeleteVertexArrays(1, &vao);
            glDeleteProgram(shader);
        }

        void imp_drawRectangle(renapi::Rectangle&& rectangle)
        {
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        bool imp_initialize()
        {

            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glfw") == std::end(init::initialized))
            {
                initGLFW();
                init::initialized.push_back("glfw");
            }

            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glad") == std::end(init::initialized))
            {
                initGLAD();
                init::initialized.push_back("glad");
            }

            initShader();
            makeDrawMeta();
        }
    };
}  // namespace glcore