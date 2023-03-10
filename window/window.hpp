#pragma once

#include <string_view>

namespace flat
{
    struct Window
    {
        virtual void initWindow() = 0;
        virtual void destroyWindow() = 0;
        virtual void bindContext() = 0;
        virtual void setWindowTitle(std::string_view title) = 0;
        virtual void setWindowWidth(int w) = 0;
        virtual void setWindowHeight(int h) = 0;
        virtual void setWindowPosition(int x,int y) = 0;
        virtual int const getWindowPositionX() = 0;
        virtual int const getWindowPositionY() = 0;
        virtual int const getWindowWidth() = 0;
        virtual int const getWindowHeight() = 0;
        virtual void const updateWindow() = 0;
    };
}