#ifndef LS_MATRIX_H
#define LS_MATRIX_H

#include "lsGlobal.h"

/**
 * @brief 矩阵结构体定义
 * @note 主要用于计算几何中的运算，考虑到齐次坐标，故使用4x4的矩阵，不是任意维度的矩阵。
 * 
 */
typedef struct
{
    lsReal m[4][4];// 按列向量存储。m := [c0[4], c1[4], c2[4], c3[4]]，即 m[col][row]，m[列编号][行编号]
} lsMatrix;


#include "lsMatrix.h"

/**
 * @brief 矩阵克隆
 * 
 * @param src 
 * @param dst 
 */
void ls_matrix_clone(const lsMatrix *src, lsMatrix *dst);

/**
 * @brief 矩阵加法。m = a + b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_addition
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_add(lsMatrix *m, const lsMatrix *a, const lsMatrix *b);

/**
 * @brief 矩阵减法。ret = a - b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_addition
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_sub(lsMatrix *m, const lsMatrix *a, const lsMatrix *b);

/**
 * @brief 矩阵乘法。m = a * b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_multiplication
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_mul(lsMatrix *m, const lsMatrix *a, const lsMatrix *b);

/**
 * @brief 矩阵标量乘法。m *= f
 * 
 * Ref : https://en.wikipedia.org/wiki/Scalar_multiplication
 * 
 * @param m 
 * @param f 
 */
void ls_matrix_scale(lsMatrix *m, lsReal f);

/**
 * @brief 矩阵转置
 * 
 * Ref : https://en.wikipedia.org/wiki/Transpose
 * 
 * @param m 
 */
void ls_matrix_transpose(lsMatrix *m);

/**
 * @brief 矩阵设置为单位矩阵
 * 
 * Reference : https://en.wikipedia.org/wiki/Identity_matrix
 * 
 * @param m 
 */
void ls_matrix_set_identity(lsMatrix *m);

/**
 * @brief 矩阵设置为零矩阵
 * 
 * @param m 
 */
void ls_matrix_set_zero(lsMatrix *m);

/**
 * @brief 矩阵设置为平移矩阵
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_set_translate(lsMatrix *m, lsReal x, lsReal y, lsReal z);

/**
 * @brief 应用平移变换
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_apply_translate(lsMatrix *m, lsReal x, lsReal y, lsReal z);

/**
 * @brief 矩阵设置为缩放矩阵
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_set_scale(lsMatrix *m, lsReal x, lsReal y, lsReal z);

/**
 * @brief 应用缩放变换
 * 
 * @param m 
 * @param x x缩放系数
 * @param y y缩放系数
 * @param z z缩放系数
 */
void ls_matrix_apply_scale(lsMatrix *m, lsReal x, lsReal y, lsReal z);

/**
 * @brief 矩阵设置为旋转矩阵。旋转通过轴角表示
 * 
 * Ref : https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
 *       https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 * @param theta 弧度制
 */
void ls_matrix_set_rotate(lsMatrix *m, lsReal x, lsReal y, lsReal z, lsReal theta);

/**
 * @brief 应用旋转变换
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 * @param theta 
 */
void ls_matrix_apply_rotate(lsMatrix *m, lsReal x, lsReal y, lsReal z, lsReal theta);

#endif // LS_MATRIX_H
