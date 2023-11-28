#include "lsMatrix.h"

/**
 * @brief 矩阵克隆
 * 
 * @param src 
 * @param dst 
 */
void ls_matrix_clone(const lsMatrix *src, lsMatrix *dst)
{
    if (src == dst)
        return;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; i < 4; ++j)
            dst->m[i][j] = src->m[i][j];
    }
}

/**
 * @brief 矩阵加法。m = a + b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_addition
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_add(lsMatrix *m, const lsMatrix *a, const lsMatrix *b)
{
    lsMatrix ret;
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
            ret.m[i][j] = a->m[i][j] + b->m[i][j];
    }
    ls_matrix_clone(&ret, m);
}

/**
 * @brief 矩阵减法。ret = a - b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_addition
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_sub(lsMatrix *m, const lsMatrix *a, const lsMatrix *b)
{
    lsMatrix ret;
	for (size_t i = 0; i < 4; i++)
    {
		for (size_t j = 0; j < 4; j++)
			ret.m[i][j] = a->m[i][j] - b->m[i][j];
	}
    ls_matrix_clone(&ret, m);
}

/**
 * @brief 矩阵乘法。m = a * b
 * 
 * Ref : https://en.wikipedia.org/wiki/Matrix_multiplication
 * 
 * @param m 
 * @param a 
 * @param b 
 */
void ls_matrix_mul(lsMatrix *m, const lsMatrix *a, const lsMatrix *b)
{
	lsMatrix ret;
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			ret.m[j][i] = (a->m[j][0] * b->m[0][i]) +
						  (a->m[j][1] * b->m[1][i]) +
						  (a->m[j][2] * b->m[2][i]) +
						  (a->m[j][3] * b->m[3][i]);
		}
	}
	ls_matrix_clone(&ret, m);
}

/**
 * @brief 矩阵标量乘法。m *= f
 * 
 * Ref : https://en.wikipedia.org/wiki/Scalar_multiplication
 * 
 * @param m 
 * @param f 
 */
void ls_matrix_scale(lsMatrix *m, lsReal f)
{
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) 
			m->m[i][j] = m->m[i][j] * f;
	}
}

/**
 * @brief 矩阵转置
 * 
 * Ref : https://en.wikipedia.org/wiki/Transpose
 * 
 * @param m 
 */
void ls_matrix_transpose(lsMatrix *m)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
            m->m[i][j] = m->m[j][i];
    }
}

/**
 * @brief 矩阵设置为单位矩阵
 * 
 * Reference : https://en.wikipedia.org/wiki/Identity_matrix
 * 
 * @param m 
 */
void ls_matrix_set_identity(lsMatrix *m)
{
	m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0f; 
	m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
	m->m[1][0] = m->m[1][2] = m->m[1][3] = 0.0f;
	m->m[2][0] = m->m[2][1] = m->m[2][3] = 0.0f;
	m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
}

/**
 * @brief 矩阵设置为零矩阵
 * 
 * @param m 
 */
void ls_matrix_set_zero(lsMatrix *m)
{
	m->m[0][0] = m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
	m->m[1][0] = m->m[1][1] = m->m[1][2] = m->m[1][3] = 0.0f;
	m->m[2][0] = m->m[2][1] = m->m[2][2] = m->m[2][3] = 0.0f;
	m->m[3][0] = m->m[3][1] = m->m[3][2] = m->m[3][3] = 0.0f;
}

/**
 * @brief 矩阵设置为平移矩阵
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_set_translate(lsMatrix *m, lsReal x, lsReal y, lsReal z)
{
	ls_matrix_set_identity(m);
	m->m[3][0] = x;
	m->m[3][1] = y;
	m->m[3][2] = z;
}

/**
 * @brief 叠加平移变换
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_apply_translate(lsMatrix *m, lsReal x, lsReal y, lsReal z)
{
    lsMatrix translate;
    ls_matrix_set_translate(&translate, x, y, z);
    ls_matrix_mul(m, &translate, m);
}

/**
 * @brief 矩阵设置为缩放矩阵
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 */
void ls_matrix_set_scale(lsMatrix *m, lsReal x, lsReal y, lsReal z)
{
	ls_matrix_set_identity(m);
	m->m[0][0] = x;
	m->m[1][1] = y;
	m->m[2][2] = z;
}

/**
 * @brief 应用缩放变换
 * 
 * @param m 
 * @param x x缩放系数
 * @param y y缩放系数
 * @param z z缩放系数
 */
void ls_matrix_apply_scale(lsMatrix *m, lsReal x, lsReal y, lsReal z)
{
    lsMatrix scale;
    ls_matrix_set_scale(&scale, x, y, z);
    ls_matrix_mul(m, &scale, m);
}

/**
 * @brief 获取变换矩阵中的缩放因子
 * 
 * @param m 
 * @return lsReal 
 */
lsReal ls_matrix_get_scale(const lsMatrix *m)
{
    return m->m[3][0];
}

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
void ls_matrix_set_rotate(lsMatrix *m, lsReal x, lsReal y, lsReal z, lsReal theta)
{
    lsReal len = sqrt(x * x + y * y + z * z);
    x /= len;
    y /= len;
    z /= len;

    lsReal c = cos(theta);
    lsReal s = sin(theta);
    lsReal t = 1 - c;

    m->m[0][0] = c + x * x * t;
    m->m[1][0] = x * y * t - z * s;
    m->m[2][0] = x * z * t + y * s;
    m->m[0][1] = y * x * t + z * s;
    m->m[1][1] = c + y * y * t;
    m->m[2][1] = y * z *t - x * s;
    m->m[0][2] = z * x * t - y * s;
    m->m[1][2] = z * y * t + x * s;
    m->m[2][2] = c + z * z * t;
	m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
	m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;	
	m->m[3][3] = 1.0f;
}

/**
 * @brief 应用旋转变换
 * 
 * @param m 
 * @param x 
 * @param y 
 * @param z 
 * @param theta 
 */
void ls_matrix_apply_rotate(lsMatrix *m, lsReal x, lsReal y, lsReal z, lsReal theta)
{
    lsMatrix rotate;
    ls_matrix_set_rotate(&rotate, x, y, z, theta);
    ls_matrix_mul(m, &rotate, m);
}
