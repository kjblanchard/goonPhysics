#include <GoonPhysics/aabb.h>

int gpIntersectBoxBox(gpBB *lhs, gpBB *rhs)
{
    if (lhs->x < rhs->x + rhs->w &&
        lhs->x + lhs->w > rhs->x &&
        lhs->y < rhs->y + rhs->h &&
        lhs->y + lhs->h > rhs->y)
    {
        return 1;
    }
    return 0;
}