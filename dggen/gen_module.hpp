#pragma once

#include <concepts>

#include "Renderer/renderer.hpp"

namespace dggen
{
// renderer backend
enum class RENDERER_OPENGL_CORE {};
enum class RENDERER_OPENGL_COMP {};
enum class RENDERER_DIRECTX9 {};
enum class RENDERER_DIRECT11 {};
// audio backend
enum class AUDIOPLAYER_OPENAL_SOFT {};
// mouse input backend
enum class MOUSESOURCE_GLFW {};
// kyboard input backend
enum class KEYBOARDSOURCE_GLFW {};

// static type check
// return true if there's any same type
// using magic :(
template <typename T, typename... Args> constexpr bool same_type()
{
    if constexpr(sizeof...(Args) == 0)
        return false;
    else
        return (std::same_as<T, Args> || ...) || same_type<Args...>();
}

// 下述类型实际上应该填写对应实现类型名
template <typename T>
concept AnyRenderer = same_type<T, RENDERER_OPENGL_CORE, RENDERER_OPENGL_COMP, RENDERER_DIRECTX9, RENDERER_DIRECT11>;
template <typename T>
concept AnyAudioPlayer = same_type<T, AUDIOPLAYER_OPENAL_SOFT>;
template <typename T>
concept AnyMouseSource = same_type<T, MOUSESOURCE_GLFW>;
template <typename T>
concept AnyKeyboardSource = same_type<T, KEYBOARDSOURCE_GLFW>;

template <typename T>
Renderer<T>&& genRenderer()
    requires AnyRenderer<T>
{
    if constexpr(std::same_as<T, RENDERER_OPENGL_CORE>) {}
    else if constexpr(std::same_as<T, RENDERER_OPENGL_COMP>) {}
    else if constexpr(std::same_as<T, RENDERER_DIRECTX9>) {}
    else if constexpr(std::same_as<T, RENDERER_DIRECT11>) {}
}
}  // namespace dggen
