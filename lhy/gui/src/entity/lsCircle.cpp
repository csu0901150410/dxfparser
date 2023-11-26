#include "lsCircle.h"

lsBoundbox ls_circle_get_boundbox(const lsCircle *circle)
{
    lsVector v1 = {circle->r, circle->r};
    lsVector v2 = {-circle->r, -circle->r};
    lsVector c1 = ls_vector_translate(&circle->c, &v1);
    lsVector c2 = ls_vector_translate(&circle->c, &v2);
    return ls_boundbox_create(&c1, &c2);
}

lsCircle ls_circle_scale(const lsCircle *circle, lsReal scale)
{
    lsCircle ret;
    ret.c = ls_vector_scale(&circle->c, scale);
    ret.r = circle->r * scale;
    return ret;
}

lsCircle ls_circle_translate(const lsCircle *circle, const lsVector *vector)
{
    lsCircle ret;
    ret.c = ls_vector_translate(&circle->c, vector);
    ret.r = circle->r;
    return ret;
}

/**
 * @brief 整圆的坐标系变换。将整圆的世界坐标转换到坐标系 \p cs 下的坐标表示。
 * 
 * @param circle 
 * @param cs 
 * @return lsCircle 
 */
lsCircle ls_circle_transform(const lsCircle *circle, const lsCoordSystem *cs)
{
    lsCircle ret;
    lsVector translate = ls_vector_scale(&cs->origin, -1.0);
    ret.c = ls_vector_transform(&circle->c, &translate, cs->scale);
    ret.r = circle->r * cs->scale;
    return ret;
}

lsCircle ls_circle_transform_by(const lsCircle *circle, const lsMatrix *m)
{
    /**
     * @brief 整圆应用矩阵变换，得到的可能是整圆、椭圆、线段，先不处理
     * 
     * Ref : https://math.stackexchange.com/questions/258351/geometric-transformation-on-circle-equation
     */

    lsCircle ret;
    return ret;
}
