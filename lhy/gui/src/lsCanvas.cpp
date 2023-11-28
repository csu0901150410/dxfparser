#include <conio.h>
#include <iostream>

#include "lsCanvas.h"
#include "lsBoundbox.h"

#include "lsArc.h"

/**
 * @brief 画布参数重置
 * 
 * @param canvas 
 */
void ls_canvas_param_reset(lsCanvas *canvas)
{
    canvas->bDirty = true;

    canvas->bPan = false;

    canvas->bZoom = false;
    canvas->zoomCenter = ls_canvas_get_center(canvas);
    canvas->zoomFactor = 1.0;

    canvas->bHome = true;

    ls_matrix_set_identity(&canvas->w2v);
}

/**
 * @brief Initialize canvas
 * 
 * @param canvas 
 */
void ls_canvas_init(lsCanvas *canvas, int w, int h)
{
    if (!canvas)
        return;

    canvas->w = w;
    canvas->h = h;

    ls_canvas_param_reset(canvas);

    initgraph(canvas->w, canvas->h);
}

/**
 * @brief Get the boundbox of canvas
 * 
 * @param canvas 
 * @return lsBoundbox 
 */
lsBoundbox ls_canvas_get_boundbox(lsCanvas *canvas)
{
    lsVector tl = {0, 0}, br = {canvas->w - 1, canvas->h - 1};
    return ls_boundbox_create(&tl, &br);
}

// 建议通过接口获取宽高，防止直接读取时宽高被修改
lsReal ls_canvas_get_w(lsCanvas *canvas)
{
    return canvas->w;
}

// 建议通过接口获取宽高，防止直接读取时宽高被修改
lsReal ls_canvas_get_h(lsCanvas *canvas)
{
    return canvas->h;
}

/**
 * @brief 获取画布的中心坐标
 * 
 * @param canvas 
 * @return lsVector 
 */
lsVector ls_canvas_get_center(lsCanvas *canvas)
{
    lsVector center;
    center.x = ls_canvas_get_w(canvas) / 2.0;
    center.y = ls_canvas_get_h(canvas) / 2.0;
    return center;
}

// lhy test
void ls_canvas_load_entity_test(lsCanvas *canvas)
{
    lsVector lb = {300, 200};
    lsVector lt = {300, 500};
    lsVector rt = {700, 500};
    lsVector rb = {700, 200};

    lsLine left     = {lb, lt};
    lsLine top      = {lt, rt};
    lsLine right    = {rt, rb};
    lsLine bottom   = {rb, lb};

    ls_canvas_add_entity(canvas, ls_entity_convert_line(&left));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&top));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&right));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&bottom));

    // lsCircle circle;
    // circle.c = {15783, 3365};
    // circle.r = 100;
    // ls_canvas_add_entity(canvas, ls_entity_convert_circle(&circle));

    // // 生成一些随机的线段
    // lsReal w = ls_canvas_get_w(canvas);
    // lsReal h = ls_canvas_get_h(canvas);
    // for (size_t i = 0; i < 10; ++i)
    // {
    //     lsLine line = ls_line_random_line(0, 0, w, h);
    //     ls_canvas_add_entity(canvas, ls_entity_convert_line(&line));
    // }
}

/**
 * @brief Load entitys from vector to canvas
 * 
 * @param canvas 
 * @param entitys 
 */
void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys)
{
    for (size_t i = 0; i < entitys->size(); ++i)
    {
        lsEntity ent = (*entitys)[i];
        switch (ent.type)
        {
        case kLine:
            ent.data.line.s.y = canvas->h - ent.data.line.s.y;
            ent.data.line.e.y = canvas->h - ent.data.line.e.y;
            break;

        case kCircle:
            ent.data.circle.c.y = canvas->h - ent.data.circle.c.y;
            break;
        }

        canvas->entitys.push_back(ent);
    }
    canvas->bDirty = true;
}

/**
 * @brief Add a entity to canvas
 * 
 * @param canvas 
 * @param entity 
 */
void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity)
{
    if (!canvas)
        return;

    canvas->entitys.push_back(entity);
    canvas->bDirty = true;// need to redraw
}

/**
 * @brief Flush the drawed data to memory
 * 
 * @param canvas 
 */
void ls_canvas_flush(lsCanvas *canvas)
{
    FlushBatchDraw();
    Sleep(10);
}

/**
 * @brief Draw single entity
 * 
 * @param canvas 
 * @param entity 
 */
