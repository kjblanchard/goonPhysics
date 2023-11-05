#include <GoonPhysics/body.h>

gpBody *gpBodyNew(gpBB boundingBox)
{
    gpBody *body;
    body = calloc(1, sizeof(*body));
    body->velocity = gpV(0,0);
    body->boundingBox = boundingBox;
    // body->overlapWatchers = 0;
    return body;
}