#include <conio.h>

#include "lsCanvas.h"

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
