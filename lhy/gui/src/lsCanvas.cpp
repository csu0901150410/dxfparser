#include <conio.h>

#include "lsCanvas.h"
#include "lsBoundbox.h"

/**
 * @brief 初始化画布。启动窗口。
 * 
 * @param canvas 画布指针
 */
void ls_canvas_init(lsCanvas *canvas, int w, int h)
{
    if (!canvas)
        return;

    canvas->w = w;
    canvas->h = h;

    initgraph(canvas->w, canvas->h);
}

/**
 * @brief 从实体数组往画布加载实体
 * 
 * @param canvas 画布指针
 * @param entitys 实体数组指针
 */
void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys)
{
    for (size_t i = 0; i < entitys->size(); ++i)
        canvas->entitys.push_back((*entitys)[i]);
    canvas->bDirty = true;
}

/**
 * @brief 画布添加实体
 * 
 * @param canvas 
 * @param entity 
 */
void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity)
{
    if (!canvas)
        return;

    canvas->entitys.push_back(entity);
    canvas->bDirty = true;// 数据脏了，需要重新绘制，会全部重绘
}

/**
 * @brief 画布双缓冲绘图刷新。并不是重绘。
 * 
 * @param canvas 
 */
void ls_canvas_flush(lsCanvas *canvas)
{
    FlushBatchDraw();
    Sleep(100);
}

/**
 * @brief 画布重绘
 * 
 * @param canvas 
 */
void ls_canvas_redraw(lsCanvas *canvas)
{
    if (!canvas)
        return;
    if (!canvas->bDirty)
        return;// 不脏就不绘制了

    // 先求出全部实体的边界盒
    lsBoundbox box;
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
        box = ls_boundbox_combine(&box, &subbox);
    }

    // 计算平移向量和缩放系数
    lsPoint origin = ls_boundbox_min(&box);
    origin.x = -origin.x;
    origin.y = -origin.y;
    lsReal boxw = ls_boundbox_width(&box), boxh = ls_boundbox_height(&box);
    lsReal scalex = boxw / canvas->w, scaley = boxh / canvas->h;
    lsReal scale = MAX(scalex, scaley);
    scale = 1 / scale;

    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = ls_entity_scale(&canvas->entitys[i], scale, scale);

        switch (entity.type)
        {
        case kLine:
            lsLine l = entity.data.line;
            line(l.s.x, l.s.y, l.e.x, l.e.y);
            break;

        case kCircle:
            lsCircle cir = entity.data.circle;
            circle((int)cir.c.x, (int)cir.c.y, (int)cir.r);
            break;
        
        default:
            break;
        }
    }

    canvas->bDirty = false;
}

/**
 * @brief 画布轮询。在这里响应按键。
 * 
 * @param canvas 
 */
void ls_canvas_polling(lsCanvas *canvas)
{
    if (!canvas)
        return;

    BeginBatchDraw();

    while (1)
    {
        ls_canvas_flush(canvas);
        ls_canvas_redraw(canvas);

        if (_kbhit())
            break;
    }

    EndBatchDraw();
}

/**
 * @brief 销毁画布
 * 
 * @param canvas 
 */
void ls_canvas_destroy(lsCanvas *canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}
