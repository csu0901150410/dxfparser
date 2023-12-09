#pragma once
#include <wx/wx.h>

#include "lsCommon.h"
#include "lsFrame.h"

class lsApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;

public:
    lsFrame *m_frame;
};

// extern lsApp& wxGetApp();
wxDECLARE_APP(lsApp);
