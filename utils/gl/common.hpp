#pragma once
#include <array>
#include "../template.hpp"
#include "../physics/common.hpp"

namespace ni::opengl
{
	struct Red : public utils::__Enchased<float>
    {
        Red(const float& f = 1.0f) : __Enchased(f) {}
    };

    struct Green : public utils::__Enchased<float>
    {
        Green(const float& f = 1.0f) : __Enchased(f) {}
    };

    struct Blue : public utils::__Enchased<float>
    {
        Blue(const float& f = 1.0f) : __Enchased(f) {}
    };

    struct Alpha : public utils::__Enchased<float>
    {
        Alpha(const float& f = 1.0f) : __Enchased(f) {}
    };

	template <typename T>
	concept ColorData = anySame<T,Red,Green,Blue,Alpha>();

	class Color
	{
	private:
		std::array<float, 4> rgba;

	public:
        Color() : rgba{1.0f,1.0f,1.0f,1.0f} {}
		Color(const float& r,const float& g,const float& b,const float& a) : rgba{r,g,b,a} {}
		~Color() = default;

        const float& getRed() const { return rgba[0]; }
        const float& getGreen() const { return rgba[1]; }
        const float& getBlue() const { return rgba[2]; }
        const float& getAlpha() const { return rgba[3]; }
        void setRed(const float& f) { rgba[0] = f; }
        void setGreen(const float& f) { rgba[1] = f; }
        void setBlue(const float& f) { rgba[2] = f; }
        void setAlpha(const float& f) { rgba[3] = f; }
		
		template <ColorData T>
		void set(T&& t)
		{
			if constexpr (utils::isSame<T,Red>())
				rgba[0] = t;
			else if constexpr (utils::isSame<T,Green>())
				rgba[1] = t;
			else if constexpr (utils::isSame<T,Blue>())
				rgba[2] = t;
			else if constexpr (utils::isSame<T,Alpha>())
				rgba[3] = t;
		}

		template <ColorData T>
		T get()
		{
			if constexpr (utils::isSame<T,Red>())
				return Red(rgba[0]);
			else if constexpr (utils::isSame<T,Green>())
				return Green(rgba[1]);
			else if constexpr (utils::isSame<T,Blue>())
				return Blue(rgba[2]);
			else if constexpr (utils::isSame<T,Alpha>())
				return Alpha(rgba[3]);
		}
	};
}

namespace ni::opengl
{
    template <typename T>
    concept TextureCoordReturnType = utils::anySame<T,utils::AxisCoordinateX,utils::AxisCoordinateY>();

    class TextureCoord
    {
    private:
        std::array<float,2> xy;

    public:
        TextureCoord(const float& x,const float& y) : xy{x,y} {}
        ~TextureCoord() = default;

        const float& getX() const { return xy[0]; }
        const float& getY() const { return xy[1]; }
        void setX(const float& f) { xy[0] = f; }
        void setY(const float& f) { xy[1] = f; }

        template <TextureCoordReturnType T>
        T get()
        {
            if constexpr (utils::isSame<T,utils::AxisCoordinateX>())
                return utils::AxisCoordinateX(xy[0]);
            else if constexpr (utils::isSame<T,utils::AxisCoordinateY>())
                return utils::AxisCoordinateY(xy[1]);
        }

        template <TextureCoordReturnType T>
        void set(T&& t)
        {
            if constexpr (utils::isSame<T,utils::AxisCoordinateX>())
                xy[0] = t;
            else if constexpr (utils::isSame<T,utils::AxisCoordinateY>())
                xy[1] = t;
        }
    };
}

namespace ni::opengl
{
    struct Scale : public utils::__Enchased<float>
    {
        Scale(const float& f = 0.0f) : __Enchased(f) {}
    };
}