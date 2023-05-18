#include "opengl_shader.hpp"
#include <exception>

flat::opengl::ShaderProgram::ShaderProgram(std::string_view vshader,std::string_view fshader)
{
    GLuint vshader_id = compile_vertex_shader(vshader);
    check_vertex_shader(vshader_id);
    GLuint fshader_id = compile_fragment_shader(fshader);
    check_fragment_shader(fshader_id);
    link_shader_program(vshader_id, fshader_id);

    glDeleteShader(vshader_id);
    glDeleteShader(fshader_id);
}

flat::opengl::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program_id);
}

GLuint flat::opengl::ShaderProgram::compile_vertex_shader(std::string_view code)
{
    const char* source = code.data();
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader,1,&source,nullptr);
    glCompileShader(vertex_shader);

    return vertex_shader;
}

GLuint flat::opengl::ShaderProgram::compile_fragment_shader(std::string_view code)
{
    const char* source = code.data();
    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader,1,&source,nullptr);
    glCompileShader(fragment_shader);

    return fragment_shader;
}

void flat::opengl::ShaderProgram::link_shader_program(GLuint vshader_id,GLuint fshader_id)
{
    program_id = glCreateProgram();
    glAttachShader(program_id,vshader_id);
    glAttachShader(program_id,fshader_id);
    glLinkProgram(program_id);
}

GLuint flat::opengl::ShaderProgram::get_uniform_location(std::string_view uniform)
{
    GLuint location = glGetUniformLocation(program_id,uniform.data());
    return location;
}

void flat::opengl::ShaderProgram::check_vertex_shader(GLuint vshader_id)
{
    int success;
    char info_log[512];
    glGetShaderiv(vshader_id,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(vshader_id,sizeof(info_log),nullptr,info_log);
        misc::main_logger->critical("vertex shader compilation failed, shaderInfoLog: {}", info_log);
        std::terminate();
    }
}

void flat::opengl::ShaderProgram::check_fragment_shader(GLuint fshader_id)
{
    int success;
    char info_log[512];
    glGetShaderiv(fshader_id,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(fshader_id,sizeof(info_log),nullptr,info_log);
        misc::main_logger->critical("fragment shader compilation failed, shaderInfoLog: {}", info_log);
        std::terminate();
    }
}