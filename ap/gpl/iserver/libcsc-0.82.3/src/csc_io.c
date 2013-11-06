/* *****************************************************************************

libcsc: I/O Subsystem

	----------------------------------------------------------------

Copyright (c) 1999, 2001, 2002 Douglas R. Jerome, Peoria, AZ USA

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU Library General Public License as
	published by the Free Software Foundation; either version 2 of the
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	----------------------------------------------------------------

FILE NAME

	$RCSfile: csc_io.c,v $
	$Revision: 1.3 $
	$Date: 2003/03/24 04:25:26 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_io">

NAME
	csc_io

DESCRIPTION
	I/O Subsystem

FUNCTIONS
	CSCioInfoPrint     - formatted write to stdout
	CSCioWarnPrint     - formatted write to stdout
	CSCioErrorPrint    - formatted write to stderr
	CSCioSoftwareError - print a parameterized software error message
	CSCioRead          - read a specific number of bytes
	CSCioReadLine      - read bytes that are terminated by a newline
	CSCioBufWrite      - write an ASCII buffer
	CSCioBufRead       - read an ASCII buffer
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added #include <string.h>.

	20apr02	drj	Small comment changes.

	25jun01	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	29apr99	drj	Rebaselined from librt version 0.3.1.

***************************************************************************** */


/* ************************************************************************* */
/*                                                                           */
/*      F e a t u r e   S w i t c h e s                                      */
/*                                                                           */
/* ************************************************************************* */


/*
 * Select these feature by moving them from the `if UNDEF' into the `else'
 * section.
 */
#ifdef	UNDEF
#   define	_BSD_SOURCE	1	/* 4.3+bsd subsystems           */
#   define	_POSIX_SOURCE	1	/* posix.1                      */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4          */
#else
#   define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4 and MORE */
#   ifndef	_REENTRANT
#      define	_REENTRANT		/* thread-safe for glibc        */
#   endif
#endif

/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

/*
 * OS Specific Header Files
 */
/*  (None.)  */

/*
 * Standard C (ANSI) Header Files
 */
#include	<stdarg.h>
#include	<stdio.h>
#include	<string.h>
#ifdef	DEBUG
#   include	<errno.h>
#endif

/*
 * Posix Header Files
 */
#include	<unistd.h>

/*
 * 4.3+BSD Header Files
 */
/*  (None.)  */

/*
 * Project Specific Header Files
 */
#include	"libcsc_debug.h"
#include	"libcsc.h"


/* ************************************************************************* */
/*                                                                           */
/*      M a n i f e s t   C o n s t a n t s                                  */
/*                                                                           */
/* ************************************************************************* */

#define	LIST_SIG	(0x4C495354)
#define	LINE_SIZE	(80)
#define	WRITE_SIZE	(256)


/* ************************************************************************* */
/*                                                                           */
/*      E x t e r n a l   R e f e r e n c e s                                */
/*                                                                           */
/* ************************************************************************* */

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      S c a l a r   D a t a   T y p e s                                    */
/*                                                                           */
/* ************************************************************************* */

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      N o n - S c a l a r   D a t a   S t r u c t u r e s                  */
/*                                                                           */
/* ************************************************************************* */

typedef struct   S_listType
   {
#ifdef	DEBUG
          long          sig_lo;
#endif
   struct S_listType*   next;
          size_t        count;
          char          data[ LINE_SIZE ];
#ifdef	DEBUG
          long          sig_hi;
#endif
   } S_listType;


/* ************************************************************************* */
/*                                                                           */
/*      P u b l i c   G l o b a l   V a r i a b l e s                        */
/*                                                                           */
/* ************************************************************************* */

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      P r i v a t e   G l o b a l   V a r i a b l e s                      */
/*                                                                           */
/* ************************************************************************* */

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (Locally Used Functions)             */
/*                                                                           */
/* ************************************************************************* */


/**************************************************************************
 * Private Function Prototypes
 **************************************************************************/

PRIVATE S_listType*     newList (void);
PRIVATE CSCstatusType   listAdd (S_listType** const, const char);
PRIVATE CSCstatusType   listDelete (S_listType** const);


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function newList
 **************************************************************************/

