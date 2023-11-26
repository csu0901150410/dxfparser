#include "lsPoint.h"

lsPoint ls_point_translate(const lsPoint *p, const lsVector *v)
{
    lsPoint ret;
    ret.pos = ls_vector_translate(&p->pos, v);
    return ret;
}

// 以原点为中心进行缩放
lsPoint ls_point_scale(const lsPoint *p, lsReal scale)
{
    lsPoint ret;
    ret.pos = ls_vector_scale(&p->pos, scale);
    return ret;
}

/**
 * @brief 点的坐标系变换。将点的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param p 
 * @param cs 
 * @return lsPoint 坐标系 \p cs 下的点坐标
 */
lsPoint ls_point_transform(const lsPoint *p, const lsCoordSystem *cs)
{
    lsPoint ret;
    lsVector translate = ls_vector_scale(&cs->origin, -1.0);
    ret.pos = ls_vector_transform(&p->pos, &translate, cs->scale);
    return ret;
}

lsPoint ls_point_random_point(lsReal lowx, lsReal lowy, lsReal highx, lsReal highy)
{
    lsPoint ret;
    ret.pos = ls_vector_random_vector(lowx, lowy, highx, highy);
    return ret;
}

lsPoint ls_point_transform_by(const lsPoint *p, const lsMatrix *m)
{
    lsPoint ret;
    ret.pos = ls_vector_transform_by(&p->pos, m);
    return ret;
}
