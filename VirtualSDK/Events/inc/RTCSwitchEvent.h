#ifndef _INCLUDED_CLASS_FONT_STYLE_EVENT_H_
#define _INCLUDED_CLASS_FONT_STYLE_EVENT_H_

#include <wx/event.h>

class RTCSwitchEvent: public wxEvent
{
	DECLARE_DYNAMIC_CLASS(RTCSwitchEvent)

	private:
		bool					m_bTurnOn;

	public:
								RTCSwitchEvent(int iWinid = 0, wxEventType iCommandType = wxEVT_NULL);
								RTCSwitchEvent(const RTCSwitchEvent& clsEvent);
		virtual wxEvent*		Clone() const									{return new RTCSwitchEvent(*this);}
		bool					IsBold(void) const								{return m_bBold;}
		void					SetBlod(bool bBold)								{m_bBold = bBold;}
		bool					IsTialic(void) const							{return m_bTialic;}
		void					SetTialic(bool bTialic) 						{m_bTialic =  bTialic;}
		bool					IsForceWidth(void) const						{return m_bForceWidth;}
		void					SetForceWidth(bool bForceWidth)					{m_bForceWidth = bForceWidth;}
		int						GetForcedWidthValue(void) const					{return m_iForcedWidth;}
		void					SetForcedWidthValue(int iForcedWidth)			{m_iForcedWidth = iForcedWidth;}
};

typedef void (wxEvtHandler::*RTCSwitchEventFunc)(RTCSwitchEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_RTC_SWITCH, evtID_FONT_STYLE)
END_DECLARE_EVENT_TYPES()

#define EVT_FONT_STYLE(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY(wxEVT_RTC_SWITCH, id, -1, (wxObjectEventFunction)(wxEventFunction)(RTCSwitchEventFunc)&fn, (wxObject*)NULL),



#endif // _INCLUDED_CLASS_FONT_STYLE_EVENT_H_
