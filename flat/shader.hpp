#pragma once

#include "../utils/shader.hpp"
#include "../utils/logger.hpp"
#include "../utils/template.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <exception>
#include <memory>
#include <functional>
#include <type_traits>
#include <string_view>

namespace ni::flat
{
    template <typename T>
    concept UniformArgType = ni::utils::any_same<T,float,int,glm::vec2,glm::vec3,glm::vec4,glm::mat4>();

    template <UniformArgType T>
    class UniformArg
    {
    private:
        const T& data;

    public:
        UniformArg(const T& t) : data{t} {}
        ~UniformArg() = default;
        const T& get() const { return data; }
    };

    class Shader : public ni::utils::Shader
    {
    public:
        class Uniform
        {
        private:
            Shader& shader;
            GLint location;

        public:
            Uniform(Shader& shader,GLint loc) : shader{shader},location{loc} {}
            template <typename T>
            void operator=(const UniformArg<T>& arg)
            {
                if constexpr (std::is_same_v<T,float>)
                    glUniform1f(location,arg.get());
                else if constexpr (std::is_same_v<T,int>)
                    glUniform1i(location,arg.get());
                else if constexpr (std::is_same_v<T,glm::vec2>)
                    glUniform2fv(location,glm::value_ptr(arg.get()));
                else if constexpr (std::is_same_v<T,glm::vec3>)
                    glUniform3fv(location,glm::value_ptr(arg.get()));
                else if constexpr (std::is_same_v<T,glm::vec4>)
                    glUniform4fv(location,glm::value_ptr(arg.get()));
                else if constexpr (std::is_same_v<T,glm::mat4>)
                    glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(arg.get()));
            }

            template <UniformArgType T>
            operator T() const
            {
                GLint size;
                GLenum type;
                glGetActiveUniform(shader.getShaderID(),location,0,nullptr,&size,&type,nullptr);

                GLenum aimType;
                if constexpr (std::is_same_v<T,float>)
                    aimType = GL_FLOAT;
                else if constexpr (std::is_same_v<T,int>)
                    aimType = GL_INT;
                else if constexpr (std::is_same_v<T,glm::vec2>)
                    aimType = GL_FLOAT_VEC2;
                else if constexpr (std::is_same_v<T,glm::vec3>)
                    aimType = GL_FLOAT_VEC3;
                else if constexpr (std::is_same_v<T,glm::vec4>)
                    aimType = GL_FLOAT_VEC4;
                else if constexpr (std::is_same_v<T,glm::mat4>)
                    aimType = GL_FLOAT_MAT4;

                if(size != 1 || type != aimType)
                {
                    ni::utils::otherLogger()->critical("uniform cast failed");
                    std::terminate();
                }

                T value;
                if constexpr (std::is_same_v<T,float>)
                    glGetUniformfv(shader.getShaderID(),location,&value);
                else if constexpr (std::is_same_v<T,int>)
                    glGetUniformiv(shader.getShaderID(),location,&value);
                else
                    glGetUniformfv(shader.getShaderID(),location,glm::value_ptr(value));

                return value;
            }
        };

        Uniform operator[](std::string_view uniform)
        {
            auto location = glGetUniformLocation(getShaderID(), uniform.data());
            return Uniform{*this,location};
        }

        Uniform operator[](const char* uniform)
        {
            auto location = glGetUniformLocation(getShaderID(), uniform);
            return Uniform{*this,location};
        }
    };
}