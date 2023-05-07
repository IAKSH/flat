#pragma once

#include "enchased.hpp"

namespace ni::flat
{
    struct Scale : public Enchased<float>
    {
        Scale(const float& val = 1.0f) : Enchased(val) {}
    };
}