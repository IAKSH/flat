#pragma once

namespace ni::flat
{
    bool collisionCheckGJK(float x1, float y1, float w1, float h1,float r1, float x2, float y2, float w2, float h2, float r2);

    // bad
    static bool collisionCheckAABB(float x1,float y1,float w1,float h1,float x2,float y2,float w2,float h2)
    {
        return (x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
    }
}