#include "lsPoint.h"

void ls_point_negative(lsPoint *pt)
{
    pt->x = -pt->x;
    pt->y = -pt->y;
    pt->z = -pt->z;
}

lsPoint ls_point_sub(lsPoint *p1, lsPoint *p2)
{
    lsPoint ret;
    ret.x = p1->x - p2->x;
    ret.y = p1->y - p2->y;
    return ret;
}

lsPoint ls_point_add(lsPoint *p1, lsPoint *p2)
{
    lsPoint ret;
    ret.x = p1->x + p2->x;
    ret.y = p1->y + p2->y;
    return ret;
}
