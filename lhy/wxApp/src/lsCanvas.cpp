#include "lsCanvas.h"

// 事件表绑定
wxBEGIN_EVENT_TABLE(lsCanvas, wxPanel)
    EVT_PAINT(lsCanvas::OnPaint)
wxEND_EVENT_TABLE()

lsCanvas::lsCanvas(lsFrame *parent) : wxPanel(parent)
{

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
    // draw some text
    dc.DrawText(wxT("Testing"), 40, 60); 
    
    // draw a circle
    dc.SetBrush(*wxGREEN_BRUSH); // green filling
    dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

    // 注意这里绘制的坐标原点是去除了菜单栏之后的部分
    dc.DrawCircle( wxPoint(700,550), 25 /* radius */ );
    
    // draw a rectangle
    dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
    dc.DrawRectangle( 300, 100, 400, 200 );
    
    // draw a line
    dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle
    
    // Look at the wxDC docs to learn how to draw other stuff
}
