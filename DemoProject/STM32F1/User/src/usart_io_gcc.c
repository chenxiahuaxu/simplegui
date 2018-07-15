#include <stdio.h>
#include "Usart.h"
#include "usart_io.h"

#define BUFLEN          (127)

struct _USART_IO_BUFFER_
{
    int         iStartIdx;
    int         iEndIdx;
    char        arrcBuffer[BUFLEN+1];
}USART_BUFFER;

static inline int inc_ndx(int n) { return ((n + 1) % BUFLEN); }
static inline int dec_ndx(int n) { return (((n + BUFLEN) - 1) % BUFLEN); }

/*****************************************************************************/
/** Function Name:	_write							                        **/
/** Purpose:		Override gnu write function, called by libc stdio       **/
/**                 fwrite functions.                        		        **/
/** Params:																    **/
/**	@ifd            File ID.                                                **/
/**	@pcBuffer       Write buffer.   									    **/
/**	@iSize			Write buffer size.  								    **/
/** Return:			Number of written bytes.							    **/
/*****************************************************************************/
int _write(int ifd, char *pcBuffer, int iSize)
{
    int i = 0;
    char*   pcSendData;

    pcSendData = pcBuffer;
    for (i=0; i<iSize; i++)
    {
        USART_Putc(*pcSendData);
        pcSendData++;
    }
    return iSize;
}

/*****************************************************************************/
/** Function Name:	_write							                        **/
/** Purpose:		Override gnu write function, called by libc stdio       **/
/**                 fwrite functions.                        		        **/
/** Params:																    **/
/**	@ifd            File ID.                                                **/
/**	@pcBuffer       Read buffer.   									        **/
/**	@iSize			Read buffer size.  								        **/
/** Return:			Number of read bytes.							    **/
/*****************************************************************************/
int _read(int fd, char *ptr, int len)
{
    int my_len;
    /* Only work for STDOUT, STDIN, and STDERR */
    if (fd > 2)
    {
        return -1;
    }

    get_buffered_line();
    my_len = 0;

    while ((buf_len > 0) && (len > 0))
    {
        *ptr++ = *(buf +start_ndx);
        start_ndx = inc_ndx(start_ndx);
        my_len++;
        len--;
    }

    return my_len; /* return the length we got */
}


