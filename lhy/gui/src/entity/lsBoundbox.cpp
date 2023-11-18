#include "lsBoundbox.h"

lsBoundbox ls_boundbox_init()
{
    lsBoundbox box;
    box.c1 = invalidVector;
    box.c2 = invalidVector;
    // box.c1.x = MAX_REAL;
    // box.c1.y = MAX_REAL;
    // box.c2.x = -MAX_REAL;
    // box.c2.y = -MAX_REAL;
    return box;
}

bool ls_boundbox_is_valid(const lsBoundbox *box)
{
    return (ls_vector_is_valid(&box->c1) && ls_vector_is_valid(&box->c2));
}

lsBoundbox ls_boundbox_create(const lsVector *v1, const lsVector *v2)
{
    lsBoundbox ret;
    ret.c1 = *v1;
    ret.c2 = *v2;
    return ret;
}

lsVector ls_boundbox_get_min(const lsBoundbox *box)
{
    return ls_vector_get_min(&box->c1, &box->c2);
}

lsVector ls_boundbox_get_max(const lsBoundbox *box)
{
    return ls_vector_get_max(&box->c1, &box->c2);
}

lsBoundbox ls_boundbox_combine(const lsBoundbox *box1, const lsBoundbox *box2)
{
    lsBoundbox ret;

    lsVector min1 = ls_boundbox_get_min(box1);
    lsVector max1 = ls_boundbox_get_max(box1);
    lsVector min2 = ls_boundbox_get_min(box2);
    lsVector max2 = ls_boundbox_get_max(box2);

    ret.c1 = ls_vector_get_min(&min1, &min2);
    ret.c2 = ls_vector_get_max(&max1, &max2);
    return ret;
}

lsReal ls_boundbox_width(const lsBoundbox *box)
{
    return fabs(box->c1.x - box->c2.x);
}

lsReal ls_boundbox_height(const lsBoundbox *box)
{
    return fabs(box->c1.y - box->c2.y);
}

lsVector ls_boundbox_center(const lsBoundbox *box)
{
    lsVector ret = ls_vector_add(&box->c1, &box->c2);
    ret = ls_vector_scale(&ret, 0.5);
    return ret;
}

lsBoundbox ls_boundbox_scale(const lsBoundbox *box, lsReal scale)
{
    lsBoundbox ret;
    ret.c1 = ls_vector_scale(&box->c1, scale);
    ret.c2 = ls_vector_scale(&box->c2, scale);
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
    ret.c1 = ls_vector_transform(&box->c1, &cs->origin, cs->scale);
    ret.c2 = ls_vector_transform(&box->c2, &cs->origin, cs->scale);
    return ret;
}

lsVector ls_boundbox_get_corner1(const lsBoundbox *box)
{
    return box->c1;
}

lsVector ls_boundbox_get_corner2(const lsBoundbox *box)
{
    return box->c2;
}
