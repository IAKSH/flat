#include "object.hpp"
#include "pipe.hpp"

flat::Frame::Frame(int w,int h)
    : fbo(w,h)
{
}

flat::Frame::~Frame() = default;

const flat::opengl::FrameBuffer& flat::Frame::get() const
{
    return fbo;
}

void flat::Frame::flush_to_screen(const Camera& camera) const
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
    glBindTexture(GL_TEXTURE_2D,fbo.get_texture_id());

    glBindVertexArray(get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}