/*************************************************************************/
/** Copyright.															**/
/** FileName: GUI_Common.c												**/
/** Author: Polarix														**/
/** Version: 1.0.0.0													**/
/** Description: Draw text.												**/
/*************************************************************************/

//=======================================================================//
//= Include files.													    =//
//=======================================================================//
#include "GUI_Common.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
#ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
#include <iconv.h>
#include <time.h>
#endif // _SIMPLE_GUI_ENABLE_ICONV_GB2312_
#include <malloc.h>
#endif //_SIMPLE_GUI_ENABLE_SIMULATOR_

//=======================================================================//
//= Static variable declaration.									    =//
//=======================================================================//
#if defined(_SIMPLE_GUI_ENABLE_SIMULATOR_)&&defined(_SIMPLE_GUI_ENABLE_ICONV_GB2312_)
static char g_arrcEncodeBuffer[ENCODE_BUFFER_SIZE];
#endif

//=======================================================================//
//= Function implementation.										    =//
//=======================================================================//
/*****************************************************************************/
/** Function Name:	GUI_Common_IntegerToStringWithDecimalPoint				**/
/** Purpose:		Convert number to a string and insert decimal point.	**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@iInteger:			Source number.										**/
/**	@uiDecimalPlaces:	Decimal point places.								**/
/**	@pszStringBuffer:	Bit map data buffer.								**/
/**	@iAlignment:		Alignment of number string, positive numbers means	**/
/**						right aligned and negative means left alignment.	**/
/** Return:			Converted string length.								**/
/** Notice:			Only applies to decimal numbers.						**/
/*****************************************************************************/
uint16_t GUI_Common_IntegerToStringWithDecimalPoint(int32_t iInteger, uint16_t uiDecimalPlaces, char* pszStringBuffer, int16_t iAlignment, char cFillCharacter)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char		szNumberString[GUI_NUMBER_STR_LENGTH_MAX] = {0x00};
	uint32_t	uiSourceNumber;
	uint16_t	uiSignBit;
	uint16_t	uiNumberStringLength;
	uint16_t	uiDecimalLength;
	uint16_t	uiOutputLength;
	char*		pcSrcPtr;
	char*		pcDestPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	// Judged sign
	if(iInteger < 0)
	{
		uiSignBit = 1;
		uiSourceNumber = -iInteger;
	}
	else
	{
		uiSignBit = 0;
		uiSourceNumber = iInteger;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Insert dot to string.
	if(uiDecimalPlaces > 0)
	{
		uiDecimalLength = uiDecimalPlaces;
		// Convert number to string, ignore sign.
		uiNumberStringLength = GUI_Common_IntegerToString(uiSourceNumber, szNumberString, 10, 0, cFillCharacter);
        // Set pointer.
		pcSrcPtr = szNumberString + uiNumberStringLength - 1;
		if(uiDecimalLength < uiNumberStringLength)
		{
			uiOutputLength = uiNumberStringLength + 1;
		}
		else
		{
			uiOutputLength = uiDecimalLength + 2;
		}
		pcDestPtr = pszStringBuffer + uiOutputLength + uiSignBit;
		// Process decimal string character.
		*pcDestPtr = '\0';
		pcDestPtr--;
		while((pcSrcPtr >= szNumberString) && (uiDecimalLength > 0))
		{
			*pcDestPtr = *pcSrcPtr;
			pcDestPtr--;
			pcSrcPtr--;
			uiDecimalLength--;
		}
		while(uiDecimalLength > 0)
		{
			*pcDestPtr = '0';
			pcDestPtr--;
			uiDecimalLength --;
		}
		*pcDestPtr = '.';
		pcDestPtr--;
		// Process integer string character.
		if(uiDecimalPlaces >= uiNumberStringLength)
		{
			*pcDestPtr = '0';
			pcDestPtr--;
		}
		else
		{
            while(pcSrcPtr >= szNumberString)
			{
				*pcDestPtr = *pcSrcPtr;
				pcDestPtr--;
				pcSrcPtr--;
			}
		}
		if(uiSignBit > 0)
		{
			*pcDestPtr = '-';
		}

		// Alignment
		uiOutputLength = uiOutputLength + uiSignBit;
		if(iAlignment > 0)
		{
			pcSrcPtr = pszStringBuffer + uiOutputLength - 1;
			if(uiOutputLength > iAlignment)
			{
				iAlignment = uiOutputLength;
			}
			else
			{
				uiOutputLength = iAlignment;
			}
			pcDestPtr = pszStringBuffer + iAlignment;
			*pcDestPtr = '\0';
			pcDestPtr--;

			while(pcDestPtr >= pszStringBuffer)
			{
				if(pcSrcPtr >= pszStringBuffer)
				{
					*pcDestPtr = *pcSrcPtr;
					pcSrcPtr--;
				}
				else
				{
					*pcDestPtr = cFillCharacter;
				}
				pcDestPtr--;
			}
		}
		else
		{
			iAlignment = -iAlignment;
			pcSrcPtr = pszStringBuffer;
			pcDestPtr = pszStringBuffer + uiOutputLength;
			if(uiOutputLength > iAlignment)
			{
				iAlignment = 0;
			}
			else
			{
				iAlignment = iAlignment - uiOutputLength;
				uiOutputLength = uiOutputLength + iAlignment;
			}
			while(iAlignment --)
			{
				*pcDestPtr = cFillCharacter;
				pcDestPtr ++;
			}
			*pcDestPtr = '\0';
		}

	}
	else
	{
		// Convert number to string.
		uiOutputLength = GUI_Common_IntegerToString(iInteger, pszStringBuffer, 10, iAlignment, cFillCharacter);
	}

	return uiOutputLength;
}