PRIVATE S_listType*   newList (void)
   {
   S_listType*   newListPtr;

   newListPtr = (S_listType*)CSC_MALLOC_FUNC (1, sizeof(S_listType));

   if (newListPtr != NULL)
      {
      newListPtr->next  = NULL;
      newListPtr->count = 0;
      memset (newListPtr->data, '\0', LINE_SIZE);
#ifdef	DEBUG
      newListPtr->sig_lo = LIST_SIG;
      newListPtr->sig_hi = LIST_SIG;
#endif
      }

   return (newListPtr);
   }


/**************************************************************************
 * Private Function listAdd
 **************************************************************************/

PRIVATE CSCstatusType   listAdd (S_listType** const listPtrPtr, const char ch)
   {
   CSCstatusType   addStatus  = CSC_OK;
   S_listType*     newListPtr = NULL;

   ASSERT_RTN (listPtrPtr != NULL, "listAdd: NULL listPtrPtr", CSC_BADARG);

   if (*listPtrPtr == NULL) *listPtrPtr = newList();

   if (*listPtrPtr != NULL)
      {
   ASSERT_RTN ((*listPtrPtr)->sig_lo == LIST_SIG, "listAdd: ouch", CSC_CORRUPT);
   ASSERT_RTN ((*listPtrPtr)->sig_hi == LIST_SIG, "listAdd: ouch", CSC_CORRUPT);
      if ((*listPtrPtr)->count == LINE_SIZE)
         {
         newListPtr = newList();
         if (newListPtr != NULL)
            {
   ASSERT_RTN (newListPtr->sig_lo == LIST_SIG, "listAdd: ouch", CSC_CORRUPT);
   ASSERT_RTN (newListPtr->sig_hi == LIST_SIG, "listAdd: ouch", CSC_CORRUPT);
            newListPtr->next = *listPtrPtr;
            *listPtrPtr = newListPtr;
            }
         else
            addStatus = CSC_ERROR;
         }
      if (addStatus != CSC_ERROR)
         {
         (*listPtrPtr)->data[ (*listPtrPtr)->count ] = ch;
         (*listPtrPtr)->count += 1;
         }
      }
   else
      addStatus = CSC_ERROR;

   return (addStatus);
   }


/**************************************************************************
 * Private Function listDelete
 **************************************************************************/

PRIVATE CSCstatusType   listDelete (S_listType** const listPtrPtr)
   {
   CSCstatusType   deleteStatus = CSC_OK;
   S_listType*     listPtr1     = NULL;
   S_listType*     listPtr2     = NULL;

   ASSERT_RTN (listPtrPtr != NULL,  "listDelete: NULL listPtrPtr",  CSC_BADARG);
   ASSERT_RTN (*listPtrPtr != NULL, "listDelete: NULL *listPtrPtr", CSC_BADARG);

   listPtr1 = *listPtrPtr;
   while (listPtr1 != NULL)
      {
   ASSERT_RTN(listPtr1->sig_lo==LIST_SIG,"listDelete: no LIST_SIG",CSC_CORRUPT);
   ASSERT_RTN(listPtr1->sig_hi==LIST_SIG,"listDelete: no LIST_SIG",CSC_CORRUPT);
      listPtr2 = listPtr1;
      listPtr1 = listPtr1->next;
      (void)CSC_FREE_FUNC (listPtr2);
      }
   *listPtrPtr = NULL;

   return (deleteStatus);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCioInfoPrint
 ***************************************************************************

<SUBROUTINE NAME="CSCioInfoPrint">

NAME
        CSCioInfoPrint - formatted write to stdout

SYNOPSYS
        #include "libcsc.h"

        void   CSCioInfoPrint (
                               const char*   cscPtr,
                               const char*   csuPtr,
                               const char*   fmtPtr,
                               );

RETURN VALUE
        CSCioInfoPrint() returns no value.

DESCRIPTION
        CSCioInfoPrint() is a front end, or wrapper, around fprintf() to
        standard output. Before printing the typical formatted string,
        CSCioInfoPrint() prints a string with `csc' and `csu':
        "<csc>-INFO-<csu>: ".

EXAMPLE
        stat = 55;
        (void)CSCioInfoPrint ("CSCio", "CSCioBufRead", "stat is %d\n", stat);

        // This will print to standard output:
        // "CSCio-INFO-CSCioBufRead: stat is 55\n"

SEE ALSO
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCioInfoPrint) (
                               const char*   cscPtr,
                               const char*   csuPtr,
                               const char*   fmtPtr,
                               ...
                               )
   {
   va_list   ap;

/*
   ASSERT_RTN (cscPtr != NULL, "CSCioInfoPrint: NULL cscPtr", CSC_BADARG);
   ASSERT_RTN (csuPtr != NULL, "CSCioInfoPrint: NULL csuPtr", CSC_BADARG);
   ASSERT_RTN (fmtPtr != NULL, "CSCioInfoPrint: NULL fmtPtr", CSC_BADARG);
*/

   (void)fprintf (stdout, "%s-INFO-%s: ", cscPtr, csuPtr);
   va_start (ap, fmtPtr);
   (void)vfprintf (stdout, fmtPtr, ap);
   va_end (ap);

   return;
   }


