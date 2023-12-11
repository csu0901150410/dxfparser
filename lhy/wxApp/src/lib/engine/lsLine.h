#ifndef LS_LINE_H
#define LS_LINE_H

#include "lsVector.h"

class lsLine
{
public:
    lsLine();
    lsLine(lsReal sx, lsReal sy, lsReal ex, lsReal ey);
    lsLine(const lsVector& s, const lsVector& e);

public:
    lsVector getStartPoint() const;
    void setStartPoint(const lsVector& v);
    lsVector getEndPoint() const;
    void setEndPoint(const lsVector& v);

    lsVector getMiddlePoint() const;

    lsReal getLength() const;

public:
    lsVector s;
    lsVector e;
};

#endif // LS_LINE_H
