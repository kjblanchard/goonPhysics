#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GoonPhysics/scene.h>
#include <GoonPhysics/body.h>
#include <GoonPhysics/gravity.h>

static int _currentNumBodies = 0;
static int _currentCapacityBodies = 4;
static gpBody **_currentBodies;

static void ApplyYVelocity(gpBody *body, float gameTime);
static void ApplyXVelocity(gpBody *body, float gameTime);

// static int _currentNumStaticBodies = 0;
// static int _currentCapacityStaticBodies = 4;
// static gpBody **_currentStaticBodies;

void gpSceneUpdate(gpScene *scene, float gameTime)
{
    gpSceneGravity sceneGravity;
    sceneGravity.sceneGravity = scene->gravity;
    sceneGravity.sceneFriction = 0.0f;
    sceneGravity.sceneMaxXVelocity = 100000;
    sceneGravity.sceneMaxYVelocity = 100000;
    sceneGravity.sceneMinYVelocity = 0.001;
    sceneGravity.sceneMinXVelocity = 0.001;

    for (size_t i = 0; i < _currentNumBodies; i++)
    {
        gpGravityBodyStep(_currentBodies[i], &sceneGravity, gameTime);
    }
    for (size_t i = 0; i < _currentNumBodies; i++)
    {
        ApplyYVelocity(_currentBodies[i], gameTime);
        ApplyXVelocity(_currentBodies[i], gameTime);
    }
}

static void ApplyYVelocity(gpBody *body, float gameTime)
{
    float initialYStep = body->velocity.y * gameTime;
    float iterYStep = initialYStep;
    float stepSize = (int)initialYStep != 0 ? initialYStep > 0 ? 1 : -1 : initialYStep;
    int shouldStep = stepSize != 0 ? 1 : 0;
    while (shouldStep)
    {
        float bodyInitialY = body->boundingBox.y;
        body->boundingBox.y += stepSize;
        // Check for collisions for each body
        // For body in bodies, if collides,
        // then send out notify for subscribers with info of collision bounding box and body num
        // If it is a blocking body, then we should set shouldStep to False
        if (!shouldStep)
        {
            // If we are set to be blocked by the other body,
            // then set should step to 0, and revert body back to initial
            body->boundingBox.y -= stepSize;
            continue;
        }
        iterYStep -= stepSize;
        if (iterYStep && fabs(iterYStep) < 1)
        {
            // We have a partial step remaining, so add that in a final round.
            stepSize = iterYStep;
        }
        else if (!iterYStep)
        {
            shouldStep = 0;
        }
    }
}

static void ApplyXVelocity(gpBody *body, float gameTime)
{
    float initialXStep = body->velocity.x * gameTime;
    float iterXStep = initialXStep;
    float stepSize = (int)initialXStep != 0 ? initialXStep > 0 ? 1 : -1 : initialXStep;
    int shouldStep = stepSize != 0 ? 1 : 0;
    while (shouldStep)
    {
        float bodyInitialX = body->boundingBox.x;
        body->boundingBox.x += stepSize;
        // Check for collisions for each body
        // For body in bodies, if collides,
        // then send out notify for subscribers with info of collision bounding box and body num
        // If it is a blocking body, then we should set shouldStep to False
        if (!shouldStep)
        {
            // If we are set to be blocked by the other body,
            // then set should step to 0, and revert body back to initial
            body->boundingBox.x -= stepSize;
            continue;
        }
        iterXStep -= stepSize;
        if (iterXStep && fabs(iterXStep) < 1)
        {
            // We have a partial step remaining, so add that in a final round.
            stepSize = iterXStep;
        }
        else if (!iterXStep)
        {
            shouldStep = 0;
        }
    }
}

gpScene *gpInitScene(void)
{
    gpScene *scene = malloc(sizeof(*scene));
    _currentBodies = calloc(_currentCapacityBodies, _currentCapacityBodies * sizeof(gpBody *));
    return scene;
}

void gpSceneSetGravity(gpScene *scene, float gravity)
{
    scene->gravity = gravity;
}

int gpSceneAddBody(gpBody *body)
{
    if (_currentNumBodies > _currentCapacityBodies / 2)
    {
        _currentBodies = realloc(_currentBodies, _currentCapacityBodies * 2 * sizeof(gpBody *));
        if (_currentBodies == NULL)
        {
            fprintf(stderr, "Couldn't reallocate to increase body size, what the");
        }
        _currentCapacityBodies *= 2;
    }
    _currentBodies[_currentNumBodies] = body;
    ++_currentNumBodies;
    return _currentNumBodies - 1;
}

gpBody* gpSceneGetBody(int bodyRef)
{
    if(bodyRef < _currentNumBodies && _currentBodies[bodyRef])
    {
        return _currentBodies[bodyRef];
    }
}

int gpSceneAddStaticBody(gpBody *body)
{
}
