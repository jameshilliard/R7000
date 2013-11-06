/* *****************************************************************************

libcsc: Debug Subsystem

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

	$RCSfile: xcsc_debug.c,v $
	$Revision: 1.3 $
	$Date: 2003/03/24 04:26:45 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

	This file provides the libcsc debuging functions. These functions are a
	few assertion catching functions, and wrapper functions for common libc
	functions which take pointers for arguments.

CHANGE LOG

	23mar03	drj	Added #include <stdlib.h>.

	24apr02	drj	Added newline at end of user_string in xcsc_assert_fail.

	20apr02	drj	Small comment changes.

	25jun01	drj	Converted to libcsc: renamed everything from rt to csc,
			reorganized everything.

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

#ifndef	DEBUG
#   define	DEBUG
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
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
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


/**************************************************************************
 * Public Function xcsc_assert_fail
 **************************************************************************/

void   xcsc_assert_fail (
                        const char*          file_name,
                              unsigned int   line_number,
                        const char*          assert_expression,
                        const char*          user_string,
                              int            fail_flag
                        )
   {
   /*
    * Make sure all the user's output is flushed before taking any debugging
    * steps.
    */
   (void)fflush (stdout);
   (void)fflush (stderr);

   /*
    * Display the assertion data on the standard error device. Flush this
    * output in case any further debugging steps do something bad.
    */
   (void)fprintf (
                 stderr,
                 "Assertion failed: FILE %s, LINE %u, EPRESSION `%s'.\n",
                 file_name, line_number, assert_expression
                 );
   if (user_string != (void*)0)
      {
      (void)fprintf (stderr, "\t-- %s\n", user_string);
      }
   (void)fflush (stderr);

   /*
    * Do something if the fail_flag is set, otherwise simply return.
    */
   if (fail_flag) abort();

   return;
   }


/**************************************************************************
 * Public Function xcsc_assert_errno
 **************************************************************************/

void   xcsc_assert_errno (
                         const char*          file_name,
                               unsigned int   line_number,
                                        int   error_number,
                                        int   fail_flag
                         )
   {
   /*
    * Make sure all the user's output is flushed before taking any debugging
    * steps.
    */
   (void)fflush (stdout);
   (void)fflush (stderr);

   /*
    * Display the assertion data on the standard error device. Flush this
    * output in case any further debugging steps do something bad.
    */
   (void)fprintf (
                 stderr,
                 "Assertion failed: FILE %s, LINE %u, errno %d.\n",
                 file_name, line_number, error_number
                 );
   errno = error_number;
   (void)perror ("\tperror");
   (void)fflush (stderr);

   /*
    * Do something if the fail_flag is set, otherwise simply return.
    */
   if (fail_flag) abort();

   return;
   }


/***************************************************************************
 * Public Function xcsc_memcpy
 ***************************************************************************/

void*   xcsc_memcpy (
                     const char*          file_name,
                           unsigned int   line_number,
                           void*          dst,
                     const void*          src,
                           size_t         n
                     )
   {
   if (dst == NULL)
      {
      fprintf (
              stderr,
              "memcpy: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   if (src == NULL)
      {
      fprintf (
              stderr,
              "memcpy: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (memcpy(dst,src,n));
   }


/***************************************************************************
 * Public Function xcsc_memset
 ***************************************************************************/

void*   xcsc_memset (
                     const char*          file_name,
                           unsigned int   line_number,
                           void*          dst,
                           int            c,
                           size_t         n
                     )
   {
   if (dst == NULL)
      {
      fprintf (
              stderr,
              "memset: caught NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (memset(dst,c,n));
   }


/***************************************************************************
 * Public Function xcsc_strcat
 ***************************************************************************/

char*   xcsc_strcat (
                    const char*          file_name,
                          unsigned int   line_number,
                          char*          dst,
                    const char*          src
                    )
   {
   if (dst == NULL)
      {
      fprintf (
              stderr,
              "strcat: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   if (src == NULL)
      {
      fprintf (
              stderr,
              "strcat: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (strcat(dst,src));
   }


/***************************************************************************
 * Public Function xcsc_strcmp
 ***************************************************************************/

int   xcsc_strcmp (
                  const char*          file_name,
                        unsigned int   line_number,
                  const char*          str1,
                  const char*          str2
                  )
   {
   if (str1 == NULL)
      {
      fprintf (
              stderr,
              "strcmp: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (-1);
      }
   if (str2 == NULL)
      {
      fprintf (
              stderr,
              "strcmp: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (1);
      }
   return (strcmp(str1,str2));
   }


/***************************************************************************
 * Public Function xcsc_strncmp
 ***************************************************************************/

int   xcsc_strncmp (
                   const char*          file_name,
                         unsigned int   line_number,
                   const char*          str1,
                   const char*          str2,
                         size_t         n
                   )
   {
   if (str1 == NULL)
      {
      fprintf (
              stderr,
              "strncmp: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (-1);
      }
   if (str2 == NULL)
      {
      fprintf (
              stderr,
              "strncmp: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (1);
      }
   return (strncmp(str1,str2,n));
   }


/***************************************************************************
 * Public Function xcsc_strcpy
 ***************************************************************************/

char*   xcsc_strcpy (
                    const char*          file_name,
                          unsigned int   line_number,
                          char*          dst,
                    const char*          src
                    )
   {
   if (dst == NULL)
      {
      fprintf (
              stderr,
              "strcpy: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   if (src == NULL)
      {
      fprintf (
              stderr,
              "strcpy: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (strcpy(dst,src));
   }


/***************************************************************************
 * Public Function xcsc_strncpy
 ***************************************************************************/

char*   xcsc_strncpy (
                     const char*          file_name,
                           unsigned int   line_number,
                           char*          dst,
                     const char*          src,
                           size_t         n
                     )
   {
   if (dst == NULL)
      {
      fprintf (
              stderr,
              "strncpy: 1st argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   if (src == NULL)
      {
      fprintf (
              stderr,
              "strncpy: 2nd argument is NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (strncpy(dst,src,n));
   }


/***************************************************************************
 * Public Function xcsc_strlen
 ***************************************************************************/

int   xcsc_strlen (
                  const char*          file_name,
                        unsigned int   line_number,
                  const char*          ptr
                  )
   {
   if (ptr == NULL)
      {
      fprintf (
              stderr,
              "strlen: caught NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (0);
      }
   return (strlen(ptr));
   }


/***************************************************************************
 * Public Function xcsc_strrchr
 ***************************************************************************/

char*   xcsc_strrchr (
                     const char*          file_name,
                           unsigned int   line_number,
                     const char*          ptr,
                           int            c
                     )
   {
   if (ptr == NULL)
      {
      fprintf (
              stderr,
              "strrchr: caught NULL pointer in FILE %s, LINE %u.\n",
              file_name, line_number
              );
      return (NULL);
      }
   return (strrchr(ptr,c));
   }


/* End of file. */
