#include "opengl_shader.hpp"

ni::utils::ShaderProgram::ShaderProgram(std::string_view vshader,std::string_view fshader)
{
    loadFromGLSL(vshader,fshader);
}

ni::utils::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programID);
}

GLuint ni::utils::ShaderProgram::compileVertexShader(std::string_view code)
{
    const char* source = code.data();
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &source, nullptr);
    glCompileShader(vertexShader);

    return vertexShader;
}

GLuint ni::utils::ShaderProgram::compileFragmentShader(std::string_view code)
{
    const char* source = code.data();
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &source, nullptr);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

GLuint ni::utils::ShaderProgram::linkShaderProgram(const GLuint& vshaderID,const GLuint& fshaderID)
{
    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vshaderID);
    glAttachShader(shaderProgramID, fshaderID);
    glLinkProgram(shaderProgramID);

    return shaderProgramID;
}

GLuint ni::utils::ShaderProgram::tryGetUniformLocation(std::string_view uniform)
{
    GLuint location = glGetUniformLocation(programID,uniform.data());
    //if(!location)
    //{
    //    core::utilsLogger->critical("can't find uniform \"{}\" in shader (id = {})",uniform,programID);
    //    std::terminate();
    //}

    return location;
}

void ni::utils::ShaderProgram::checkVertexShader(GLuint vshaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(vshaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vshaderID, sizeof(infoLog), nullptr, infoLog);
        core::utilsLogger->critical("vertex shader compilation failed, shaderInfoLog: {}", infoLog);
        std::terminate();
    }
}

void ni::utils::ShaderProgram::checkFragmentShader(GLuint fshaderID)
{
    int success;
    char infoLog[512];
    glGetShaderiv(fshaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fshaderID, sizeof(infoLog), nullptr, infoLog);
        core::utilsLogger->critical("fragment shader compilation failed, shaderInfoLog: {}", infoLog);
        std::terminate();
    }
}

void ni::utils::ShaderProgram::loadFromGLSL(std::string_view vshader,std::string_view fshader)
{
    GLuint vshaderID = compileVertexShader(vshader);
    checkVertexShader(vshaderID);
    GLuint fshaderID = compileFragmentShader(fshader);
    checkFragmentShader(fshaderID);
    programID = linkShaderProgram(vshaderID, fshaderID);

    glDeleteShader(vshaderID);
    glDeleteShader(fshaderID);
}
