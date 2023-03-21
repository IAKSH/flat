#include "gameplay.hpp"

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

flat::Animation::Animation() : currentSet(nullptr),lastTextureSwap(std::chrono::steady_clock::now()) {}

flat::Animation::~Animation() {}

void flat::Animation::tryUpdateAnimation()
{
    if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastTextureSwap).count() >= currentSet->second.first)
    {
        lastTextureSwap = std::chrono::steady_clock::now();
        if(currentTexture != currentSet->second.second.end())
            currentTexture++;
        else
            currentTexture = currentSet->second.second.begin();
    }
}

void flat::Animation::addTextureToSet(std::string name, int intervalMS, std::unique_ptr<flat::Texture>& tex)
{
    auto& temp = textureSets[name];
    temp.first = intervalMS;
    temp.second.push_back(std::move(tex));
}

void flat::Animation::addTextureToSet(std::string name, std::unique_ptr<flat::Texture> &tex)
{
    textureSets[name].second.push_back(std::move(tex));
}

void flat::Animation::switchTextureSet(std::string name)
{
    currentSet = textureSets.find(name);
    if(currentSet == textureSets.end())
    {
        std::cerr << "error: can't find key \"" << name << "\" in textureSets" << std::endl;
        abort();
    }

    currentTexture = currentSet->second.second.begin();
}

flat::Texture& flat::Animation::getCurrentTexture()
{
    flat::Texture& temp = **currentTexture;
    tryUpdateAnimation();
    return temp;
}
