#include "lsCoordSystem.h"

/**
 * @brief 求视口坐标系 \p cs 下向量 \p screen 的世界坐标
 * 
 * @param cs 
 * @param screen 
 * @return lsVector 
 */
lsVector ls_cs_screen2world(const lsCoordSystem *cs, const lsVector *screen)
{
    // world.x = (screen.x / scale) + origin.x
    lsVector ret = *screen;
    ret = ls_vector_scale(&ret, 1.0 / cs->scale);// 缩放回去，使得坐标刻度和世界坐标系一致
    ret = ls_vector_add(&ret, &cs->origin);// 相对坐标加上原点偏移得到绝对世界坐标
    return ret;
}

/**
 * @brief 求世界坐标下向量 \p world 在视口坐标系 \p cs 中的坐标
 * 
 * @param cs 
 * @param world 
 * @return lsVector 
 */
lsVector ls_cs_world2screen(const lsCoordSystem *cs, const lsVector *world)
{
    // screen.x = (world.x - origin.x) * scale
    lsVector ret = ls_vector_sub(world, &cs->origin);
    ret = ls_vector_scale(&ret, cs->scale);
    return ret;
}

/**
 * @brief 视口坐标系 \p cs 以视口中向量 \p screen 为缩放，以 \p zoomLevel 为缩放系数，变换到新的坐标系
 * 
 * @param cs 
 * @param screen 
 * @param zoomLevel 
 * @return lsCoordSystem 返回新的坐标系
 */
lsCoordSystem ls_cs_zoom_around_center(const lsCoordSystem *cs, const lsVector *screen, lsReal zoomLevel)
{
    lsCoordSystem ret = *cs;
    lsVector vectorBefore = ls_cs_screen2world(&ret, screen);// 缩放前光标点对应的世界坐标
    ret.scale = zoomLevel;// 视口坐标系叠加缩放，视口坐标系原点不动只进行缩放
    lsVector vectorAfter = ls_cs_screen2world(&ret, screen);// 缩放后screen这个坐标值的屏幕点对应到新的世界坐标点上了

    lsVector worldTranslate = ls_vector_sub(&vectorBefore, &vectorAfter);// 计算新旧两个世界坐标点的平移向量
    ret.origin = ls_vector_add(&ret.origin, &worldTranslate);// 视口坐标系原点平移，使得缩放后screen这个坐标值的屏幕点对应到原本的世界坐标点上

    return ret;
}
