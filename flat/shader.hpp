#pragma once


#include <memory>
#include <functional>
#include <type_traits>
#include <string_view>

#include "../utils/shader.hpp"
#include "any_same.hpp"

#include "glm/fwd.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace ni::flat
{
    template <typename T>
    concept UniformArgType = any_same<T,float,int,glm::vec2,glm::vec3,glm::vec4,glm::mat4>();

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
        struct Uniform
        {
            GLint location;

            Uniform(GLint loc) : location{loc} {}
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
        };

        Uniform operator[](std::string_view uniform)
        {
            auto location = glGetUniformLocation(getShaderID(), uniform.data());
            return Uniform{location};
        }
    };
}