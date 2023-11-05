#ifndef LS_POINT_H
#define LS_POINT_H
#include "lsVector.h"
typedef struct
{
    lsReal x;
    lsReal y;
    lsReal z;
} lsPoint;

void ls_point_negative(lsPoint *pt);

lsPoint ls_point_sub(lsPoint *p1, lsPoint *p2);

lsPoint ls_point_add(lsPoint *p1, lsPoint *p2);

lsPoint ls_point_mirror(lsPoint *o, lsPoint *p);

#endif // LS_POINT_H
