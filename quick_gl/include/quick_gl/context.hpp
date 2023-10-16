#pragma once

#include <vector>
#include <memory>
#include <quick_gl/window.hpp>

// Context需要改造
// 改造为统一管理OpenGL object的绑定与其他管理
// 以后绑定任何OpenGL组件，直接context.bind(T);
// 解绑大概像context.unbind(GL_ARRAY_BUFFER);
// 还可以检查是否绑定context.is_binded(GL_ARRAY_BUFFER);
// 以及可以获取目前绑定的object id: context.get_binding(GL_ARRAY_BUFFER);

// context最好不依赖任何类，绑定操作使用template + concepts确定实际参数类型

namespace quick3d::gl
{
    class Context
    {
    private:
        std::vector<std::unique_ptr<Window>> windows;

        void setup_context(std::string_view title,int w,int h) noexcept(false);

        void destroy_context() noexcept;

    public:
        Context(std::string_view title,int w,int h) noexcept;
        Context(Context&) = delete;
        ~Context() noexcept;

        Window& get_window(uint32_t index) noexcept(false);
        uint32_t add_new_window(std::string_view title,int w,int h) noexcept;
        void remove_window(uint32_t index) noexcept(false);
    };
}