#ifndef LS_BOUNDBOX_H
#define LS_BOUNDBOX_H

#include "lsPoint.h"

typedef struct _lsBoundbox
{
    lsVector minc;// min corner (minx, miny)
    lsVector maxc;// max corner (maxx, maxy)
} lsBoundbox;

lsBoundbox ls_boundbox_init();

bool ls_boundbox_is_valid(const lsBoundbox *box);

lsBoundbox ls_boundbox_create(const lsVector *v1, const lsVector *v2);

lsVector ls_boundbox_get_min(const lsBoundbox *box);

lsVector ls_boundbox_get_max(const lsBoundbox *box);

lsBoundbox ls_boundbox_combine(const lsBoundbox *box1, const lsBoundbox *box2);

lsReal ls_boundbox_width(const lsBoundbox *box);

lsReal ls_boundbox_height(const lsBoundbox *box);

lsVector ls_boundbox_center(const lsBoundbox *box);

lsBoundbox ls_boundbox_scale(const lsBoundbox *box, lsReal scale);

lsBoundbox ls_boundbox_transform(const lsBoundbox *box, const lsCoordSystem *cs);

bool ls_boundbox_overlap(const lsBoundbox *box1, const lsBoundbox *box2);

#endif // LS_BOUNDBOX_H
