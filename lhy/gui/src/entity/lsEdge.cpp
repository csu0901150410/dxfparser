#include "lsEdge.h"

// 从这里开始要用一些C++语法了，慢慢过渡到C++

lsEdge ls_edge_construct(const lsVector& s, const lsVector& e, const lsVector& c, bool bccw)
{
    lsEdge ret;
    ret.s = s;
    ret.e = e;
    ret.c = c;
    ret.bccw = bccw;
    ret.barc = true;
    return ret;
}

lsEdge ls_edge_construct(const lsVector& s, const lsVector& e)
{
    lsEdge ret;
    ret.s = s;
    ret.e = e;
    ret.barc = false;
    return ret;
}

lsVector ls_edge_get_start(const lsEdge& edge)
{
    return edge.s;
}

lsVector ls_edge_get_end(const lsEdge& edge)
{
    return edge.e;
}

lsVector ls_edge_get_mid(const lsEdge& edge)
{
    lsVector ret;
    if (edge.barc)
    {
        
    }
    else
    {
        lsVector dir = ls_vector_sub(&edge.e, &edge.s);
        dir = ls_vector_scale(&dir, 0.5f);
        ret = ls_vector_add(&edge.s, &dir);
    }
    return ret;
}

lsReal ls_edge_get_length(const lsEdge& edge)
{
    lsReal ret;
    if (edge.barc)
    {

    }
    else
    {
        lsVector dir = ls_vector_sub(&edge.e, &edge.s);
        ret = ls_vector_length(&dir);
    }
    return ret;
}
