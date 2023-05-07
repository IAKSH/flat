#pragma once

#include <array>

namespace ni::flat
{
    class Color
    {
    private:
        std::array<float,4> rgba;

    public:
        Color() : rgba{1.0f,1.0f,1.0f,1.0f} {}
        Color(const float& r,const float& g,const float& b,const float& a) : rgba{r,g,b,a} {}
        const float& getRed() const {return rgba[0];}
        const float& getGreen() const {return rgba[1];}
        const float& getBlue() const {return rgba[2];}
        const float& getAlpha() const {return rgba[3];}
        void setRed(const float& val) {rgba[0] = val;}
        void setGreen(const float& val) {rgba[1] = val;}
        void setBlue(const float& val) {rgba[2] = val;}
        void setAlpha(const float& val) {rgba[3] = val;}
    };
}