#include "lsBoundbox.h"

lsBoundbox ls_boundbox_init()
{
    lsBoundbox box;
    box.minc.x = MAX_REAL;
    box.minc.y = MAX_REAL;
    box.maxc.x = -MAX_REAL;
    box.maxc.y = -MAX_REAL;
    return box;
}

bool ls_boundbox_is_valid(const lsBoundbox *box)
{
    return (box->minc.x < box->maxc.x) && (box->minc.y < box->maxc.y);
}

lsBoundbox ls_boundbox_create(const lsVector *v1, const lsVector *v2)
{
    lsBoundbox ret;
    ret.minc = ls_vector_get_min(v1, v2);
    ret.maxc = ls_vector_get_max(v1, v2);
    return ret;
}

lsVector ls_boundbox_get_min(const lsBoundbox *box)
{
    return box->minc;
}

lsVector ls_boundbox_get_max(const lsBoundbox *box)
{
    return box->maxc;
}

lsBoundbox ls_boundbox_combine(const lsBoundbox *box1, const lsBoundbox *box2)
{
    lsBoundbox ret;
    ret.minc = ls_vector_get_min(&box1->minc, &box2->minc);
    ret.maxc = ls_vector_get_min(&box1->maxc, &box2->maxc);
    return ret;
}

lsReal ls_boundbox_width(const lsBoundbox *box)
{
    return fabs(box->maxc.x - box->minc.x);
}

lsReal ls_boundbox_height(const lsBoundbox *box)
{
    return fabs(box->maxc.y - box->minc.y);
}

lsVector ls_boundbox_center(const lsBoundbox *box)
{
    lsVector ret = ls_vector_add(&box->minc, &box->maxc);
    ret = ls_vector_scale(&ret, 0.5f);
    return ret;
}

lsBoundbox ls_boundbox_scale(const lsBoundbox *box, lsReal scale)
{
    lsBoundbox ret;
    ret.minc = ls_vector_scale(&box->minc, scale);
    ret.maxc = ls_vector_scale(&box->maxc, scale);
    return ret;
}

/**
 * @brief 边界盒的坐标系变换。将边界盒的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param boundbox 
 * @param cs 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_transform(const lsBoundbox *box, const lsCoordSystem *cs)
{
    lsBoundbox ret;
    ret.minc = ls_vector_transform(&box->minc, &cs->origin, cs->scale);
    ret.maxc = ls_vector_transform(&box->maxc, &cs->origin, cs->scale);
    return ret;
}

// 判断两包围盒是否重叠
bool ls_boundbox_overlap(const lsBoundbox *box1, const lsBoundbox *box2)
{
    // 不可能重叠的情况
    return !(box1->minc.x > box2->maxc.x || box1->minc.y > box2->maxc.y ||
             box1->maxc.x < box2->minc.x || box1->maxc.y < box2->minc.y);
}
