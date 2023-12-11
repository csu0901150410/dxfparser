#include "lsPoint.h"

/**
 * @brief 构造一个无效的点对象
 * 
 */
lsPoint::lsPoint()
{
}

lsPoint::lsPoint(lsReal vx, lsReal vy, lsReal vz)
    : pos(vx, vy, vz)
{
}

lsPoint::lsPoint(const lsVector& pos)
    : pos(pos)
{
}

