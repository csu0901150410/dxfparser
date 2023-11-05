#ifndef LS_VECTOR_H
#define LS_VECTOR_H

#include "lsGlobal.h"

typedef struct
{
    lsReal x;
    lsReal y;
} lsVector;

/**
 * @brief ʵ����ֵ
 *
 * @param x1
 * @param x2
 * @param t
 * @return lsReal
 */
lsReal _interp(lsReal x1, lsReal x2, lsReal t);

/**
 * @brief ����ģ�� ret = |v|
 *
 * @param v
 * @return lsReal
 */
lsReal ls_vector_length(const lsVector* v);

/**
 * @brief ������� ret = v1 + v2
 *
 * @param v1
 * @param v2
 * @return lsVector
 */
lsVector ls_vector_add(const lsVector* v1, const lsVector* v2);

/**
 * @brief ������� ret = v1 - v2
 *
 * @param v1
 * @param v2
 * @return lsVector
 */
lsVector ls_vector_sub(const lsVector* v1, const lsVector* v2);

/**
 * @brief ������� ret = v1 . v2
 *
 * @param v1
 * @param v2
 * @return lsReal
 */
lsReal ls_vector_dot(const lsVector* v1, const lsVector* v2);

/**
 * @brief ������� ret = v1 x v2
 *
 * @param v1
 * @param v2
 * @return lsReal
 */
lsReal ls_vector_cross(const lsVector* v1, const lsVector* v2);

/**
 * @brief ������ֵ
 *
 * @param v1
 * @param v2
 * @param t
 * @return lsVector
 */
lsVector ls_vector_interp(const lsVector* v1, const lsVector* v2, lsReal t);

/**
 * @brief ������һ��
 *
 * @param v
 * @return lsVector
 */
lsVector ls_vector_normalize(const lsVector* v);

/**
 * @brief ��������
 *
 * @param v
 * @param factor
 * @return lsVector
 */
lsVector ls_vector_scale(const lsVector* v, lsReal factor);

/**
 * @brief �����н� [0, pi]
 *
 * @param v1
 * @param v2
 * @return lsReal
 */
lsReal ls_vector_include_angle(const lsVector* v1, const lsVector* v2);

/**
 * @brief ����ת��
 *
 * @param v1
 * @param v2
 * @param bccw true-ccw  false-cw
 * @return lsReal
 */
lsReal ls_vector_rotate_angle(const lsVector* v1, const lsVector* v2, bool bccw);

#endif // LS_VECTOR_H
