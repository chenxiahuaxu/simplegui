#include "RTCSwitchEvent.h"

IMPLEMENT_DYNAMIC_CLASS(RTCSwitchEvent, wxEvent)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_RTC_SWITCH)

RTCSwitchEvent::RTCSwitchEvent(int iWinid, wxEventType iCommandType):
wxEvent(iWinid, iCommandType)
{
	m_bBold = false;
	m_bTialic = false;
	m_bForceWidth = false;
	m_iForcedWidth = 4;
}

RTCSwitchEvent::RTCSwitchEvent(const RTCSwitchEvent& clsEvent):
wxEvent(clsEvent)
{
	m_bBold = clsEvent.IsBold();
	m_bTialic = clsEvent.IsTialic();
	m_bForceWidth = clsEvent.IsForceWidth();
	m_iForcedWidth = clsEvent.GetForcedWidthValue();
}