/***************************************************************************
 * Public Function CSCioWarnPrint
 ***************************************************************************

<SUBROUTINE NAME="CSCioWarnPrint">

NAME
        CSCioWarnPrint - formatted write to stdout

SYNOPSYS
        #include "libcsc.h"

        void   CSCioWarnPrint (
                               const char*   cscPtr,
                               const char*   csuPtr,
                               const char*   fmtPtr,
                               );

RETURN VALUE
        CSCioWarnPrint() returns no value.

DESCRIPTION
        CSCioWarnPrint() is a front end, or wrapper, around fprintf() to
        standard output. Before printing the typical formatted string,
        CSCioWarnPrint() prints a string with `csc' and `csu':
        "<csc>-WARN-<csu>: ".

EXAMPLE
        stat = 55;
        (void)CSCioWarnPrint ("CSCio", "CSCioBufRead", "stat is %d\n", stat);

        // This will print to standard output:
        // "CSCio-WARN-CSCioBufRead: stat is 55\n"

SEE ALSO
        CSCioInfoPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCioWarnPrint) (
                               const char*   cscPtr,
                               const char*   csuPtr,
                               const char*   fmtPtr,
                               ...
                               )
   {
   va_list   ap;

/*
   ASSERT_RTN (cscPtr != NULL, "CSCioWarnPrint: NULL cscPtr", CSC_BADARG);
   ASSERT_RTN (csuPtr != NULL, "CSCioWarnPrint: NULL csuPtr", CSC_BADARG);
   ASSERT_RTN (fmtPtr != NULL, "CSCioWarnPrint: NULL fmtPtr", CSC_BADARG);
*/

   (void)fprintf (stdout, "%s-WARN-%s: ", cscPtr, csuPtr);
   va_start (ap, fmtPtr);
   (void)vfprintf (stdout, fmtPtr, ap);
   va_end (ap);

   return;
   }


/***************************************************************************
 * Public Function CSCioErrorPrint
 ***************************************************************************

<SUBROUTINE NAME="CSCioErrorPrint">

NAME
        CSCioErrorPrint - formatted write to stderr

SYNOPSYS
        #include "libcsc.h"

        void   CSCioErrorPrint (
                               const char*   cscPtr,
                               const char*   csuPtr,
                               const char*   fmtPtr,
                               );

RETURN VALUE
        CSCioErrorPrint() returns no value.

DESCRIPTION
        CSCioErrorPrint() is a front end, or wrapper, around fprintf() to
        standard error. Before printing the typical formatted string,
        CSCioErrorPrint() prints a string with `csc' and `csu':
        "<csc>-ERROR-<csu>: ".

EXAMPLE
        stat = 55;
        (void)CSCioErrorPrint ("CSCio", "CSCioBufRead", "bad stat %d\n", stat);

        // This will print to standard error:
        // "CSCio-ERROR-CSCioBufRead: bad stat 55\n"

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCioErrorPrint) (
                                const char*   cscPtr,
                                const char*   csuPtr,
                                const char*   fmtPtr,
                                ...
                                )
   {
   va_list   ap;

/*
   ASSERT_RTN (cscPtr != NULL, "CSCioErrorPrint: NULL cscPtr", CSC_BADARG);
   ASSERT_RTN (csuPtr != NULL, "CSCioErrorPrint: NULL csuPtr", CSC_BADARG);
   ASSERT_RTN (fmtPtr != NULL, "CSCioErrorPrint: NULL fmtPtr", CSC_BADARG);
*/

   (void)fprintf (stderr, "%s-ERROR-%s: ", cscPtr, csuPtr);
   va_start (ap, fmtPtr);
   (void)vfprintf (stderr, fmtPtr, ap);
   va_end (ap);

   return;
   }


