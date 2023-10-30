#include <conio.h>
#include <iostream>

#include "lsCanvas.h"
#include "lsBoundbox.h"

/**
 * @brief 画布参数重置
 * 
 * @param canvas 
 */
void ls_canvas_param_reset(lsCanvas *canvas)
{
    canvas->bDirty = true;
    canvas->viewRatio = 0.8;// 初始化时图形显示占据80%的窗口

    canvas->bDrag = false;
    canvas->dragStartPoint = {0.0, 0.0};
    canvas->dragVector = {0.0, 0.0};

    canvas->viewCenter = ls_canvas_get_center(canvas);
    canvas->zoomCenter = ls_canvas_get_center(canvas);
    canvas->zoomFactor = 1.0;
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
    lsPoint tl = {0, 0}, br = {canvas->w - 1, canvas->h - 1};
    return ls_bounbox_create(&tl, &br);
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
 * @return lsPoint 
 */
lsPoint ls_canvas_get_center(lsCanvas *canvas)
{
    lsPoint center;
    center.x = ls_canvas_get_w(canvas) / 2.0;
    center.y = ls_canvas_get_h(canvas) / 2.0;
    return center;
}

// lhy test
void ls_canvas_load_entity_test(lsCanvas *canvas)
{
    lsBoundbox box;

    lsReal wndw = ls_canvas_get_w(canvas);
    lsReal wndh = ls_canvas_get_h(canvas);

    box.left = wndw * (1 / 4.0);
    box.right = wndw * (3 / 4.0);
    box.bottom = wndh * (1 / 4.0);
    box.top = wndh * (2 / 4.0);

    lsPoint bl = {box.left, box.bottom};
    lsPoint tl = {box.left, box.top};
    lsPoint tr = {box.right, box.top};
    lsPoint br = {box.right, box.bottom};

    lsLine left = {bl, tl};
    lsLine top = {tl, tr};
    lsLine right = {tr, br};
    lsLine bottom = {br, bl};

    ls_canvas_add_entity(canvas, ls_entity_convert_line(&left));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&top));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&right));
    ls_canvas_add_entity(canvas, ls_entity_convert_line(&bottom));

    lsCircle circle;
    circle.c = {canvas->w / 2.0, canvas->h / 2.0};
    circle.r = MIN(circle.c.x, circle.c.y);
    ls_canvas_add_entity(canvas, ls_entity_convert_circle(&circle));
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

    // get the boundbox of all entitys
    lsBoundbox box = ls_boundbox_init();
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
        box = ls_boundbox_combine(&box, &subbox);
    }

    if (!ls_boundbox_is_valid(&box))
        return;

    // 计算图形缩放到窗口边界盒大小时的缩放比例。目的是在当前窗口能够完整预览所有图形
    lsReal boxw = ls_boundbox_width(&box), boxh = ls_boundbox_height(&box);
    lsReal wndw = ls_canvas_get_w(canvas), wndh = ls_canvas_get_h(canvas);
    lsReal scale = MAX(boxw / wndw, boxh / wndh);
    scale = 1 / scale;
    scale = canvas->viewRatio * scale;

    // 图形包围盒中心和原点重合时的平移向量
    lsPoint transBoxToOrigin = ls_boundbox_center(&box);
    ls_point_negative(&transBoxToOrigin);

    // 缩放中心平移到原点的向量
    lsPoint transZoomCenterToOrigin = canvas->zoomCenter;
    ls_point_negative(&transZoomCenterToOrigin);

    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];

        // 原始图形缩放并移动到显示中心点
        entity = ls_entity_translate(&entity, &transBoxToOrigin);// 移到原点
        entity = ls_entity_scale(&entity, scale, scale);// 缩放
        entity = ls_entity_translate(&entity, &canvas->viewCenter);// 移到显示中心点

        // 应用光标缩放
        entity = ls_entity_translate(&entity, &transZoomCenterToOrigin);
        entity = ls_entity_scale(&entity, canvas->zoomFactor, canvas->zoomFactor);
        entity = ls_entity_translate(&entity, &canvas->zoomCenter);

        ls_canvas_draw_entity(canvas, &entity);

        if (canvas->bDrag)
        {
            setlinecolor(RED);
            setlinestyle(PS_DASHDOT);
            entity = ls_entity_translate(&entity, &canvas->dragVector);// 叠加拖动偏移
            ls_canvas_draw_entity(canvas, &entity);
            setlinecolor(WHITE);
            setlinestyle(PS_SOLID);
        }
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
            canvas->bDrag = true;
            canvas->dragStartPoint.x = msg.x;
            canvas->dragStartPoint.y = msg.y;
            break;

        case WM_MBUTTONUP:
        {
            canvas->bDrag = false;
            lsPoint dragEnd = {msg.x, msg.y};
            canvas->dragVector = ls_point_sub(&dragEnd, &canvas->dragStartPoint);
            
            // 更新图形显示中心
            canvas->viewCenter = ls_point_add(&canvas->viewCenter, &canvas->dragVector);

            canvas->bDirty = true;
            break;
        }

        case WM_MOUSEMOVE:
        {
            if (canvas->bDrag)
            {
                lsPoint dragEnd = {msg.x, msg.y};
                canvas->dragVector = ls_point_sub(&dragEnd, &canvas->dragStartPoint);
                canvas->bDirty = true;
            }
            break;
        }

        case WM_MOUSEWHEEL:
            if (msg.wheel < 0)
            {
                canvas->zoomFactor -= 0.05;
                if (canvas->zoomFactor < 0.2)
                    canvas->zoomFactor = 0.2;

                canvas->zoomCenter.x = msg.x;
                canvas->zoomCenter.y = msg.y;

                canvas->bDirty = true;
            }
            else
            {
                canvas->zoomFactor += 0.05;

                canvas->zoomCenter.x = msg.x;
                canvas->zoomCenter.y = msg.y;

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
