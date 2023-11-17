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
void ls_canvas_param_reset(lsCanvas* canvas)
{
    canvas->bDirty = true;

    canvas->bDrag = false;
    canvas->dragStartPoint = { 0.0, 0.0 };
    canvas->dragEndPoint = { 0.0, 0.0 };
    canvas->dragVector_P = { 0.0, 0.0 };

    canvas->dragVector_V = { 0.0, 0.0 };

    canvas->bZoom = false;
    canvas->zoomCenter = ls_canvas_get_center(canvas);
    canvas->zoomFactor = 1.0;

    canvas->bHome = true;
}



/**
 * @brief Initialize canvas
 *
 * @param canvas
 */
void ls_canvas_init(lsCanvas* canvas, int w, int h)
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
lsBoundbox ls_canvas_get_boundbox(lsCanvas* canvas)
{
    lsPoint tl = { 0, 0 }, br = { canvas->w - 1, canvas->h - 1 };
    return ls_boundbox_create(&tl, &br);
}

// 建议通过接口获取宽高，防止直接读取时宽高被修改
lsReal ls_canvas_get_w(lsCanvas* canvas)
{
    return canvas->w;
}

// 建议通过接口获取宽高，防止直接读取时宽高被修改
lsReal ls_canvas_get_h(lsCanvas* canvas)
{
    return canvas->h;
}

/**
 * @brief 获取画布的中心坐标
 *
 * @param canvas
 * @return lsPoint
 */
lsPoint ls_canvas_get_center(lsCanvas* canvas)
{
    lsPoint center;
    center.x = ls_canvas_get_w(canvas) / 2.0;
    center.y = ls_canvas_get_h(canvas) / 2.0;
    return center;
}

// lhy test
void ls_canvas_load_entity_test(lsCanvas* canvas)
{
    // lsBoundbox box;

    // lsReal wndw = ls_canvas_get_w(canvas);
    // lsReal wndh = ls_canvas_get_h(canvas);

    // box.left = wndw * (1 / 4.0);
    // box.right = wndw * (3 / 4.0);
    // box.bottom = wndh * (1 / 4.0);
    // box.top = wndh * (2 / 4.0);

    // lsPoint bl = {box.left, box.bottom};
    // lsPoint tl = {box.left, box.top};
    // lsPoint tr = {box.right, box.top};
    // lsPoint br = {box.right, box.bottom};

    // lsLine left = {bl, tl};
    // lsLine top = {tl, tr};
    // lsLine right = {tr, br};
    // lsLine bottom = {br, bl};

    // ls_canvas_add_entity(canvas, ls_entity_convert_line(&left));
    // ls_canvas_add_entity(canvas, ls_entity_convert_line(&top));
    // ls_canvas_add_entity(canvas, ls_entity_convert_line(&right));
    // ls_canvas_add_entity(canvas, ls_entity_convert_line(&bottom));

    // lsCircle circle;
    // circle.c = {canvas->w / 2.0, canvas->h / 2.0};
    // circle.r = MIN(circle.c.x, circle.c.y);
    // ls_canvas_add_entity(canvas, ls_entity_convert_circle(&circle));

    // lsPoint ps = {100, 200};
    // lsPoint pa = {150, 185};
    // lsPoint pe = {230, 240};
    // lsArc circlearc = ls_arc_construct_from_ppp(ps, pa, pe);
    // ls_canvas_add_entity(canvas, ls_entity_convert_arc(&circlearc));

    lsCircle circle;
    circle.c = { 15783, 3365 };
    circle.r = 100;
    ls_canvas_add_entity(canvas, ls_entity_convert_circle(&circle));
}

/**
 * @brief Load entitys from vector to canvas
 *
 * @param canvas
 * @param entitys
 */
void ls_canvas_load_entity(lsCanvas* canvas, std::vector<lsEntity>* entitys)
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
void ls_canvas_add_entity(lsCanvas* canvas, lsEntity entity)
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
void ls_canvas_flush(lsCanvas* canvas)
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
void ls_canvas_draw_entity(lsCanvas* canvas, lsEntity* entity)
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
        arc(box.left, box.top, box.right, box.bottom,
            ls_arc_get_start_angle(&circlearc), ls_arc_get_end_angle(&circlearc));
        break;
    }

    default:
        break;
    }
}

// 以下这两个函数意义上应该属于坐标系统的变换的，也就是lsCoordSystem.cpp中的，但是，
// 我没有解决头文件循环包含的问题，所以暂时放在这里。

/**
 * @brief 求视口坐标系 \p cs 下点 \p screen 的世界坐标
 *
 * @param cs
 * @param screen
 * @return lsPoint
 */
lsPoint ls_cs_screen2world(const lsCoordSystem* cs, const lsPoint* screen)
{
    // world.x = (screen.x / scale) + origin
    lsPoint ret = *screen;
    ret = ls_point_scale(&ret, 1.0 / cs->scale);
    ret = ls_point_translate(&ret, &cs->origin);
    return ret;
}

