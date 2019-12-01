#ifndef _INCLUDE_DEMO_RESOURCE_UTF8_H_
#define _INCLUDE_DEMO_RESOURCE_UTF8_H_

/* Screen 1: Multiple lines text. */
/* Start screen scroll text. */
#define     DEMO_START_NOTICE           (\
"Welcom to SimpleGUI demo process, it will show you how \
to use GUI to show and deal some user action with HMI \
interfacce.\n\
This program uses a uart port to simulate user interaction. \
The serial format is 115200/N/8/1.\
Send \"SPACE\" to start process."\
)

/* Screen 2: List*/
/* Demo list title. */
#define     DEMO_LIST_TITLE             ("Test list")
/* Enumed list item choice type. */
#define     DEMO_LIST_ITEM_NOTICE_TEXT  ("Text message")
#define     DEMO_LIST_ITEM_NOTICE_TIME  ("RTC time")
#define     DEMO_LIST_ITEM_ENUM_VALUE1  ("Enumeration1")
#define     DEMO_LIST_ITEM_ENUM_VALUE2  ("Enumeration2")
#define     DEMO_LIST_ITEM_ENUM_VALUE3  ("Enumeration3")


/* List items data.						Sign	ListText						List item type			List value					Decimal point				Enumed text list    */
/*																										 init.  min.   max.          init.  min.   max.								*/
#define     DEMO_LIST_ITEM_0            {0,     "Simple Item",					LIST_ITEM_NORMAL,		{0,     0,     0     },		{0,     0,     0     },		NULL}
#define     DEMO_LIST_ITEM_1			{1,     "Enum item",					LIST_ITEM_ENUM,			{0,     0,     1     },		{0,     0,     0     },		s_arrszNoticeType}
#define     DEMO_LIST_ITEM_2            {2,     "Integer item",					LIST_ITEM_DIGIT,		{0,     -50,   50    },		{0,     0,     3     },		NULL}
#define     DEMO_LIST_ITEM_3			{3,     "Float item",					LIST_ITEM_DIGIT,		{1,     -50,   50    },		{2,     0,     5     },		NULL}
#define     DEMO_LIST_ITEM_4            {4,     "Looooong text item",			LIST_ITEM_NORMAL,		{0,     0,     0     },		{0,     0,     0     },		NULL}
#define     DEMO_LIST_ITEM_5            {5,     "Edit box",						LIST_ITEM_NORMAL,		{0,     0,     0     },		{0,     0,     0     },		NULL}
#define     DEMO_LIST_ITEM_6			{6,     "Real time graph",				LIST_ITEM_NORMAL,		{0,     0,     0     },		{0,     0,     0     },		NULL}
#define     DEMO_LIST_ITEM_7            {7,     "Test item 1",				    LIST_ITEM_NORMAL,		{0,     0,     0     },		{0,     0,     0     },		NULL}
#define     DEMO_LIST_ITEM_8            {8,     "Test item 2",				    LIST_ITEM_ENUM,			{0,     0,     2     },		{0,     0,     0     },		s_arrszEnumedValue}
#define     DEMO_LIST_ITEM_9			{9,     "Test item 3",				    LIST_ITEM_DIGIT,		{0,     -50,   50    },		{0,     0,     3     },		NULL}

/* Screen 3: Text notice box. */
/* List notice text format. */
#define     DEMO_LIST_NOTICE_TEXT_FMT   ("Select index %u.")

/* Screen 4: RTC notice box. */
#define     DEMO_RTC_NOTICE_TEXT_FMT    ("Now time:\n%04u-%02u-%02u\n%02u:%02u:%02u")

/* Screen 5: Variable box. */
#define     DEMO_VARIABLE_BOX_TITLE     ("Edit box demo")
#define     DEMO_VARIABLE_BOX_HELPER    ("Press TAB to switch focus.\nUp&Down to change value。\nSend \"SPACE\" to continue.")

#endif // _INCLUDE_DEMO_RESOURCE_UTF8_H_
