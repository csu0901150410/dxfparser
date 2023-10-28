#ifndef LS_POINT_H
#define LS_POINT_H

#define _CRT_SECURE_NO_WARNINGS

#include <float.h>

typedef double lsReal;

#define MAX_REAL    DBL_MAX
#define MIN_REAL    DBL_MIN

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) < (b)) ? (b) : (a)

typedef struct
{
    lsReal x;
    lsReal y;
    lsReal z;
} lsPoint;

void ls_point_negative(lsPoint *pt);

lsPoint ls_point_sub(lsPoint *p1, lsPoint *p2);

lsPoint ls_point_add(lsPoint *p1, lsPoint *p2);

#endif // LS_POINT_H
