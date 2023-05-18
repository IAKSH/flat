#include "pipe.hpp"
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
    // TODO:
}

std::unique_ptr<flat::Frame> flat::RenderPipe::ren_frame(const Frame& frame) const
{
    // TODO:
}
