#include <fstream>
#include <sstream>
#include <iostream>
#include <quick_gl/shader.hpp>

quick3d::gl::Program::Program(GLSLString vs,GLSLString fs) noexcept(false)
{
    create_program(vs,fs);
}

quick3d::gl::Program::Program(std::string_view path_to_vs,std::string_view path_to_fs) noexcept(false)
{
    create_program(
        read_glsl_from_file(path_to_vs),
        read_glsl_from_file(path_to_fs)
        );
}

quick3d::gl::Program::~Program() noexcept
{
    glDeleteProgram(program_id);
}

GLuint quick3d::gl::Program::get_program_id() const noexcept
{
    return program_id;
}

std::string&& quick3d::gl::Program::read_glsl_from_file(std::string_view path) noexcept(false)
{
    std::ifstream file(path.data());
    if (!file.is_open())
        throw std::runtime_error(std::format("can't open glsl file from {}",path));

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLint quick3d::gl::Program::get_uniform_location(std::string_view uniform) noexcept(false)
{
    if (int location = glGetUniformLocation(program_id, uniform.data()); location == -1)
		throw std::runtime_error(std::format("opengl uniform \"{}\" not found", uniform));
	else
		return location;
}

void quick3d::gl::Program::create_program(std::string_view vs,std::string_view fs) noexcept(false)
{
    GLuint vs_id,fs_id;
    vs_id = compile_shader<GL_VERTEX_SHADER>(vs);
    fs_id = compile_shader<GL_FRAGMENT_SHADER>(fs);

    if(!check_shader<GL_VERTEX_SHADER>(vs_id))
        throw std::runtime_error("failed when compiling vertex shader from glsl");

    if(!check_shader<GL_FRAGMENT_SHADER>(fs_id))
        throw std::runtime_error("failed when compiling fragment shader from glsl");
    
    program_id = glCreateProgram();
	glAttachShader(program_id,vs_id);
	glAttachShader(program_id,fs_id);
	glLinkProgram(program_id);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
}

template <GLenum shader_type>
GLuint quick3d::gl::Program::compile_shader(std::string_view glsl) noexcept
{
    const char* source {glsl.data()};
	GLuint shader_id {glCreateShader(shader_type)};

	glShaderSource(shader_id, 1, &source, nullptr);
	glCompileShader(shader_id);

    return shader_id;
}

template <GLenum shader_type>
bool quick3d::gl::Program::check_shader(GLuint shader_id) const noexcept
{
    int success;
	char info_log[512];
	if (glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);!success)
	{
		glGetShaderInfoLog(shader_id,sizeof(info_log),nullptr,info_log);
		std::cerr << info_log << '\n';
	}

    return static_cast<bool>(success);
}