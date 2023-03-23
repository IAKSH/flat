#pragma once

#include <chrono>
#include <memory>
#include <vector>
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

    class TextureSet
    {
    private:
        int intervalMS;
        std::vector<std::unique_ptr<flat::Texture>> textures;
        int index;
        void updateCurrentTexture();

    public:
        TextureSet();
        ~TextureSet();
        void resetCurrentTexture();
        void setIntervalMS(int ms);
        void addTexture(flat::Texture& texture);
        const int& getIntervalMS();
        flat::Texture& getCurrentTexture();
    };

    class Animation
    {
    private:
        std::unordered_map<std::string, TextureSet> textureSets;
        std::unordered_map<std::string, TextureSet>::iterator currentSet;
        std::chrono::steady_clock::time_point lastTextureSwap;

    public:
        Animation();
        ~Animation();
        void addTextureToSet(std::string name, std::unique_ptr<flat::Texture>& tex);
        void addTextureToSet(std::string name, int intervalMS, std::unique_ptr<flat::Texture>& tex);
        void switchTextureSet(std::string name);
        flat::Texture& getCurrentTexture();
    };

    template <typename T> class GameObject : public Physics2D, public Animation
    {
    private:
        std::unordered_map<std::string,std::string> attribs;

    public:
        void onInitialize() { static_cast<T*>(this)->imp_onInitialize(); }
        void onCreate() { static_cast<T*>(this)->imp_onCreate(); }
        void onTick() { static_cast<T*>(this)->imp_onTick(); }
        void onDestroy() { static_cast<T*>(this)->imp_onDestroy(); }

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