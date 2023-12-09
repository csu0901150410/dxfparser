#include "lsFrame.h"
#include "lsApp.h"
#include "lsCanvas.h"

#include "sample.xpm"

// 事件表绑定
wxBEGIN_EVENT_TABLE(lsFrame, wxFrame)
    EVT_MENU(kMenuQuit, lsFrame::OnQuit)
wxEND_EVENT_TABLE()

// member methods implementation

lsFrame::lsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(kMenuQuit, "E&xit\tAlt-X", "退出应用");
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");

    SetMenuBar(menuBar);

    // 界面布局
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    // 实例化绘图窗口
    m_canvas = new lsCanvas(this);
    sizer->Add(m_canvas, 1, wxEXPAND);

    SetSizer(sizer);
    SetSize(wxSize(800, 600));
    SetAutoLayout(true);
    SetIcon(wxIcon(sample_xpm));
}

void lsFrame::OnQuit(wxCommandEvent &event)
{
    Close(true);
}
