#include <GoonPhysics/bb.h>

gpBB gpBBNew(float x, float y, float w, float h)
{
    gpBB boundingBox;
    boundingBox.x = x;
    boundingBox.y = y;
    boundingBox.w = w;
    boundingBox.h = h;
    return boundingBox;
}

gpBB gpBBCopy(gpBB body)
{
    gpBB boundingBox;
    boundingBox.x = body.x;
    boundingBox.y = body.y;
    boundingBox.w = body.w;
    boundingBox.h = body.h;
    return boundingBox;
}