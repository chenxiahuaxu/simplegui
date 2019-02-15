/*************************************************************************/
/** Copyright.															**/
/** FileName: SGUI_Interface.c											**/
/** Author: Polarix														**/
/** Description: System platform interface.								**/
/*************************************************************************/
//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "SGUI_Interface.h"
#include "SGUI_FlashData.h"

// SDK string encode convert library interface
#ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
 #ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
  #include <iconv.h>
 #endif
#endif

// System RTC interface switch.
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
#include <windows.h>
#include <time.h>
#else
	// Include platform RTC interface declare here.
#include "RTC.h"
#endif

// Dynamic memory operation switch.
#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
 #ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
  #include <malloc.h>
  #include <string.h>
 #endif
#else
	// Include MMU interface header file here.
#include <string.h>
#endif

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
 #ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
  static SGUI_CHAR	g_arrcEncodeBuffer[SGUI_ENCODE_BUFFER_SIZE];
 #endif
#endif

//=======================================================================//
//= Function define.										            =//
//=======================================================================//
#ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
/*************************************************************************/
/** Function Name:	SGUI_SystemIF_EncodeConvert							**/
/** Purpose:		Convert string encode.								**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ szSourceEncode[in]: Source encoder name.							**/
/**	@ szDestinationEncode[in]: Destination encoder name.				**/
/**	@ szSource[in]:		String will converted.							**/
/** Return:			String after convert.								**/
/*************************************************************************/
SGUI_SZSTR SGUI_SystemIF_EncodeConvert(SGUI_CSZSTR szSourceEncode, SGUI_SZSTR szDestinationEncode, SGUI_SZSTR szSource)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SZSTR					pszResultPtr;
	SGUI_SIZE					uiSourceLength, uiOutputBufferSize;
	SGUI_SIZE					uiEncoderResult;
	iconv_t						pIconv;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiEncoderResult			= -1;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	pIconv = iconv_open(szDestinationEncode, szSourceEncode);
	if((iconv_t)-1 != pIconv)
	{
		uiSourceLength = SGUI_SystemIF_StringLength(szSource) + 1;
		uiOutputBufferSize = SGUI_ENCODE_BUFFER_SIZE;
		pszResultPtr = g_arrcEncodeBuffer;
		uiEncoderResult = iconv(pIconv, &szSource, &uiSourceLength, &pszResultPtr, &uiOutputBufferSize);
		if (uiEncoderResult == -1)
		{
			pszResultPtr = NULL;
		}
		else
		{
			pszResultPtr = g_arrcEncodeBuffer;
		}
	}
	iconv_close(pIconv);
	return pszResultPtr;
}
#endif

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_GetNowTime							**/
/** Purpose:		Get system now time.								**/
/** Resources:		System RTC interface.								**/
/** Params:																**/
/**	@ pstTime[out]:		RTC time data structure pointer.				**/
/** Return:			None.												**/
/** Notice:			user need to override this function according to 	**/
/**					the platform used.									**/
/*************************************************************************/
void SGUI_SystemIF_GetNowTime(SGUI_TIME* pstTime)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	time_t						rawtime;
	struct tm*					timeinfo;
#else
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
	time_t						rawtime;
	struct tm*					timeinfo;
#else
	// Add date structure variable declare here.
#endif
#endif
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstTime)
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		// Add RTC Interface call of the platform.
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		if(NULL != timeinfo)
		{
			pstTime->Year = timeinfo->tm_year+1900;
			pstTime->Month = timeinfo->tm_mon+1;
			pstTime->Day = timeinfo->tm_mday;
			pstTime->Hour = timeinfo->tm_hour;
			pstTime->Minute = timeinfo->tm_min;
			pstTime->Second = timeinfo->tm_sec;
		}
#else
		// Add RTC Interface call of the platform.
#ifdef _SIMPLE_GUI_VIRTUAL_ENVIRONMENT_SIMULATOR_
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		if(NULL != timeinfo)
		{
			pstTime->Year = timeinfo->tm_year+1900;
			pstTime->Month = timeinfo->tm_mon+1;
			pstTime->Day = timeinfo->tm_mday;
			pstTime->Hour = timeinfo->tm_hour;
			pstTime->Minute = timeinfo->tm_min;
			pstTime->Second = timeinfo->tm_sec;
		}
#else
        pstTime->Year = g_stCleandar.tm_year;
        pstTime->Month = g_stCleandar.tm_mon;
        pstTime->Day = g_stCleandar.tm_mday;
        pstTime->Hour = g_stCleandar.tm_hour;
        pstTime->Minute = g_stCleandar.tm_min;
        pstTime->Second = g_stCleandar.tm_sec;
#endif

