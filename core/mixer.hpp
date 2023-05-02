#pragma once

#include "template.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace ni::core
{
	template <typename Diverse>
	struct Mixer : public DisableCopy
	{
	};
}