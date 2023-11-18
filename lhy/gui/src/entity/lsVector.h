#ifndef LS_VECTOR_H
#define LS_VECTOR_H

#include "lsGlobal.h"

typedef struct
{
    lsReal x;
    lsReal y;
    lsReal z;
    lsReal w;
    bool invalid;
} lsVector;

static const lsVector invalidVector = {0, 0, 0, 0, true};

/**
 * @brief 实数插值
 * 
 * @param x1 
 * @param x2 
 * @param t 
 * @return lsReal 
 */
lsReal _interp(lsReal x1, lsReal x2, lsReal t);

/**
 * @brief 向量模长 ret = |v|
 * 
 * @param v 
 * @return lsReal 
 */
lsReal ls_vector_length(const lsVector *v);

/**
 * @brief 向量相加 ret = v1 + v2
 * 
 * @param v1 
 * @param v2 
 * @return lsVector 
 */
lsVector ls_vector_add(const lsVector *v1, const lsVector *v2);

/**
 * @brief 向量相减 ret = v1 - v2
 * 
 * @param v1 
 * @param v2 
 * @return lsVector 
 */
lsVector ls_vector_sub(const lsVector *v1, const lsVector *v2);

/**
 * @brief 向量点积 ret = v1 . v2
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_dot(const lsVector *v1, const lsVector *v2);

/**
 * @brief 向量叉积 ret = v1 x v2
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_cross(const lsVector *v1, const lsVector *v2);

/**
 * @brief 向量插值
 * 
 * @param v1 
 * @param v2 
 * @param t 
 * @return lsVector 
 */
lsVector ls_vector_interp(const lsVector *v1, const lsVector *v2, lsReal t);

/**
 * @brief 向量归一化
 * 
 * @param v 
 * @return lsVector 
 */
lsVector ls_vector_normalize(const lsVector *v);

/**
 * @brief 向量缩放
 * 
 * @param v 
 * @param factor 
 * @return lsVector 
 */
lsVector ls_vector_scale(const lsVector *v, lsReal factor);

/**
 * @brief 向量平移
 * 
 * @param v 
 * @param translate 
 * @return lsVector 
 */
lsVector ls_vector_translate(const lsVector *v, const lsVector *translate);

/**
 * @brief 向量夹角 [0, pi]
 * 
 * @param v1 
 * @param v2 
 * @return lsReal 
 */
lsReal ls_vector_include_angle(const lsVector *v1, const lsVector *v2);

/**
 * @brief 向量转角
 * 
 * @param v1 
 * @param v2 
 * @param bccw true-ccw  false-cw
 * @return lsReal 
 */
lsReal ls_vector_rotate_angle(const lsVector *v1, const lsVector *v2, bool bccw);

lsVector ls_vector_get_min(const lsVector *v1, const lsVector *v2);

lsVector ls_vector_get_max(const lsVector *v1, const lsVector *v2);

bool ls_vector_is_valid(const lsVector *v);

lsVector ls_vector_transform(const lsVector *v, const lsVector *translate, lsReal scale);

#endif // LS_VECTOR_H
