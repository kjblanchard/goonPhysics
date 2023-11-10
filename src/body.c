#include <stdio.h>
#include <GoonPhysics/body.h>

#define MAX_OVERLAP_BODIES 10

gpBody *gpBodyNew(gpBB boundingBox)
{
    gpBody *body;
    body = calloc(1, sizeof(*body));
    body->overlappingBodies = calloc(MAX_OVERLAP_BODIES, sizeof(*body));
    body->bodyType = 1;
    body->gravityEnabled = 1;
    body->numOverlappingBodies = 0;
    body->velocity = gpV(0, 0);
    body->boundingBox = boundingBox;
    body->bodyNum = -1;
    return body;
}

gpBody *gpBodyNewStatic(gpBB boundingBox)
{
    gpBody *body = gpBodyNew(boundingBox);
    body->bodyType = 0;
    return body;
}

void gpBodyAddOverlap(gpBody *body, gpBody *overlapBody)
{
    if (body->numOverlappingBodies < MAX_OVERLAP_BODIES)
    {
        body->overlappingBodies[body->numOverlappingBodies] = overlapBody;
        ++body->numOverlappingBodies;
    }
}

int gpBodyIsOnGround(gpBody *body)
{
    for (size_t i = 0; i < body->numOverlappingBodies; i++)
    {
        gpBody *overlap = body->overlappingBodies[i];
        if (overlap->boundingBox.y >= body->boundingBox.y + body->boundingBox.h)
            return 1;
    }
    return 0;
}