/*****************************************************************************/
/** Function Name:	GUI_Common_ConvertIntegerToString						**/
/** Purpose:		Convert number to a string and insert decimal point.	**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@iInteger:			Source number.										**/
/**	@pszStringBuffer:	Bit map data buffer.								**/
/**	@uiBase:			Conversion base.									**/
/**	@iAlignment:		Alignment of number string, positive numbers means	**/
/**						right aligned and negative means left alignment.	**/
/**	@cFillCharacter:	Used when convert string length is less then		**/
/**						alignment length.									**/
/** Return:			Converted string length.								**/
/** Notice:			None.													**/
/*****************************************************************************/
uint16_t GUI_Common_IntegerToString(int32_t iInteger, char* pszStringBuffer, uint16_t uiBase, int16_t iAlignment, char cFillCharacter)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char		szNumberString[GUI_NUMBER_STR_LENGTH_MAX] = {0x00};
	uint32_t	uiSourceNumber;
	uint16_t	uiNumberStringLength = 0;
    char*		pcSrcPtr;
    char*		pcDestPtr;
    uint16_t	uiDigitBit;
    uint16_t	uiSignBit;

    /*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pcSrcPtr = szNumberString + GUI_NUMBER_STR_LENGTH_MAX - 1;
	pcDestPtr = szNumberString;
	*pcSrcPtr = '\0';
	pcSrcPtr--;
	// Judged sign
    if(iInteger < 0)
	{
		if(uiBase == 16)
		{
			uiSignBit = 0;
			uiSourceNumber = (uint32_t)iInteger;
		}
		else
		{
			uiSignBit = 1;
			uiSourceNumber = -iInteger;
		}
	}
	else
	{
		uiSignBit = 0;
		uiSourceNumber = (uint32_t)iInteger;
	}

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	// Convert number to string.
    while(uiSourceNumber != 0)
	{
		uiDigitBit = uiSourceNumber % uiBase;
		if(uiDigitBit < 10)
		{
			*pcSrcPtr = uiDigitBit + '0';
		}
		else
		{
			*pcSrcPtr = uiDigitBit - 10 + 'A';
		}
		uiSourceNumber = uiSourceNumber / uiBase;
		pcSrcPtr--;
		uiNumberStringLength++;
	}
	if(uiSignBit == 1)
	{
		*pcSrcPtr = '-';
		uiNumberStringLength++;
	}
	else
	{
		pcSrcPtr++;
	}

	while((pcDestPtr - uiNumberStringLength) != szNumberString)
	{
		*pcDestPtr = *pcSrcPtr;
		pcSrcPtr++;
		pcDestPtr++;
	}
	if(uiNumberStringLength == 0)
	{
		pcDestPtr = szNumberString;
		*pcDestPtr = '0';
		pcDestPtr++;
		uiNumberStringLength++;
	}
	*pcDestPtr = '\0';
	// Move to out put buffer
	if(iAlignment > 0)
	{
		pcSrcPtr = szNumberString + uiNumberStringLength-1;
		if(uiNumberStringLength > iAlignment)
		{
			iAlignment = uiNumberStringLength;
		}
		else
		{
			uiNumberStringLength = iAlignment;
		}
		pcDestPtr = pszStringBuffer + iAlignment;
		*pcDestPtr = '\0';
		pcDestPtr--;

		while(pcDestPtr >= pszStringBuffer)
		{
			if(pcSrcPtr >= szNumberString)
			{
				*pcDestPtr = *pcSrcPtr;
				pcSrcPtr--;
			}
			else
			{
				*pcDestPtr = cFillCharacter;
			}
			pcDestPtr--;
		}
	}
	else
	{
		iAlignment = -iAlignment;
		if(uiNumberStringLength > iAlignment)
		{
			iAlignment = uiNumberStringLength;
		}
		else
		{
			uiNumberStringLength = iAlignment;
		}
		pcDestPtr = pszStringBuffer;
		pcSrcPtr = szNumberString;
		while(iAlignment > 0)
		{
			if(*pcSrcPtr != '\0')
			{
				*pcDestPtr = *pcSrcPtr;
				pcSrcPtr++;
			}
			else
			{
				*pcDestPtr = cFillCharacter;
			}
			pcDestPtr++;
			iAlignment--;
		}
		*pcDestPtr = '\0';
	}
	return uiNumberStringLength;
}

/*****************************************************************************/
/** Function Name:	GUI_ConvertStringToUnsignedInteger						**/
/** Purpose:		Convert a string to number.								**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@szString:			Source number.										**/
/**	@pcEndPointer:		Convert end pointer output in string.				**/
/**	@uiBase:			Conversion base.									**/
/** Return:			Converted number.										**/
/** Notice:			None.													**/
/*****************************************************************************/
uint32_t GUI_Common_ConvertStringToUnsignedInteger(char* szString, char** pcEndPointer, uint16_t uiBase)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    uint32_t				uiResult;
	uint32_t				uiBitValue;
	char*					pcCurPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiResult = 				0;
	pcCurPtr =				szString;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcCurPtr)
	{
		// Skip header space.
		while(' ' == *pcCurPtr)
		{
			pcCurPtr++;
		}
		// Convert string.
		if(uiBase == 16)
		{
			if((*(pcCurPtr) == '0') && ((*(pcCurPtr+1) == 'x') || (*(pcCurPtr+1) == 'X')))
			{
				pcCurPtr += 2;
			}
			while(('\0' != (*pcCurPtr)) && (true == GUI_ISHEXDIGIT(*pcCurPtr)))
			{
				uiBitValue = GUI_ISDIGIT(*pcCurPtr)?((*pcCurPtr)-'0'):(10+GUI_TOUPPER(*pcCurPtr)-'A');
				uiResult = uiResult*uiBase + uiBitValue;
				pcCurPtr++;
			}
		}
		else if((uiBase == 8) || (uiBase == 10))
		{
			while(('\0' != (*pcCurPtr)) && (true == GUI_ISDIGIT(*pcCurPtr)))
			{
				uiBitValue =(*pcCurPtr)-'0';
				uiResult = uiResult*uiBase + uiBitValue;
				pcCurPtr++;
			}
		}
	}
	if(NULL != pcEndPointer)
	{
		*pcEndPointer = pcCurPtr;
	}
    return uiResult;
}

