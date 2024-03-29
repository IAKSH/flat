#pragma once

#include "flat/text_renderer.hpp"
#include "utils/timer.hpp"
#include <cstdio>
#include <string_view>

#include <stdio.h>
#include <stdlib.h>

namespace demo
{
    using ni::flat::TextRenderer;
    using ni::utils::TimeRecorder;
    using ni::utils::MilliSeconds;

    class Text
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

        void tryToWrite()
        {
            if(index != str.length() && recoder.getSpanAsMilliSeconds() >= interval)
            {
                ++index;
                recoder.update();
            }

            std::u32string_view currentStr{std::begin(str),std::begin(str) + index};
            ren.drawText(currentStr,ni::flat::Point(0.0f,200.0f,0.9f),
				ni::flat::Color(1.0f,1.0f,1.0f,1.0f),ni::flat::Scale(1.0f));
        }
    };
}