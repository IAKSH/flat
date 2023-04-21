#pragma once

namespace ni::utils
{
    template <typename T>
    class Enchased
    {
    private:
        T t;

    public:
        Enchased() = default;
        Enchased(const T& t) : t{t} {}
        ~Enchased() = default;

        operator T() const { return t; }
        Enchased operator+(const Enchased& other) const { return Enchased(t + other); }
        Enchased operator-(const Enchased& other) const { return Enchased(t - other); }
        Enchased operator*(const Enchased& other) const { return Enchased(t * other); }
        Enchased operator/(const Enchased& other) const { return Enchased(t / other); }
    };

    class Scale : public Enchased<float>
    {
    public:
        Scale() : Enchased(1.0f) {}
        Scale(float s) : Enchased(s) {}
        ~Scale() = default;
    };
}