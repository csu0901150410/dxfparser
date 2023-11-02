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

/**
 * @brief 求点 \p p 关于点 \p o 的镜像点
 * 
 * @param o 
 * @param p 
 * @return lsPoint 
 */
lsPoint ls_point_mirror(lsPoint *o, lsPoint *p)
{
    lsPoint ret;
    ret.x = 2 * o->x - p->x;
    ret.y = 2 * o->y - p->y;
    return ret;
}
