#pragma once

namespace flat
{
    class Object
    {
    private:
        inline static unsigned long long object_count = 0;
        long long id;

    protected:
        void generate_id();

    public:
        virtual ~Object() = default;
        long long get_id() const;
    };

    class Sample : public Object
    {

    };

    class SoundEffect : public Object
    {

    };

    class Music : public Object
    {

    };

    class Image : public Object
    {

    };

    class Texture : public Object
    {

    };

    class Font : public Object
    {

    };
}