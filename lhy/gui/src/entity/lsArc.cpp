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
lsArc ls_arc_construct_from_ppp(lsPoint s, lsPoint a, lsPoint e)
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
    lsVector radial = {arc->s.x - arc->c.x, arc->s.y - arc->c.y};
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
    lsVector cs = {arc->s.x - arc->c.x, arc->s.y - arc->c.y};
    lsVector ce = {arc->e.x - arc->c.x, arc->e.y - arc->c.y};
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
    lsVector cs = {arc->s.x - arc->c.x, arc->s.y - arc->c.y};
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
    lsVector ce = {arc->e.x - arc->c.x, arc->e.y - arc->c.y};
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
    lsPoint c = arc->c;
    lsReal r = ls_arc_get_radius(arc);
    lsPoint p1 = {c.x - r, c.y - r};
    lsPoint p2 = {c.x + r, c.y + r};
    return ls_boundbox_create(&p1, &p2);
}

lsArc ls_arc_translate(const lsArc *arc, const lsVector *vector)
{
    lsArc ret;
    ret.s = ls_point_translate(&arc->s, vector);
    ret.e = ls_point_translate(&arc->e, vector);
    ret.c = ls_point_translate(&arc->c, vector);
    ret.bccw = arc->bccw;
    return ret;
}

lsArc ls_arc_scale(const lsArc *arc, lsReal scale)
{
    lsArc ret;
    ret.s = ls_point_scale(&arc->s, scale);
    ret.e = ls_point_scale(&arc->e, scale);
    ret.c = ls_point_scale(&arc->c, scale);
    ret.bccw = arc->bccw;
    return ret;
}

lsArc ls_arc_scale_ref(const lsArc * arc, const lsPoint *c, lsReal scale)
{
    lsArc ret;
    ret.s = ls_point_scale_ref(&arc->s, c, scale);
    ret.e = ls_point_scale_ref(&arc->e, c, scale);
    ret.c = ls_point_scale_ref(&arc->c, c, scale);
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
    ret.s = ls_point_transform(&arc->s, cs);
    ret.e = ls_point_transform(&arc->e, cs);
    ret.c = ls_point_transform(&arc->c, cs);
    ret.bccw = arc->bccw;
    return ret;
}
