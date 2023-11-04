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

lsPoint ls_point_translate(const lsPoint *p, const lsVector *v)
{
    lsPoint ret;
    ret.x = p->x + v->x;
    ret.y = p->y + v->y;
    return ret;
}

// 以原点为中心进行缩放
lsPoint ls_point_scale(const lsPoint *p, lsReal scale)
{
    lsPoint ret;
    ret.x = p->x * scale;
    ret.y = p->y * scale;
    return ret;
}

// 以指定点为中心进行缩放
lsPoint ls_point_scale_ref(const lsPoint *p, const lsPoint *c, lsReal scale)
{
    // 计算向量cp，然后缩放向量，再移动到中心c
    lsVector v = {c->x - p->x, c->y - p->y};
    v = ls_vector_scale(&v, scale);

    lsPoint ret;
    ret.x = v.x + c->x;
    ret.y = v.y + c->y;
    return ret;
}
