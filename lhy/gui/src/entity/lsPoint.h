#ifndef LS_POINT_H
#define LS_POINT_H

#include "lsVector.h"
#include "lsCoordSystem.h"

typedef struct
{
    lsVector pos;
} lsPoint;

lsPoint ls_point_translate(const lsPoint *p, const lsVector *v);

lsPoint ls_point_scale(const lsPoint *p, lsReal scale);

lsPoint ls_point_transform(const lsPoint *p, const lsCoordSystem *cs);

lsPoint ls_point_random_point(lsReal lowx, lsReal lowy, lsReal highx, lsReal highy);

#endif // LS_POINT_H
