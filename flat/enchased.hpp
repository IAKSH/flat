#pragma once

namespace ni::flat
{
    template <typename T>
    class Enchased
    {
    private:
        T t;

    public:
        Enchased() {};
        Enchased(const T& t) : t(t) {}
        ~Enchased() = default;
        T& get() {return t;}
    };
}