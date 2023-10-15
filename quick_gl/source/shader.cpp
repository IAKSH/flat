#include <fstream>
#include <iostream>
#include <quick_gl/shader.hpp>

quick3d::gl::GLSLReader::GLSLReader(std::string_view path) noexcept(false)
    : path(path)
{
    read_all_glsl();
}

void quick3d::gl::GLSLReader::read_all_glsl() noexcept(false)
{
    std::ifstream file(path.data());
    if (!file.is_open())
        throw std::runtime_error(std::format("can't open glsl file from {}", path));

    stream << file.rdbuf();
}

std::string quick3d::gl::GLSLReader::get_glsl() const noexcept
{
    return stream.str();
}

std::string_view quick3d::gl::GLSLReader::get_path() const noexcept
{
    return path;
}

quick3d::gl::Program::Program(std::string_view vs, std::string_view fs) noexcept(false)
{
    create_program(vs,fs);
}

quick3d::gl::Program::Program(const GLSLReader& vs, const GLSLReader& fs) noexcept(false)
{
    create_program(vs.get_glsl(), fs.get_glsl());
}

quick3d::gl::Program::~Program() noexcept
{
    glDeleteProgram(program_id);
}

GLuint quick3d::gl::Program::get_program_id() const noexcept
{
    return program_id;
}

void quick3d::gl::Program::bind_uniform_block(std::string_view name, GLuint point) noexcept(false)
{
    auto uniform_block_index = glGetUniformBlockIndex(program_id, name.data());
    if (uniform_block_index == GL_INVALID_INDEX)
        throw std::runtime_error(std::format("can't find Uniform Block \"{}\" from shader", name));

    glUniformBlockBinding(program_id, uniform_block_index, point);
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