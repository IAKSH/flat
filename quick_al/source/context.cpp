#include <vector>
#include <memory>
#include <stdexcept>
#include <quick_al/context.hpp>

quick3d::al::Context::Context(Device& device) noexcept(false)
    : device(&device)
{
    setup_context();
}

quick3d::al::Context::~Context() noexcept
{
    destroy_context();
}

void quick3d::al::Context::setup_context() noexcept(false)
{
    context = alcCreateContext(device->get_device(),nullptr);
    if(!alcMakeContextCurrent(context))
        throw std::runtime_error("can't bind OpenAL context");
}

void quick3d::al::Context::destroy_context() noexcept
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
}

ALCcontext* quick3d::al::Context::get_context() noexcept
{
    return context;
}