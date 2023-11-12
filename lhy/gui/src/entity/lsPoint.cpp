#include "lsPoint.h"

/**
 * @brief 点转向量
 * 
 * @param p 
 * @return lsVector 
 */
lsVector ls_point_p2v(const lsPoint *p)
{
    lsVector ret;
    ret.x = p->x;
    ret.y = p->y;
    return ret;
}

/**
 * @brief 向量转点
 * 
 * @param v 
 * @return lsVector 
 */
lsPoint ls_point_v2p(const lsVector *v)
{
    lsPoint ret;
    ret.x = v->x;
    ret.y = v->y;
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
    ret.x = 2.0 * o->x - p->x;
    ret.y = 2.0 * o->y - p->y;
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

    lsVector vp = ls_point_p2v(p);
    lsVector op = ls_vector_sub(&vp, &cs->origin);
    op = ls_vector_scale(&op, cs->scale);

    ret = ls_point_v2p(&op);
    return ret;
}
