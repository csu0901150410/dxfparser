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

bool ls_line_intersect(const lsLine *m, const lsLine *n, lsVector *p)
{
    lsVector mes = ls_vector_sub(&m->s, &m->e);
    lsVector nes = ls_vector_sub(&n->s, &n->e);
    lsVector ss = ls_vector_sub(&m->s, &n->s);

    lsReal dinominator = ls_vector_cross(&mes, &nes);
    if (fabs(dinominator) < EPS)
        return false;// 共线了

    lsReal t = ls_vector_cross(&ss, &nes) / dinominator;
    lsReal u = ls_vector_cross(&ss, &mes) / dinominator;

    if (t < 0 || t > 1 || u < 0 || u > 1)
        return false;
    
    lsVector mse = ls_vector_scale(&mes, -1.0 * t);// 反向，由开始点指向结束点（即直线方向向量），再缩放到t倍
    *p = ls_vector_add(&m->s, &mse);// 开始点 + 缩放后的方向向量 = 结束点（交点）
    return true;
}

void ls_line_find_lines_intersections_naive(const std::vector<lsLine>& lines, std::vector<lsVector>& intersections)
{
    for (size_t i = 0; i < lines.size(); ++i)
    {
        const lsLine& iLine = lines[i];

        // 以此和后续所有线段求交点
        for (size_t j = i + 1; j < lines.size(); ++j)
        {
            const lsLine& jLine = lines[j];

            lsVector cross;
            if (ls_line_intersect(&iLine, &jLine, &cross))
            {
                intersections.push_back(cross);
            }
        }
    }
}
