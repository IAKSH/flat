#pragma once

#include "utils/is_same.hpp"

namespace flat::ni
{
	namespace flat::ni::renflag
	{
		class DrawRectangle
		{

		};

		class UseTexture
		{

		};

		class SetColor
		{

		};

		class SetTransform
		{

		};

		class SetTexOffset
		{

		};

		class Flush
		{

		};
	}

	template <typename T>
	concept AnyRenFlag = flat::is_same<T,
		flat::ni::renflag::DrawRectangle,
		flat::ni::renflag::UseTexture,
		flat::ni::renflag::SetColor,
		flat::ni::renflag::SetTransform,
		flat::ni::renflag::SetTexOffset,
		flat::ni::renflag::Flush>();

	template <typename T>
	class RenStream
	{
	public:
		RenStream();
		~RenStream();

		template <AnyRenFlag U>
		RenStream& operator<< (U&& u)
		{
			using UType = std::remove_cvref_t<U>;
			if constexpr (std::is_same<UType, flat::ni::renflag::DrawRectangle>())
				static_cast<T*>(this)->imp_drawRectangle(u);
			else if constexpr (std::is_same<UType, flat::ni::renflag::UseTexture>())
				static_cast<T*>(this)->imp_useTexture(u);
			else if constexpr (std::is_same<UType, flat::ni::renflag::SetColor>())
				static_cast<T*>(this)->imp_setColor(u);
			else if constexpr (std::is_same<UType, flat::ni::renflag::SetTransform>())
				static_cast<T*>(this)->imp_setTransform(u);
			else if constexpr (std::is_same<UType, flat::ni::renflag::SetTexOffset>())
				static_cast<T*>(this)->imp_setTexOffset(u);
			else if constexpr (std::is_same < UType, flat::ni::renflag::Flush())
				static_cast<T*>(this)->imp_flush();
		}
	};
}