/*****************************************************************************/
/** Function Name:	GUI_ConvertStringToInteger								**/
/** Purpose:		Convert a string to number with sign.					**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@szString:			Source number.										**/
/**	@pcEndPointer:		Convert end pointer output in string.				**/
/**	@uiBase:			Conversion base.									**/
/** Return:			Converted number.										**/
/** Notice:			None.													**/
/*****************************************************************************/
int32_t GUI_Common_ConvertStringToInteger(char* szString, char** pcEndPointer, uint16_t uiBase)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
    int32_t					iResult;
    int32_t					iSign;
	char*					pcCurPtr;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	iResult = 				0;
	iSign =					1;
	pcCurPtr =				szString;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pcCurPtr)
	{
		// Skip header space.
		while(' ' == *pcCurPtr)
		{
			pcCurPtr++;
		}
		// Check sign.
		if((10 == uiBase) || (8 == uiBase))
		{
			if('+' == *pcCurPtr)
			{
				pcCurPtr++;
			}
			else if('-' == *pcCurPtr)
			{
				pcCurPtr++;
				iSign = -1;
			}
		}
		// Convert string without sign.
		iResult = GUI_Common_ConvertStringToUnsignedInteger(pcCurPtr, pcEndPointer, uiBase);
		if((iResult > 0) && (-1 == iSign))
		{
			iResult = -iResult;
		}
	}
	return iResult;
}

#ifdef _SIMPLE_GUI_ENABLE_ICONV_GB2312_
/*************************************************************************/
/** Function Name:	GUI_EncodeConvert									**/
/** Purpose:		Convert string encode.								**/
/** Resources:		None.												**/
/** Params:																**/
/**	@[in]encFrom:		Source encoder.									**/
/**	@[in]encTo:			Destination encoder.							**/
/**	@[in]szFilePath:	File path.										**/
/** Return:			String after convert.								**/
/*************************************************************************/
char* GUI_EncodeConvert(char *szSourceEncode, char *szDestinationEncode, char *szSource)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	char					*pszResultPtr;
	size_t					uiSourceLength, uiOutputBufferSize;
	size_t					uiEncoderResult;
	iconv_t					pIconv;
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
		uiSourceLength = strlen(szSource) + 1;
		uiOutputBufferSize = ENCODE_BUFFER_SIZE;
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

