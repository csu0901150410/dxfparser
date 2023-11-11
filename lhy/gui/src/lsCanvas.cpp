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
    circle.c = {15783, 3365};
    circle.r = 100;
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

    /**
     * @brief 说明
     * 简单说一下几个概念。
     * 
     * 世界坐标系：这是最大的坐标系，我们的几何实体中的坐标就是世界坐标，理论上是无限大的，
     * 几何实体就摆放在其中。
     * 
     * 画布坐标系/视口坐标系/窗口坐标系：这是我们观察世界坐标系上的几何实体的一个矩形窗口。
     * 我们说透过这个窗口可以看见一部分的世界坐标系，实际上是说，将世界坐标系中可见的那部分
     * 几何实体绘制到矩形窗口上。那么，我们就需要计算出这些几何实体的窗口坐标系坐标，这里
     * 涉及世界坐标系到窗口坐标系的坐标转换。
     * 
     * 很自然的，有时候我们透过窗口看不到任何实体，要想看到实体，显然要移动窗口。注意，这
     * 里说的是，窗口也能在世界坐标系下表示，或者说窗口坐标系的原点有一个对应的世界坐标系
     * 坐标，当我们移动窗口时，其实是在移动这个原点。
     * 
     * 初始化的时候，认为窗口坐标系原点和世界坐标原点重合，X轴正方向向右、Y轴正方向向下，
     * 我们设定世界坐标系也是这样（实际上，我们常用的世界坐标系Y轴是向上的）。
     * 
     */

    // // 计算图形缩放到窗口边界盒大小时的缩放比例。目的是在当前窗口能够完整预览所有图形
    // lsReal boxw = ls_boundbox_width(&box), boxh = ls_boundbox_height(&box);
    // lsReal wndw = ls_canvas_get_w(canvas), wndh = ls_canvas_get_h(canvas);
    // lsReal scale = MAX(boxw / wndw, boxh / wndh);
    // scale = 1 / scale;
    // scale = canvas->viewRatio * scale;


    // 方式一：窗口坐标系原点和世界坐标系原点重合，两个坐标系是等价的，所以几何实体的世界坐标
    // 即是窗口坐标，直接使用世界坐标进行绘制，很显然，几何实体位于窗口之外，看不到。
    setlinecolor(WHITE);
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        ls_canvas_draw_entity(canvas, &entity);
    }

    FlushBatchDraw();

    // 方式二：求解几何实体的包围盒，将窗口坐标系原点移动到包围盒中心。这时候，几何实体的世界
    // 坐标就要转换成窗口坐标才能在窗口上绘制了（在窗口绘制是用的坐标叫窗口坐标）。比如说，有
    // 一个点的世界坐标是P(11, 11)，窗口在世界坐标系原点O时，这个P(11, 11)自然也是窗口坐
    // 标，但是现在将窗口原点移动到W(10, 10)，那么这个点的窗口坐标将变成Q(1, 1)，这个变换
    // 就是在世界坐标系下，P(11, 11) + WO(0-10, 0-10) = OQ(1-0, 1-0)，这是向量的角度
    // 向量坐标表示是终点坐标减去起点坐标。
    // 不难发现，世界坐标到窗口坐标的转换就是点的世界坐标减去窗口原点的世界坐标等于点的窗口坐标

    setlinecolor(RED);

    // get the boundbox of all entitys
    lsBoundbox box = ls_boundbox_init();
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
        box = ls_boundbox_combine(&box, &subbox);
    }
    if (!ls_boundbox_is_valid(&box))
        return;
    // 包围盒的中心，也是移动之后的窗口坐标系原点的世界坐标
    lsPoint boxCenter = ls_boundbox_center(&box);
    ls_point_negative(&boxCenter);// 取反
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        // 平移/坐标转换，二者是等效的描述。
        // 平移说的是，以窗口为参考系保持不动，将几何实体平移到窗口内。概念是移动，但是实际上没有实体发生移动。
        // 坐标转换说的是，以窗口原点为参考重新计算几何实体的坐标，这种描述更接近本质。或者说，这是坐标系的平移。
        // 后续将更新使用transform变换接口。
        entity = ls_entity_translate(&entity, &boxCenter);
        ls_canvas_draw_entity(canvas, &entity);
    }


    // 方式三：将窗口坐标系原点移动到包围盒左下角。对比和方式二的效果。
    setlinecolor(BLUE);
    lsPoint bottomLeftCenter = ls_boundbox_min(&box);
    ls_point_negative(&bottomLeftCenter);// 取反
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_translate(&entity, &bottomLeftCenter);
        ls_canvas_draw_entity(canvas, &entity);
    }

    /**
     * @brief 缩放。
     * 
     * 说一下缩放。缩放可以用两点之间坐标距离来描述。给定一个点P，世界坐标为(0, 1)，
     * 给定一个点Q，世界坐标为(0, 2)，那么PQ的世界坐标距离即是1，我们以此为基准描述
     * 距离。假设有一个坐标系A原点和世界坐标系原点重合，但是P在A中的坐标为(0, 2)，
     * Q在A中的坐标为(0, 4)，显然，坐标系A的坐标刻度是世界坐标系的一半，或者说，A
     * 比世界坐标系更精细。注意，世界坐标中的点一定是不会变动的，变动的只是描述这些点
     * 的坐标系。来看看坐标距离，PQ的基准距离即世界坐标系距离为1，A坐标系距离为2，就
     * 坐标距离来说，两点距离变大了，这就是放大，准确说是坐标刻度缩小。举个例子，从米
     * 的视角来观察，原子和原子之间的距离还是太小了（数值上，以米为单位，即刻度），但
     * 是如果从纳米的视角来观察，这个数值就比较大了，刻度在缩小，坐标尺寸却在变大，这
     * 就是放大。缩小反之。
     * 
     */

    // 现在来写代码。上述描述中的两点距离，将其中一点定为原点，就能得到点的缩放公式。
    // newP - newQ = factor * (oldP - oldQ); oldQ == newQ == Origin
    // so, newP = factor * oldP = (factor * p.x, factor * p.y)
    // 假设窗口坐标系相对于世界坐标系放大两倍。窗口原点还在世界原点，显然，毛都看不到
    setlinecolor(GREEN);
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_scale(&entity, 2, 2);
        ls_canvas_draw_entity(canvas, &entity);
    }

    // 缩放完再将窗口原点移到上次的中心看看。显然，还是毛都看不到。
    // 一个很形象的一维例子，O----A----B，A是实体位置，放大后的坐标距离如果照搬到
    // 世界坐标而不考虑刻度，实体已经到了B位置，如果还是将窗口移到之前的包围盒中心A，
    // 显然是看不到B的。正确的做法是，我们也要将旧的窗口位置A放大到B。
    setlinecolor(CYAN);
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_scale(&entity, 2, 2);
        entity = ls_entity_translate(&entity, &bottomLeftCenter);
        ls_canvas_draw_entity(canvas, &entity);
    }

    // 将窗口坐标原点平移向量OA也放大两倍到OB，再将将窗口移动到B。Ohhhhhhhhh, nb
    // 注意，这里我对圆的缩放是叠加了半径缩放的，如果半径不缩放，黄色圆将会盖住蓝色。
    setlinecolor(YELLOW);
    bottomLeftCenter = ls_point_scale(&bottomLeftCenter, 2);
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_scale(&entity, 2, 2);
        entity = ls_entity_translate(&entity, &bottomLeftCenter);
        ls_canvas_draw_entity(canvas, &entity);
    }

    // 先睡觉，后续更新从变换的角度看待panning&zooming，到这里，一定要掌握点在世界坐
    // 标系中绝对位置不变，只是描述点的坐标系变化这个概念，后续变换都是基于此，即坐标系
    // 的变换。

    // 现在使用坐标变换的视角去看平移和缩放。称世界坐标系为参考系，窗口坐标系为目标系。
    // 平移视为目标系原点在参考系中的移动，缩放视为目标系刻度相对于参考系的变化。通过
    // 窗口使得参考系中的物体可见或者缩放，背后是使用目标系对参考系物体位置的重新描述。
    // 这一描述是通过坐标值来体现的，我们说点P在参考系的坐标是(0, 1)，在目标系的坐标
    // 是(0, 2)，我们是通过坐标数对去描述位置、平移、缩放的，从个描述我们知道，目标
    // 系平移向量为(0, 0)，即两坐标系原点重合，目标系相对于参考系放大系数为2，即向量
    // OP的坐标距离（数值，无单位）从1变成2。
    // 假设现在参考系中有一点Q(2, 2)，参考系的原点平移和点Q重合，问点P在目标系中坐标？
    // 如果还使用点的视角去观察和描述，无疑是困难的，因为点的视角注定和位置有关。这里
    // 引入向量，向量是和位置无关的，但是又带有长度和方向属性，很方便描述平移和缩放。
    // 重新描述，平移视为目标系原点沿着向量OO'移动的变换，缩放视为点P到点P'的变换，其
    // 中满足O'P' = factor * O'P（O/O'/P均是参考系描述，P'是目标系描述），这里使
    // 用了变换一词，这说的是这个描述是针对坐标系中的所有点的。
    // 回到刚才的例子，平移向量OQ为(2, 2)，注意，此时并未知道坐标系的缩放，所以平移向
    // 量是在参考系下描述的，目标向量QP(-2, -1) = P - Q（向量等于终点-起点），目标
    // 向量还是在参考系下的描述，按照缩放系数，目标向量将变成(-4, -2)，这就是在目标系
    // 下的描述，注意(-2, -1)和(-4, -2)是两个坐标系对同一个向量的不同描述，假设我们
    // 是已知这两个描述，那么就能反推出坐标系的缩放。好，现在知道了目标系下QP(-4, -2)，
    // 而且目标系原点正是Q(0, 0)----这是目标系下的坐标，那么不难得出目标系下P点的坐标
    // 就是(-4, -2)。
    // 追踪一下计算链，我们已知点P(0, 1)的参考系坐标，要求其目标系坐标P1，并且目标系原点
    // 和参考系下Q(2, 2)重合，坐标系缩放为2。那么根据P' = O' + O'P'，其中O'(0, 0)，
    // O'P' = QP * factor，所以P' = (P - Q) * factor，这就是坐标变换公式。

    // 先给canvas增加origin和scale成员，代表平移量和缩放量。再增加transform接口
    // 试着将目标系平移到圆左上角区域某点，然后放大显示
    setlinecolor(BROWN);
    canvas->origin = canvas->entitys.front().data.circle.c;
    canvas->origin.x -= 150;
    canvas->origin.y -= 150;
    canvas->scale = 1.5;// 在圆心左上角(150, 150)的地方以1.5倍观察世界坐标系中的这个圆
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsEntity entity = canvas->entitys[i];
        entity = ls_entity_transform(&entity, &canvas->origin, canvas->scale);
        ls_canvas_draw_entity(canvas, &entity);
    }

    canvas->bDirty = false;
}




