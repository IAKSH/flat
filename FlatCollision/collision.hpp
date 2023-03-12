#pragma once

namespace flat
{
    struct Hitbox2D
    {
        virtual ~Hitbox2D() {}
        virtual bool checkHit(flat::Hitbox2D& hitbox) = 0;
        virtual float const getPosX() = 0;
        virtual float const getPosY() = 0;
        virtual float const getRotate() = 0;
        virtual float const getWidth() = 0;
        virtual float const getHeight() = 0;
        virtual void setPosX(float posX) = 0;
        virtual void setPosY(float posY) = 0;
        virtual void setRotate(float rotate) = 0;
        virtual void setWidth(float width) = 0;
        virtual void setHeight(float height) = 0;
    };
}