/**************************************************************************
 * Public Function CSCioSoftwareError
 **************************************************************************

<SUBROUTINE NAME="CSCioSoftwareError">

NAME
        CSCioSoftwareError - print a parameterized software error message

SYNOPSYS
        #include "libcsc.h"

        void   CSCioSoftwareError (
                                  const char*   identPtr,
                                  const char*   csciPtr,
                                  const char*   fmtPtr,
                                  ...
                                  );

RETURN VALUE
        CSCioSoftwareError() returns no value.

DESCRIPTION
        CSCioSoftwareError() is a utility function that prints a software error
        message with `csciPtr' being the name of the program, `identPtr' being a
        version description. `fmtPtr' is a printf() style format string, the
        last arguments, if any, are format items.

        The message will look something like this:

<csci>-ERROR-softwareError: INTERNAL SOFTWARE ERROR.
<fmt+items>
        -- Please report this to the maintainer(s) of <csci>.
        -- Please include the command-line invocation of, the conditions under
        -- which this error happened, and the following version description:
        <ident>

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC void   (CSCioSoftwareError) (
                                   const char*   identPtr,
                                   const char*   csciPtr,
                                   const char*   fmtPtr,
                                   ...
                                   )
   {
   va_list   ap;

/*
   ASSERT_RTN (identPtr != NULL, "CSCioSoftwareError: NULL cscPtr", CSC_BADARG);
   ASSERT_RTN (csciPtr != NULL,  "CSCioSoftwareError: NULL csuPtr", CSC_BADARG);
   ASSERT_RTN (fmtPtr != NULL,   "CSCioSoftwareError: NULL fmtPtr", CSC_BADARG);
*/

   ASSERT (identPtr != NULL);
   ASSERT (csciPtr != NULL);
   ASSERT (fmtPtr != NULL);

   (void)fprintf (stderr, "\n");
   (void)CSCioErrorPrint (
                         csciPtr,
                         "softwareError",
                         "INTERNAL SOFTWARE ERROR.\n"
                         );

   va_start (ap, fmtPtr);
   (void)vfprintf (stderr, fmtPtr, ap);
   va_end (ap);

   (void)fprintf (
                 stderr,
"\t-- Please report this error to the mantainer(s) of %s.\n"
"\t-- Please include the command-line invocation, the conditions under\n"
"\t-- which this error happened, and the following version description:\n"
"\t%s\n",
                 csciPtr, identPtr
                 );
   (void)fprintf (stderr, "\n");
   }


