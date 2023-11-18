#ifndef LS_CANVAS_H
#define LS_CANVAS_H

#define _CRT_SECURE_NO_WARNINGS

#include <graphics.h>
#include <vector>

#include "lsEntity.h"
#include "lsCoordSystem.h"

typedef struct
{
    int w;
    int h;

    lsCoordSystem vcs;// Viewport Coordinate System

    bool bDirty;// 脏标记

    bool bPan;// 图形拖动标记
    lsVector panStart;// 拖动开始点
    lsVector panOffset;
    
    bool bZoom;
    lsVector zoomCenter;// 图形缩放的中心点----全部用向量表示，设计上lsPoint属于几何图元，在几何图元描述之外不应使用
    lsReal zoomFactor;// 缩放系数

    bool bHome;

    std::vector<lsEntity> entitys;
} lsCanvas;

void ls_canvas_param_reset(lsCanvas *canvas);

void ls_canvas_init(lsCanvas *canvas, int w, int h);

lsBoundbox ls_canvas_get_boundbox(lsCanvas *canvas);

lsReal ls_canvas_get_w(lsCanvas *canvas);

lsReal ls_canvas_get_h(lsCanvas *canvas);

lsVector ls_canvas_get_center(lsCanvas *canvas);

void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys);

void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity);

void ls_canvas_flush(lsCanvas *canvas);

void ls_canvas_redraw(lsCanvas *canvas);

void ls_canvas_polling(lsCanvas *canvas);

void ls_canvas_destroy(lsCanvas *canvas);

void ls_canvas_load_entity_test(lsCanvas *canvas);

#endif // LS_CANVAS_H
