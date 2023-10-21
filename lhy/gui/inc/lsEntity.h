#ifndef LS_ENTITY_H
#define LS_ENTITY_H

typedef double lsReal;

typedef enum
{
    kUnknown = 0,
    kPoint,
    kLine,
    kArc,
    kCircle,
    kXLine
} EntityType;

typedef struct
{
    lsReal x;
    lsReal y;
} lsPoint;

typedef struct
{
    lsPoint s;
    lsPoint e;
} lsLine;

typedef struct
{
    lsPoint center;
    lsReal radius;
} lsCircle;

typedef union
{
    lsPoint point;
    lsLine line;
    lsCircle circle;
} EntityData;

typedef struct
{
    EntityType type;
    EntityData data;
} lsEntity;

lsEntity ls_entity_make_point(lsReal vx, lsReal vy);
lsEntity ls_entity_make_line(lsReal x1, lsReal y1, lsReal x2, lsReal y2);
// lsEntity ls_entity_make_line(lsPoint ps, lsPoint pe);
lsEntity ls_entity_make_circle(lsReal cx, lsReal cy, lsReal r);

#endif // LS_ENTITY_H
