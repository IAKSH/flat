#include "object.hpp"
#include "pipe.hpp"

flat::Frame::Frame(int w,int h)
    : fbo(w,h)
{
}

flat::Frame::~Frame() = default;

void flat::Frame::flush_to_screen(const Camera& camera)
{
    opengl::Scope scope;
    default_shader->use();
    
    // temp code, may cause problem
    glm::mat4 trans(1.0f);
    trans *= glm::translate(glm::mat4(1.0f),glm::vec3(get_position_x(),get_position_y(),get_position_z()));
    trans *= glm::scale(glm::mat4(1.0f),glm::vec3(1.0f,1.0f,1.0f));
    trans *= glm::rotate(glm::mat4(1.0f),0.0f,glm::vec3(0.0f,0.0f,1.0f));

    default_shader->set_uniform("transform",trans);
    default_shader->set_uniform("camTrans",camera.get_matrix());

    glBindTexture(GL_TEXTURE_2D,fbo.get_texture_id());

    glBindVertexArray(get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}