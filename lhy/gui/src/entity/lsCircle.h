#ifndef LS_CIRCLE_H
#define LS_CIRCLE_H

#include "lsPoint.h"
#include "lsBoundbox.h"
#include "lsCoordSystem.h"

typedef struct
{
    lsPoint c;
    lsReal r;
} lsCircle;

lsBoundbox ls_circle_get_boundbox(const lsCircle *circle);

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale);

lsCircle ls_circle_translate(const lsCircle *circle, const lsVector *vector);

lsCircle ls_circle_transform(const lsCircle *circle, const lsCoordSystem *cs);

#endif // LS_CIRCLE_H
