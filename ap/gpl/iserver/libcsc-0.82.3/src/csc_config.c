/* *****************************************************************************

libcsc: Configuration and General Function Subsystem

	----------------------------------------------------------------

Copyright (c) 2001 Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: csc_config.c,v $
	$Revision: 1.3 $
	$Date: 2002/05/04 05:15:35 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_config">

NAME
	csc_config

DESCRIPTION
	Configuration and General Function Subsystem

FUNCTIONS
	CSCstatStr - get string describing libcsc function return value
	CSCcflags  - get string containing compiler command-line options
	CSCldflags - get string containing compiler command-line options
	CSClibs    - get string containing compiler command-line options
	CSCversion - get string containing the libcsc version
	CSCcredits - get string containing the libcsc credits
	CSCchkup   - check scalar data sizes assumed by libcsc
</SUBSYSTEM>

CHANGE LOG

	03may02	drj	Added 2002 to copyright in CSCcredits().

	29apr02	drj	Added entries to CSCstatStr().

	20apr02	drj	Small comment changes.

	25jun01	drj	File generation.

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
#include	<stdio.h>

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
#include	"csc_config.h"


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
/*      E x e c u t a b l e   C o d e   (Signal Handlers)                    */
/*                                                                           */
/* ************************************************************************* */


/**************************************************************************
 * Signal Handler Function Prototypes
 **************************************************************************/

/*  (None.)  */


/* ---------------------------------------------------------------------- */


/***************************************************************************
 * Signal Handler
 ***************************************************************************/

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
 * Public Function CSCstatStr
 ***************************************************************************

<SUBROUTINE NAME="CSCstatStr">

NAME
        CSCstatStr - get string describing libcsc function return value

SYNOPSYS
        #include "libcsc.h"

        const char*   CSCstatStr (int status);

DESCRIPTION
        Most libcsc functions return an integer status; this integer status is
        passed as the `status' argument to CSCstatStr().

        CSCstatStr() returns a pointer to a constant ASCII-Z string containing
        the text describing `status'.

SEE ALSO
	CSCcflags(3)
	CSCldflags(3)
	CSClibs(3)
	CSCversion(3)
	CSCcredits(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSCstatStr) (int status)
   {
   const char*   statStr = NULL;

   switch (status)
      {
      default:  statStr = NULL;  break;
      case CSC_ERROR:     statStr = "general error";          break;
      case CSC_OK:        statStr = "all ok";                 break;
      case CSC_BADARG:    statStr = "bad argument";           break;
      case CSC_CORRUPT:   statStr = "internal corruption";    break;
      case CSC_NOMEM:     statStr = "can't allocate memory";  break;
      case CSC_NOTFOUND:  statStr = "can't find item";        break;
      case CSC_NOSVC:     statStr = "no service available";   break;
      case CSC_NOPROT:    statStr = "no protocol available";  break;
      case CSC_NOSOCK:    statStr = "no socket available";    break;
      case CSC_NOBIND:    statStr = "can't bind something";   break;
      case CSC_NOLISTEN:  statStr = "listen() failed";        break;
      case CSC_DUPKEY:    statStr = "duplicate key";          break;
      }

   return (statStr);
   }


