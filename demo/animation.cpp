#include "gameplay.hpp"

#include <chrono>
#include <iostream>
#include <iterator>
#include <string>

/*
    flat::Animation
*/

flat::Animation::Animation()
    : intervalMS(0)
{
}

flat::Animation::Animation(int ms,std::initializer_list<flat::Texture*> list)
    : intervalMS(ms)
{
    for(auto& item : list)
        textures.push_back(item);
}

flat::Animation::~Animation()
{
}

int flat::Animation::getTotalFrameCount()
{
    return textures.size();
}

int flat::Animation::getIntervalMS()
{
    return intervalMS;
}

void flat::Animation::addTexture(flat::Texture *texture)
{
    textures.push_back(texture);
}

void flat::Animation::setInterval(int ms)
{
    intervalMS = ms;
}

flat::Texture* flat::Animation::getTextureAt(int index)
{
    return textures.at(index);
}

/*
    flat::Animator
*/

flat::Animator::Animator()
    : currentAnimation(nullptr),currentTextureIndex(0)
{    
}

flat::Animator::~Animator()
{
}

void flat::Animator::bindAnimation(std::string_view name, Animation &ani)
{
    animations[std::move(std::string(name))] = ani;
}

void flat::Animator::tryUpdateTextureIndex()
{
    if(std::chrono::steady_clock::now() - lastUpdate <= std::chrono::milliseconds(currentAnimation->getIntervalMS()))
    {
        if(currentTextureIndex < (currentAnimation->getTotalFrameCount() - 1))
            ++currentTextureIndex;
        else
            currentTextureIndex = 0;
    }
}

flat::Texture& flat::Animator::getCurrentTexture()
{
    if(!currentAnimation)
    {
        std::cerr << "error: animator used before switch to any animation" << std::endl;
        abort();
    }

    flat::Texture& buffer = *currentAnimation->getTextureAt(currentTextureIndex);
    tryUpdateTextureIndex();
    return buffer;
}

void flat::Animator::switchAnimationTo(std::string_view name)
{
    std::string buffer(name);
    if(animations.count(buffer) == 0)
    {
        std::cerr << "error: can't find animation \"" << name << '\"' << std::endl;
        abort();
    }

    currentTextureIndex = 0;
    currentAnimation = &animations[buffer];
}