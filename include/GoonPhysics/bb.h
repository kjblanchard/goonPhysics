/**
 * @file bb.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

typedef struct gpBB {
    float x, y, w, h;
} gpBB;

gpBB gpBBNew(float x, float y, float w, float h);
gpBB gpBBCopy(gpBB body);