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
// private void ApplyYVelocity(GameTime gameTime, double yStep)
// {
//     if (yStep >= 1)
//     {
//         bool collision = false;
//         while (yStep >= 1)
//         {
//             //Temporarily add 1 to Y and check for collisions
//             Parent.Location.Y++;
//             var tilesToCheck = _gravity._tiledGameComponent.LoadedTmxContent.SolidTiles;
//             tilesToCheck.ForEach(solidTile =>
//             {
//                 if (collision)
//                     return;
//                 var tileCollider =
//                     solidTile.GetComponent<BoxColliderComponent>(EngineTags.ComponentTags.BoxCollider);
//                 var sourceRect = _collider.Bounds;
//                 if (sourceRect.Intersects(tileCollider.Bounds))
//                 {
//                     yStep = 0;
//                     collision = true;
//                     Parent.Location.Y--;
//                     _velocity.Y = 0;
//                     CollisionEvent(Directions.Down);
//                 }
//             });
//             if (collision)
//                 break;
//             yStep--;
//             // Parent._location.Y++;
//         }
//     }
//     else if (yStep <= -1)
//     {
//         bool collision = false;
//         while (yStep <= -1)
//         {
//             //Temporarily add 1 to Y and check for collisions
//             Parent.Location.Y--;
//             var tilesToCheck = _gravity._tiledGameComponent.LoadedTmxContent.SolidTiles;
//             tilesToCheck.ForEach(solidTile =>
//             {
//                 if (collision)
//                     return;
//                 var tileCollider =
//                     solidTile.GetComponent<BoxColliderComponent>(EngineTags.ComponentTags.BoxCollider);
//                 var sourceRect = _collider.Bounds;
//                 if (sourceRect.Intersects(tileCollider.Bounds))
//                 {
//                     yStep = 0;
//                     collision = true;
//                     Parent.Location.Y++;
//                     _velocity.Y = 0;
//                     CollisionEvent(Directions.Top);
//                 }
//             });
//             if (collision)
//                 return;
//             yStep++;
//             // Parent._location.Y++;
//         }
//     }
// }

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

int gpSceneAddStaticBody(gpBody *body)
{
}
