#ifndef LS_BOUNDBOX_H
#define LS_BOUNDBOX_H

#include "lsPoint.h"

typedef struct _lsBoundbox
{
    lsReal left;
    lsReal top;
    lsReal right;
    lsReal bottom;
} lsBoundbox;

lsBoundbox ls_boundbox_init();

bool ls_boundbox_is_valid(const lsBoundbox *box);

/**
 * @brief Create box from two point
 * 
 * @param p1 
 * @param p2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_create(const lsPoint *p1, const lsPoint *p2);

/**
 * @brief Get the box min point(left, bottom)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_min(const lsBoundbox *box);

/**
 * @brief Get the box max point(right, top)
 * 
 * @param box 
 * @return lsPoint 
 */
lsPoint ls_boundbox_max(const lsBoundbox *box);

/**
 * @brief Combine two box to a box
 * 
 * @param box1 
 * @param box2 
 * @return lsBoundbox 
 */
lsBoundbox ls_boundbox_combine(const lsBoundbox *box1, const lsBoundbox *box2);

lsReal ls_boundbox_width(const lsBoundbox *box);

lsReal ls_boundbox_height(const lsBoundbox *box);

lsPoint ls_boundbox_center(const lsBoundbox *box);

lsBoundbox ls_boundbox_scale(const lsBoundbox *box, lsReal scalex, lsReal scaley);

lsBoundbox ls_boundbox_transform(const lsBoundbox *boundbox, const lsCoordSystem *cs);

#endif // LS_BOUNDBOX_H
