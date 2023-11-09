#include <math.h>
#include <stdio.h>
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

// void gpResolveOverlap(gpBB *lhs, gpBB *rhs)
// {
//     float overlap = 0;
//     // Calculate overlap in the x-axis
//     float xOverlap = fmin(lhs->x + lhs->w, rhs->x + rhs->w) - fmax(lhs->x, rhs->x);
//     // Calculate overlap in the y-axis
//     float yOverlap = fmin(lhs->y + lhs->h, rhs->y + rhs->h) - fmax(lhs->y, rhs->y);

//     // Determine the direction of overlap for each axis
//     if (xOverlap > 0 && yOverlap > 0)
//     {
//         if (xOverlap < yOverlap)
//         {
//             trueXOverlap = (lhs->x + lhs->w / 2 < rhs->x + rhs->w / 2) ? -xOverlap : xOverlap;
//         }
//         else
//         {
//             trueYOverlap = (lhs->y + lhs->h / 2 < rhs->y + rhs->h / 2) ? -yOverlap : yOverlap;
//         }
//     }

//     // Move the box to resolve the overlap
//     // lhs->x += trueXOverlap;
//     lhs->y += trueYOverlap;
// }
void gpResolveOverlapY(gpBB *lhs, gpBB *rhs)
{
       gpBB result;

    float Amin, Amax, Bmin, Bmax;

    /* Horizontal intersection */
    Amin = lhs->x;
    Amax = Amin + lhs->w;
    Bmin = rhs->x;
    Bmax = Bmin + rhs->w;
    if (Bmin > Amin)
        Amin = Bmin;
    result.x = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result.w = Amax - Amin;

    /* Vertical intersection */
    Amin = lhs->y;
    Amax = Amin + lhs->h;
    Bmin = rhs->y;
    Bmax = Bmin + rhs->h;
    if (Bmin > Amin)
        Amin = Bmin;
    result.y = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result.h = Amax - Amin;

        // Resolve overlap independently in x and y directions
    // if (result.w > 0) {
    //     // Determine the direction of overlap for the x-axis
    //     float overlapX = (lhs->x + lhs->w / 2 < rhs->x + rhs->w / 2) ? -result.w : result.w;

    //     // Resolve overlap in the x-axis
    //     lhs->x += overlapX;
    // }

    if (result.h > 0) {
        // Determine the direction of overlap for the y-axis
        float overlapY = (lhs->y + lhs->h / 2 < rhs->y + rhs->h / 2) ? -result.h : result.h;

        // Resolve overlap in the y-axis
        lhs->y += overlapY;
    }


}

void gpResolveOverlapX(gpBB *lhs, gpBB *rhs)
{
       gpBB result;

    float Amin, Amax, Bmin, Bmax;

    /* Horizontal intersection */
    Amin = lhs->x;
    Amax = Amin + lhs->w;
    Bmin = rhs->x;
    Bmax = Bmin + rhs->w;
    if (Bmin > Amin)
        Amin = Bmin;
    result.x = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result.w = Amax - Amin;

    /* Vertical intersection */
    Amin = lhs->y;
    Amax = Amin + lhs->h;
    Bmin = rhs->y;
    Bmax = Bmin + rhs->h;
    if (Bmin > Amin)
        Amin = Bmin;
    result.y = Amin;
    if (Bmax < Amax)
        Amax = Bmax;
    result.h = Amax - Amin;

        // Resolve overlap independently in x and y directions
    if (result.w > 0) {
        // Determine the direction of overlap for the x-axis
        float overlapX = (lhs->x + lhs->w / 2 < rhs->x + rhs->w / 2) ? -result.w : result.w;

        // Resolve overlap in the x-axis
        lhs->x += overlapX;
    }

    // if (result.h > 0) {
    //     // Determine the direction of overlap for the y-axis
    //     float overlapY = (lhs->y + lhs->h / 2 < rhs->y + rhs->h / 2) ? -result.h : result.h;

    //     // Resolve overlap in the y-axis
    //     lhs->y += overlapY;
    // }


}

