#pragma once
#include <wx/wx.h>

#include "lsCommon.h"

class lsFrame : public wxFrame
{
public:
    lsFrame(const wxString& title);

public:
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    wxDECLARE_EVENT_TABLE();
};