#endif
	}
}

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_StringLengthCopy						**/
/** Purpose:		Copy string.										**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ szDest[in]:		Source string.									**/
/**	@ szSrc[in]:		Destination string.								**/
/**	@ uiSize[in]:		String length will be copied.					**/
/** Return:			Destination string pointer.							**/
/*************************************************************************/
SGUI_SZSTR SGUI_SystemIF_StringLengthCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc, SGUI_SIZE uiSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	const SGUI_CHAR*			pcSrcPtr;
	SGUI_CHAR*					pcDestPtr;
	SGUI_SIZE					sCopiedCount;
#endif

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	pcSrcPtr =					szSrc;
	pcDestPtr =					szDest;
	sCopiedCount =				0;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != szDest) && (NULL != szSrc))
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		strncpy(szDest, szSrc, uiSize);
#else
		// Add string(character array) copy with length process here;
		while(('\0' != *pcSrcPtr) && (sCopiedCount < uiSize))
		{
			*pcDestPtr++ = *pcSrcPtr++;
			sCopiedCount++;
		}
#endif
	}

	return szDest;
}

#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
/*************************************************************************/
/** Function Name:	SGUI_SystemIF_Allocate								**/
/** Purpose:		Allocate a memory block.							**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ uiSize[in]:		Allocated memory size.							**/
/** Return:			Allocated memory block started address, same as STD	**/
/**					malloc interface.									**/
/*************************************************************************/
void* SGUI_SystemIF_Allocate(SGUI_SIZE uiSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	void						*pAllocatedMemory;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pAllocatedMemory =		NULL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	pAllocatedMemory = malloc(uiSize);
#else
	// Add allocate memory function here;
	pAllocatedMemory = malloc(uiSize);
#endif
	return pAllocatedMemory;
}

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_Free									**/
/** Purpose:		Free a memory block.								**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ pFreePointer[in]:	Free memory pointer 							**/
/** Return:			None.												**/
/*************************************************************************/
void SGUI_SystemIF_Free(void* pFreePointer)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pFreePointer)
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		free(pFreePointer);
#else
		// Add allocate memory function here;
		free(pFreePointer);
#endif
	}
}
#endif

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_MemoryCopy							**/
/** Purpose:		Copy memory block to a new address.					**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ pDest[in]:		Memory address will copied to.					**/
/**	@ pSrc[in]:			Memory data source.								**/
/**	@ sSize[in]:		Copied data size(in byte).						**/
/** Return:			Destination memory block pointer.					**/
/*************************************************************************/
SGUI_PTR SGUI_SystemIF_MemoryCopy(SGUI_PTR pDest, const SGUI_PTR pSrc, SGUI_SIZE sSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	SGUI_SIZE                   sIdx;
	SGUI_BYTE*					pSrcPtr;
#endif
	SGUI_BYTE*					pDestPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pDestPtr =					NULL;
#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	pSrcPtr =					(SGUI_BYTE*)pSrc;
	pDestPtr =					(SGUI_BYTE*)pDest;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pDest) && (NULL != pSrc))
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		// Add memory block copy process here;
		pDestPtr = memcpy(pDest, pSrc, sSize);
#else
		for(sIdx=0; sIdx<sSize; sIdx++)
		{
			*pDestPtr++ = *pSrcPtr++;
		}
#endif
	}

	return pDestPtr;
}

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_MemorySet								**/
/** Purpose:		Set memory area data.           					**/
/** Params:																**/
/**	@ pMemoryPtr[in]:	Memory address will filled. 					**/
/**	@ iSetValue[in]:	Memory data byte value.							**/
/**	@ sSize[in]:		Memory area size.  				        		**/
/** Return:			None.                           					**/
/*************************************************************************/
void SGUI_SystemIF_MemorySet(SGUI_PTR pMemoryPtr, SGUI_BYTE iSetValue, SGUI_SIZE sSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	SGUI_SIZE                   sIdx;
	SGUI_BYTE*					pcbBytePtr;
#endif

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pMemoryPtr) && (0 != sSize))
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		// Add memory area value set process here.
        memset(pMemoryPtr, iSetValue, sSize);
#else
		pcbBytePtr = (SGUI_BYTE*)pMemoryPtr;
        for(sIdx=0; sIdx<sSize; sIdx++)
        {
            *pcbBytePtr++ = iSetValue;
        }
#endif
	}
}

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_StringLength							**/
/** Purpose:		Get string length in bytes.							**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ szString[in]:		String head pointer.							**/
/** Return:			String length in bytes.								**/
/*************************************************************************/
SGUI_SIZE SGUI_SystemIF_StringLength(SGUI_CSZSTR szString)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	SGUI_SIZE					uiStringLength;
	const SGUI_CHAR*			pcCharPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiStringLength =			0;
	pcCharPtr =					szString;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcCharPtr)
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		// Add string(character array) length process here;
		uiStringLength = strlen(pcCharPtr);
