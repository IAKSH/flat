#include "gameplay.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

flat::TextureSet::TextureSet()
    : intervalMS(0), index(0)
{
}

flat::TextureSet::~TextureSet()
{
}

void flat::TextureSet::updateCurrentTexture()
{
    if(index == textures.size() - 1)
        index = 0;
    else
        ++index;
}

void flat::TextureSet::resetCurrentTexture()
{
    index = 0;
}

void flat::TextureSet::setIntervalMS(int ms)
{
    intervalMS = ms;
}

void flat::TextureSet::addTexture(flat::Texture& texture)
{
    textures.push_back(std::make_unique<flat::Texture>(std::move(texture)));
}

const int& flat::TextureSet::getIntervalMS()
{
    return intervalMS;
}

flat::Texture& flat::TextureSet::getCurrentTexture()
{
    auto& buffer = *textures.at(index);;
    updateCurrentTexture();
    return buffer;
}

flat::Animation::Animation()
    : currentSet(nullptr), lastTextureSwap(std::chrono::steady_clock::now())
{
}

flat::Animation::~Animation()
{
}

void flat::Animation::addTextureToSet(std::string name, int intervalMS, std::unique_ptr<flat::Texture>& tex)
{
    auto& temp = textureSets[name];
    temp.setIntervalMS(intervalMS);
    temp.addTexture(*tex);
}

void flat::Animation::addTextureToSet(std::string name, std::unique_ptr<flat::Texture>& tex)
{
    textureSets[name].addTexture(*tex);
}

void flat::Animation::switchTextureSet(std::string name)
{
    currentSet->second.resetCurrentTexture();
    currentSet = textureSets.find(name);
    if(currentSet == textureSets.end())
    {
        std::cerr << "error: can't find key \"" << name << "\" in textureSets" << std::endl;
        abort();
    }
}

flat::Texture& flat::Animation::getCurrentTexture()
{
    return currentSet->second.getCurrentTexture();
}
