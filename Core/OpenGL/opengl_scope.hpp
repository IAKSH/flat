#pragma once

#include <glad/glad.h>

namespace flat::opengl
{
    // OpenGl state manager based on RAII
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