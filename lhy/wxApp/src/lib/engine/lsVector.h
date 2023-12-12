#ifndef LS_VECTOR_H
#define LS_VECTOR_H

#include <vector>

using lsReal = double;

/**
 * @brief Represents a 3d vector (x,y,z)
 * @author Hongyu Liang
 */
class lsVector
{
public:
    lsVector() = default;
    lsVector(lsReal vx, lsReal vy, lsReal vz = 0.0);
    explicit lsVector(lsReal angle);
    explicit lsVector(bool valid);
    ~lsVector() = default;

    // 根据方向角设置单位向量
    void set(lsReal angle);

    void set(lsReal vx, lsReal vy, lsReal vz = 0.0);

    void setPolar(lsReal radius, lsReal angle);

    static lsVector polar(lsReal rho, lsReal theta);

    // 向量模长
    lsReal magnitude() const;

    lsVector normalize();

    lsVector getNormalized() const;

    lsReal distanceTo(const lsVector& v) const;

    // 获取方向角
    lsReal angle() const;

    // 向量转角，逆时针转到指定向量的转角
    lsReal angleTo(const lsVector& v) const;

    // 向量夹角，范围为[0, PI)
    lsReal angleBetween(const lsVector& v1, const lsVector& v2) const;

public:
    lsReal x = 0.0;
    lsReal y = 0.0;
    lsReal z = 0.0;
    bool valid = false;
};

#endif // LS_VECTOR_H
