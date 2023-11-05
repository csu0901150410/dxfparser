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

lsPoint ls_point_translate(const lsPoint *p, const lsVector *v);

lsPoint ls_point_scale(const lsPoint *p, lsReal scale);

lsPoint ls_point_scale_ref(const lsPoint *p, const lsPoint *c, lsReal scale);

#endif // LS_POINT_H
