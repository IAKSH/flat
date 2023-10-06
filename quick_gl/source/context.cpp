#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_gl/context.hpp>

quick3d::gl::Context::Context(std::string_view title,int w,int h) noexcept
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