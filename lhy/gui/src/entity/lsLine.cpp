#include "lsLine.h"

lsBoundbox ls_line_get_boundbox(const lsLine *line)
{
    return ls_boundbox_create(&line->s, &line->e);
}

lsLine ls_line_scale(const lsLine *line, lsReal scale)
{
    lsLine ret;
    ret.s = ls_point_scale(&line->s, scale);
    ret.e = ls_point_scale(&line->e, scale);
    return ret;
}

lsLine ls_line_translate(const lsLine *line, const lsVector *vector)
{
    lsLine ret;
    ret.s = ls_point_translate(&line->s, vector);
    ret.e = ls_point_translate(&line->e, vector);
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
    ret.s = ls_point_transform(&line->s, cs);
    ret.e = ls_point_transform(&line->e, cs);
    return ret;
}
