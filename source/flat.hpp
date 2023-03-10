#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat::data
{
    struct RGBColor
    {
        float r,g,b;
    };
}

namespace flat::top
{
    using flat::data::RGBColor;

    struct Texture
    {
        virtual void loadTextureFromFile(std::filesystem::path path) = 0;
        virtual void releaseTexture() = 0;
    };

    struct Drawable
    {
        virtual void drawElement() = 0;
        virtual glm::mat4&& getTramsformMat() = 0;
    };

    struct Audible
    {
        virtual void const playSound(uint32_t soundId) = 0;
        virtual void const stopSound(uint32_t soundId) = 0;
        virtual void const pauseSound(uint32_t soundId) = 0;
        virtual void const resumeSound(uint32_t soundId) = 0;
    };

    struct Listener
    {
        virtual void initListener() = 0;
        virtual void setListenerPosition(float x,float y) = 0;
        virtual void addListenerPosition(float x,float y) = 0;
        virtual void setListenerVelocity(float x,float y) = 0;
        virtual void addListenerVelocity(float x,float y) = 0;
    };

    struct Physical
    {
        virtual const glm::vec3& getPosition() = 0;
        virtual const glm::vec3& getVelocity() = 0;
        virtual bool collisionCheck(const Physical& obj) = 0;
        virtual void addPosition(const glm::vec3& vec) = 0;
        virtual void addVelocity(const glm::vec3& vec) = 0;
        virtual void setPosition(const glm::vec3& vec) = 0;
        virtual void setVelocity(const glm::vec3& vec) = 0;
        virtual void applyMovement(uint32_t ms);
    };

    struct Renderer
    {
        virtual void initRenderer() = 0;
        virtual void clean(const RGBColor& color);
        virtual void drawRectangle(std::array<RGBColor,4> colors,float x,float y,float w,float h,float rotate) = 0;
        virtual void drawRound(std::array<RGBColor,3> colors,float x,float y,float r) = 0;
        virtual void drawPixel(const RGBColor& color,float x,float y) = 0;
        virtual void bindTexture(const Texture& tex,float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4) = 0;
        virtual void bindTransform(float dx,float dy,float scale,float rotate);
        virtual void bindTexTransform(float dx,float dy,float scale,float rotate);
    };

    struct InputSource
    {
        virtual bool const checkKeyUp(int ascii) = 0;
        virtual bool const checkKeyDown(int ascii) = 0;
        virtual bool const checkMouseMiddle() = 0;
        virtual bool const checkMouseLeft() = 0;
        virtual bool const checkMouseRight() = 0;
        virtual float const getMousePosX() = 0;
        virtual float const getMousePosY() = 0;
    };

    struct Window
    {
        virtual void initWindow() = 0;
        virtual void setWindowTitle(std::string_view title) = 0;
        virtual void setWindowWidth(flaot w) = 0;
        virtual void setWindowHeight(float h) = 0;
        virtual void setWindowPosition(float x,float y) = 0;
        virtual float const getWindowPositionX() = 0;
        virtual float const getWindowPositionY() = 0;
    };

    class GameObject
    {
        
    }

    class GamePlay
    {

    };
}