#ifndef LS_COORD_SYSTEM_H
#define LS_COORD_SYSTEM_H

#include "lsVector.h"

typedef struct
{
    lsVector origin;// 坐标系原点相对于世界坐标系的平移向量
    lsReal scale;// 坐标系相对于世界坐标系的缩放系数
} lsCoordSystem;

/**
 * @brief 求视口坐标系 \p cs 下向量 \p screen 的世界坐标
 * 
 * @param cs 
 * @param screen 
 * @return lsVector 
 */
lsVector ls_cs_screen2world(const lsCoordSystem *cs, const lsVector *screen);

/**
 * @brief 求世界坐标下向量 \p world 在视口坐标系 \p cs 中的坐标
 * 
 * @param cs 
 * @param world 
 * @return lsVector 
 */
lsVector ls_cs_world2screen(const lsCoordSystem *cs, const lsVector *world);

/**
 * @brief 视口坐标系 \p cs 以视口中向量 \p screen 为缩放，以 \p zoomLevel 为缩放系数，变换到新的坐标系
 * 
 * @param cs 
 * @param screen 
 * @param zoomLevel 
 * @return lsCoordSystem 返回新的坐标系
 */
lsCoordSystem ls_cs_zoom_around_center(const lsCoordSystem *cs, const lsVector *screen, lsReal zoomLevel);

#endif // LS_COORD_SYSTEM_H
