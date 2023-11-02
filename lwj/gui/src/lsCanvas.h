#ifndef LS_CANVAS_H
#define LS_CANVAS_H

#define _CRT_SECURE_NO_WARNINGS

#include <graphics.h>
#include <vector>

#include "lsEntity.h"

typedef struct
{
    int w;
    int h;

    bool bDirty;// 脏标记
    lsReal viewRatio;// 初始可视区域占画布的比例

    bool bDrag;// 图形拖动标记
    lsPoint dragStartPoint;// 拖动开始点
    lsPoint dragVector;// 拖动平移向量
    
    lsPoint viewCenter;// 图形显示的中心点
    lsPoint zoomCenter;// 图形缩放的中心点
    lsReal zoomFactor;// 缩放系数

    std::vector<lsEntity> entitys;
} lsCanvas;

void ls_canvas_param_reset(lsCanvas *canvas);

void ls_canvas_init(lsCanvas *canvas, int w, int h);

lsBoundbox ls_canvas_get_boundbox(lsCanvas *canvas);

lsReal ls_canvas_get_w(lsCanvas *canvas);

lsReal ls_canvas_get_h(lsCanvas *canvas);

lsPoint ls_canvas_get_center(lsCanvas *canvas);

void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys);

void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity);

void ls_canvas_flush(lsCanvas *canvas);

void ls_canvas_redraw(lsCanvas *canvas);

void ls_canvas_polling(lsCanvas *canvas);

void ls_canvas_destroy(lsCanvas *canvas);

void ls_canvas_load_entity_test(lsCanvas *canvas);

#endif // LS_CANVAS_H