/***************************************************************************
 * Public Function CSCcflags
 ***************************************************************************

<SUBROUTINE NAME="CSCcflags">

NAME
        CSCcflags - get string containing compiler command-line options

SYNOPSYS
        #include "libcsc.h"

        const char*   CSCcflags (void);

DESCRIPTION
        CSCldflags() returns a pointer to a constant ASCII-Z string containing
        the compiler specfic (cc) command-line options.

SEE ALSO
	CSCstatStr(3)
	CSCldflags(3)
	CSClibs(3)
	CSCversion(3)
	CSCcredits(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSCcflags) (void)
   {
   return (CSC_CFLAGS);
   }


/***************************************************************************
 * Public Function CSCldflags
 ***************************************************************************

<SUBROUTINE NAME="CSCldflags">

NAME
        CSCldflags - get string containing compiler command-line options

SYNOPSYS
        #include "libcsc.h"

        const char*   CSCldflags (void);

DESCRIPTION
        CSCldflags() returns a pointer to a constant ASCII-Z string containing
        the linker (ld) command-line options.

SEE ALSO
	CSCstatStr(3)
	CSCcflags(3)
	CSClibs(3)
	CSCversion(3)
	CSCcredits(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSCldflags) (void)
   {
   return (CSC_LDFLAGS);
   }


/***************************************************************************
 * Public Function CSClibs
 ***************************************************************************

<SUBROUTINE NAME="CSClibs">

NAME
        CSClibs - get string containing compiler command-line options

SYNOPSYS
        #include "libcsc.h"

        const char*   CSClibs (void);

DESCRIPTION
        CSClibs() returns a pointer to a constant ASCII-Z string containing
        the the compiler command-line options that specify the libraries
        that libcsc is linked against.

SEE ALSO
	CSCstatStr(3)
	CSCcflags(3)
	CSCldflags(3)
	CSCversion(3)
	CSCcredits(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSClibs) (void)
   {
   return (CSC_LIBS);
   }


/***************************************************************************
 * Public Function CSCversion
 ***************************************************************************

<SUBROUTINE NAME="CSCversion">

NAME
        CSCversion - get string containing the libcsc version

SYNOPSYS
        #include "libcsc.h"

        const char*   CSCversion (void);

DESCRIPTION
        CSCversion() returns a pointer to a constant ASCII-Z string containing
        the libcsc version.

SEE ALSO
	CSCstatStr(3)
	CSCcflags(3)
	CSCldflags(3)
	CSClibs(3)
	CSCcredits(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSCversion) (void)
   {
   return ("libcsc "CSC_VERSION);
   }


/***************************************************************************
 * Public Function CSCcredits
 ***************************************************************************

<SUBROUTINE NAME="CSCcredits">

NAME
        CSCcredits - get string containing the libcsc credits

SYNOPSYS
        #include "libcsc.h"

        const char*   CSCcredits (void);

DESCRIPTION
        CSCcredits() returns a pointer to a constant ASCII-Z string containing
        the names of the major libcsc developers.

SEE ALSO
	CSCstatStr(3)
	CSCcflags(3)
	CSCldflags(3)
	CSClibs(3)
	CSCversion(3)
	CSCchkup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC const char*   (CSCcredits) (void)
   {
   return (
          "Copyright (c) 2001, 2002 "
          "Douglas R. Jerome <djerome@users.sourceforge.net>"
          );
   }


/***************************************************************************
 * Public Function CSCchkup
 ***************************************************************************

<SUBROUTINE NAME="CSCchkup">

NAME
        CSCchkup - check scalar data sizes assumed by libcsc

SYNOPSYS
        #include "libcsc.h"

        void   CSCchkup (void);

RETURN VALUE
        CSCchkup() returns no value.

DESCRIPTION
        CSCchkup is a diagnostic function that checks libcsc assumptions made
        about scalar data sizes e.g., sizeof(int) is 4.

SEE ALSO
	CSCstatStr(3)
	CSCcflags(3)
	CSCldflags(3)
	CSClibs(3)
	CSCversion(3)
	CSCcredits(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCchkup) (void)
   {
   int   terror = 0;
   if (sizeof(long) != 4)
      {
      printf ("***** ERROR scalar data type `long' is broken.\n");
      printf ("\t`sizeof(long)' is %d; it should be 4.\n", sizeof(uint32));
      terror = 1;
      }
   if (sizeof(uint32) != 4)
      {
      printf ("***** ERROR scalar data type `uint32' is broken.\n");
      printf ("\t`sizeof(uint32)' is %d; it should be 4.\n", sizeof(uint32));
      terror = 1;
      }
   if (sizeof(int32) != 4)
      {
      printf ("***** ERROR scalar data type `int32' is broken.\n");
      printf ("\t`sizeof(int32)' is %d; it should be 4.\n", sizeof(int32));
      terror = 1;
      }
   if (sizeof(uint16) != 2)
      {
      printf ("***** ERROR scalar data type `uint16' is broken.\n");
      printf ("\t`sizeof(uint16)' is %d; it should be 2.\n", sizeof(uint16));
      terror = 1;
      }
   if (sizeof(int16) != 2)
      {
      printf ("***** ERROR scalar data type `int16' is broken.\n");
      printf ("\t`sizeof(int16)' is %d; it should be 2.\n", sizeof(int16));
      terror = 1;
      }
   if (sizeof(uint8) != 1)
      {
      printf ("***** ERROR scalar data type `uint8' is broken.\n");
      printf ("\t`sizeof(uint8)' is %d; it should be 1.\n", sizeof(uint8));
      terror = 1;
      }
   if (sizeof(int8) != 1)
      {
      printf ("***** ERROR scalar data type `int8' is broken.\n");
      printf ("\t`sizeof(int8)' is %d; it should be 1.\n", sizeof(int8));
      terror = 1;
      }
   if (!terror) printf ("test: ok\n");
   }


/* End of file. */
