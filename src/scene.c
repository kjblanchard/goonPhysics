#include <stdio.h>
#include <stdlib.h>
#include <GoonPhysics/scene.h>
#include <GoonPhysics/body.h>

static int _currentNumBodies = 0;
static int _currentCapacityBodies = 4;
static gpBody **_currentBodies;

// static int _currentNumStaticBodies = 0;
// static int _currentCapacityStaticBodies = 4;
// static gpBody **_currentStaticBodies;

void gpInitScene()
{
    _currentBodies = calloc(_currentCapacityBodies, _currentCapacityBodies * sizeof(gpBody*));
}

void gpSceneSetGravity(gpScene *scene, float gravity)
{
    scene->gravity = gravity;
}

int gpSceneAddBody(gpBody *body)
{
    if (_currentNumBodies > _currentCapacityBodies / 2)
    {
        _currentBodies = realloc(_currentBodies, _currentCapacityBodies * 2 * sizeof(gpBody*));
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

int gpSceneAddStaticBody(gpBody *body)
{
}
