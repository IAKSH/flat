#pragma once

#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>


#include "renderer.hpp"

namespace flat
{
    class Physics2D
    {
    private:
        float posX, posY, width, height, rotate;

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
        std::unordered_map<std::string, std::pair<uint32_t, std::vector<std::unique_ptr<flat::Texture>>>> textureSets;
        std::pair<uint32_t, std::vector<std::unique_ptr<flat::Texture>>> currentSet;
        std::vector<std::unique_ptr<flat::Texture>>::iterator currentTexture;
        std::chrono::steady_clock::time_point lastTextureSwap;

    public:
        Animation();
        ~Animation();
        void createNewTextureSet(std::string, uint32_t intervalMs);
        void addTextureToSet(std::string name, std::unique_ptr<flat::Texture>& tex);
        void switchTextureSet(std::string);
        flat::Texture& getCurrentTexture();
    };

    class GameObject : public Physics2D, public Animation
    {
    private:
    public:
        GameObject();
        ~GameObject();
    };
}  // namespace flat