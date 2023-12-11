#ifndef LS_CANVAS_H
#define LS_CANVAS_H

#include <wx/wx.h>

#include "lsFrame.h"

#include "lsPoint.h"
#include "lsLine.h"

class lsCanvas : public wxPanel
{
public:
    lsCanvas(lsFrame *parent);

// 事件响应
public:
    void OnPaint(wxPaintEvent &event);
    void render(wxDC &dc);

public:
    void loadRandomEntity();

public:
    std::vector<lsPoint> m_points;
    std::vector<lsLine> m_lines;

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // LS_CANVAS_H
