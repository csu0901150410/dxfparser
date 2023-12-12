#include <cmath>

#include "lsVector.h"
#include "lsMath.h"

lsVector::lsVector(lsReal vx, lsReal vy, lsReal vz)
    : x(vx), y(vy), z(vz), valid(true)
{
}

/**
 * @brief 根据给定弧度构造向量
 * 
 * @param angle 单位 弧度
 */
lsVector::lsVector(lsReal angle)
    : x(std::cos(angle))
    , y(std::sin(angle))
    , valid(true)
{
}

/**
 * @brief 构造一个有效的零向量
 * 
 * @param valid 
 */
lsVector::lsVector(bool valid)
    : valid(valid)
{
}

/**
 * @brief 根据方向角将向量设置成单位向量
 * 
 * @param angle 单位 弧度
 */
void lsVector::set(lsReal angle)
{
    x = std::cos(angle);
    y = std::sin(angle);
    z = 0.0;
    valid = true;
}

/**
 * @brief 根据笛卡尔坐标给向量重新设置位置
 * 
 * @param vx 
 * @param vy 
 * @param vz 
 */
void lsVector::set(lsReal vx, lsReal vy, lsReal vz)
{
    x = vx;
    y = vy;
    z = vz;
    valid = true;
}

/**
 * @brief 根据极坐标给向量重新设置位置
 * 
 * @param radius 极径
 * @param angle 极角 单位 弧度
 */
void lsVector::setPolar(lsReal radius, lsReal angle)
{
    x = radius * std::cos(angle);
    y = radius * std::sin(angle);
    z = 0.0;
    valid = true;
}

/**
 * @brief 将极坐标转换为笛卡尔坐标并返回。静态函数
 * 
 * @param rho 极径
 * @param theta 极角 单位 弧度
 * @return lsVector 
 */
lsVector lsVector::polar(lsReal rho, lsReal theta)
{
    return {rho * std::cos(theta), rho * std::sin(theta), 0.0};
}

/**
 * @brief 向量模长
 * 
 * @return lsReal 
 */
lsReal lsVector::magnitude() const
{
    if (!valid)
        return NAN_REAL;
    return sqrt(x * x + y * y + z * z);
}

/**
 * @brief 向量单位化，并返回单位化后的单位向量
 * 
 * @return lsVector 
 */
lsVector lsVector::normalize()
{
    *this = getNormalized();
    return *this;
}

/**
 * @brief 计算当前向量的单位向量
 * 
 * @return lsVector 
 */
lsVector lsVector::getNormalized() const
{
    lsReal len = magnitude();
    if (len < 1e-9)
        return lsVector(false);
    return lsVector(x / len, y / len, z / len);
}
