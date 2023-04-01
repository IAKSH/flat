#include "shader.hpp"

#include <fstream>

#include "log.hpp"

flat::core::Shader::~Shader()
{
    if (shaderID)
    {
        glDeleteProgram(shaderID);
    }
}

void flat::core::Shader::loadFromFile(std::string_view vertexShaderPath, std::string_view fragmentShaderPath)
{
    std::ifstream vshaderIfs(vertexShaderPath.data(), std::ios::in);
    vshaderIfs.seekg(0, std::ios::end);
    const auto vshaderFileSize = vshaderIfs.tellg();
    vshaderIfs.seekg(0, std::ios::beg);
    std::string vshaderCode;
    vshaderCode.resize(vshaderFileSize);
    vshaderIfs.read(vshaderCode.data(), vshaderFileSize);

    std::ifstream fshaderIfs(fragmentShaderPath.data(), std::ios::in);
    fshaderIfs.seekg(0, std::ios::end);
    const auto fshaderFileSize = fshaderIfs.tellg();
    fshaderIfs.seekg(0, std::ios::beg);
    std::string fshaderCode;
    fshaderCode.resize(fshaderFileSize);
    fshaderIfs.read(fshaderCode.data(), fshaderFileSize);

    loadFromGLSL(vshaderCode, fshaderCode);
}

void flat::core::Shader::loadFromGLSL(std::string_view vertexShaderCode, std::string_view fragmentShaderCode)
{
    auto vshaderID = compileVertexShader(vertexShaderCode);
    checkVertexShader(vshaderID);
    auto fshaderID = compileFragmentShader(fragmentShaderCode);
    checkFragmentShader(fshaderID);
    shaderID = linkShaderProgram(vshaderID, fshaderID);

    glDeleteShader(vshaderID);
    glDeleteShader(fshaderID);
}

GLuint flat::core::Shader::compileVertexShader(std::string_view code)
{
    const char* source = code.data();
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);

    return vertexShader;
}

GLuint flat::core::Shader::compileFragmentShader(std::string_view code)
{
    const char* source = code.data();
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

GLuint flat::core::Shader::linkShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID)
{
    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    return shaderProgramID;
}

bool flat::core::Shader::checkVertexShader(GLuint vertexShaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderID, sizeof(infoLog), nullptr, infoLog);
        LOG_CRITICAL("Vertex shader compilation failed! ShaderInfoLog: {}", infoLog);
        abort();
    }
}

bool flat::core::Shader::checkFragmentShader(GLuint fragmentShaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderID, sizeof(infoLog), nullptr, infoLog);
        LOG_CRITICAL("Fragment shader compilation failed! ShaderInfoLog: {}", infoLog);
        abort();
    }
}