#pragma once

namespace flat
{
    template <typename T> struct KeyboardSource
    {
    public:
        bool checkKey(int code) { return static_cast<T*>(this)->imp_checkKey(code); }
    };
}  // namespace flat