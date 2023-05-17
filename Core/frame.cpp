#include "object.hpp"

flat::Frame::Frame(int w,int h)
    : fbo(w,h)
{
}

flat::Frame::~Frame() = default;

void flat::Frame::flush_to_screen()
{
    // TODO:
}