/**************************************************************************
 * Public Function CSCioRead
 **************************************************************************

<SUBROUTINE NAME="CSCioRead">

NAME
        CSCioRead - read a specific number of bytes

SYNOPSYS
        #include "libcsc.h"

        int   CSCioRead (
                        int            fd,
                        char*    const bufPtr,
                        size_t         size
                        );

RETURN VALUE
        CSCioRead() returns the number of bytes read. On read error, zero is
        returned. if `fd' is zero, `bufPtr' is NULL, or `size' is zero, then
        -1 is returned.

DESCRIPTION
        CSCioRead() reads `size' bytes from `fd' into `bufPtr' by calling the
        read() system call in a loop until `size' bytes is read, or until a
        read error.

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCioRead) (
                         int            fd,
                         char*    const bufPtr,
                         size_t         size
                         )
   {
   int   bytesRead = 0;
   int   readCount = (int)size;
   int   count     = 0;

   ASSERT_RTN (fd >= 0,        "CSCioRead: no fd",       -1);
   ASSERT_RTN (bufPtr != NULL, "CSCioRead: NULL bufPtr", -1);
   ASSERT_RTN (size > 0,       "CSCioRead: zero size",   -1);

/*
   if ((fd <= 0) || (bufPtr == NULL) || (size == 0)) return (-1);
*/

   do
      {
      count = read (fd, &bufPtr[ bytesRead ], readCount);
      if (count > 0)
         {
         readCount -= count;
         bytesRead += count;
         }
      else
         {
         bytesRead = count;
         }
      }
   while ((count > 0) && (bytesRead < (int)size));

   return (bytesRead);
   }


/**************************************************************************
 * Public Function CSCioReadLine
 **************************************************************************

<SUBROUTINE NAME="CSCioReadLine">

NAME
        CSCioReadLine - read bytes that are terminated by a newline

SYNOPSYS
        #include "libcsc.h"

        int   CSCioReadLine (
                            int                    fd,
                            char**           const bufPtrPtr,
                            CSCmemListType   const memList,
                            int                    tagData
                            );

RETURN VALUE
        CSCioReadLine(), when successful, returns the number of bytes read
        from `fd'.

        CSCioReadLine() indicates error by returning -1. Errors are: `fd' is
        zero or `bufPtrPtr' is NULL, read error, or memory allocation error.

DESCRIPTION
        CSCioReadLine() reads bytes from `fd' until a newline character is
        encountered. The bytes are stored in a single dynamically allocated
        buffer; the pointer to the buffer is returned to the caller by writing
        the pointer to *bufPtrPtr.

        NOTE    Since the buffer is dynamically allocated with CSCmemAlloc(),
                the caller must free *bufPtrPtr with CSCmemFree() or
                CSCmemListFree() to avoid a memory leak.

        The terminating newline (maybe just LF or maybe CRLF) is in the returned
        data.

        `memList' and `tag' are as use with CSCmemAlloc().

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioBufWrite(3)
        CSCioBufRead(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCioReadLine) (
                             int                    fd,
                             char**           const bufPtrPtr,
                             CSCmemListType   const memList,
                             int                    tagData
                             )
   {
   char          ch             = '\0';
   int           count          = 0;
   int           inputCount     = 0;
   S_listType*   internalBuffer = NULL;

   ASSERT_RTN (fd >= 0,           "CSCioReadLine: no fd",          -1);
   ASSERT_RTN (bufPtrPtr != NULL, "CSCioReadLine: NULL bufPtrPtr", -1);
   ASSERT_RTN (memList != NULL,   "CSCioReadLine: NULL memList",   -1);

/*
   if ((fd <= 0) || (bufPtrPtr == NULL)) return (-1);
*/
   if (memList == NULL) return (-1);

   do
      {
      count = read (fd, &ch, 1);
      if (count == 1)
         {
         if (listAdd(&internalBuffer,ch) == CSC_OK)
            {
            ++inputCount;
            }
         else
            {
            (void)listDelete (&internalBuffer);
            count = 0;
            inputCount = -1;
            }
         }
      }
   while ((count == 1) && (ch != '\n'));

   if (inputCount > 0)
      {
      *bufPtrPtr = NULL;
      (void)CSCmemAlloc (
                        memList,
                        (void**)bufPtrPtr,
                        sizeof(char),
                        inputCount+1,
                        tagData
                        );
      if (*bufPtrPtr != NULL)
         {
         char*         cpPtr          = NULL;
         S_listType*   oldInternalBuf = NULL;
         cpPtr = &((*bufPtrPtr)[ inputCount ]);
         *cpPtr = '\0';
         while (internalBuffer != NULL)
            {
            cpPtr -= internalBuffer->count;
            (void)memcpy (cpPtr, internalBuffer->data, internalBuffer->count);
            oldInternalBuf = internalBuffer;
            internalBuffer = internalBuffer->next;
            (void)CSC_FREE_FUNC (oldInternalBuf);
            }
         }
      else
         {
         inputCount = -1;
         (void)listDelete (&internalBuffer);
         }
      }

   return (inputCount);
   }