// // backup
// void ls_canvas_redraw(lsCanvas *canvas)
// {
//     if (!canvas)
//         return;
//     if (!canvas->bDirty)
//         return;
//     if (canvas->entitys.empty())
//         return;

//     cleardevice();

//     // get the boundbox of all entitys
//     lsBoundbox box = ls_boundbox_init();
//     for (size_t i = 0; i < canvas->entitys.size(); ++i)
//     {
//         lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
//         box = ls_boundbox_combine(&box, &subbox);
//     }

//     if (!ls_boundbox_is_valid(&box))
//         return;

//     // 计算图形缩放到窗口边界盒大小时的缩放比例。目的是在当前窗口能够完整预览所有图形
//     lsReal boxw = ls_boundbox_width(&box), boxh = ls_boundbox_height(&box);
//     lsReal wndw = ls_canvas_get_w(canvas), wndh = ls_canvas_get_h(canvas);
//     lsReal scale = MAX(boxw / wndw, boxh / wndh);
//     scale = 1 / scale;
//     scale = canvas->viewRatio * scale;

//     // 图形包围盒中心和原点重合时的平移向量
//     lsPoint transBoxToOrigin = ls_boundbox_center(&box);
//     ls_point_negative(&transBoxToOrigin);

//     // 缩放中心平移到原点的向量
//     lsPoint transZoomCenterToOrigin = canvas->zoomCenter;
//     ls_point_negative(&transZoomCenterToOrigin);

