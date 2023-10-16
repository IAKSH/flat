#pragma once

#include <format>
#include <iostream>
#include <functional>
#include <string_view>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace quick3d::gl
{
    template <bool print_error_info>
    GLenum __check_ogl_error(const char* file_name,int line)
    {
        GLenum error_code;
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
        return error_code;
    }

#define check_ogl_error() __check_ogl_error<true>(__FILE__,__LINE__)
#define get_ogl_error() __check_ogl_error<false>(__FILE__,__LINE__)

    inline static std::string __get_source_string(GLenum source)
    {
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:             return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:     return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:     return "Application";
        case GL_DEBUG_SOURCE_OTHER:           return "Other";
        default:                              return "Unknown";
        }
    }

    inline static std::string __get_type_string(GLenum type)
    {
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:               return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
        case GL_DEBUG_TYPE_OTHER:               return "Other";
        default:                                return "Unknown";
        }
    }

    inline static std::string __get_severity_string(GLenum severity)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:       return "Medium";
        case GL_DEBUG_SEVERITY_LOW:          return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
        default:                             return "Unknown";
        }
    }

    inline static void try_insert_debug_callback() noexcept
    {
        if (glDebugMessageCallback)
        {
            glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param)
                {
                    std::string error_message = std::format(
                        "OpenGL Error!\n"
                        "Source: {}\n"
                        "Type: {}\n"
                        "ID: {}\n"
                        "Severity: {}\n"
                        "Length: {}\n"
                        "Message:\n{}\n"
                        "User Param: {}\n",
                        __get_source_string(source),
                        __get_type_string(type),
                        id,
                        __get_severity_string(severity),
                        length,
                        message,
                        user_param);
#ifdef _MSC_VER
                    MessageBoxA(NULL, error_message.c_str(), "OpenGL Error", MB_OK | MB_ICONERROR);
#else
                    std::cerr << error_message << std::endl;
#endif
                }, nullptr);

            glEnable(GL_DEBUG_OUTPUT);
            std::clog << "OpenGL debug callback binded!" << std::endl;
        }
    }
}