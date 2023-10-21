#include <conio.h>

#include "lsCanvas.h"

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

    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity ent = canvas->entitys[i];

        switch (ent.type)
        {
        case kLine:
            lsLine l = ent.data.line;
            line(l.s.x, l.s.y, l.e.x, l.e.y);
            break;

        case kCircle:
            lsCircle cir = ent.data.circle;
            circle((int)cir.center.x, (int)cir.center.y, (int)cir.radius);
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
