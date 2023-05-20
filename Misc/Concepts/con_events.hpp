#pragma once

#include <concepts>

namespace flat::misc::concepts
{
    enum class CoreEvent
    {
        KeyPress,KeyRelease,MousePress,MouseRelease,MouseMove,MouseScroll,
        WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMove
    };

    template <typename T>
    concept Event = requires(T t)
    {
        {t.get_event_type()} -> std::same_as<CoreEvent>;
    };
}