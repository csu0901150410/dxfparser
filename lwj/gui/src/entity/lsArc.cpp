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

    lsVector cs = { ret.s.x - ret.c.x, ret.s.y - ret.c.y };
    lsVector ce = { ret.e.x - ret.c.x, ret.e.y - ret.c.y };
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
lsReal ls_arc_get_radius(lsArc* arc)
{
    lsVector radial = { arc->s.x - arc->c.x, arc->s.y - arc->c.y };
    return ls_vector_length(&radial);
}

/**
 * @brief 获取圆弧弧度
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_radian(lsArc* arc)
{
    lsVector cs = { arc->s.x - arc->c.x, arc->s.y - arc->c.y };
    lsVector ce = { arc->e.x - arc->c.x, arc->e.y - arc->c.y };
    return ls_vector_rotate_angle(&cs, &ce, arc->bccw);
}

/**
 * @brief 获取圆弧起始弧度
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_start_angle(lsArc* arc)
{
    lsVector cx = { 1, 0 };
    lsVector cs = { arc->s.x - arc->c.x, arc->s.y - arc->c.y };
    return ls_vector_rotate_angle(&cx, &cs, arc->bccw);
}

/**
 * @brief 获取圆弧终止弧度
 *
 * @param arc
 * @return lsReal
 */
lsReal ls_arc_get_end_angle(lsArc* arc)
{
    lsVector cx = { 1, 0 };
    lsVector ce = { arc->e.x - arc->c.x, arc->e.y - arc->c.y };
    return ls_vector_rotate_angle(&cx, &ce, arc->bccw);
}

/**
 * @brief 获取圆弧所在圆包围盒
 *
 * @param arc
 * @return lsBoundbox
 */
lsBoundbox ls_arc_get_circle_boundbox(lsArc* arc)
{
    lsPoint c = arc->c;
    lsReal r = ls_arc_get_radius(arc);
    lsPoint p1 = { c.x - r, c.y - r };
    lsPoint p2 = { c.x + r, c.y + r };
    return ls_bounbox_create(&p1, &p2);
}

/**
* @brief 圆弧的缩放
*
* @param arc scale
* @return lsReal
*/
lsArc ls_arc_scale(const lsArc* arc, lsReal scale)
{
    lsArc ret;
    ret.s = ls_point_scale(&arc->s, scale);
    ret.e = ls_point_scale(&arc->e, scale);
    ret.c = ls_point_scale(&arc->c, scale);
    ret.bccw = arc->bccw;
    return ret;

}

lsArc ls_arc_translate(const lsArc* arc, const lsVector* vector)
{
    lsArc ret;
    ret.s = ls_point_translate(&arc->s, vector);
    ret.e = ls_point_translate(&arc->e, vector);
    ret.c = ls_point_translate(&arc->c, vector);
    ret.bccw = arc->bccw;
    return ret;
}

/**
* @brief 以指定点为中心缩放圆弧
*
* @param arc scale
* @return lsReal
*/
lsArc ls_arc_scale_ref(const lsArc* arc, const lsPoint* c, lsReal scale)
{
    lsArc ret;
    ret.s = ls_point_scale_ref(&arc->s, c, scale);
    ret.e = ls_point_scale_ref(&arc->e, c, scale);
    ret.c = ls_point_scale_ref(&arc->c, c, scale);
    ret.bccw = arc->bccw;
    return ret;
}


// lhy test
#include "easyx.h"
void ls_arc_draw(lsArc* circlearc)
{
    lsBoundbox box = ls_arc_get_circle_boundbox(circlearc);
    lsReal startAngle = ls_arc_get_start_angle(circlearc);
    lsReal endAngle = ls_arc_get_end_angle(circlearc);

    line(box.left, box.bottom, box.left, box.top);
    line(box.left, box.top, box.right, box.top);
    line(box.right, box.top, box.right, box.bottom);
    line(box.right, box.bottom, box.left, box.bottom);
    arc(box.left, box.top, box.right, box.bottom, startAngle, endAngle);
 
}