#else
		while('\0' != *pcCharPtr)
		{
			uiStringLength++;
			pcCharPtr++;
		}
#endif
	}

	return uiStringLength;
}

/*************************************************************************/
/** Function Name:	SGUI_SystemIF_StringCopy							**/
/** Purpose:		Copy string.										**/
/** Resources:		None.												**/
/** Params:																**/
/**	@ szDest[in]:		Source string.									**/
/**	@ szSrc[in]:		Destination string	.							**/
/** Return:			Destination string pointer.							**/
/*************************************************************************/
SGUI_SZSTR SGUI_SystemIF_StringCopy(SGUI_SZSTR szDest, SGUI_CSZSTR szSrc)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	const SGUI_CHAR*			pcSrcPtr;
	SGUI_CHAR*					pcDestPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcSrcPtr =					szSrc;
	pcDestPtr =					szDest;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pcDestPtr) && (NULL != pcSrcPtr))
	{
#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
		// Add string(character array) time process here;
		strcpy(pcDestPtr, pcSrcPtr);
#else
		while('\0' != *pcSrcPtr)
		{
			*pcDestPtr++ = *pcSrcPtr++;
		}
		*pcDestPtr = '\0';
#endif
	}

	return pcDestPtr;
}

/*****************************************************************************/
/** Function Name:	SGUI_FlashData_GetFilash								**/
/** Purpose:		Read a byte array form ROM(ex. flash).					**/
/** Params:																	**/
/**	@ pstIFObj[in]:		SimpleGUI device interface object pointer.			**/
/**	@ eDataSource[in]:	Data source.										**/
/**	@ adStartAddr[in]:	Read data array start address in source.			**/
/**	@ sReadSize[in]:	Number of data want to read.						**/
/** Return:			None.													**/
/** Notice:			You can specify a data source by eDataSource parameter,	**/
/**					and it always used when your data is in different ROM	**/
/**					space yet. For example, Font data is in external flash	**/
/**					and bitmap data is in chip.								**/
/**					Text paint and bitmap paint in SimpleGUI are processed	**/
/**					as bitmap yet, so tt is necessary to distinguish data	**/
/**					sources in some cases.									**/
/**					This function will be re-write when use in different 	**/
/**					hardware PF.											**/
/*****************************************************************************/
SGUI_SIZE SGUI_SystemIF_GetFlashData(SGUI_SCR_DEV* pstIFObj, SGUI_FLASH_DATA_SOURCE eDataSource, SGUI_ROM_ADDRESS adStartAddr, SGUI_SIZE sReadSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
//#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	SGUI_ROM_ADDRESS			adBaseAddr;
	SGUI_BYTE*					pOutPutDataPtr;
	SGUI_CBYTE*					pDataSource;
//#endif
	SGUI_SIZE					sReadBytes;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
//#ifndef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	adBaseAddr =				adStartAddr;
	pOutPutDataPtr =			pstIFObj->arrBmpDataBuffer;
	pDataSource =				NULL;
//#endif
 	sReadBytes =				0;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
//#ifdef _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	// Add flash operation function here.
//#else
	if((eDataSource > SGUI_FONT_SRC_NONE) && (eDataSource < SGUI_FONT_SRC_UNKNOWN) && (sReadSize > 0))
	{
		switch(eDataSource)
		{
			case SGUI_FONT_SRC_H8:
			{
				pDataSource = SGUI_FONT_H8;
				break;
			}
			case SGUI_FONT_SRC_H12:
			{
				pDataSource = SGUI_FONT_H12;
				break;
			}
			case SGUI_FONT_SRC_H16:
			{
				pDataSource = SGUI_FONT_H16;
				break;
			}
#if 0
			case SGUI_FONT_SRC_H32:
			{
				pDataSource = SGUI_FONT_H32;
				break;
			}
#endif
			case SGUI_NOTICE_ICON:
			{
				pDataSource = SGUI_NOTICE_ICON_DATA;
                break;
			}
			default:
			{
				/* no valid data. */
				break;
			}
		}

		if(NULL != pDataSource)
		{
            for(sReadBytes=0; sReadBytes<sReadSize; sReadBytes++)
			{
				*(pOutPutDataPtr+sReadBytes) = *(pDataSource+adBaseAddr+sReadBytes);
			}
		}
	}
//#endif // _SIMPLE_GUI_USE_SYS_PF_FUNCTIONS_
	return sReadBytes;
}
