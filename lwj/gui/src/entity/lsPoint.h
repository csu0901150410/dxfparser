#ifndef LS_POINT_H
#define LS_POINT_H
#include "lsVector.h"
#include "lsCoordSystem.h"

typedef struct
{
    lsReal x;
    lsReal y;
    lsReal z;
} lsPoint;

lsVector ls_point_p2v(const lsPoint* p);

lsPoint ls_point_v2p(const lsVector* v);

lsPoint ls_point_mirror(lsPoint *o, lsPoint *p);

lsPoint ls_point_translate(const lsPoint* p, const lsVector* v);


lsPoint ls_point_scale(const lsPoint* p, lsReal scale);

lsPoint ls_point_scale_ref(const lsPoint* p, const lsPoint* c, lsReal scale);

lsPoint ls_point_transform(const lsPoint* p, const lsCoordSystem* cs);

#endif // LS_POINT_H
