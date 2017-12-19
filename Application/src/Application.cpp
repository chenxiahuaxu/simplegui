#include "wx\wx.h"
#include "Application.h"

IMPLEMENT_APP(Application);

bool Application::OnInit(void)
{
    wxInitAllImageHandlers();

	m_pclsMainFrame = new LCD_VirtualDevice((wxWindow*)NULL);

	SetTopWindow(m_pclsMainFrame);

	m_pclsMainFrame->Show();

    return true;
}

int Application::OnExit()
{
    return 0;
}
