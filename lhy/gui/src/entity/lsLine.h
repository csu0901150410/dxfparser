#ifndef LS_LINE_H
#define LS_LINE_H

#define _CRT_SECURE_NO_WARNINGS

#include <vector>

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

/**
 * @brief 线段求交点
 * 
 * Ref : https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment
 * 
 * @param m 输入线段
 * @param n 输入线段
 * @param p 输出交点
 * @return true 存在交点
 * @return false 无交点
 */
bool ls_line_intersect(const lsLine *m, const lsLine *n, lsVector *p);

/**
 * @brief 给定一个线段集合，求集合内所有线段之间的交点
 * 
 * @note 暴力求解方法。有更好的方法，关键词：sweep line algorithm
 * 
 * Ref : https://en.wikipedia.org/wiki/Bentley%E2%80%93Ottmann_algorithm
 * 
 * @param lines 线段集合
 * @param intersections 交点集合
 */
void ls_line_find_lines_intersections_naive(const std::vector<lsLine>& lines, std::vector<lsVector>& intersections);

#endif // LS_LINE_H
