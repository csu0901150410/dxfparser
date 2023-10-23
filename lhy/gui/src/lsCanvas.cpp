#include <conio.h>

#include "lsCanvas.h"
#include "lsBoundbox.h"

/**
 * @brief ��ʼ���������������ڡ�
 * 
 * @param canvas ����ָ��
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
 * @brief ��ʵ����������������ʵ��
 * 
 * @param canvas ����ָ��
 * @param entitys ʵ������ָ��
 */
void ls_canvas_load_entity(lsCanvas *canvas, std::vector<lsEntity> *entitys)
{
    for (size_t i = 0; i < entitys->size(); ++i)
        canvas->entitys.push_back((*entitys)[i]);
    canvas->bDirty = true;
}

/**
 * @brief �������ʵ��
 * 
 * @param canvas 
 * @param entity 
 */
void ls_canvas_add_entity(lsCanvas *canvas, lsEntity entity)
{
    if (!canvas)
        return;

    canvas->entitys.push_back(entity);
    canvas->bDirty = true;// �������ˣ���Ҫ���»��ƣ���ȫ���ػ�
}

/**
 * @brief ����˫�����ͼˢ�¡��������ػ档
 * 
 * @param canvas 
 */
void ls_canvas_flush(lsCanvas *canvas)
{
    FlushBatchDraw();
    Sleep(100);
}

/**
 * @brief �����ػ�
 * 
 * @param canvas 
 */
void ls_canvas_redraw(lsCanvas *canvas)
{
    if (!canvas)
        return;
    if (!canvas->bDirty)
        return;// ����Ͳ�������

    // �����ȫ��ʵ��ı߽��
    lsBoundbox box;
    for (size_t i = 0; i < canvas->entitys.size(); ++i)
    {
        lsBoundbox subbox = ls_entity_get_boundbox(&canvas->entitys[i]);
        box = ls_boundbox_combine(&box, &subbox);
    }

    // ����ƽ������������ϵ��
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
 * @brief ������ѯ����������Ӧ������
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
 * @brief ���ٻ���
 * 
 * @param canvas 
 */
void ls_canvas_destroy(lsCanvas *canvas)
{
    closegraph();

    if (NULL == canvas)
        return;
}
