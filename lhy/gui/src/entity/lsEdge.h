#ifndef LS_EDGE_H
#define LS_EDGE_H

#include "lsVector.h"

// 边结构体定义，可表示线段和圆弧，用于描述多边形
typedef struct
{
    lsVector s;
    lsVector e;
    lsVector c;
    bool bccw;
    bool barc;
} lsEdge;

lsEdge ls_edge_construct(const lsVector& s, const lsVector& e, const lsVector& c, bool bccw);

lsEdge ls_edge_construct(const lsVector& s, const lsVector& e);

lsVector ls_edge_get_start(const lsEdge& edge);

lsVector ls_edge_get_end(const lsEdge& edge);

lsVector ls_edge_get_mid(const lsEdge& edge);

lsReal ls_edge_get_length(const lsEdge& edge);

#endif // LS_EDGE_H
