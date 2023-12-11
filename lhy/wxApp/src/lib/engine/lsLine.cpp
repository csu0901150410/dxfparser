#include "lsLine.h"

lsLine::lsLine()
{
}

lsLine::lsLine(lsReal sx, lsReal sy, lsReal ex, lsReal ey)
    : s(sx, sy)
    , e(ex, ey)
{
}

lsLine::lsLine(const lsVector& s, const lsVector& e)
    : s(s)
    , e(e)
{
}

lsVector lsLine::getStartPoint() const
{
    return s;
}

void lsLine::setStartPoint(const lsVector& v)
{
    s = v;
}

lsVector lsLine::getEndPoint() const
{
    return e;
}

void lsLine::setEndPoint(const lsVector& v)
{
    e = v;
}
