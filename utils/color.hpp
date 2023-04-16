#pragma once

#include <cstdint>

namespace ni::utils
{
    class ColorComponent
    {
    private:
        uint8_t component;

    public:
        ColorComponent() : component(0) {}
        ColorComponent(uint8_t val) : component(val) {}
        ~ColorComponent() = default;
        operator uint8_t&() {return component;}
    };

    class Red : public ColorComponent
    {
    public:
        Red() : ColorComponent() {}
        Red(uint8_t val) : ColorComponent(val) {}
        ~Red() = default;
    };

    class Green : public ColorComponent
    {
    public:
        Green() : ColorComponent() {}
        Green(uint8_t val) : ColorComponent(val) {}
        ~Green() = default;
    };

    class Blue : public ColorComponent
    {
    public:
        Blue() : ColorComponent() {}
        Blue(uint8_t val) : ColorComponent(val) {}
        ~Blue() = default;
    };

    class Alpha : public ColorComponent
    {
    public:
        Alpha() : ColorComponent() {}
        Alpha(uint8_t val) : ColorComponent(val) {}
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
        Color() : r{0},g{0},b{0},a{0} {}
        Color(uint8_t r,uint8_t g,uint8_t b,uint8_t a) : r{r},g{g},b{b},a{a} {}
        ~Color() = default;

        operator Red&() {return r;}
        operator Green&() {return g;}
        operator Blue&() {return b;}
        operator Alpha&() {return a;}
    };
}