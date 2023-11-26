#include "lsArc.h"

/**
 * @brief 从三点构造圆弧
 * Ref : https://stackoverflow.com/questions/52990094/calculate-circle-given-3-points-code-explanation
 * 
 * @param s 
 * @param a 
 * @param e 
 * @return lsArc 
 */
lsArc ls_arc_construct_from_ppp(lsVector s, lsVector a, lsVector e)
{
    lsArc ret;

    lsReal temp = a.x * a.x + a.y * a.y;
    lsReal sa = (s.x * s.x + s.y * s.y - temp) / 2;
    lsReal ae = (temp - e.x * e.x - e.y * e.y) / 2;
    lsReal det = (s.x - a.x) * (a.y - e.y) - (a.x - e.x) * (s.y - a.y);

    if (fabs(det) < EPS)
    {
        ret.valid = false;
        return ret;
    }

    ret.s = s;
    ret.e = e;
    ret.c.x = (sa * (a.y - e.y) - ae * (s.y - a.y)) / det;
    ret.c.y = ((s.x - a.x) * ae - (a.x - e.x) * sa) / det;

    lsVector cs = {ret.s.x - ret.c.x, ret.s.y - ret.c.y};
    lsVector ce = {ret.e.x - ret.c.x, ret.e.y - ret.c.y};
    lsReal cross = ls_vector_cross(&cs, &ce);
    if (fabs(cross) > EPS)
        ret.bccw = true;
    else
        ret.bccw = false;

    ret.valid = true;
    return ret;
}

/**
 * @brief 获取圆弧半径
 * 
 * @param arc 
 * @return lsReal 
 */
lsReal ls_arc_get_radius(const lsArc *arc)
{
    lsVector radial = ls_vector_sub(&arc->s, &arc->c);
    return ls_vector_length(&radial);
}

/**
 * @brief 获取圆弧弧度
 * 
 * @param arc 
 * @return lsReal 
 */
lsReal ls_arc_get_radian(const lsArc *arc)
{
    lsVector cs = ls_vector_sub(&arc->s, &arc->c);
    lsVector ce = ls_vector_sub(&arc->e, &arc->c);
    return ls_vector_rotate_angle(&cs, &ce, arc->bccw);
}

/**
 * @brief 获取圆弧起始弧度
 * 
 * @param arc 
 * @return lsReal 
 */
lsReal ls_arc_get_start_angle(const lsArc *arc)
{
    lsVector cx = {1, 0};
    lsVector cs = ls_vector_sub(&arc->s, &arc->c);
    return ls_vector_rotate_angle(&cx, &cs, arc->bccw);
}

/**
 * @brief 获取圆弧终止弧度
 * 
 * @param arc 
 * @return lsReal 
 */
lsReal ls_arc_get_end_angle(const lsArc *arc)
{
    lsVector cx = {1, 0};
    lsVector ce = ls_vector_sub(&arc->e, &arc->c);
    return ls_vector_rotate_angle(&cx, &ce, arc->bccw);
}

/**
 * @brief 获取圆弧所在圆包围盒
 * 
 * @param arc 
 * @return lsBoundbox 
 */
lsBoundbox ls_arc_get_circle_boundbox(const lsArc *arc)
{
    lsReal r = ls_arc_get_radius(arc);
    lsVector v1 = {r, r};
    lsVector v2 = {-r, -r};
    lsVector c1 = ls_vector_translate(&arc->c, &v1);
    lsVector c2 = ls_vector_translate(&arc->c, &v2);
    return ls_boundbox_create(&c1, &c2);
}

lsArc ls_arc_translate(const lsArc *arc, const lsVector *vector)
{
    lsArc ret;
    ret.s = ls_vector_translate(&arc->s, vector);
    ret.e = ls_vector_translate(&arc->e, vector);
    ret.c = ls_vector_translate(&arc->c, vector);
    ret.bccw = arc->bccw;
    return ret;
}

lsArc ls_arc_scale(const lsArc *arc, lsReal scale)
{
    lsArc ret;
    ret.s = ls_vector_scale(&arc->s, scale);
    ret.e = ls_vector_scale(&arc->e, scale);
    ret.c = ls_vector_scale(&arc->c, scale);
    ret.bccw = arc->bccw;
    return ret;
}

/**
 * @brief 圆弧的坐标系变换。将圆弧的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param arc 
 * @param cs 
 * @return lsArc 
 */
lsArc ls_arc_transform(const lsArc *arc, const lsCoordSystem *cs)
{
    lsArc ret;
    lsVector translate = ls_vector_scale(&cs->origin, -1.0);
    ret.s = ls_vector_transform(&arc->s, &translate, cs->scale);
    ret.e = ls_vector_transform(&arc->e, &translate, cs->scale);
    ret.c = ls_vector_transform(&arc->c, &translate, cs->scale);
    ret.bccw = arc->bccw;
    return ret;
}

lsArc ls_arc_transform_by(const lsArc *arc, const lsMatrix *m)
{
    /**
     * @brief 圆弧应用矩阵变换，结果是对圆弧所在整圆进行变换，截取部分，也不确定变换后是什么，暂不处理
     * 
     */
}
