#include "lsLine.h"

lsBoundbox ls_line_get_boundbox(lsLine *line)
{
    return ls_bounbox_create(&line->s, &line->e);
}

lsLine ls_line_scale(const lsLine *line, lsReal scalex, lsReal scaley)
{
     lsPoint s = line->s, e = line->e;
    s.x = s.x * scalex;
    s.y = s.y * scaley;
    e.x = e.x * scalex;
    e.y = e.y * scaley;
    lsLine l = {s, e};
    return l;
}