//     for (size_t i = 0; i < canvas->entitys.size(); ++i)
//     {
//         lsEntity entity = canvas->entitys[i];

//         // 原始图形缩放并移动到显示中心点
//         entity = ls_entity_translate(&entity, &transBoxToOrigin);// 移到原点
//         entity = ls_entity_scale(&entity, scale, scale);// 缩放
//         entity = ls_entity_translate(&entity, &canvas->viewCenter);// 移到显示中心点

//         if (canvas->bZoom)
//         {
//             // 应用光标缩放
//             entity = ls_entity_translate(&entity, &transZoomCenterToOrigin);
//             entity = ls_entity_scale(&entity, canvas->zoomFactor, canvas->zoomFactor);
//             entity = ls_entity_translate(&entity, &canvas->zoomCenter);
//         }

//         ls_canvas_draw_entity(canvas, &entity);

//         if (canvas->bDrag)
//         {
//             setlinecolor(RED);
//             setlinestyle(PS_DASHDOT);
//             entity = ls_entity_translate(&entity, &canvas->dragVector);// 叠加拖动偏移
//             ls_canvas_draw_entity(canvas, &entity);
//             setlinecolor(WHITE);
//             setlinestyle(PS_SOLID);
//         }
//     }

//     if (canvas->bZoom)
//         canvas->bZoom = false;

//     canvas->bDirty = false;
// }

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
void ls_canvas_destroy(lsCanvas *canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}
