#pragma once

#include <cstdint>

namespace ni::utils
{
    class ColorComponent
    {
    private:
        float component;

    public:
        ColorComponent() : component(0) {}
        ColorComponent(float val) : component(val) {}
        ~ColorComponent() = default;
        operator float&() {return component;}
    };

    class Red : public ColorComponent
    {
    public:
        Red() : ColorComponent() {}
        Red(float val) : ColorComponent(val) {}
        ~Red() = default;
    };

    class Green : public ColorComponent
    {
    public:
        Green() : ColorComponent() {}
        Green(float val) : ColorComponent(val) {}
        ~Green() = default;
    };

    class Blue : public ColorComponent
    {
    public:
        Blue() : ColorComponent() {}
        Blue(float val) : ColorComponent(val) {}
        ~Blue() = default;
    };

    class Alpha : public ColorComponent
    {
    public:
        Alpha() : ColorComponent() {}
        Alpha(float val) : ColorComponent(val) {}
        ~Alpha() = default;
    };

    class Color
    {
    private:
        Red r;
        Green g;
        Blue b;
        Alpha a;

    public:
        Color() : r{1.0f},g{1.0f},b{1.0f},a{1.0f} {}
        Color(float r,float g,float b,float a) : r{r},g{g},b{b},a{a} {}
        ~Color() = default;

        operator Red&() {return r;}
        operator Green&() {return g;}
        operator Blue&() {return b;}
        operator Alpha&() {return a;}
    };
}