/**************************************************************************
 * Public Function CSCioBufWrite
 **************************************************************************

<SUBROUTINE NAME="CSCioBufWrite">

NAME
        CSCioBufWrite - write an ASCII buffer

SYNOPSYS
        #include "libcsc.h"

        int   CSCioBufWrite (
                                  int      fd,
                            const void*    dataPtr,
                                  size_t   size
                            );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... fd is zero, dataPtr is NULL, or size is zero

        CSC_ERROR .... write error

DESCRIPTION
        CSCioBufWrite() converts the size_t value of `size' to an ASCII string
        and writes this to `fd', followed by a newline. Then, `size' bytes,
        starting at `dataPtr', are each converted to two ASCII characters (a
        standard "bin to hex" conversion) and written to `fd', followed by a
        newline.

        Use CSCioBufWrite() and CSCioBufRead() to store and retrieve arbitrary
        binary data in portable ASCII format.

EXAMPLE
        int   data = 0x12FACE55;

        stat = rtsIObufWrite (fd, &data, sizeof(int));

        // Written to fd (no NULL character sent): "4\n12FACE55\n"

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufRead(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCioBufWrite) (
                                   int      fd,
                             const void*    dataPtr,
                                   size_t   size
                             )
   {
   int      ioBufWriteStat = CSC_OK;
   int      index          = 0;
   int      jndex          = 0;
   size_t   count;
   char     outBuf[ 10 ];

   ASSERT_RTN (fd >= 0,         "CSCioBufWrite: no fd",        CSC_BADARG);
   ASSERT_RTN (dataPtr != NULL, "CSCioBufWrite: NULL dataPtr", CSC_BADARG);
   ASSERT_RTN (size > 0,        "CSCioBufWrite: zero size",    CSC_BADARG);

/*
   if ((fd <= 0) || (dataPtr == NULL) || (size = 0)) return (CSC_BADARG);
*/

   (void)sprintf (outBuf, "%d\n", (int)size);
   count = write (fd, outBuf, strlen(outBuf));
   ASSERT_RTN (					\
              count == strlen(outBuf),		\
              "CSCioBufWrite: write failed",	\
              CSC_ERROR				\
              );

   if (count == strlen(outBuf))
      {
      for (index = 0 ; index < (int)size ; ++index)
         {
         (void)sprintf (outBuf, "%02X", ((char*)dataPtr)[ index ]);
         count = write (fd, outBuf, 2);
         if (count == 2)
            {
            if (++jndex == 40)
               {
               count = write (fd, "\n", 1);
               if (count == 1)
                  jndex = 0;
               else
                  {
                  ioBufWriteStat = CSC_ERROR;
                  index = size-1;
                  }
               }
            }
         else
            {
            ioBufWriteStat = CSC_ERROR;
            index = size-1;
            }
         }
      }
   else
      {
      ioBufWriteStat = CSC_ERROR;
      }

   if (jndex != 0)
      {
      count = write (fd, "\n", 1);
      if (count != 1)
         {
         ioBufWriteStat = CSC_ERROR;
         }
      }

   return (ioBufWriteStat);
   }