void ls_canvas_draw_entity(lsCanvas *canvas, lsEntity *entity)
{
    switch (entity->type)
    {
    case kLine:
        lsLine l = entity->data.line;
        line(l.s.x, l.s.y, l.e.x, l.e.y);
        break;

    case kCircle:
        lsCircle cir = entity->data.circle;
        circle((int)cir.c.x, (int)cir.c.y, (int)cir.r);
        break;

    case kArc:
    {
        lsArc circlearc = entity->data.arc;
        lsBoundbox box = ls_arc_get_circle_boundbox(&circlearc);
        lsVector lb = ls_boundbox_get_min(&box);
        lsVector rt = ls_boundbox_get_max(&box);
        arc(lb.x, rt.y, rt.x, lb.y, 
            ls_arc_get_start_angle(&circlearc), ls_arc_get_end_angle(&circlearc));
        break;
    }
    
    default:
        break;
    }
}

/**
 * @brief Canvas redraw
 * 
 * @param canvas 
 */
void ls_canvas_redraw(lsCanvas *canvas)
{
    if (!canvas)
        return;
    if (!canvas->bDirty)
        return;
    if (canvas->entitys.empty())
        return;

    cleardevice();

    if (canvas->bHome)
    {
        canvas->bHome = false;

        // 按下HOME键，重置视口
        lsBoundbox box = ls_entity_get_boundbox(canvas->entitys);
        canvas->vcs.origin = ls_boundbox_get_min(&box);
        canvas->vcs.scale = 1.0;
    }

    // 缩放触发，计算缩放后的视口再显示
    if (canvas->bZoom)
    {
        canvas->bZoom = false;
        canvas->vcs = ls_cs_zoom_around_center(&canvas->vcs, &canvas->zoomCenter, canvas->zoomFactor);
    }

    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_transform(&entity, &canvas->vcs);
        ls_canvas_draw_entity(canvas, &entity);
    }

    if (canvas->bPan)
    {
        lsCoordSystem viewport = canvas->vcs;
        viewport.origin = ls_vector_sub(&viewport.origin, &canvas->panOffset);

        setlinecolor(RED);
        setlinestyle(PS_DASH);
        for (size_t i = 0; i < canvas->entitys.size(); ++i)
        {
            lsEntity entity = canvas->entitys[i];
            entity = ls_entity_transform(&entity, &viewport);
            ls_canvas_draw_entity(canvas, &entity);
        }
        setlinecolor(WHITE);
        setlinestyle(PS_SOLID);
    }

    canvas->bDirty = false;
}

/**
 * @brief Canvas polling, wait for user input
 * 
 * @param canvas 
 */
void ls_canvas_polling(lsCanvas *canvas)
{
    if (!canvas)
        return;

    ExMessage msg;
    bool bExit = false;

    BeginBatchDraw();

    while (1)
    {
        ls_canvas_redraw(canvas);
        ls_canvas_flush(canvas);

        msg = getmessage(EX_MOUSE | EX_KEY);
        switch (msg.message)
        {
        case WM_MBUTTONDOWN:
            canvas->bPan = true;
            canvas->panStart.x = msg.x;
            canvas->panStart.y = msg.y;
            break;

        case WM_MBUTTONUP:
        {
            canvas->vcs.origin = ls_vector_sub(&canvas->vcs.origin, &canvas->panOffset);

            canvas->bPan = false;
            canvas->bDirty = true;
            break;
        }

        case WM_MOUSEMOVE:
        {
            if (canvas->bPan)
            {
                lsVector panEnd;
                panEnd.x = msg.x;
                panEnd.y = msg.y;

                lsVector offset = ls_vector_sub(&panEnd, &canvas->panStart);
                canvas->panOffset = ls_vector_scale(&offset, 1.0 / canvas->vcs.scale);
                canvas->bDirty = true;
            }
            break;
        }

        case WM_MOUSEWHEEL:
            if (msg.wheel < 0)
            {
                if (canvas->zoomFactor == 0.2)
                    continue;

                canvas->zoomFactor -= 0.1;
                if (canvas->zoomFactor < 0.2)
                    canvas->zoomFactor = 0.2;

                canvas->zoomCenter.x = msg.x;
                canvas->zoomCenter.y = msg.y;

                canvas->bZoom = true;
                canvas->bDirty = true;
            }
            else
            {
                if (canvas->zoomFactor > 10)
                    continue;

                canvas->zoomFactor += 0.1;

                canvas->zoomCenter.x = msg.x;
                canvas->zoomCenter.y = msg.y;

                canvas->bZoom = true;
                canvas->bDirty = true;
            }
            break;

        case WM_KEYDOWN:
            if (VK_ESCAPE == msg.vkcode)
                bExit = true;
            else if (VK_HOME == msg.vkcode)
            {
                // 按下HOME键，回到初始显示状态
                ls_canvas_param_reset(canvas);
            }
            break;
        }

        if (bExit)
            break;
    }

    EndBatchDraw();
}

/**
 * @brief Canvas destroy
 * 
 * @param canvas 
 */
void ls_canvas_destroy(lsCanvas *canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}
