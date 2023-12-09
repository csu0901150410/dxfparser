#ifndef LS_CANVAS_H
#define LS_CANVAS_H

#include <wx/wx.h>

#include "lsFrame.h"

class lsCanvas : public wxPanel
{
public:
    lsCanvas(lsFrame *parent);

// 事件响应
public:
    void OnPaint(wxPaintEvent &event);
    void render(wxDC &dc);

private:
    wxDECLARE_EVENT_TABLE();
};

#endif // LS_CANVAS_H
