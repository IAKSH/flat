#include <regex>
#include <format>
#include <fstream>
#include <filesystem>
#include <quick_gl/shader.hpp>
#include <spdlog/spdlog.h>

quick3d::gl::Program::Program(const Shader& vs, const Shader& fs) noexcept(false)
{
    create_program(vs,fs);
}

quick3d::gl::Program::Program(const Shader& vs, const Shader& gs, const Shader& fs) noexcept(false)
{
    create_program(vs, gs, fs);
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

void quick3d::gl::Program::create_program(const Shader& vs, const Shader& fs) noexcept(false)
{
    program_id = glCreateProgram();
    glAttachShader(program_id, vs.get_id());
    glAttachShader(program_id, fs.get_id());
    glLinkProgram(program_id);
}

void quick3d::gl::Program::create_program(const Shader& vs, const Shader& gs, const Shader& fs) noexcept(false)
{
    program_id = glCreateProgram();
    glAttachShader(program_id, vs.get_id());
    glAttachShader(program_id, gs.get_id());
    glAttachShader(program_id, fs.get_id());
    glLinkProgram(program_id);
}

quick3d::gl::Shader::Shader(GLenum shader_type, std::string_view glsl) noexcept(false)
{
    compile(shader_type, glsl);
    check_compile_status();
}

quick3d::gl::Shader::~Shader() noexcept
{
    glDeleteShader(shader_id);
}

GLuint quick3d::gl::Shader::get_id() const noexcept
{
    return shader_id;
}

void quick3d::gl::Shader::compile(GLenum shader_type, std::string_view glsl) noexcept(false)
{
    const char* source{ glsl.data() };
    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);

    //spdlog::debug("glsl code:\n------\n{}\n------\n", glsl);
}

void quick3d::gl::Shader::check_compile_status() noexcept(false)
{
    int success;
    char info_log[512];
    if (glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success); !success)
    {
        glGetShaderInfoLog(shader_id, sizeof(info_log), nullptr, info_log);
        throw std::runtime_error(std::format("failed when compile shader, log as below:\n{}", info_log));
    }
}

std::string quick3d::gl::GLSLManager::impl_glsl_include(std::string_view glsl) noexcept(false)
{
    // TODO:...
    return std::string(glsl);
}

GLenum quick3d::gl::GLSLManager::get_glsl_shader_type(std::string glsl) noexcept(false)
{
    std::regex pattern("#glsl_type\\s+\"([^\"]*)\"");
    std::smatch matches;
    if (std::regex_search(glsl.cbegin(), glsl.cend(), matches, pattern)) {
        if (matches.size() > 2)
            spdlog::warn("found multiple \"#glsl_type\"");// TODO: can't work, fix this

        std::string flag{ matches[1].str() };
        if (flag == "vertex")
            return GL_VERTEX_SHADER;
        else if (flag == "geometry")
            return GL_GEOMETRY_SHADER;
        else if (flag == "fragment")
            return GL_FRAGMENT_SHADER;
        else
            throw std::runtime_error(std::format("unknown glsl type flag \"{}\"", flag));
    }
    else
        throw std::runtime_error("can't parse glsl type, maybe missing \"#glsl_type \"xxx\"\"");
}

bool quick3d::gl::GLSLManager::check_shader_type_extension_enabled(std::string_view glsl) noexcept
{
    std::regex pattern("#extension\\s+GL_CPPOES_shader_type_flag\\s*:\\s*enable");
    return std::regex_search(glsl.data(), pattern);
}

void quick3d::gl::GLSLManager::remove_cppoes_extensions(std::string& glsl) noexcept
{
    std::vector<std::regex> patterns
    {
        std::regex("#extension\\s+GL_CPPOES_shader_type_flag\\s*:\\s*enable"),
        std::regex("#glsl_type\\s+\"([^\"]*)\"")
        // TODO: GL_CPPOES_include
    };

    for (const auto& pattern : patterns)
        glsl = std::regex_replace(glsl, pattern, " ");
}

void quick3d::gl::GLSLManager::parse_from_file(std::string_view path) noexcept(false)
{
    std::stringstream ss;
    std::ifstream file;
    if (file.open(path.data()); !file.is_open())
        throw std::runtime_error(std::format("can't open glsl file from \"{}\"", path));

    ss << file.rdbuf();
    std::string glsl{ ss.str() };
    if (!check_shader_type_extension_enabled(glsl))
        throw std::runtime_error("parsing glsl without GL_CPPOES_shader_type_flag enabled, this extension is required");
    glsls[std::filesystem::path(path).filename().string()] = glsl;
}

void quick3d::gl::GLSLManager::parse(std::string_view name, std::string_view glsl) noexcept(false)
{
    if (!check_shader_type_extension_enabled(glsl))
        throw std::runtime_error("parsing glsl without GL_CPPOES_shader_type_flag enabled, this extension is required");
    glsls[std::string(name)] = glsl;
}

std::unique_ptr<quick3d::gl::Shader> quick3d::gl::GLSLManager::compile(std::string_view name) noexcept(false)
{
    std::string_view raw_glsl{ glsls[std::string(name)] };
    if (raw_glsl.empty())
        throw std::runtime_error(std::format("can't find shader \"{}\" from GLSLManager", name));

    GLenum glsl_type{ get_glsl_shader_type(std::string(raw_glsl)) };
    std::string glsl{ impl_glsl_include(raw_glsl) };
    remove_cppoes_extensions(glsl);
    return std::make_unique<quick3d::gl::Shader>(glsl_type, glsl);
}