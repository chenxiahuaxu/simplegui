#ifndef _INCLUDE_CLASS_NAVI_BUTTON_EVENT_H_
#define _INCLUDE_CLASS_NAVI_BUTTON_EVENT_H_

#include <wx/event.h>

class TimerSwitchEvent: public wxEvent
{
	DECLARE_DYNAMIC_CLASS(TimerSwitchEvent)

	private:
		//NAVI_DIRECTION			m_eDirection;
	public:
								TimerSwitchEvent(int iWinid = 0, wxEventType iCommandType = wxEVT_NULL);
								TimerSwitchEvent(const TimerSwitchEvent& clsEvent);
		virtual wxEvent*		Clone() const									{return new TimerSwitchEvent(*this);}
};

typedef void (wxEvtHandler::*TimerSwitchEventFunc)(TimerSwitchEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_TIMER_SWITCH, evtID_NAVI_BUTTON)
END_DECLARE_EVENT_TYPES()

#define EVT_NAVI_BTN(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_TIMER_SWITCH, id, -1, (wxObjectEventFunction)(wxEventFunction)(TimerSwitchEventFunc)&fn, (wxObject*)NULL),


#endif // _INCLUDE_CLASS_NAVI_BUTTON_EVENT_H_
