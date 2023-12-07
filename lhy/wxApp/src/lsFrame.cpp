#include "lsFrame.h"

wxBEGIN_EVENT_TABLE(lsFrame, wxFrame)
    EVT_MENU(kMenuQuit, lsFrame::OnQuit)
    EVT_MENU(kMenuAbout, lsFrame::OnAbout)
wxEND_EVENT_TABLE()

// member methods implementation

lsFrame::lsFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;

    fileMenu->Append(kMenuQuit, "E&xit\tAlt-X", "退出应用");
    helpMenu->Append(kMenuAbout, "&About", "关于");

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    SetSize(wxSize(800, 600));
}

void lsFrame::OnQuit(wxCommandEvent& event)
{
    Close(true);
}

void lsFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(wxString::Format("帮助界面 %d", 2023), "Title", wxOK | wxICON_INFORMATION, this);
}
