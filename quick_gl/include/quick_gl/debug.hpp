#pragma once

#include <format>
#include <iostream>
#include <string_view>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace quick3d::gl
{
    template <bool print_error_info>
    GLenum __check_ogl_error(const char* file_name,int line)
    {
        GLenum error_code;
#ifdef __GPU_EXT_DEBUGGER__
        goto end;
#endif

        while ((error_code = glGetError()) != GL_NO_ERROR)
        {
            std::string_view error;
            switch (error_code)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            if constexpr (print_error_info)
                std::cerr << std::format("OpenGL ERROR: {} | file {} line {}\n",error,file_name,line) << std::endl;
        }
#ifdef __GPU_EXT_DEBUGGER__
end:
#endif
        return error_code;
    }

#define check_ogl_error() __check_ogl_error<true>(__FILE__,__LINE__)
#define get_ogl_error() __check_ogl_error<false>(__FILE__,__LINE__)
}