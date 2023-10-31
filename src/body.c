#include <GoonPhysics/body.h>

gpBody *gpBodyNew(gpBB boundingBox)
{
    gpBody *body;
    body = calloc(1, sizeof(*body));
    body->boundingBox = boundingBox;
    return body;
}