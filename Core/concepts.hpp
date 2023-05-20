#pragma once

#include <array>
#include <string>
#include <concepts>

namespace flat
{
    enum class CoreEventTypeMark
    {
        KeyButton,MouseButton,MouseMove,MouseScroll,WindowResize,WindowMove,WindowLostFocus,WindowFocus,WindowClose,Customed
    };

    enum class KeyButtonCode
    {
        SPACE = 32,
        APOSTROPHE = 39,  /* ' */
        COMMA = 44,  /* , */
        MINUS = 45,  /* - */
        PERIOD = 46,  /* . */
        SLASH = 47,  /* / */
        NUM_0 = 48,
        NUM_1 = 49,
        NUM_2 = 50,
        NUM_3 = 51,
        NUM_4 = 52,
        NUM_5 = 53,
        NUM_6 = 54,
        NUM_7 = 55,
        NUM_8 = 56,
        NUM_9 = 57,
        SEMICOLON = 59,  /* ; */
        EQUAL = 61,  /* = */
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LEFT_BRACKET = 91,  /* [ */
        BACKSLASH = 92,  /* \ */
        RIGHT_BRACKET = 93,  /* ] */
        GRAVE_ACCENT = 96,  /* ` */
        WORLD_1 = 161, /* non-US #1 */
        WORLD_2 = 162, /* non-US #2 */

        /* Function keys */
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        DELETE_KEY = 261,
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        PAGE_UP = 266,
        PAGE_DOWN = 267,
        HOME = 268,
        END = 269,
        CAPS_LOCK = 280,
        SCROLL_LOCK = 281,
        NUM_LOCK = 282,
        PRINT_SCREEN = 283,
        PAUSE = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_DECIMAL = 330,
        KP_DIVIDE = 331,
        KP_MULTIPLY = 332,
        KP_SUBTRACT = 333,
        KP_ADD = 334,
        KP_ENTER = 335,
        KP_EQUAL = 336,
        LEFT_SHIFT = 340,
        LEFT_CONTROL = 341,
        LEFT_ALT = 342,
        LEFT_SUPER = 343,
        RIGHT_SHIFT = 344,
        RIGHT_CONTROL = 345,
        RIGHT_ALT = 346,
        RIGHT_SUPER = 347,
        MENU = 348
    };

    enum class KeyButtonStatus
    {
        Press,Release,Hold
    };

    enum class MouseButtonCode
    {
        Left,Right,Middle
    };

    enum class MouseButtonStatus
    {
        Press,Release
    };

    template <typename T>
    concept WithEventTypeMark = requires(T t,CoreEventTypeMark typemark)
    {
        {t.get_event_typemark()} -> std::same_as<CoreEventTypeMark>;
    };

    template <typename T>
    concept WithKeyButtonCode = requires(T t)
    {
        {t.get_key_button_code()} -> std::same_as<KeyButtonCode>;
    };

    template <typename T>
    concept WithKeyStatus = requires(T t)
    {
        {t.get_key_button_status()} -> std::same_as<KeyButtonStatus>;
    };

    template <typename T>
    concept WithMouseButtonCode = requires(T t)
    {
        {t.get_mouse_button_code()} -> std::same_as<MouseButtonCode>;
    };

    template <typename T>
    concept WithMouseButtonStatus = requires(T t)
    {
        {t.get_mouse_button_status()} -> std::same_as<MouseButtonStatus>;
    };

    template <typename T>
    concept WithMouseMoveInfo = requires(T t)
    {
        {t.get_mouse_movement()} -> std::same_as<std::array<double,2>>;
        {t.get_mouse_movement_x()} -> std::same_as<double>;
        {t.get_mouse_movement_y()} -> std::same_as<double>;
    };

    template <typename T>
    concept WithMouseScrollInfo = requires(T t)
    {
        {t.get_mouse_scroll()} -> std::same_as<std::array<double,2>>;
        {t.get_mouse_scroll_x()} -> std::same_as<double>;
        {t.get_mouse_scroll_y()} -> std::same_as<double>;
    };

    //template <typename T>
    //concept Pointable = requires(T t,float x,float y,float z)
    //{
    //    {t.get_position_x()} -> std::same_as<float>;
    //    {t.get_position_y()} -> std::same_as<float>;
    //    {t.get_position_z()} -> std::same_as<float>;
    //    
    //    {t.set_position_x(x)} -> std::same_as<void>;
    //    {t.set_position_y(y)} -> std::same_as<void>;
    //    {t.set_position_z(z)} -> std::same_as<void>;
    //};

    //template <typename T>
    //concept Velociable = requires(T t,float vx,float vy,float vz)
    //{
    //    {t.get_velocity_x()} -> std::same_as<float>;
    //    {t.get_velocity_y()} -> std::same_as<float>;
    //    {t.get_velocity_z()} -> std::same_as<float>;
    //    
    //    {t.set_velocity_x(vx)} -> std::same_as<void>;
    //    {t.set_velocity_y(vy)} -> std::same_as<void>;
    //    {t.set_velocity_z(vz)} -> std::same_as<void>;
    //};

    //template <typename T>
    //concept Rotatable = requires(T t,float front,float right,float up)
    //{
    //    {t.get_orientation_quat()} -> std::same_as<std::array<float,4>>;
    //    {t.rotate(front,right,up)} -> std::same_as<void>;
    //    {t.move(front,right,up)} -> std::same_as<void>;
    //};

    //template <typename T>
    //concept WithWidthAndHeight = requires(T t,float w,float h)
    //{
    //    {t.get_width()} -> std::same_as<float>;
    //    {t.get_height()} -> std::same_as<float>;
    //    
    //    {t.set_width(w)} -> std::same_as<void>;
    //    {t.set_height(h)} -> std::same_as<void>;
    //};

    //template <typename T>
    //concept WithRadius = requires(T t,float radius)
    //{
    //    {t.get_radius()} -> std::same_as<float>;
    //    
    //    {t.set_radius(radius)} -> std::same_as<void>;
    //};

    //template <typename T>
    //concept Square = Pointable<T> && Velociable<T> && Rotatable<T> && WithWidthAndHeight<T>;

    //template <typename T>
    //concept Ball = Pointable<T> && Velociable<T> && Rotatable<T> && WithRadius<T>;

    //template <typename T>
    //concept PhysicsModel = Square<T> || Ball<T>;

    //template <typename T>
    //concept Window = requires(T t,int x,int y,int w,int h,std::array<int,2> position,std::array<int,2> size,std::string_view title)
    //{
    //    {t.get_window_position()} -> std::same_as<std::array<int,2>>;
    //    {t.get_window_position_x()} -> std::same_as<int>;
    //    {t.get_window_position_y()} -> std::same_as<int>;
    //    {t.get_window_size()} -> std::same_as<std::array<int,2>>;
    //    {t.get_window_size_w()} -> std::same_as<int>;
    //    {t.get_window_size_h()} -> std::same_as<int>;
    //    {t.get_window_title()} -> std::same_as<std::string>;

    //    {t.set_window_position(position)} -> std::same_as<void>;
    //    {t.set_window_position_x(x)} -> std::same_as<void>;
    //    {t.set_window_position_y(y)} -> std::same_as<void>;
    //    {t.set_window_size(size)} -> std::same_as<void>;
    //    {t.set_window_size_w(w)} -> std::same_as<void>;
    //    {t.set_window_size_h(h)} -> std::same_as<void>;
    //    {t.set_window_title(title)} -> std::same_as<void>;
    //};
};