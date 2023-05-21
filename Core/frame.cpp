#include "object.hpp"
#include "pipe.hpp"

flat::Frame::Frame(int w,int h)
    : fbo(w,h)
{
}

flat::Frame::~Frame() = default;

void flat::Frame::flush() const
{
    // TODO: ...
};

void flat::Frame::flush(const Camera& camera) const
{
    opengl::Scope scope;
    default_shader->use();

    const auto& orien = rotator.get_orientation_quat();
    
    glm::mat4 trans(1.0f);
    trans *= glm::translate(glm::mat4(1.0f),glm::vec3(position[0],position[1],position[2]));
    trans *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,1.0f));
    trans *= glm::toMat4(glm::quat(orien[0],orien[1],orien[2],orien[3]));

    default_shader->set_uniform("transform",trans);
    default_shader->set_uniform("camTrans",get_camera_matrix(camera));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,fbo.get_texture_id());

    // TODO: ...
    //glBindVertexArray(get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}