#ifndef LS_CONTOUR_H
#define LS_CONTOUR_H

#include <vector>

#include "lsEdge.h"

// 轮廓结构体定义，用于描述闭合或者非闭合的轮廓线
typedef struct
{
    std::vector<lsEdge> edges;
} lsContour;

void ls_contour_append(lsContour& contour, const lsEdge& edge);

lsReal ls_contour_get_length(const lsContour& contour);

#endif // LS_CONTOUR_H
