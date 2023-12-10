#include "lsCanvas.h"

// 事件表绑定
wxBEGIN_EVENT_TABLE(lsCanvas, wxPanel)
    EVT_PAINT(lsCanvas::OnPaint)
wxEND_EVENT_TABLE()

lsCanvas::lsCanvas(lsFrame *parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColor(42, 42, 42));

    loadRandomEntity();
}

// 窗口重绘
void lsCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void lsCanvas::render(wxDC &dc)
{
    wxPen oldPen = dc.GetPen();
    dc.SetPen(wxColor(255, 255, 255));

    // 绘制实体
    for (const auto& entity : m_entitys)
    {
        switch (entity.type)
        {
        case kLine:
            lsLine l = entity.data.line;
            dc.DrawLine(l.s.x, l.s.y, l.e.x, l.e.y);
            break;

        case kCircle:
            lsCircle cir = entity.data.circle;
            dc.DrawCircle(wxPoint(cir.c.x, cir.c.y), cir.r);
            break;

        case kArc:
            lsArc arc = entity.data.arc;
            dc.DrawArc(wxPoint(arc.s.x, arc.s.y), wxPoint(arc.e.x, arc.e.y), wxPoint(arc.c.x, arc.c.y));
            break;
        }
    }

    dc.SetPen(oldPen);
}

void lsCanvas::loadRandomEntity()
{
    lsLine l;
    l.s.x = 100;
    l.s.y = 100;
    l.e.x = 200;
    l.e.y = 200;
    lsEntity entity = ls_entity_convert_line(&l);
    m_entitys.push_back(entity);


    // std::vector<lsLine> lines;

    // // 生成一些随机的线段
    // lsReal w, h;
    // int iw, ih;
    // GetClientSize(&iw, &ih);
    // w = iw;
    // h = ih;
    // for (size_t i = 0; i < 10; ++i)
    // {
    //     lsLine line = ls_line_random_line(0, 0, w, h);
    //     lsEntity entity = ls_entity_convert_line(&line);
    //     m_entitys.push_back(entity);
    //     lines.push_back(line);
    // }

    // // 所有线段求交点，以圆的方式加入实体，方便观察
    // std::vector<lsVector> intersections;
    // ls_line_find_lines_intersections_naive(lines, intersections);

    // for (const auto& cross : intersections)
    // {
    //     lsCircle cir;
    //     cir.c = {cross.x, cross.y};
    //     cir.r = 10;
    //     lsEntity entity = ls_entity_convert_circle(&cir);
    //     m_entitys.push_back(entity);
    // }
}
