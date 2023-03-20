#include "gameplay.hpp"
#include <_mingw_mac.h>

flat::Physics2D::Physics2D()
    : posX(0.0f),posY(0.0f),width(0.0f),height(0.0f),rotate(0.0f)
{   
}

flat::Physics2D::~Physics2D()
{
}

float flat::Physics2D::getPosX()
{
    return posX;
}

float flat::Physics2D::getPosY()
{
    return posY;
}

float flat::Physics2D::getWidth()
{
    return width;
}

float flat::Physics2D::getHeight()
{
    return height;
}

float flat::Physics2D::getRotate()
{
    return rotate;
}

void flat::Physics2D::setPosX(float f)
{
    posX = f;
}

void flat::Physics2D::setPosY(float f)
{
    posY = f;
}

void flat::Physics2D::setWidth(float f)
{
    width = f;
}

void flat::Physics2D::setHeight(float f)
{
    height = f;
}

void flat::Physics2D::setRotate(float f)
{
    rotate = f;
}

bool flat::Physics2D::collisionCheck(Physics2D &obj)
{
    // TODO: GJK collision check
}
