#pragma once

#include "../core/template.hpp"
#include <glad/glad.h>
#include <string_view>

namespace ni::utils
{
	class Shader : public core::DisableCopy
	{
	private:
		GLuint shaderID;
		GLuint compileVertexShader(std::string_view code);
		GLuint compileFragmentShader(std::string_view code);
		GLuint linkShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
		void checkVertexShader(GLuint vertexShaderID);
		void checkFragmentShader(GLuint fragmentShaderID);

	public:
		Shader() = default;
		~Shader();
		const GLuint& getShaderID() const
		{
			return shaderID;
		}

		void loadFromFile(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		void loadFromGLSL(std::string_view vertexShaderCode, std::string_view fragmentShaderCode);

		operator GLuint() const
		{
			return shaderID;
		}
	};
}