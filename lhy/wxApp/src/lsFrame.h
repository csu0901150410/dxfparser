#pragma once
#include <wx/wx.h>

#include "lsCommon.h"

class lsCanvas;

class lsFrame : public wxFrame
{
public:
    lsFrame(const wxString& title);

public:
    void OnQuit(wxCommandEvent& event);

public:
    lsCanvas *m_canvas;

private:
    wxDECLARE_EVENT_TABLE();
};
