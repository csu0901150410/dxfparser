#ifndef LS_LINE_H
#define LS_LINE_H

#define _CRT_SECURE_NO_WARNINGS

#include "lsPoint.h"
#include "lsBoundbox.h"
#include "lsCoordSystem.h"

typedef struct
{
    lsPoint s;
    lsPoint e;
} lsLine;

lsBoundbox ls_line_get_boundbox(const lsLine *line);

lsLine ls_line_scale(const lsLine *line, lsReal scale);

lsLine ls_line_translate(const lsLine *line, const lsVector *vector);

lsLine ls_line_transform(const lsLine* l, const lsCoordSystem* cs);

#endif // LS_LINE_H
