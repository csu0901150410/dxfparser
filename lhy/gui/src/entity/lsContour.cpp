#include "lsContour.h"

void ls_contour_append(lsContour& contour, const lsEdge& edge)
{
    contour.edges.push_back(edge);
}

lsReal ls_contour_get_length(const lsContour& contour)
{
    lsReal ret = 0.0f;
    for (const auto& edge : contour.edges)
    {
        ret += ls_edge_get_length(edge);
    }
    return ret;
}
