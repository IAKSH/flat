#pragma once

#include <string_view>

#include <glad/glad.h>

namespace flat::utils
{
	class Shader
	{
	private:
		GLuint shaderID;
		GLuint compileVertexShader(std::string_view code);
		GLuint compileFragmentShader(std::string_view code);
		GLuint linkShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
		bool checkVertexShader(GLuint vertexShaderID);
		bool checkFragmentShader(GLuint fragmentShaderID);

	public:
		Shader() = default;
		~Shader();
		const GLuint& getShaderID() const
		{
			return shaderID;
		}

		void loadFromFile(std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		void loadFromGLSL(std::string_view vertexShaderCode, std::string_view fragmentShaderCode);
	};
}