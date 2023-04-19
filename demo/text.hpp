#pragma once

#include "../flat/text_renderer.hpp"
#include "../utils/timer.hpp"
#include "../utils/gameobj.hpp"
#include "../utils/color.hpp"
#include "../utils/enchased.hpp"
#include "../utils/any_same.hpp"
#include "../utils/camera.hpp"
#include <cstdio>
#include <string>
#include <string_view>
#include <type_traits>

namespace Flat
{
    using ni::flat::TextRenderer;
    using ni::utils::TimeRecorder;
    using ni::utils::MilliSeconds;
    using ni::utils::Font;
    using ni::utils::GameObject;
    using ni::utils::Color;
    using ni::utils::Scale;
    using ni::utils::Point;
    using ni::utils::Camera2D;
    using ni::utils::any_same;

    template <typename T>
    concept TextAttrib = any_same<T,Color,Scale,Point,Font,TextRenderer,std::u32string_view,std::u32string>();

    class Text : public GameObject
    {
    protected:
        TextRenderer* ren;
        Font* font;
        Camera2D* cam;
        Color color;
        Scale scale;
        std::u32string_view str;

    public:
        Text(TextRenderer& ren,Font& font,std::u32string_view str)
            : ren(&ren),font(&font),str(str),cam(nullptr)
        {
        }

        Text(TextRenderer& ren,Font& font,Camera2D* cam,std::u32string_view str)
            : ren(&ren),font(&font),str(str),cam(cam)
        {
        }

        Text(Text&) = delete;
        ~Text() = default;

        template <TextAttrib T>
        void set(T&& t)
        {
            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,Color>)
                color = t;
            else if constexpr(std::is_same_v<U,Point>)
            {
                const Point& p = t;
                setPosX(p.getPosX());
                setPosY(p.getPosY());
                setPosZ(p.getPosZ());
            }
            else if constexpr(std::is_same_v<U,Scale>)
                scale = t;
            else if constexpr(std::is_same_v<U,Font>)
                font = &t;
            else if constexpr(std::is_same_v<U,TextRenderer>)
                ren = &t;
            else if constexpr(std::is_same_v<U,std::u32string_view>)
                str = t;
            else if constexpr(std::is_same_v<U,std::u32string>)
                str = t;
        }

        template <TextAttrib T>
        const T& get()
        {
            using U = std::remove_cvref_t<T>;
            if constexpr(std::is_same_v<U,Color>)
                return color;
            else if constexpr(std::is_same_v<U,Point>)
                return static_cast<Point&>(*this);
            else if constexpr(std::is_same_v<U,Scale>)
                return scale;
            else if constexpr(std::is_same_v<U,Font>)
                return font;
            else if constexpr(std::is_same_v<U,TextRenderer>)
                return ren;
            else if constexpr(std::is_same_v<U,std::u32string_view>)
                return str;
        }
        
        virtual void onAttach() override
        {
            
        }

        virtual void onDetach() override
        {

        }

        virtual void onUpdate() override
        {

        }

        virtual void onRender() override
        {
            ren->drawText(str,static_cast<Point>(*this),
				color,scale,font,cam);
        }

        virtual void onEvent(ni::core::Event& e) override
        {

        }
    };

    class RollingText : public Text
    {
    private:
        MilliSeconds interval;
        TimeRecorder recoder;
        size_t index;

    public:
        RollingText(TextRenderer& ren,Font& font,MilliSeconds interval,std::u32string_view str)
            : Text(ren,font,str),interval(interval),index(0)
        {
        }

        RollingText(RollingText&) = delete;
        ~RollingText() = default;

        virtual void onRender() override
        {
            if(index != str.length() && recoder.getSpanAsMilliSeconds() >= interval)
            {
                ++index;
                recoder.update();
            }

            std::u32string_view currentStr{std::begin(str),std::begin(str) + index};
            ren->drawText(currentStr,static_cast<Point>(*this),
				color,scale,font,cam);
        }
    };
}