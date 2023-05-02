#pragma once

#include <glad/glad.h>

namespace ni::utils::opengl
{
    // OpenGL state manager based on RAII
    class Scope
    {
    public:
        Scope()
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
        }
        ~Scope()
        {
            glPopMatrix();
            glPopAttrib();
        }
    };
}