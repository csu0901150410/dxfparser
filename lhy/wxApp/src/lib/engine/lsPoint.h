#ifndef LS_POINT_H
#define LS_POINT_H

#include "lsVector.h"

class lsPoint
{
public:
    lsPoint();
    lsPoint(lsReal vx, lsReal vy, lsReal vz = 0.0);
    lsPoint(const lsVector& pos);

public:
    lsVector getPos() const { return pos; }

    void setPos(const lsVector& pos) { this->pos = pos; }

public:
    lsVector pos;
};

#endif // LS_POINT_H
