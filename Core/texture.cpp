#include "glm/ext/matrix_transform.hpp"
#include "object.hpp"
#include "pipe.hpp"
#include "../../Misc/logger.hpp"
#include "OpenGL/opengl_scope.hpp"
#include <exception>
#include <memory>

flat::Texture::Texture(const unsigned char* const data,int x,int y,int w,int h,int channels)
{
    if(channels == 1)
    {
        misc::main_logger->critical("image with only 1 channel is not supported yet");
        std::terminate();
    }
    else if(channels == 3)
    {
        texture = std::make_unique<opengl::Texture<opengl::ColorChannel::RGB,opengl::ColorChannel::RGBA>>(data,x,y,w,h);
    }
    else if(channels == 4)
    {
        texture = std::make_unique<opengl::Texture<opengl::ColorChannel::RGBA,opengl::ColorChannel::RGBA>>(data,x,y,w,h);
    }
    else
    {
        misc::main_logger->critical("Unknown image channel type");
        std::terminate();
    }
}

flat::Texture::~Texture() = default;

void flat::Texture::flush_to_screen()
{
    // TODO:
    openal::Scope scope;
    
    flat::default_shader.use();
    glm::mat4 trans_matrix(1.0f);
    trans_matrix *= glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f));
    trans_matrix *= glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    trans_matrix *= glm::rotate(glm::mat4(1.0f),0.0f,glm::vec3(0.0f,0.0f,1.0f));
    flat::default_shader.set_uniform("transform",trans_matrix);
    
}