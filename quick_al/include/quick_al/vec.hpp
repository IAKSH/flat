#include <array>
#include <Al/al.h>

namespace quick3d::al
{
    template <std::size_t len>
	using Vec = std::array<ALfloat,len>;
	using Vec3 = Vec<3>;
}