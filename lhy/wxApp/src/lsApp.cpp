#include "lsApp.h"

wxIMPLEMENT_APP(lsApp);

// member methods implementation

bool lsApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    m_frame = new lsFrame("lsApp");
    m_frame->Show(true);
    return true;
}
