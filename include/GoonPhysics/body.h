/**
 * @file body.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <GoonPhysics/bb.h>
#include <GoonPhysics/vec.h>
#include <stdlib.h>

// typedef struct gpBodyOverlap {
//     gpBody* body;
//     gpBody* overlapBody;
// } gpBodyOverlap;

typedef struct gpBody
{
    gpBB boundingBox;
    gpVec velocity;
    // int overlapWatcherCount;
    // void** overlapWatchers;

} gpBody;

gpBody *gpBodyNew(gpBB boundingBox);

// void gpBodyAddWatcherFunc();


