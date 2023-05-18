#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/ctti.hpp"
#include "../../Misc/logger.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <exception>

namespace flat::opengl
{
    template <typename T>
    concept UniformType = misc::any_same<T,float,int,glm::vec2,glm::vec3,glm::vec4,glm::mat4>();

    class ShaderProgram : misc::DisableCopy
    {
    private:
        GLuint program_id;

        GLuint compile_vertex_shader(std::string_view code);
        GLuint compile_fragment_shader(std::string_view code);
        GLuint get_uniform_location(std::string_view uniform);
        void link_shader_program(GLuint vshader_id,GLuint fshader_id);
        void check_vertex_shader(GLuint vshader_id);
        void check_fragment_shader(GLuint fshader_id);

    public:
        ShaderProgram(std::string_view vshader,std::string_view fshader);
        ~ShaderProgram();

        GLuint get_shader_id() const
        {
            return program_id;
        }

        void use()
        {
            glUseProgram(program_id);
        }

        void active_texture(std::string_view texture_uniform,GLuint n)
        {
            glUniform1i(glGetUniformLocation(program_id,texture_uniform.data()),n);
        }

        template <UniformType T>
        void set_uniform(std::string_view uniform,const T& t)
        {
            GLuint location = get_uniform_location(uniform);

            if constexpr(misc::is_same<T,float>())
                glUniform1f(location,t);
            else if constexpr(misc::is_same<T,int>())
                glUniform1i(location,t);
            else if constexpr(misc::is_same<T,glm::vec2>())
                glUniform2fv(location,glm::value_ptr(t));
            else if constexpr(misc::is_same<T,glm::vec3>())
                glUniform3fv(location,glm::value_ptr(t));
            else if constexpr(misc::is_same<T,glm::vec4>())
                glUniform4fv(location,glm::value_ptr(t));
            else if constexpr(misc::is_same<T,glm::mat4>())
                glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(t));
            else
            {
                misc::main_logger->critical("Template switch failed");
                std::terminate();
            }
        }

        template <UniformType T>
        T get_uniform(std::string_view uniform)
        {
            GLint size;
            GLenum type;
            GLuint&& location = get_uniform_location(uniform);
            glGetActiveUniform(program_id,location,0,nullptr,&size,&type,nullptr);

            GLenum aim_type;
            if constexpr(misc::is_same<T,float>())
                aim_type = GL_FLOAT;
            else if constexpr(misc::is_same<T,int>())
                aim_type = GL_INT;
            else if constexpr(misc::is_same<T,glm::vec2>())
                aim_type = GL_FLOAT_VEC2;
            else if constexpr(misc::is_same<T,glm::vec3>())
                aim_type = GL_FLOAT_VEC3;
            else if constexpr(misc::is_same<T,glm::vec4>())
                aim_type = GL_FLOAT_VEC4;
            else if constexpr(misc::is_same<T,glm::mat4>())
                aim_type = GL_FLOAT_MAT4;

            if(size != 1)
            {
                misc::main_logger->critical("got too many uniform named \"{}\" from shader (id = {})",uniform,program_id);
                std::terminate();
            }
            if(type != aim_type)
            {
                misc::main_logger->critical("wrong uniform type when try to get uniform \"{}\" from shader (id = {})",uniform,program_id);
                std::terminate();
            }

            T value;
            if constexpr(misc::is_same<T,float>())
                glGetUniformfv(program_id,location,&value);
            else if constexpr(misc::is_same<T,int>())
                glGetUniformiv(program_id,location,&value);
            else
                glGetUniformfv(program_id,location,glm::value_ptr(value));
            
            return value;
        }
    };
}