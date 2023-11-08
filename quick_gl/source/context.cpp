#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_gl/context.hpp>

quick3d::gl::Context::Context(std::string_view title,int w,int h) noexcept(false)
{
    setup_context(title,w,h);
}

quick3d::gl::Context::~Context() noexcept
{
    destroy_context();
}

static bool initialized{ false };

void quick3d::gl::Context::setup_context(std::string_view title,int w,int h) noexcept(false)
{
    static bool glad_loaded{ false };

    if(initialized)
        throw std::runtime_error("gl context has been initialized for multiple times");
    else
    {
        glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
		glfwSetErrorCallback([](int error, const char* description) {
            std::cerr << std::format("GLFW error: {}\n",description);
			std::terminate();
			});

        windows.push_back(std::make_unique<Window>(title,w,h));
        glfwMakeContextCurrent(windows[0]->get_glfw_window());
    
	    if (!glad_loaded)
	    {
	    	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	    	{
	    		std::cerr << "failed to initialize GLAD" << std::endl;
	    		std::terminate();
	    	}

	    	glad_loaded = true;
	    }

        // glfw has a bug, which will always setup a GL_INVALID_ENUM error code
        // this is to fix this
        glGetError();
    
        //glfwMakeContextCurrent(nullptr);
        initialized = true;
    }
}

void quick3d::gl::Context::destroy_context() noexcept
{
    initialized = false;
    windows.clear();
    glfwTerminate();
}

quick3d::gl::Window& quick3d::gl::Context::get_window(uint32_t index) noexcept(false)
{
    return *windows.at(index);
}

uint32_t quick3d::gl::Context::add_new_window(std::string_view title,int w,int h) noexcept
{
    windows.push_back(std::make_unique<Window>(title,w,h));
    return static_cast<uint32_t>(windows.size() - 1);
}

void quick3d::gl::Context::remove_window(uint32_t index) noexcept(false)
{
    if (index >= windows.size())
        throw std::out_of_range("index out of range");
    windows.erase(std::next(std::begin(windows), index));
}

GLuint quick3d::gl::Context::get_binding_obj_id(GLenum target) noexcept(false)
{
    switch (target)
    {
    case GL_ARRAY_BUFFER:
    case GL_ELEMENT_ARRAY_BUFFER:
        return get_binding_buffer(target);
    case GL_VERTEX_ARRAY:
        return get_binding_vao();
    case GL_PROGRAM:
        return get_binding_shader();
    case GL_TEXTURE_2D:
        return get_binding_texture();
    case GL_TEXTURE_CUBE_MAP:
        return get_binding_cubemap();
    case GL_FRAMEBUFFER:
        return get_binding_framebuffer();
    default:
        throw std::invalid_argument(std::format("invalid ogl target: 0x{:X}", target));
    }
}

void quick3d::gl::Context::swap_window_buffers() noexcept
{
    glfwSwapBuffers(glfwGetCurrentContext());
}

void quick3d::gl::Context::poll_events() noexcept
{
    glfwPollEvents();
}

void quick3d::gl::Context::fill_frame_color(std::array<float, 4> color) noexcept
{
    glClearColor(color[0],color[1],color[2],color[3]);
}

void quick3d::gl::Context::fill_frame_color(float r, float g, float b, float a) noexcept
{
    glClearColor(r,g,b,a);
}

void quick3d::gl::Context::clean_frame_buffers() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

GLuint quick3d::gl::Context::get_binding_buffer(GLenum target) noexcept(false)
{
    GLint id;
    switch (target)
    {
    case GL_ARRAY_BUFFER:
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id);
        break;
    case GL_ELEMENT_ARRAY_BUFFER:
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);
        break;
    case GL_UNIFORM_BUFFER:
        glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &id);
        break;
    case GL_SHADER_STORAGE_BUFFER:
        glGetIntegerv(GL_SHADER_STORAGE_BUFFER_BINDING, &id);
        break;
    case GL_TEXTURE_BUFFER:
        glGetIntegerv(GL_TEXTURE_BUFFER_BINDING, &id);
        break;
    case GL_PIXEL_PACK_BUFFER:
        glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &id);
        break;
    case GL_PIXEL_UNPACK_BUFFER:
        glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &id);
        break;
    default:
        throw std::invalid_argument(std::format("invalied ogl target: 0x{:X}", target));
    }
}

GLuint quick3d::gl::Context::get_binding_vao() noexcept
{
    GLint id;
    glGetIntegerv(GL_VERTEX_ARRAY, &id);
    return id;
}

GLuint quick3d::gl::Context::get_binding_shader() noexcept
{
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);
    return id;
}

GLuint quick3d::gl::Context::get_binding_texture() noexcept
{
    GLint id;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
    return id;
}

GLuint quick3d::gl::Context::get_binding_cubemap() noexcept
{
    GLint id;
    glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &id);
    return id;
}

GLuint quick3d::gl::Context::get_binding_framebuffer() noexcept
{
    GLint id;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &id);
    return id;
}

void quick3d::gl::Context::unbind_buffer(GLenum target) noexcept
{
    glBindBuffer(target, 0);
}

void quick3d::gl::Context::unbind_vao() noexcept
{
    glBindVertexArray(0);
}

void quick3d::gl::Context::unbind_shader() noexcept
{
    glUseProgram(0);
}

void quick3d::gl::Context::unbind_texture() noexcept
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void quick3d::gl::Context::unbind_cubemap() noexcept
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void quick3d::gl::Context::unbind_framebuffer() noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}