#include "pipe.hpp"
#include <memory>

namespace flat
{
    opengl::ShaderProgram default_shader(default_vertex_shader,default_fragment_shader);
}

flat::RenderPipe::RenderPipe(std::string_view vshader,std::string_view fshader)
    : shader(vshader,fshader)
{
}

flat::RenderPipe::~RenderPipe() = default;

std::unique_ptr<flat::Frame> flat::RenderPipe::ren_texture(const Texture& texture) const
{
    // TODO:
}

std::unique_ptr<flat::Frame> flat::RenderPipe::ren_frame(const Frame& frame) const
{
    // TODO:
}
