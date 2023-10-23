#ifndef LS_LINE_H
#define LS_LINE_H

#define _CRT_SECURE_NO_WARNINGS

#include "lsPoint.h"
#include "lsBoundbox.h"

typedef struct
{
    lsPoint s;
    lsPoint e;
} lsLine;

lsBoundbox ls_line_get_boundbox(lsLine *line);

lsLine ls_line_scale(const lsLine *line, lsReal scalex, lsReal scaley);

#endif // LS_LINE_H