/**************************************************************************
 * Public Function CSCioBufRead
 **************************************************************************

<SUBROUTINE NAME="CSCioBufRead">

NAME
        CSCioBufRead - read an ASCII buffer

SYNOPSYS
        #include "libcsc.h"

        int   CSCioBufRead (
                           int                    fd,
                           void**           const dataPtrPtr,
                           size_t*          const sizePtr,
                           CSCmemListType   const memList,
                           int                    tagData
                           );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... fd is zero, or dataPtrPtr or sizePtr is NULL

        CSC_ERROR .... read error; no bytes to read, or maybe an odd count of
                       bytes where there was an expected even count

        CSC_NOMEM .... can't allocate memory for the read buffer

DESCRIPTION
        CSCioBufRead() reads from `fd' an ASCII representation of arbitrary
        bytes that are formatted as created by CSCioBufWrite(). The ASCII data
        is converted to binary data and stored in a single dynamically allocated
        memory block.

        The void pointer that is pointed to by `dataPtrPtr' is updated with the
        pointer to newly allocated memory containing the bytes read from fd.

        NOTE    Since the buffer is dynamically allocated with CSCmemAlloc(),
                the caller must free *bufPtrPtr with CSCmemFree() or
                CSCmemListFree() to avoid a memory leak.

        The size_t pointed to by `sizePtr' is updated to contain the number of
        bytes in the newly allocated buffer.

        Use CSCioBufWrite() and CSCioBufRead() to store and retrieve arbitrary
        binary data in portable ASCII format.

        `memList' and `tag' are as use with CSCmemAlloc().

EXAMPLE
        void*    data;
        size_t   size;

        // Read from fd (no NULL character received): "4\n12FACE55\n"

        stat = rtsIObufRead (fd, &data, &size);

        // Now: *data = 0x12, 0xFA, 0xCE, 0x55
        //      size  = 4;

SEE ALSO
        CSCioInfoPrint(3)
        CSCioWarnPrint(3)
        CSCioErrorPrint(3)
        CSCioSoftwareError(3)
        CSCioRead(3)
        CSCioReadLine(3)
        CSCioBufWrite(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCioBufRead) (
                            int                    fd,
                            void**           const dataPtrPtr,
                            size_t*          const sizePtr,
                            CSCmemListType   const memList,
                            int                    tagData
                            )
   {
   int      ioBufReadStat = CSC_OK;
   int      readCount     = 0;
   int      index         = 0;
   int      val           = 0;
   char*    bufPtr        = NULL;
   char*    bufPtr2       = NULL;
   char*    linePtr       = NULL;
   size_t   bufSize       = 0;
   size_t   bufSize2      = 0;

   ASSERT_RTN (fd >= 0,            "CSCioBufRead: no fd",           CSC_BADARG);
   ASSERT_RTN (dataPtrPtr != NULL, "CSCioBufRead: NULL dataPtrPtr", CSC_BADARG);
   ASSERT_RTN (sizePtr != NULL,    "CSCioBufRead: NULL sizePtr",    CSC_BADARG);
   ASSERT_RTN (memList != NULL,    "CSCioBufRead: NULL memList",    CSC_BADARG);

/*
   if ((fd <= 0) || (dataPtrPtr == NULL) || (sizePtr == NULL))
      {
      return (CSC_BADARG);
      }
*/
   if (memList == NULL) return (-1);

   readCount = CSCioReadLine (fd, &bufPtr, memList, tagData);
   bufSize = (size_t)atoi(bufPtr);
   (void)CSC_FREE_FUNC (bufPtr);

   ASSERT_RTN (bufSize > 0, "CSCioBufRead: no calculated bufSize", CSC_ERROR);

   (void)CSCmemAlloc (memList, (void**)&bufPtr, sizeof(char), bufSize, tagData);
   bufPtr2  = bufPtr;
   bufSize2 = bufSize;

   if (bufPtr != NULL)
      {
      while (bufSize2 > 0)
         {
         readCount = CSCioReadLine (fd, &linePtr, memList, tagData);
         index = 0;
         while ((readCount > 1) && (bufSize2 > 0))
            {
            (void)sscanf (&linePtr[ index++ ], "%02X", &val);
            *bufPtr2++ = (char)val;
            readCount -= 2;
            --bufSize2;
            }
         (void)CSC_FREE_FUNC (linePtr);
         }
      if ((bufSize2 == 0) && (readCount == 0))
         {
         *dataPtrPtr = bufPtr;
         *sizePtr = bufSize;
         }
      else
         {
         ioBufReadStat = CSC_ERROR;
         }
      }
   else
      {
      ioBufReadStat = CSC_ERROR;
      }

   return (ioBufReadStat);
   }


/* End of file. */
