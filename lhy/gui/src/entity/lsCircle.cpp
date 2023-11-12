#include "lsCircle.h"

lsBoundbox ls_circle_get_boundbox(const lsCircle *circle)
{
    lsPoint c = circle->c;
    lsReal r = circle->r;
    lsPoint p1 = {c.x - r, c.y - r};
    lsPoint p2 = {c.x + r, c.y + r};
    return ls_boundbox_create(&p1, &p2);
}

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale)
{
    lsCircle ret;
    ret.c = ls_point_scale(&circle->c, scale);
    ret.r = circle->r * scale;
    return ret;
}

lsCircle ls_circle_translate(const lsCircle *circle, const lsVector *vector)
{
    lsCircle ret;
    ret.c = ls_point_translate(&circle->c, vector);
    ret.r = circle->r;
    return ret;
}

/**
 * @brief 整圆的坐标系变换。将整圆的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param circle 
 * @param cs 
 * @return lsCircle 
 */
lsCircle ls_circle_transform(const lsCircle *circle, const lsCoordSystem *cs)
{
    lsCircle ret;
    ret.c = ls_point_transform(&circle->c, cs);
    ret.r = circle->r * cs->scale;
    return ret;
}
