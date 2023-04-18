#pragma once

#include "../flat/text_renderer.hpp"
#include "../utils/timer.hpp"
#include "../utils/mass_point.hpp"
#include <cstdio>
#include <string_view>

namespace Flat
{
    using ni::flat::TextRenderer;
    using ni::utils::TimeRecorder;
    using ni::utils::MilliSeconds;
    using ni::utils::Font;
    using ni::utils::Point;

    class Text : public Point
    {
    private:
        TextRenderer& ren;
        MilliSeconds interval;
        TimeRecorder recoder;
        std::u32string_view str;
        size_t index;

    public:
        Text(TextRenderer& ren,MilliSeconds interval,std::u32string_view str) : ren{ren},interval{interval},str{str},index{0} {}
        Text(Text&) = delete;
        ~Text() = default;

        void tryToWrite(Font& font)
        {
            if(index != str.length() && recoder.getSpanAsMilliSeconds() >= interval)
            {
                ++index;
                recoder.update();
            }

            std::u32string_view currentStr{std::begin(str),std::begin(str) + index};
            ren.drawText(currentStr,ni::flat::Point(getPosX(),getPosY(),getPosZ()),
				ni::flat::Color(1.0f,1.0f,1.0f,1.0f),ni::flat::Scale(1.0f),&font);
        }
    };
}