#ifdef _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_
/*************************************************************************/
/** Function Name:	GUI_Common_Allocate									**/
/** Purpose:		Allocate a memory block.							**/
/** Resources:		None.												**/
/** Params:																**/
/**	@[in]uiSize:		Allocated memory size.							**/
/** Return:			Allocated memory block started address, same as STD	**/
/**					malloc interface.									**/
/*************************************************************************/
void* GUI_Common_Allocate(uint32_t uiSize)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	void					*pAllocatedMemory;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pAllocatedMemory =		NULL;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
	pAllocatedMemory = malloc(uiSize);
#else
	// Add allocate memory function here;
#endif // _SIMPLE_GUI_ENABLE_SIMULATOR_
	return pAllocatedMemory;
}

/*************************************************************************/
/** Function Name:	GUI_Common_Free										**/
/** Purpose:		Free a memory block.								**/
/** Resources:		None.												**/
/** Params:																**/
/**	@[in]pFreePointer:	Free memory pointer 							**/
/** Return:			None.												**/
/*************************************************************************/
void GUI_Common_Free(void* pFreePointer)
{
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	free(pFreePointer);
}

#endif // _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_

/*************************************************************************/
/** Function Name:	GUI_Common_MemoryCopy								**/
/** Purpose:		Copy memory block to a new address.					**/
/** Resources:		None.												**/
/** Params:																**/
/**	@[in]pDest:			Memory address will copied to.					**/
/**	@[in]pSrc:			Memory data source.								**/
/**	@[in]size:			Copied data size(in byte).						**/
/** Return:			Same as STD memcpy function.						**/
/*************************************************************************/
void* GUI_Common_MemoryCopy(void* pDest, const void* pSrc, uint32_t size)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	void					*pCopiedMemory;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	pCopiedMemory =		NULL;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if((NULL != pDest) && (NULL != pSrc))
	{
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
	pCopiedMemory = memcpy(pDest, pSrc, size);
#else
	// Add RTC time process here;
#endif // _SIMPLE_GUI_ENABLE_SIMULATOR_
	}

	return pCopiedMemory;
}

uint32_t GUI_Common_StringLength(const char* szString)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	uint32_t				uiStringLength;

	/*----------------------------------*/
	/* Initialize						*/
	/*----------------------------------*/
	uiStringLength =		0;
	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != szString)
	{
#ifdef _SIMPLE_GUI_ENABLE_SIMULATOR_
	uiStringLength = strlen(szString);
#else
	// Add RTC time process here;
#endif // _SIMPLE_GUI_ENABLE_SIMULATOR_
	}

	return uiStringLength;
}

/*****************************************************************************/
/** Function Name:	GUI_Common_GetNowTime									**/
/** Purpose:		Get system now time.									**/
/** Resources:		System RTC interface.									**/
/** Params:																	**/
/**	@pstTime:			RTC time data structure pointer.					**/
/** Return:			None.													**/
/** Notice:			user need to override this function according to the	**/
/**					platform used.											**/
/*****************************************************************************/
void GUI_Common_GetNowTime(GUI_TIME* pstTime)
{
	/*----------------------------------*/
	/* Variable Declaration				*/
	/*----------------------------------*/
	time_t				rawtime;
	struct tm*			timeinfo;

	/*----------------------------------*/
	/* Process							*/
	/*----------------------------------*/
	if(NULL != pstTime)
	{
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
	}
}

/*****************************************************************************/
/** Function Name:	GUI_Common_RefreshScreen								**/
/** Purpose:		Refresh screen when needed.								**/
/** Resources:		None.													**/
/** Params:			None.													**/
/** Return:			None.													**/
/** Notice:			Need to be implemented, and call when needed in GUI API	**/
/**					optimization.											**/
/*****************************************************************************/
void GUI_Common_RefreshScreen(void)
{
	/* Add screen refresh function or process here. */
}

/*****************************************************************************/
/** Function Name:	GUI_Common_ReadFlashROM									**/
/** Purpose:		Read byte or byte array form internal flash or external	**/
/**					flash.													**/
/** Resources:		None.													**/
/** Params:																	**/
/**	@uiAddressHead:		Start address will be read.							**/
/**	@uiDataLength:		Number of byte will be read.						**/
/**	@pBuffer:			Read byte buffer.									**/
/** Return:			None.													**/
/** Notice:			This function need to override when use external flash	**/
/**					ROM data.												**/
/*****************************************************************************/
void GUI_Common_ReadFlashROM(uint32_t uiAddressHead, uint32_t uiDataLength, uint8_t* pBuffer)
{
	/* Add flash ROM IO process here. */
}

