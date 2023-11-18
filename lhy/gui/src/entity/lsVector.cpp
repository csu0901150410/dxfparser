#include <math.h>

#include "lsVector.h"

// TODO : 或许还得写个lsMath
/**
 * @brief 实数插值
 * 
 * @param x1 
 * @param x2 
 * @param t 
 * @return lsReal 
 */
lsReal _interp(lsReal x1, lsReal x2, lsReal t)
{
    return x1 + (x2 - x1) * t;
}

/**
 * @brief 向量模长 ret = |v|
 * 
 * @param v 
 * @return lsReal 
 */
lsReal ls_vector_length(const lsVector *v)
{
    lsReal sq = v->x * v->x + v->y * v->y;
    return sqrt(sq);
}

/**
 * @brief 向量相加 ret = v1 + v2
 * 
 * @param v1 
 * @param v2 
 * @return lsVector 
 */
lsVector ls_vector_add(const lsVector *v1, const lsVector *v2)
{
    lsVector ret;
    ret.x = v1->x + v2->x;
    ret.y = v1->y + v2->y;
    ret.invalid = v1->invalid || v2->invalid;
    return ret;
}

/**
 * @brief 向量相减 ret = v1 - v2
 * 
 * @param v1 
 * @param v2 
 * @return lsVector 
 */
lsVector ls_vector_sub(const lsVector *v1, const lsVector *v2)
{
    lsVector ret;
    ret.x = v1->x - v2->x;
    ret.y = v1->y - v2->y;
    ret.invalid = v1->invalid || v2->invalid;
    return ret;
}

/**
 * @brief 向量点积 ret = v1 . v2
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_dot(const lsVector *v1, const lsVector *v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

/**
 * @brief 向量叉积 ret = v1 x v2
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_cross(const lsVector *v1, const lsVector *v2)
{
    return v1->x * v2->y - v1->y * v2->x;
}

/**
 * @brief 向量插值
 * 
 * @param v1 
 * @param v2 
 * @param t 
 * @return lsVector 
 */
lsVector ls_vector_interp(const lsVector *v1, const lsVector *v2, lsReal t)
{
    lsVector ret;
    ret.x = _interp(v1->x, v2->x, t);
    ret.y = _interp(v1->y, v2->y, t);
    ret.invalid = v1->invalid || v2->invalid;
    return ret;
}

/**
 * @brief 向量归一化
 * 
 * @param v 
 * @return lsVector 
 */
lsVector ls_vector_normalize(const lsVector *v)
{
    lsVector ret = *v;
    lsReal length = ls_vector_length(v);
    if (fabs(length) > EPS)
    {
        length = 1.0f / length;
        ret.x *= length;
        ret.y *= length;
    }
    return ret;
}

/**
 * @brief 向量缩放
 * 
 * @param v 
 * @param factor 
 * @return lsVector 
 */
lsVector ls_vector_scale(const lsVector *v, lsReal factor)
{
    lsVector ret;
    ret.x = v->x * factor;
    ret.y = v->y * factor;
    ret.invalid = v->invalid;
    return ret;
}

/**
 * @brief 向量平移
 * 
 * @param v 
 * @param translate 
 * @return lsVector 
 */
lsVector ls_vector_translate(const lsVector *v, const lsVector *translate)
{
    return ls_vector_add(v, translate);
}

/**
 * @brief 向量夹角 [0, pi]
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_include_angle(const lsVector *v1, const lsVector *v2)
{
    lsReal dot = ls_vector_dot(v1, v2);
    lsReal ll = ls_vector_length(v1) * ls_vector_length(v2);

    if (ll < EPS)
        return 0;
    return acos(dot / ll);
}

/**
 * @brief 向量转角
 * 
 * @param v1 
 * @param v2 
 * @param bccw true-ccw  false-cw
 * @return lsReal 
 */
lsReal ls_vector_rotate_angle(const lsVector *v1, const lsVector *v2, bool bccw)
{
    lsReal angle = ls_vector_include_angle(v1, v2);

    bool ccw;
    lsReal cross = ls_vector_cross(v1, v2);
    if (fabs(cross) > EPS)
        ccw = true;
    else
        ccw = false;

    if ((bccw && ccw) || (!bccw && !ccw))
        return angle;
    return 2 * PI - angle;
}

lsVector ls_vector_get_min(const lsVector *v1, const lsVector *v2)
{
    lsVector ret;
    bool v1valid = ls_vector_is_valid(v1);
    bool v2valid = ls_vector_is_valid(v2);
    if (v1valid || v2valid)
    {
        // 至少有一个valid
        ret.x = MIN(v1valid ? v1->x : MAX_REAL, v2valid ? v2->x : MAX_REAL);
        ret.y = MIN(v1valid ? v1->y : MAX_REAL, v2valid ? v2->y : MAX_REAL);
    }
    ret.invalid = !v1valid && !v2valid;
    return ret;
}

lsVector ls_vector_get_max(const lsVector *v1, const lsVector *v2)
{
    lsVector ret;
    bool v1valid = ls_vector_is_valid(v1);
    bool v2valid = ls_vector_is_valid(v2);
    if (v1valid || v2valid)
    {
        // 至少有一个valid
        ret.x = MAX(v1valid ? v1->x : -MAX_REAL, v2valid ? v2->x : -MAX_REAL);
        ret.y = MAX(v1valid ? v1->y : -MAX_REAL, v2valid ? v2->y : -MAX_REAL);
    }
    ret.invalid = !v1valid && !v2valid;
    return ret;
}

bool ls_vector_is_valid(const lsVector *v)
{
    return !v->invalid;
}

/**
 * @brief 向量变换。先平移再缩放
 * 
 * @param v 
 * @param translate 
 * @param scale 
 * @return lsVector 
 */
lsVector ls_vector_transform(const lsVector *v, const lsVector *translate, lsReal scale)
{
    lsVector ret;
    ret = ls_vector_add(v, translate);
    ret = ls_vector_scale(&ret, scale);
    ret.invalid = v->invalid || translate->invalid;
    return ret;
}
