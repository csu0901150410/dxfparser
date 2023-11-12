#ifndef LS_COORD_SYSTEM_H
#define LS_COORD_SYSTEM_H

#include "lsVector.h"

typedef struct
{
    lsVector origin;// 坐标系原点相对于世界坐标系的平移向量
    lsReal scale;// 坐标系相对于世界坐标系的缩放系数
} lsCoordSystem;

#endif // LS_COORD_SYSTEM_H
