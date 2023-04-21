#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <charconv>

namespace ni::utils
{
    template <typename T>
    std::u32string to_u32string(const T& value)
    {
        std::array<char, 64> buffer{'\0'};
        auto result = std::to_chars(buffer.begin(), buffer.end(), value);
        std::u32string str;
        for(const auto& c : buffer)
        {
            if(c == '\0')
                break;
            str += static_cast<char32_t>(c);
        }
        return str;
    }
}