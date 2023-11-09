#pragma once

#include <format>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <string_view>
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace quick3d::gl
{
    template <typename T,typename U>
	constexpr bool is_same()
	{
		using Type = std::remove_cvref_t<T>;
		return std::is_same<Type, U>();
	}

	template <typename T,typename... Args>
	constexpr bool any_same()
	{
		if constexpr (sizeof...(Args) == 0)
			return false;
		else
			return (std::same_as<std::remove_reference_t<T>, Args> || ...) || any_same<Args...>();
	}

    template <typename T>
    concept Uniform = any_same<T,int,float,glm::vec2,glm::vec3,glm::vec4,glm::mat3,glm::mat4>();

	class GLSLReader
	{
	private:
		std::stringstream stream;
		std::string_view path;
		void read_all_glsl() noexcept(false);

	public:
		GLSLReader(std::string_view path) noexcept(false);
		GLSLReader(GLSLReader&) = delete;
		~GLSLReader() = default;

		std::string get_glsl() const noexcept;
		std::string_view get_path() const noexcept;
	};

    class Program
    {
    private:
        GLuint program_id;

        template <GLenum shader_type>
        GLuint compile_shader(std::string_view glsl) noexcept;

        template <GLenum shader_type>
        bool check_shader(GLuint shader_id) const noexcept;

		void create_program(std::string_view vs, std::string_view fs) noexcept(false);
		void create_program(std::string_view vs, std::string_view gs, std::string_view fs) noexcept(false);
		void create_program(const GLSLReader& vs, const GLSLReader& fs) noexcept(false);
		void create_program(const GLSLReader& vs, const GLSLReader& gs, const GLSLReader& fs) noexcept(false);
		GLint get_uniform_location(std::string_view uniform) noexcept(false);

    public:
        Program(std::string_view vs, std::string_view fs) noexcept(false);
		Program(std::string_view vs, std::string_view gs, std::string_view fs) noexcept(false);
		Program(const GLSLReader& vs, const GLSLReader& fs) noexcept(false);
		Program(const GLSLReader& vs, const GLSLReader& gs, const GLSLReader& fs) noexcept(false);
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