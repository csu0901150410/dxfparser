#include "lsLine.h"

lsBoundbox ls_line_get_boundbox(const lsLine *line)
{
    return ls_boundbox_create(&line->s, &line->e);
}

lsLine ls_line_scale(const lsLine *line, lsReal scale)
{
    lsLine ret;
    ret.s = ls_vector_scale(&line->s, scale);
    ret.e = ls_vector_scale(&line->e, scale);
    return ret;
}

lsLine ls_line_translate(const lsLine *line, const lsVector *vector)
{
    lsLine ret;
    ret.s = ls_vector_translate(&line->s, vector);
    ret.e = ls_vector_translate(&line->e, vector);
    return ret;
}

/**
 * @brief 线段的坐标系变换。将线段的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param line 
 * @param cs 
 * @return lsLine 坐标系 \p cs 下的线段坐标
 */
lsLine ls_line_transform(const lsLine *line, const lsCoordSystem *cs)
{
    lsLine ret;
    lsVector translate = ls_vector_scale(&cs->origin, -1.0);
    ret.s = ls_vector_transform(&line->s, &translate, cs->scale);
    ret.e = ls_vector_transform(&line->e, &translate, cs->scale);
    return ret;
}

lsReal ls_line_get_length(const lsLine *line)
{
    lsVector v = ls_vector_sub(&line->e, &line->s);
    return ls_vector_length(&v);
}

lsLine ls_line_random_line(lsReal lowx, lsReal lowy, lsReal highx, lsReal highy)
{
    lsLine ret;
    do
    {
        ret.s = ls_vector_random_vector(lowx, lowy, highx, highy);
        ret.e = ls_vector_random_vector(lowx, lowy, highx, highy);
    } while (fabs(ls_line_get_length(&ret) < EPS));

    return ret;
}

lsLine ls_line_transform_by(const lsLine *line, const lsMatrix *m)
{
    lsLine ret;
    ret.s = ls_vector_transform_by(&line->s, m);
    ret.e = ls_vector_transform_by(&line->e, m);
    return ret;
}
