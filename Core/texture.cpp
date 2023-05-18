#include "object.hpp"
#include "pipe.hpp"
#include "../../Misc/logger.hpp"
#include "OpenGL/opengl_scope.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
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

void flat::Texture::flush_to_screen(const Camera& camera)
{
    opengl::Scope scope;
    default_shader->use();
    
    glm::mat4 trans(1.0f);
    trans *= glm::translate(glm::mat4(1.0f),glm::vec3(get_position_x(),get_position_y(),get_position_z()));
    trans *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,1.0f));
    trans *= glm::toMat4(glm::quat(get_orientation()[0],get_orientation()[1],get_orientation()[2],get_orientation()[3]));

    default_shader->set_uniform("transform",trans);
    default_shader->set_uniform("camTrans",camera.get_matrix());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture->get_texture_id());

    glBindVertexArray(get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}