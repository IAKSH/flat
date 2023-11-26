#pragma once

#include <format>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <string_view>
#include <unordered_map>
#include <glad/gles2.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace quick3d::gl
{
	class Shader
	{
	private:
		GLuint shader_id;
		void check_compile_status() noexcept(false);
		void compile(GLenum shader_type,std::string_view glsl) noexcept(false);

	public:
		Shader(GLenum shader_type, std::string_view glsl) noexcept(false);
		Shader(Shader&) = delete;
		~Shader() noexcept;
		GLuint get_id() const noexcept;
	};

	class GLSLManager
	{
	private:
		std::unordered_map<std::string, std::string> glsls;
		// ʵ��һ��ƽ̨�޹صģ�����ʵ�ֵ�GL_CPPOES_include��չ
		// �����չ��ѡ
		// #extension GL_CPPOES_include : enable
		// #glsl_name "xxx"
		// #include "xxx"
		std::string impl_glsl_include(std::string_view glsl) noexcept(false);
		// ʵ��һ��ƽ̨�޹صģ�����ʵ�ֵ�GL_CPPOES_shader_type
		// �����չ���뿪��
		// #extension GL_CPPOES_shader_type_flag : enable
		// #glsl_type "vertex"
		// #glsl_type "geometry"
		// #glsl_type "fragment"
		GLenum get_glsl_shader_type(std::string glsl) noexcept(false);
		bool check_shader_type_extension_enabled(std::string_view glsl) noexcept;
		void remove_cppoes_extensions(std::string& glsl) noexcept;

	public:
		GLSLManager() = default;
		GLSLManager(GLSLManager&) = delete;
		~GLSLManager() = default;
		
		void parse_from_file(std::string_view path) noexcept(false);
		void parse(std::string_view name, std::string_view glsl) noexcept(false);
		std::unique_ptr<Shader> compile(std::string_view name) noexcept(false);
	};

	template <typename T, typename U>
	constexpr bool is_same()
	{
		using Type = std::remove_cvref_t<T>;
		return std::is_same<Type, U>();
	}

	template <typename T, typename... Args>
	constexpr bool any_same()
	{
		if constexpr (sizeof...(Args) == 0)
			return false;
		else
			return (std::same_as<std::remove_reference_t<T>, Args> || ...) || any_same<Args...>();
	}

	template <typename T>
	concept Uniform = any_same<T, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>();

    class Program
    {
    private:
        GLuint program_id;

		void create_program(const Shader& vs, const Shader& fs) noexcept(false);
		void create_program(const Shader& vs, const Shader& gs, const Shader& fs) noexcept(false);
		GLint get_uniform_location(std::string_view uniform) noexcept(false);

    public:
        Program(const Shader& vs, const Shader& fs) noexcept(false);
		Program(const Shader& vs, const Shader& gs, const Shader& fs) noexcept(false);
        Program(Program&) = delete;
        ~Program() noexcept;

        GLuint get_program_id() const noexcept;
		void bind_uniform_block(std::string_view name, GLuint point) noexcept(false);

        template <Uniform T>
        void set_uniform(std::string_view uniform,const T& t) noexcept(false)
        {
            glUseProgram(program_id);

            GLint location{ get_uniform_location(uniform) };
			if constexpr (is_same<T, int>() || is_same<T, bool>())
				glUniform1i(location, t);
			else if constexpr (is_same<T, float>())
				glUniform1f(location, t);
			else if constexpr (is_same<T, glm::vec2>())
				glUniform2fv(location, 1, glm::value_ptr(t));
			else if constexpr (is_same<T, glm::vec3>())
				glUniform3fv(location, 1, glm::value_ptr(t));
			else if constexpr (is_same<T, glm::vec4>())
				glUniform4fv(location, 1, glm::value_ptr(t));
			else if constexpr (is_same<T, glm::mat3>())
				glUniformMatrix3fv(location, 1, false, glm::value_ptr(t));
			else if constexpr (is_same<T, glm::mat4>())
				glUniformMatrix4fv(location, 1, false, glm::value_ptr(t)); 
			else
				throw std::runtime_error("compile-time uniform type check failed");

            glUseProgram(0);
        }

        template <Uniform T>
        T get_uniform(std::string_view uniform) noexcept(false)
        {
            int size;
			unsigned int type;

			GLint location;
            if(location = get_uniform_location(uniform);!location)
                throw std::runtime_error(std::format("uniform {} not found from shader program {}",uniform,program_id));

			glGetActiveUniform(program_id, location, 0, nullptr, &size, &type, nullptr);

			unsigned int aimed_type;
			if constexpr (is_same<T, int>())
				aimed_type = GL_INT;
			else if constexpr (is_same<T, float>())
				aimed_type = GL_FLOAT;
			else if constexpr (is_same<T, glm::vec2>())
				aimed_type = GL_FLOAT_VEC2;
			else if constexpr (is_same<T, glm::vec3>())
				aimed_type = GL_FLOAT_VEC3;
			else if constexpr (is_same<T, glm::vec4>())
				aimed_type = GL_FLOAT_VEC4;
			else if constexpr (is_same<T, glm::mat3>())
				aimed_type = GL_FLOAT_MAT3;
			else if constexpr (is_same<T, glm::mat4>())
				aimed_type = GL_FLOAT_MAT4;
			else
				throw std::runtime_error("compile-time uniform type check failed");

			if (size != 1)
				throw std::runtime_error("uniform name conflict");
			if (type != aimed_type)
				throw("unsupported uniform type");

			T ret_uniform;
			if constexpr (is_same<T, int>())
				glGetUniformiv(program_id, location, &ret_uniform);
			else if constexpr (is_same<T, float>())
				glGetUniformfv(program_id, location, &ret_uniform);
			else
				glGetUniformfv(program_id, location, glm::value_ptr(ret_uniform));

			return ret_uniform;
        }
    };
}