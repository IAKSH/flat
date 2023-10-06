#pragma once

#include <vector>
#include <memory>
#include <quick_gl/window.hpp>

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