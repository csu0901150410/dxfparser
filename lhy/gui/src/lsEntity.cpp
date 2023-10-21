#include "lsEntity.h"

lsEntity ls_entity_make_point(lsReal vx, lsReal vy)
{
    lsEntity entity;

    lsPoint pt;
    pt.x = vx;
    pt.y = vy;

    entity.type = kPoint;
    entity.data.point = pt;

    return entity;
}

lsEntity ls_entity_make_line(lsReal x1, lsReal y1, lsReal x2, lsReal y2)
{
    lsEntity entity;

    lsPoint ps, pe;
    ps.x = x1;
    ps.y = y1;
    pe.x = x2;
    pe.y = y2;

    lsLine l;
    l.s = ps;
    l.e = pe;

    entity.type = kLine;
    entity.data.line = l;

    return entity;
}

lsEntity ls_entity_make_circle(lsReal cx, lsReal cy, lsReal r)
{
    lsEntity entity;

    lsPoint center;
    center.x = cx;
    center.y = cy;
    
    lsCircle cir;
    cir.center = center;
    cir.radius = r;

    entity.type = kCircle;
    entity.data.circle = cir;

    return entity;
}
