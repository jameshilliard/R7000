/* *****************************************************************************

libcsc: String Subsystem

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

	$RCSfile: csc_string.c,v $
	$Revision: 1.3 $
	$Date: 2002/04/30 05:39:50 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_string">

NAME
	csc_string

DESCRIPTION
	String Subsystem

FUNCTIONS
	CSCstringOctal    - format an ASCII string to represent an octal number
	CSCstringBinary   - format an ASCII string to represent a binary number
	CSCstringBasename - strip directory from a filename
</SUBSYSTEM>

CHANGE LOG

	20apr02	drj	Small comments changes.

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
#   define	_BSD_SOURCE	1	/* 4.3+bsd subsystems            */
#   define	_POSIX_SOURCE	1	/* posix.1                       */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4           */
#else
#   define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4, and more */
#   ifndef	_REENTRANT
#      define	_REENTRANT		/* for glibc                     */
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
#include	<string.h>

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

/*  (None.)  */


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

/*  (None.)  */


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

/*  (None.)  */


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function
 **************************************************************************/

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCstringOctal
 ***************************************************************************

<SUBROUTINE NAME="CSCstringOctal">

NAME
        CSCstringOctal - format an ASCII string to represent an octal number

SYNOPSYS
        #include "libcsc.h"

        char*   CSCstringOctal (
                               char*   const bufPtr,
                               int32         item
                               );

RETURN VALUE
        CSCstringOctal() always returns bufPtr.

DESCRIPTION
        If `bufPtr' is not NULL, then the integer value of `item', in octal, is
        written to bufPtr with a preceding "0o" and is represented in 11 octets
        with the preceding two "0o" characters and terminating '\0' for a total
        of 14 characters.

EXAMPLE
        char*   buf[14]; // no smaller! and bigger is a waste.
        int32   i = 72;

        (void)CSCstringOctal (buf, i);
        //
        // Now: buf = "0o00000000110"

BUGS
        Beware buffer overflows; they are your responsibility.

SEE ALSO
        CSCstringBinary(3)
        CSCstringBasename(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC char*   (CSCstringOctal) (
                                char*   const bufPtr,
                                int32         item
                                )
   {
   char*   octalString;
   int32   mask;
   int     shift;

   ASSERT_RTN (bufPtr != NULL, "CSCstringOctal: NULL bufPtr", NULL);

   if (bufPtr != NULL)
      {
      octalString = &bufPtr[13];
      *octalString-- = '\0';
      for (mask = 0x07, shift = 0 ; mask != 0 ; mask = mask << 3, shift += 3)
         {
         *octalString-- = '0'+ ((item & mask) >> shift);
         }
      *octalString-- = 'o';
      *octalString-- = '0';
      }

   return (bufPtr);
   }


/**************************************************************************
 * Public Function CSCstringBinary
 **************************************************************************

<SUBROUTINE NAME="CSCstringBinary">

NAME
        CSCstringBinary - format an ASCII string to represent a binary number

SYNOPSYS
        #include "libcsc.h"

        char*   CSCstringBinary (
                                char*   const bufPtr,
                                int32         item
                                );

RETURN VALUE
        CSCstringBinary() always returns bufPtr.

DESCRIPTION
        If `bufPtr' is not NULL, then the integer value of `item', in binary, is
        written to bufPtr with a preceding "0b" and is represented in 32 bits
        with the preceding two "0b" characters and terminating '\0' for a total
        of 35 characters.

EXAMPLE
        char*   buf[35]; // no smaller! and bigger is a waste.
        int32   i = 72;

        (void)CSCstringBinary (buf, i);
        //
        // Now: buf = "0b0000000001001000"

BUGS
        Beware buffer overflows; they are your responsibility.

SEE ALSO
        CSCstringOctal(3)
        CSCstringBasename(3)
</SUBROUTINE>
 **************************************************************************/

PUBLIC char*   (CSCstringBinary) (
                                 char*   const bufPtr,
                                 int32         item
                                 )
   {
   char*   binaryString;
   int32   mask;

   ASSERT_RTN (bufPtr != NULL, "CSCstringBinary: NULL bufPtr", NULL);

   if (bufPtr != NULL)
      {
      binaryString = &bufPtr[34];
      *binaryString-- = '\0';
      for  ( mask = 0x01  ;  mask != 0  ;  mask = mask << 1 )
         {
         if ((item & mask) == mask)
            *binaryString-- = '1';
         else
            *binaryString-- = '0';
         }
      *binaryString-- = 'b';
      *binaryString-- = '0';
      }

   return (bufPtr);
   }


/**************************************************************************
 * Public Function CSCstringBasename
 **************************************************************************

<SUBROUTINE NAME="CSCstringBasename">

NAME
        CSCstringBasename - strip directory from a filename

SYNOPSYS
        #include "libcsc.h"

        char*   CSCstringBasename (
                                  char**   const pathPtrPtr
                                  );

RETURN VALUE
        CSCstringBinary() returns a pointer to the filename component of the
        pathname at *pathPtrPtr, if successful. Otherwise, CSCstringBinary()
        returns NULL, particularly if pathPtrPtr, or *pathPtrPtr is NULL.

DESCRIPTION
        CSCstringBinary() finds the first character after the last '/' character
        in the pathname pointed to by *pathPtrPtr. The last '/' character in the
        original string is replace will a NULL character.

        If the original pathname pointed to by *pathPtrPtr contains no '/'
        character, then CSCstringBinary() returns *pathPtrPtr, and sets
        *pathPtrPtr to be a pointer to the string "." (the current directory).

EXAMPLE
        char*   pathname = "just.a.file.name";
        file = CSCstringBasename (&pathname);

        // Now we have:
        //      file = "just.a.file.name"
        //      pathname = "."

        char*   pathname = "path/file";
        file = CSCstringBasename (&pathname);

        // Now we have:
        //      file = "file" ----v
        //      pathname = "path\0file"

BUGS
        If the original string has a '/' character, then that character gets
        set to '\0'; don't try this on components of argv and other strings
        that might not be writable.

SEE ALSO
        CSCstringOctal(3)
        CSCstringBinary(3)
</SUBROUTINE>
 **************************************************************************/

PUBLIC char*   (CSCstringBasename) (
                                   char**   const pathPtrPtr
                                   )
   {
   char*   namePtr = NULL;

   ASSERT_RTN (pathPtrPtr != NULL, "CSCstringBasename: NULL pathPtrPtr", NULL);
   ASSERT_RTN (*pathPtrPtr != NULL,"CSCstringBasename: NULL *pathPtrPtr",NULL);

   if (pathPtrPtr != NULL)
      {
      if (*pathPtrPtr != NULL)
         {
         namePtr = strrchr (*pathPtrPtr, '/');
         if (namePtr == NULL)
            {
            namePtr = *pathPtrPtr;
            *pathPtrPtr = ".";
            }
         else
            *namePtr++ = '\0';
         }
      }
   return (namePtr);
   }


/* End of file. */
