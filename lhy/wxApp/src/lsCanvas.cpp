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
    for (const auto& entity : m_points)
    {
        wxPoint p(entity.pos.x, entity.pos.y);
        dc.DrawCircle(p, 20);
    }

    for (const auto& entity : m_lines)
    {
        wxPoint s(entity.s.x, entity.s.y);
        wxPoint e(entity.e.x, entity.e.y);
        dc.DrawLine(s, e);
    }

    dc.SetPen(oldPen);
}

void lsCanvas::loadRandomEntity()
{
    lsVector v1(100, 200);
    m_points.push_back(v1);

    lsVector v2(200, 200);
    m_points.push_back(v2);

    lsLine l(v1, v2);
    m_lines.push_back(l);
}
