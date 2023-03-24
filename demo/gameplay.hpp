#pragma once

#include <chrono>
#include <deque>
#include <initializer_list>
#include <memory>
#include <vector>
#include <array>
#include <iterator>
#include <algorithm>
#include <string_view>
#include <unordered_map>

#include "renderer.hpp"

namespace flat
{
    class Physics2D
    {
    private:
        float posX, posY, width, height, rotate;

        struct Vec2
        {
            float x, y;
            Vec2()
                : x(0.0f), y(0.0f)
            {}

            Vec2(float _x, float _y)
                : x(_x), y(_y)
            {}
        };

        Vec2 subtract(Vec2 a, Vec2 b);
        Vec2 negate(Vec2 v);
        Vec2 perpendicular(Vec2 v);
        float dotProduct(Vec2 a, Vec2 b);
        float lengthSquared(Vec2 v);

        Vec2 tripleProduct(Vec2 a, Vec2 b, Vec2 c);
        Vec2 averagePoint(const Vec2* vertices, size_t count);
        size_t indexOfFurthestPoint(const Vec2* vertices, size_t count, Vec2 d);
        Vec2 support(const Vec2* vertices1, size_t count1,const Vec2* vertices2, size_t count2, Vec2 d);

        int iter_count = 0;

        int gjk(const Vec2* vertices1, size_t count1, const Vec2* vertices2, size_t count2);

        float Perturbation();
        Vec2 Jostle(Vec2 a);

        std::array<Vec2, 4> getHitboxVertexCoords(Physics2D& obj);

    public:
        Physics2D();
        ~Physics2D();
        float getPosX();
        float getPosY();
        float getWidth();
        float getHeight();
        float getRotate();
        void setPosX(float f);
        void setPosY(float f);
        void setWidth(float f);
        void setHeight(float f);
        void setRotate(float f);
        bool collisionCheck(Physics2D& obj);
    };

    class Animation
    {
    private:
        std::deque<flat::Texture*> textures;
        int intervalMS;

    public:
        Animation();
        Animation(int ms,std::initializer_list<flat::Texture*> list);
        ~Animation();
        int getTotalFrameCount();
        int getIntervalMS();
        void addTexture(flat::Texture* texture);
        void setInterval(int ms);
        flat::Texture* getTextureAt(int index);
    };

    class Animator
    {
    private:
        std::unordered_map<std::string, Animation> animations;
        std::chrono::steady_clock::time_point lastUpdate;
        Animation* currentAnimation;
        int currentTextureIndex;
        void tryUpdateTextureIndex();

    public:
        Animator();
        ~Animator();
        void bindAnimation(std::string_view name,Animation& ani);
        void switchAnimationTo(std::string_view name);
        flat::Texture& getCurrentTexture();
    };

    template <typename T> class GameObject : public Physics2D, public Animator
    {
    private:
        std::unordered_map<std::string,std::string> attribs;

    public:
        void onTick() { static_cast<T*>(this)->imp_onTick(); }

        void setAttrib(std::string_view name,std::string_view val)
        {
            attribs[std::move(std::string(name))] = std::move(std::string(val));
        }

        std::string_view getAttrib(std::string_view name)
        {
            return attribs[std::move(std::string(name))];
        }
    };
}  // namespace flat