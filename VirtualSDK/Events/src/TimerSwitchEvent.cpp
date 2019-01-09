#include "TimerSwitchEvent.h"

IMPLEMENT_DYNAMIC_CLASS(TimerSwitchEvent, wxEvent)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_TIMER_SWITCH)

TimerSwitchEvent::TimerSwitchEvent(int iWinid, wxEventType iCommandType):
wxEvent(iWinid, iCommandType)
{
	//m_bIsExpand = false;
	//m_eDirection = NAVI_DIRECTION_NO_OP;
}

TimerSwitchEvent::TimerSwitchEvent(const TimerSwitchEvent& clsEvent):
wxEvent(clsEvent)
{

}
