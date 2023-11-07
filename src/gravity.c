#include <GoonPhysics/gravity.h>

static void GravityConstraintX(gpBody *body, double frictionStep, gpSceneGravity *sceneGravity)
{
    if (body->velocity.x == 0)
        return;
    double step;
    double max = sceneGravity->sceneMaxXVelocity;
    if (body->velocity.x > 0)
    {
        step = body->velocity.x - frictionStep;
        if (step > max)
            step = max;
        if (step < sceneGravity->sceneMinXVelocity)
            step = 0;
    }
    else
    {
        step = body->velocity.x + frictionStep;
        if (step < -max)
            step = -max;
        if (step > -sceneGravity->sceneMinXVelocity)
            step = 0;
    }
    body->velocity.x = (float)step;
}

static void GravityConstraintY(gpBody *body, float gravityStep, gpSceneGravity *sceneGravity)
{
    double step = body->velocity.y + gravityStep;
    if (step >= 0)
    {
        if (step > sceneGravity->sceneMaxYVelocity)
            step = sceneGravity->sceneMaxYVelocity;
        if (step < sceneGravity->sceneMinYVelocity)
            step = 0;
    }
    else
    {
        if (step < -sceneGravity->sceneMaxYVelocity)
            step = -sceneGravity->sceneMaxYVelocity;
        if (step > sceneGravity->sceneMinYVelocity)
            step = 0;
    }
    body->velocity.y = (float)step;
}

void gpGravityBodyStep(gpBody *body, gpSceneGravity *sceneGravity, float deltaTime)
{
    float gravityStep = sceneGravity->sceneGravity * deltaTime;
    float frictionStep = 0.0;
    int friction = 0;
    if (friction)
    {
        frictionStep = friction * deltaTime;
    }

    // Keep Y in Bounds for Max Speed
    GravityConstraintY(body, gravityStep, sceneGravity);
    // Keep X in Bounds for max Speed
    GravityConstraintX(body, frictionStep, sceneGravity);
}