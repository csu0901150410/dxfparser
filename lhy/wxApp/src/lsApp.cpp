#include "lsApp.h"
#include "lsFrame.h"

wxIMPLEMENT_APP(lsApp);

// member methods implementation

bool lsApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    lsFrame *frame = new lsFrame("lsApp");
    frame->Show(true);
    return true;
}
