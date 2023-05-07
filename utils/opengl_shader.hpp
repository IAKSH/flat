#pragma once

#include "../core/template.hpp"
#include "../core/loggers.hpp"
#include "glm/fwd.hpp"
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace ni::utils::opengl
{
    template <typename T>
    concept UniformType = ni::core::anySame<T,float,int,glm::vec2,glm::vec3,glm::vec4,glm::mat4>();

    class ShaderProgram : public core::DisableCopy
    {
    private:
        GLuint programID;
        GLuint compileVertexShader(std::string_view code);
        GLuint compileFragmentShader(std::string_view code);
        GLuint linkShaderProgram(const GLuint& vshaderID,const GLuint& fshaderID);
        GLuint tryGetUniformLocation(std::string_view uniform);
        void checkVertexShader(GLuint vshaderID);
        void checkFragmentShader(GLuint vshaderID);
        void loadFromGLSL(std::string_view vshader,std::string_view fshader);

    public:
        ShaderProgram(std::string_view vshader,std::string_view fshader);
        ~ShaderProgram();

        const GLuint& getShaderID() const {return programID;}
        void use() {glUseProgram(programID);}
        void activeTexture(std::string_view texUniform,GLuint n) {glUniform1i(glGetUniformLocation(programID,texUniform.data()),n);}

        template <UniformType T>
        void setUniform(std::string_view uniform,T&& t)
        {
            GLuint location = tryGetUniformLocation(uniform);

            if constexpr (core::isSame<T,float>())
                glUniform1f(location,t);
            else if constexpr (core::isSame<T,int>())
                glUniform1i(location,t);
            else if constexpr (core::isSame<T,glm::vec2>())
                glUniform2fv(location,glm::value_ptr(t));
            else if constexpr (core::isSame<T,glm::vec3>())
                glUniform3fv(location,glm::value_ptr(t));
            else if constexpr (core::isSame<T,glm::vec4>())
                glUniform4fv(location,glm::value_ptr(t));
            else if constexpr (core::isSame<T,glm::mat4>())
                glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(t));
        }

        template <UniformType T>
        T getUniform(std::string_view uniform)
        {
            GLint size;
            GLenum type;
            GLuint&& location = tryGetUniformLocation(uniform);
            glGetActiveUniform(programID,location,0,nullptr,&size,&type,nullptr);
            
            GLenum aimType;
            if constexpr (core::isSame<T,float>())
                aimType = GL_FLOAT;
            else if constexpr (core::isSame<T,int>())
                aimType = GL_INT;
            else if constexpr (core::isSame<T,glm::vec2>())
                aimType = GL_FLOAT_VEC2;
            else if constexpr (core::isSame<T,glm::vec3>())
                aimType = GL_FLOAT_VEC3;
            else if constexpr (core::isSame<T,glm::vec4>())
                aimType = GL_FLOAT_VEC4;
            else if constexpr (core::isSame<T,glm::mat4>())
                aimType = GL_FLOAT_MAT4;
            
            if(size != 1)
            {
                core::utilsLogger->critical("got too many uniform named \"{}\" from shader (id = {})",uniform,programID);
                std::terminate();
            }
            if(type != aimType)
            {
                core::utilsLogger->critical("wrong uniform type when try to get uniform \"{}\" from shader (id = {})",uniform,programID);
                std::terminate();
            }

            T value;
            if constexpr (core::isSame<T,float>())
                glGetUniformfv(programID,location,&value);
            else if constexpr (core::isSame<T,int>())
                glGetUniformiv(programID,location,&value);
            else
                glGetUniformfv(programID,location,glm::value_ptr(value));

            return value;
        }
    };
}