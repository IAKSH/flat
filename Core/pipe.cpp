#include "pipe.hpp"
#include "application.hpp"
#include <GLFW/glfw3.h>
#include <memory>

namespace flat
{
    std::unique_ptr<opengl::ShaderProgram> default_shader;
}

flat::RenderPipe::RenderPipe(std::string_view vshader,std::string_view fshader)
    : shader(vshader,fshader)
{
    // TODO: need to active shader's texture mark
}

flat::RenderPipe::~RenderPipe() = default;

std::unique_ptr<flat::Frame> flat::RenderPipe::ren_texture(const Texture& texture) const
{
    opengl::Scope scope;
    auto& win = Application::get_instance().get_window();
    auto frame = std::make_unique<flat::Frame>(win.get_width(),win.get_height());
    frame->get().use();

    default_shader->use();
    
    glm::mat4 mat(1.0f);
    default_shader->set_uniform("transform",mat);
    default_shader->set_uniform("camTrans",mat);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture.get().get_texture_id());

    glBindVertexArray(texture.get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    return frame;
}

std::unique_ptr<flat::Frame> flat::RenderPipe::ren_frame(const Frame& frame) const
{
    opengl::Scope scope;
    auto& win = Application::get_instance().get_window();
    auto new_frame = std::make_unique<flat::Frame>(win.get_width(),win.get_height());
    new_frame->get().use();

    default_shader->use();
    
    glm::mat4 mat(1.0f);
    default_shader->set_uniform("transform",mat);
    default_shader->set_uniform("camTrans",mat);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,frame.get().get_texture_id());

    glBindVertexArray(frame.get_rect_vao().getVAO());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    return new_frame;
}