/**
 * @brief 求世界坐标下点 \p world 在视口坐标系 \p cs 中的坐标
 *
 * @param cs
 * @param world
 * @return lsPoint
 */
lsPoint ls_cs_world2screen(const lsCoordSystem* cs, const lsPoint* world)
{
    return ls_point_transform(world, cs);
}

/**
 * @brief 计算视口坐标系 \p cs 以视口中点 \p screen 为中心缩放到 \p zoomLevel 时的新的视口坐标系
 *
 * @param cs
 * @param screen
 * @param zoomLevel
 * @return lsCoordSystem
 */
lsCoordSystem ls_canvas_zoom_around_point(const lsCoordSystem* cs, const lsPoint* screen, lsReal zoomLevel)
{
    //lsCoordSystem ret = *cs;// 将ret赋值成cs指针，局部变量坐标系ret变不改变整体cs变
    //lsPoint pointBefore = ls_cs_world2screen(&ret, screen);
    //ret.scale = zoomLevel;
    //lsPoint pointAfter = ls_cs_world2screen(&ret, screen);

    //lsVector vectorBefore = ls_point_p2v(&pointBefore);
    //lsVector vectorAfter = ls_point_p2v(&pointAfter);
    //lsVector worldTranslate = ls_vector_sub(&vectorBefore, &vectorAfter);
    //ret.origin = ls_vector_add(&cs->origin, &worldTranslate);

    lsCoordSystem ret;
    lsPoint pointBefore = ls_cs_screen2world(cs, screen);
    ret.scale = zoomLevel;
    lsPoint pointAfter = ls_cs_screen2world(cs, screen);

    lsVector vectorBefore = ls_point_p2v(&pointBefore);
    lsVector vectorAfter = ls_point_p2v(&pointAfter);
    lsVector worldTranslate = ls_vector_sub(&vectorBefore, &vectorAfter);
    ret.origin = ls_vector_add(&cs->origin, &worldTranslate);
    
    return ret;
}

/**
 * @brief 计算视口坐标系 \p cs 拖拽后的新的视口坐标系
 *
 * @param cs
 * @param screenStart
 * @param screenEnd
 * @return lsCoordSystem
 */
lsCoordSystem ls_canvas_translate_around_point(const lsCoordSystem* cs, const lsVector* screen)
{
    lsCoordSystem ret=*cs;
    lsVector vector =*screen;
    lsVector worldTranslate = ls_vector_scale(&vector, -ret.scale);
    ret.origin = ls_vector_add(&cs->origin, &worldTranslate);

    return ret;
}

/**
 * @brief Canvas redraw
 *
 * @param canvas
 */
void ls_canvas_redraw(lsCanvas* canvas)
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
        lsPoint boxCenter = ls_boundbox_center(&box);
        lsPoint boundboxLeft = ls_boundbox_min(&box);
        canvas->vcs.origin = ls_point_p2v(&boundboxLeft);
        canvas->vcs.scale = 1.0;
    }

    // 缩放触发，计算缩放后的视口再显示
    if (canvas->bZoom)
    {
        canvas->bZoom = false;
        canvas->vcs = ls_canvas_zoom_around_point(&canvas->vcs, &canvas->zoomCenter, canvas->zoomFactor);
       
    }
  
    if (canvas->bDrag)
    {
        canvas->bDrag = false;
        canvas->vcs = ls_canvas_translate_around_point(&canvas->vcs, &canvas->dragVector_V);
     
    }
  
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
       

        lsEntity entity = canvas->entitys[i];
      
        entity = ls_entity_transform(&entity, &canvas->vcs);
      
        ls_canvas_draw_entity(canvas, &entity);
        // 拖拽触发，计算拖拽后的视口再显示
     
    }

    canvas->bDirty = false;
}

/**
 * @brief Canvas polling, wait for user input
 *
 * @param canvas
 */
void ls_canvas_polling(lsCanvas* canvas)
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
            canvas->bDirty = true;

            canvas->dragEndPoint.x = msg.x;
            canvas->dragEndPoint.y = msg.y;

            canvas->dragVector_P.x = msg.x - canvas->dragStartPoint.x;
            canvas->dragVector_P.y = msg.y - canvas->dragStartPoint.y;
            canvas->dragVector_V = ls_point_p2v(&canvas->dragVector_P);
         
            break;
        }

        case WM_MOUSEMOVE:
        {
            if (canvas->bDrag)
            {
                canvas->bDirty = true;
                canvas->dragEndPoint.x = msg.x;
                canvas->dragEndPoint.y = msg.y;
             
            }
            break;
        }

        case WM_MOUSEWHEEL:
            if (msg.wheel < 0)
            {
                if (canvas->zoomFactor == 0.2)
                    continue;

                canvas->zoomFactor -= 0.05;
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

                canvas->zoomFactor += 0.05;

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
void ls_canvas_destroy(lsCanvas* canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}
