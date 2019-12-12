/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Menu.c												**/
/** Author: Polarix														**/
/** Description: Menu component interface.								**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Menu.h"

//=======================================================================//
//= User Macro definition.											    =//
//=======================================================================//
#define	SGUI_MENU_ICON_DECLARE(NAME)				extern const SGUI_BMP_RES NAME
#define	SGUI_MENU_ICON_DEFINE(NAME, W, H, ...)		const SGUI_BYTE NAME##DATA[] = {__VA_ARGS__};\
													const SGUI_BMP_RES NAME = {W, H, NAME##DATA}
//=======================================================================//
//= Static variable define.												=//
//=======================================================================//
static SGUI_MENU_ICON_DEFINE(SGUI_MENU_ICON_MOVEUP, 5, 3,
0x04,0x06,0x07,0x06,0x04);
static SGUI_MENU_ICON_DEFINE(SGUI_MENU_ICON_MOVEDOWN, 5, 3,
0x01,0x03,0x07,0x03,0x01);

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
/*************************************************************************/
/** Function Name:	SGUI_Menu_Initialize								**/
/** Purpose:		Initialize a menu structure data.					**/
/** Params:																**/
/**	@ pstObj[in]:	Pointer of menu data will be initialized.			**/
/** @ pstFontRes[in]: Font resource object pointer.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Menu_Initialize(SGUI_MENU_STRUCT* pstObj, const SGUI_FONT_RES* pstFontRes)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstFontRes))
	{
		// Initialize member object pointer.
		pstObj->pstFontRes = pstFontRes;
		pstObj->stItems.pstItems = NULL;
		pstObj->stItems.stLayout.iPosX = pstObj->stLayout.iPosX+1;
		pstObj->stItems.stLayout.iPosY = pstObj->stLayout.iPosY+4;
		pstObj->stItems.stLayout.iWidth = pstObj->stLayout.iWidth-2;
		pstObj->stItems.stLayout.iHeight = pstObj->stLayout.iHeight-2-6;
		SGUI_ItemsBase_Initialize(&(pstObj->stItems), pstObj->pstFontRes);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Menu_BindItemsData								**/
/** Purpose:		Bind list item data to object.						**/
/** Params:																**/
/**	@ pstObj[in]:	Pointer of list object.								**/
/** @ pstItemsData[in]: List items data array.							**/
/** @ iItemsCount[in]: Number of list item data.						**/
/** Return:			None.												**/
/** Notice:			None.												**/
/*************************************************************************/
void SGUI_Menu_BindItemsData(SGUI_MENU_STRUCT* pstObj, SGUI_ITEMS_ITEM* pstItemsData, SGUI_INT iItemsCount)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pstObj) && (NULL != pstItemsData) && (iItemsCount > 0))
	{
		SGUI_ItemsBase_BindItemsData(&(pstObj->stItems), pstItemsData, iItemsCount);
	}
}

/*************************************************************************/
/** Function Name:	SGUI_Menu_Repaint									**/
/** Purpose:		Refresh list display.								**/
/** Params:																**/
/**	@ pstDeviceIF[in]: Device driver object pointer.					**/
/**	@ pstObj[in]:	Pointer of menu structure will be refreshed.		**/
/** Return:			None.												**/
/** Notice:			This function will refresh all list display on		**/
/**					screen, include edge, items, title and scrollbar.	**/
/*************************************************************************/
void SGUI_Menu_Repaint(SGUI_SCR_DEV* pstDeviceIF, SGUI_MENU_STRUCT* pstObj)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_RECT_AREA				stIconArea;
	SGUI_POINT					stIconInnerPos;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	stIconInnerPos.iPosX =		0;
	stIconInnerPos.iPosY =		0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstObj)
	{
		/* Clear list item display area. */
		SGUI_Basic_DrawRectangle(pstDeviceIF, pstObj->stLayout.iPosX, pstObj->stLayout.iPosY, pstObj->stLayout.iWidth, pstObj->stLayout.iHeight, SGUI_COLOR_FRGCLR, SGUI_COLOR_BKGCLR);
		// Paint items.
		SGUI_ItemsBase_FitLayout(&(pstObj->stItems));
		SGUI_ItemsBase_Repaint(pstDeviceIF, &(pstObj->stItems));
		/* Paint arrow icon. */
		stIconArea.iPosX = pstObj->stLayout.iPosX+1;
		stIconArea.iWidth = 5;
		stIconArea.iHeight = 3;

		if(pstObj->stItems.iPageStartIndex != 0)
		{
			stIconArea.iPosY = pstObj->stLayout.iPosY+1;
            SGUI_Basic_DrawBitMap(pstDeviceIF, &stIconArea, &stIconInnerPos, &SGUI_MENU_ICON_MOVEUP, SGUI_DRAW_NORMAL);
		}
		if(pstObj->stItems.iPageEndIndex != (pstObj->stItems.iCount-1))
		{
			stIconArea.iPosY = RECT_Y_END(pstObj->stItems.stLayout, pstObj->stItems.stLayout)+1;
			SGUI_Basic_DrawBitMap(pstDeviceIF, &stIconArea, &stIconInnerPos, &SGUI_MENU_ICON_MOVEDOWN, SGUI_DRAW_NORMAL);
		}
	}
}
