#pragma once

namespace flat
{
    template <typename T> struct MouseSource
    {
    public:
        float getMousePositionX() { return static_cast<T*>(this)->imp_getMousePositionX(); }
        float getMousePositionY() { return static_cast<T*>(this)->imp_getMousePositionY(); }
        bool checkMouseLeft() { return static_cast<T*>(this)->imp_checkMouseLeft(); }
        bool checkMouseMiddle() { return static_cast<T*>(this)->imp_checkMouseMiddle(); }
        bool checkMouseRight() { return static_cast<T*>(this)->imp_checkMouseRight(); }
    };
}  // namespace flat