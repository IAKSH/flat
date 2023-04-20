#pragma once

namespace ni::utils
{
    struct DisableCopy
    {
        DisableCopy() = default;
        DisableCopy(DisableCopy&) = delete;
        ~DisableCopy() = default;
    };
}