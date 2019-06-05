#ifndef _INCLUDE_INTERRUPT_H_
#define _INCLUDE_INTERRUPT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum _E_INT_IDX_
{
	SYS_INT_TIMER3,
	SYS_INT_USART1_REV,
	SYS_INT_RTC,
	SYS_INT_USART1_IDLE,
	USR_INT_USART1_REV,
}InterruptProcIndex;

typedef struct _ST_INT_TIG_PROC_
{
	InterruptProcIndex	eIndex;
	bool				bTriggered;
	void				(*IntProc)(void);
}InterruptFlagMgr;

#endif
