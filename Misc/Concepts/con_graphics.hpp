#pragma once

#include "../ctti.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace flat::misc::concepts
{
    template <typename T>
    concept Uniform = misc::any_same<T,float,int,glm::vec2,glm::vec3,glm::vec4,glm::mat4>();

    template <typename T,typename U>
    concept Shader = requires(T t,U u,std::string_view texture_uniform,std::string_view uniform,GLuint texture_mark)
    {
        requires(Uniform<U>);
        {t.use()} -> std::same_as<void>;
        {t.get_shader_id()} -> std::same_as<GLuint>;
        {t.active_texture_uniform(texture_uniform,texture_mark)} -> std::same_as<void>;
        {t.set_texture(uniform,u)} -> std::same_as<void>;
        {t.get_uniform(uniform)} -> std::same_as<U>;
    };
}