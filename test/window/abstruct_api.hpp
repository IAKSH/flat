#pragma once

#include <string_view>

namespace winapi
{
    template <typename T> class Window
    {
    public:
        Window() {}
        ~Window() {}
        void updateWindow() { static_cast<T*>(this)->imp_updateWindow(); }
        void setWindowPosX(int x) { static_cast<T*>(this)->imp_setWindowPosX(x); }
        void setWindowPosY(int y) { static_cast<T*>(this)->imp_setWindowPosY(y); }
        void setWindowSizeH(int h) { static_cast<T*>(this)->imp_setWindowSizeH(h); }
        void setWindowSizeW(int w) { static_cast<T*>(this)->imp_setWindowSizeW(w); }
        void setWindowTitle(std::string_view s) { static_cast<T*>(this)->imp_setWindowTitle(s); }
        int getWindowPosX() { return static_cast<T*>(this)->imp_getWindowPosX(); }
        int getWindowPosY() { return static_cast<T*>(this)->imp_getWindowPosY(); }
        int getWindowSizeH() { return static_cast<T*>(this)->imp_getWindowSizeH(); }
        int getWindowSizeW() { return static_cast<T*>(this)->imp_getWindowSizeW(); }
    };
}  // namespace winapi