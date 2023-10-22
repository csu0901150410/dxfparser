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

    bool bDirty;// ���ƹ�һ��Ͳ���Ҫ�ظ�������

    std::vector<lsEntity> entitys;// ʵ��������������C++�����ԣ�����һ���������
} lsCanvas;

void ls_canvas_init(lsCanvas *canvas, int w, int h);

void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity);

void ls_canvas_flush(lsCanvas *canvas);

void ls_canvas_redraw(lsCanvas *canvas);

void ls_canvas_polling(lsCanvas *canvas);

void ls_canvas_destroy(lsCanvas *canvas);

#endif // LS_CANVAS_H
