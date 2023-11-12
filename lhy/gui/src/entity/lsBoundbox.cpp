#include "lsBoundbox.h"

lsBoundbox ls_boundbox_init()
{
    lsBoundbox box;
    box.left = MAX_REAL;
    box.right = MIN_REAL;
    box.bottom = MAX_REAL;
    box.top = MIN_REAL;
    return box;
}

bool ls_boundbox_is_valid(const lsBoundbox *box)
{
    if (box->left < box->right && box->bottom < box->top)
        return true;
    return false;
}

/**
 * @brief Create box from two point
 * 
 * @param p1 
 * @param p2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_create(const lsPoint *p1, const lsPoint *p2)
{
    lsBoundbox box;

    box.left = MIN(p1->x, p2->x);
    box.right = MAX(p1->x, p2->x);
    box.bottom = MIN(p1->y, p2->y);
    box.top = MAX(p1->y, p2->y);
    return box;
}

/**
 * @brief Get the box min point(left, bottom)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_min(const lsBoundbox *box)
{
    lsPoint pt;
    pt.x = box->left;
    pt.y = box->bottom;
    return pt;
}

/**
 * @brief Get the box max point(right, top)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_max(const lsBoundbox *box)
{
    lsPoint pt;
    pt.x = box->right;
    pt.y = box->top;
    return pt;
}

/**
 * @brief Combine two box to a box
 * 
 * @param box1 
 * @param box2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_combine(const lsBoundbox *box1, const lsBoundbox *box2)
{
    lsBoundbox box;
    box.left = MIN(box1->left, box2->left);
    box.right = MAX(box1->right, box2->right);
    box.bottom = MIN(box1->bottom, box2->bottom);
    box.top = MAX(box1->top, box2->top);
    return box;
}

lsReal ls_boundbox_width(const lsBoundbox *box)
{
    return box->right - box->left;
}

lsReal ls_boundbox_height(const lsBoundbox *box)
{
    return box->top - box->bottom;
}

lsPoint ls_boundbox_center(const lsBoundbox *box)
{
    lsPoint center;
    center.x = (box->left + box->right) / 2;
    center.y = (box->bottom + box->top) / 2;
    return center;
}

lsBoundbox ls_boundbox_scale(const lsBoundbox *box, lsReal scalex, lsReal scaley)
{
    lsBoundbox ret;
    ret.left = box->left * scalex;
    ret.right = box->right * scalex;
    ret.bottom = box->bottom * scaley;
    ret.top = box->top * scaley;
    return ret;
}

/**
 * @brief 边界盒的坐标系变换。将边界盒的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param boundbox 
 * @param cs 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_transform(const lsBoundbox *boundbox, const lsCoordSystem *cs)
{
    lsBoundbox ret;
    lsPoint bl = ls_boundbox_min(boundbox);
    lsPoint tr = ls_boundbox_max(boundbox);

    bl = ls_point_transform(&bl, cs);
    tr = ls_point_transform(&tr, cs);
    ret = ls_boundbox_create(&bl, &tr);
    return ret;
}
