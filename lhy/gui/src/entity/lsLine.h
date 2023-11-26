#ifndef LS_LINE_H
#define LS_LINE_H

#define _CRT_SECURE_NO_WARNINGS

#include "lsBoundbox.h"
#include "lsCoordSystem.h"

typedef struct
{
    lsVector s;
    lsVector e;
} lsLine;

lsBoundbox ls_line_get_boundbox(const lsLine *line);

lsLine ls_line_scale(const lsLine *line, lsReal scale);

lsLine ls_line_translate(const lsLine *line, const lsVector *vector);

lsLine ls_line_transform(const lsLine *l, const lsCoordSystem *cs);

lsReal ls_line_get_length(const lsLine *line);

lsLine ls_line_random_line(lsReal lowx, lsReal lowy, lsReal highx, lsReal highy);

/**
 * @brief 线段应用矩阵变换
 * 
 * @param line 
 * @param m 
 * @return lsLine 
 */
lsLine ls_line_transform_by(const lsLine *line, const lsMatrix *m);

#endif // LS_LINE_H
