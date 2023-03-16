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
    class Texture : public renapi::Texture
    {
    private:
        const uint32_t textureId;

    public:
        Texture(uint32_t id) : textureId(id){};
        virtual ~Texture() override;
        uint32_t const getTextureId() { return textureId; }
    };

    class Font : public renapi::Font
    {
    private:
        // TODO:...

    public:
        Font();
        virtual ~Font() override;
        virtual renapi::Font& operator()(const renapi::Font& font) override;
    };

    class Renderer : public renapi::Renderer<Renderer>
    {
    private:
        uint32_t vao, vbo, ebo, shaderProgram;
        void makeDrawMeta()
        {
            // create VAO part1
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            // create VBO
            float vertices[]{ 1.0f, 1.0f, 0.0, 1.0, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f };

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // create EBO
            const uint32_t indices[] = { 0, 1, 3, 1, 3, 2 };

            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // create VAO part2
            // only vertex position attrib, because we transform/set color/bind texture coords in shader using glsl uniform
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void makeShaderProgram(uint32_t vshader, uint32_t fshader)
        {
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vshader);
            glAttachShader(shaderProgram, fshader);
            glLinkProgram(shaderProgram);
            glDeleteProgram(vshader);
            glDeleteProgram(fshader);
            glUseProgram(shaderProgram);
            glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);
        }

        void checkVertexShader(uint32_t vshader)
        {
            int success;
            char infoLog[512];
            glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vshader, sizeof(infoLog), nullptr, infoLog);
                std::cerr << "error: failed to compile vertex shader\nshader info log:  " << infoLog << std::endl;
                abort();
            }
        }

        void checkFragmentShader(uint32_t fshader)
        {
            int success;
            char infoLog[512];
            glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fshader, sizeof(infoLog), nullptr, infoLog);
                std::cout << "error: failed to compile fragment shader\nshader info log:  " << infoLog << std::endl;
                abort();
            }
        }

        uint32_t compileVertexShader()
        {
            static const char* VERTEX_SOURCE = "#version 330 core\n"
                                               "layout (location = 0) in vec3 aPos;\n"
                                               "layout (location = 1) in vec3 aColor;\n"
                                               "layout (location = 2) in vec2 aTexCoord;\n"
                                               "out vec3 ourColor;\n"
                                               "out vec2 TexCoord;\n"
                                               "uniform vec2 texOffset;\n"
                                               "uniform mat4 transform;\n"
                                               "void main()\n"
                                               "{\n"
                                               "   gl_Position = transform * vec4(aPos, 1.0);\n"
                                               "   ourColor = aColor;\n"
                                               "   TexCoord = vec2(aTexCoord.x + texOffset.x, 1.0 - aTexCoord.y + texOffset.y);\n"
                                               "}\n";

            uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShaderId, 1, &VERTEX_SOURCE, nullptr);
            glCompileShader(vertexShaderId);
            return vertexShaderId;
        }

        uint32_t compileFragmentShader()
        {
            static const char* FRAGMENT_SOURCE = "#version 330 core\n"
                                                 "out vec4 FragColor;\n"
                                                 "in vec3 ourColor;\n"
                                                 "in vec2 TexCoord;\n"
                                                 "uniform sampler2D texture0;\n"
                                                 "uniform sampler2D texture1;\n"
                                                 "void main()\n"
                                                 "{\n"
                                                 "   vec4 texColor = mix(texture(texture0,TexCoord),texture(texture1,TexCoord),0.5) * vec4(ourColor,1.0f);\n"
                                                 "   if(texColor.a < 0.1)\n"
                                                 "       discard;\n"
                                                 "   FragColor = texColor;\n"
                                                 "}\n";

            uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShaderId, 1, &FRAGMENT_SOURCE, nullptr);
            glCompileShader(fragmentShaderId);
            return fragmentShaderId;
        }

        void writeTransformUniform(const glm::mat4& trans)
        {
            int location = glGetUniformLocation(shaderProgram, "transform");
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));
        }

        void writeColorUniform(const glm::vec4 color)
        {
            int location = glGetUniformLocation(shaderProgram, "color");
            glUniform4fv(location, 1, glm::value_ptr(color));
        }

        void writeTextCoordsUniform(const glm::vec2 coord1, const glm::vec2 coord2, const glm::vec2 coord3, const glm::vec2 coord4)
        {
            glUniform2fv(glGetUniformLocation(shaderProgram, "coord1"), 1, glm::value_ptr(coord1));
            glUniform2fv(glGetUniformLocation(shaderProgram, "coord2"), 1, glm::value_ptr(coord2));
            glUniform2fv(glGetUniformLocation(shaderProgram, "coord3"), 1, glm::value_ptr(coord3));
            glUniform2fv(glGetUniformLocation(shaderProgram, "coord4"), 1, glm::value_ptr(coord4));
        }

    public:
        Renderer() : vao(0), vbo(0), ebo(0), shaderProgram(0) {}

        ~Renderer()
        {
            glDeleteVertexArrays(1, &vao);
            glDeleteProgram(shaderProgram);
        }

        void imp_setColor(renapi::Color&& color) { writeColorUniform(glm::vec4(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha())); }

        void imp_bindTexture(renapi::Texture&& texture)
        {
            if(typeid(texture) != typeid(Texture))
            {
                std::cerr << "error: unknow textrue type" << std::endl;
                abort();
            }

            auto& tex = (Texture&)texture;

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex.getTextureId());
        }

        void imp_drawRectangle(renapi::Rectangle&& rectangle)
        {
            glm::mat4 transfom(1.0f);
            transfom *= glm::translate(transfom, glm::vec3(rectangle.getX(), rectangle.getY(), rectangle.getZ()));
            transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateX(), glm::vec3(1.0f, 0.0f, 0.0f));
            transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateY(), glm::vec3(0.0f, 1.0f, 0.0f));
            transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateZ(), glm::vec3(0.0f, 0.0f, 1.0f));
            writeTransformUniform(transfom);
        }

        void imp_drawText(renapi::Texture&& text)
        {
            // TODO
        }

        void imp_flush()
        {
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        bool imp_initialize()
        {
            GLFWwindow* window = nullptr;
            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glfw") == std::end(init::initialized))
            {
                // initialize GLFW without window manager
                // try not to let this thing run
                std::clog << "warnning: now initializing GLFW by Renderer,instead of window manager module" << std::endl;

                glfwInit();
                glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                window = glfwCreateWindow(800, 600, "FLAT", nullptr, nullptr);
                if(!window)
                {
                    glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error | errno: " << errno << " description: " << description << std::endl; });
                    return false;
                }
                
                glfwMakeContextCurrent(window);

                init::initialized.push_back("glfw");
            }
            else { window = glfwGetCurrentContext(); }

            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glad") == std::end(init::initialized))
            {
                // initialize GLAD
                if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cerr << "error: can't get load GLAD" << std::endl;
                    return false;
                }

                glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height){ glViewport(0, 0, width, height); });
            }

            return true;
        }

        const renapi::Texture& imp_genTexture(std::string_view path)
        {
            uint32_t textureId;
            glGenTextures(1, &textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int w, h, channels;
            unsigned char* data;

            data = stbi_load(path.data(), &w, &h, &channels, 0);
            if(!data)
            {
                std::cerr << "[ERROR] Can't load " << path.data() << std::endl;
                abort();
            }

            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
            return std::move(Texture(textureId));
        }

        const renapi::Font& imp_genFont(std::string_view path)
        {
            // TODO
            return std::move(Font());
        }
    };
}  // namespace glcore