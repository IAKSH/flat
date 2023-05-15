#pragma once

namespace flat::misc
{
    // any class inherted from this will disable its copy constructor
    struct DisableCopy
    {
        DisableCopy() = default;
        DisableCopy(DisableCopy&) = delete;
        ~DisableCopy() = default;
    };
}