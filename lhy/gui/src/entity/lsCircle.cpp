#include "lsCircle.h"

lsBoundbox ls_circle_get_boundbox(lsCircle *circle)
{
    lsPoint c = circle->c;
    lsReal r = circle->r;
    lsPoint p1 = {c.x - r, c.y - r};
    lsPoint p2 = {c.x - r, c.y - r};
    return ls_bounbox_create(&p1, &p2);
}

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale)
{
    lsCircle cir = *circle;
    cir.r *= scale;// 考虑xy的话就变成椭圆了
    return cir;
}
