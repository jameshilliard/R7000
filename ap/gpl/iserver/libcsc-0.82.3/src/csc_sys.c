/* *****************************************************************************

libcsc: System Subsystem

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

	$RCSfile: csc_sys.c,v $
	$Revision: 1.7 $
	$Date: 2002/05/11 04:56:05 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_sys">

NAME
	csc_sys

DESCRIPTION
	System Subsystem

FUNCTIONS
	CSCsysLimitsGet     - find some system limits
	CSCsysInstallSignal - fairly portable signal installer
        CSCsysUsleep        - sleep some microseconds
</SUBSYSTEM>

CHANGE LOG

	10may02	drj	Miscellaneous c-switching and header file changes.

	02may02	drj	Small changes to support Solaris.

	20apr02	drj	Small comments changes.

	13apr02	drj	Added CSCsysUsleep().

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
#include	<errno.h>
#include	<string.h>
#ifdef	DEBUG
#   include	<stdio.h>
#endif

/*
 * Posix Header Files
 */
#include	<unistd.h>
#include	<signal.h>  /* use POSIX signal API */

/*
 * 4.3+BSD Header Files
 */
#ifdef	SOLARIS                /* Use extensions because the use of POSIX */
#   define	__EXTENSIONS__ /* disables "struct timeval".              */
#endif
#include	<sys/time.h>
#ifdef	SOLARIS
#   undef	__EXTENSIONS__
#endif

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
 * Public Function rtusleep
 ***************************************************************************

<SUBROUTINE NAME="CSCsysUsleep">

NAME
        CSCsysUsleep - sleep some microseconds (rounded to kernel capability)

SYNOPSYS
        #include "libcsc.h"

        void   CSCsysUsleep (
                            const size_t   microseconds
                            );

RETURN VALUE
        CSCsysUsleep() has no return value.

DESCRIPTION
        The calling process/task will block for microseconds.  The actual time
        blocked will be descretized to the granularity implemented by the
        kernel.

SEE ALSO
        CSCsysInstallSignal(3)
        CSCsysLimitsGet(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCsysUsleep) (
                             const size_t   microseconds
                             )
   {
   struct timeval  timeout;
          fd_set   readfds;
          fd_set   writefds;
          fd_set   exceptfds;

   FD_ZERO (&readfds);
   FD_ZERO (&writefds);
   FD_ZERO (&exceptfds);

   timeout.tv_sec  = microseconds / 1000000u;
   timeout.tv_usec = microseconds % 1000000u;

   select (1, &readfds, &writefds, &exceptfds, &timeout);
   }


/***************************************************************************
 * Public Function CSCsysLimitsGet
 ***************************************************************************

<SUBROUTINE NAME="CSCsysLimitsGet">

NAME
        CSCsysLimitsGet - find some system limits

SYNOPSYS
        #include "libcsc.h"

        int   CSCsysLimitsGet (
                              int*    const fileOpenMaxPtr,
                              int*    const fileNameLengthPtr,
                              int*    const filePathLengthPtr
                              );

RETURN VALUE
        RTS_OK ........ successful

        CSC_BADARG .... fileOpenMaxPtr, or fileNameLengthPtr, or
                        filePathLengthPtr is NULL

        CSC_ERROR ..... error getting limit from system call

DESCRIPTION
        CSCsysLimitsGet() makes some system calls and writes the integer
        information to the addresses specified in the arguments.

        `fileOpenMaxPtr' must be a non-NULL pointer to an integer. If the call
        to CSCsysLimitsGet() is successful, the integer value will be the
        maximum number of open files allowed per process.

        `fileNameLenghtPtr' must be a non-NULL pointer to an integer. If the
        call to CSCsysLimitsGet() is successful, the integer value will be the
        maximum files name length allowed by the system.

        `filePathLengthPtr' must be a non-NULL pointer to an integer. If the
        call to CSCsysLimitsGet() is successful, the integer value will be the
        maximum path length allowed by the system.

SEE ALSO
        CSCsysInstallSignal(3)
        CSCsysUsleep(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsysLimitsGet) (
                               int*    const fileOpenMaxPtr,
                               int*    const fileNameLengthPtr,
                               int*    const filePathLengthPtr
                               )
   {
   int   errCode    = CSC_OK;
   int   configItem = 0;

   ASSERT_RTN (							\
              fileOpenMaxPtr    != NULL,			\
              "CSCsysLimitsGet: NULL fileOpenMaxPtr",		\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              fileNameLengthPtr != NULL,			\
              "CSCsysLimitsGet: NULL fileNameLengthPtr",	\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              filePathLengthPtr != NULL,			\
              "CSCsysLimitsGet: NULL filePathLengthPtr",	\
              CSC_BADARG					\
              );

#define	I_HAVE_A_BAD_ARGUMENT	((fileOpenMaxPtr == NULL) ||	\
				(fileNameLengthPtr == NULL) ||	\
				(filePathLengthPtr == NULL))
   if (I_HAVE_A_BAD_ARGUMENT) return (CSC_BADARG);
#undef	I_HAVE_A_BAD_ARGUMENT

   /*
    * Find the maximum number of open files allowed per process. Don't use
    * the constant OPEN_MAX from the POSIX.1 header file `limits.h' because,
    * as a portable constant, it is restrictive. Use the posix function
    * `sysconf(_SC_OPEN_MAX)' to dynamically find the system's true
    * capabilities. Don't use the constant _POSIX_OPEN_MAX because it seems to
    * be even more restrictive than the constant OPEN_MAX.
    */

   configItem = sysconf (_SC_OPEN_MAX);
   if (configItem > 0)
      {
      *fileOpenMaxPtr = configItem;
      }
   else
      {
      if (errno == 0)
         {
         CSCioWarnPrint (
                        "libcsc",
                        "CSCsysLimitsGet",
                        "guessing at maximum open file count (%d).\n",
                        255
                        );
         *fileOpenMaxPtr = 255;  /* Guess at it. */
         }
      else
         {
#ifdef	DEBUG
         perror ("error for sysconf(_SC_OPEN_MAX)");
#endif
         errCode = CSC_ERROR;
         }
      }

/*
 * Find the maximum file name length. Don't use the constant NAME_MAX from the
 * POSIX.1 header file `limits.h' because, as a portable constant, it is
 * restrictive. Use the posix function `sysconf(_PC_NAME_MAX)' to dynamically
 * find the system's true capabilities. Don't use the constant _POSIX_NAME_MAX
 * because it seems to be even more restrictive than the constant NAME_MAX.
 */

   configItem = pathconf ("/", _PC_NAME_MAX);
   if (configItem > 0)
      {
      *fileNameLengthPtr = configItem;
      }
   else
      {
      if (errno == 0)
         {
         CSCioWarnPrint (
                        "libcsc",
                        "CSCsysLimitsGet",
                        "guessing at maximum file name size (%d).\n",
                        255
                        );
         *fileNameLengthPtr = 255;  /* Guess at it. */
         }
      else
         {
#ifdef	DEBUG
         perror ("error for pathconf(\"/\",_PC_NAME_MAX)");
#endif
         errCode = CSC_ERROR;
         }
      }

/*
 * Find the maximum path length. Don't use the constant PATH_MAX from the
 * POSIX.1 header file `limits.h' because, as a portable constant, it is
 * restrictive. Use the posix function `pathconf(_PC_PATH_MAX)' to dynamically
 * find the system's true capabilities. Don't use the constant _POSIX_PATH_MAX
 * because it seems to be even more restrictive than the constant PATH_MAX.
 */

   configItem = pathconf ("/", _PC_PATH_MAX);
   if (configItem > 0)
      {
      *filePathLengthPtr = configItem;
      }
   else
      {
      if (errno == 0)
         {
         CSCioWarnPrint (
                        "libcsc",
                        "CSCsysLimitsGet",
                        "guessing at maximum path size (%d).\n",
                        255
                        );
         *filePathLengthPtr = 255;  /* Guess at it. */
         }
      else
         {
#ifdef	DEBUG
         perror ("error for pathconf(\"/\",_PC_PATH_MAX)");
#endif
         errCode = CSC_ERROR;
         }
      }

   return (errCode);
   }


/***************************************************************************
 * Public Function CSCsysInstallSignal
 ***************************************************************************

<SUBROUTINE NAME="CSCsysInstallSignal">

NAME
        CSCsysInstallSignal - fairly portable signal installer

SYNOPSYS
        #include "libcsc.h"

        CSCsigFnType   CSCsysInstallSignal (
                                           const int              signo,
                                           const CSCsigFnType     func,
                                           const CSCsigModeType   mode
                                           );

RETURN VALUE
        The return value from CSCsysInstallSignal() is a function pointer to a
        signal handler.

        If CSCsysInstallSignal() is NOT successful, then the return value is
        SIG_ERR cast as a signal handler function.

        If CSCsysInstallSignal() is successful, then the return value is a
        function pointer to the previously installed handler cast as a
        signal handler function; this might be NULL in the typical case that
        there was no previous signal handler.

DESCRIPTION
        CSCsysInstallSignal() is a reliable version of signal() using POSIX
        sigaction().

        `signo' is the signal number of the signal for which the signal handler
        function `func' is installed.

        `mode' is CSC_SIG_INTERRUPT or CSC_SIG_RESTART; it is used to control
        behavior, specifically for slow system calls:

                mode                    behavior
                ----                    --------
                CSC_SIG_INTERRUPT       slow system calls are interrupted

                CSC_SIG_RESTART         slow system calls are not interrupted

        An illustration of slow system call and signal interrupt is a program
        that creates children and has a signal handler for SIGCHLD. If this
        program blocks on something like an accept() on a TCP socket connection
        and a child process terminates, then the registered SIGCHLD signal
        handler runs; but, the process unblocks and returns from the accept()
        with no connection (errno should be EINTR). This can be avoided by
        using CSCsysInstallSignal() to install the SIGCHLD signal handler
        function `func' and specifying CSC_SIG_RESTART for `mode'.

SEE ALSO
        CSCsysLimitsGet(3)
        CSCsysUsleep(3)
</SUBROUTINE>

 ***************************************************************************

 If you want to set, or possibly change, the return value or type of the
 variable `installStat', then spend some time digging through the system
 header files. Start with `signal.h'. You can really mess up things if you
 don't completely understand SIG_ERR.

 ***************************************************************************/

PUBLIC CSCsigFnType   (CSCsysInstallSignal) (
                                            const int              signo,
                                            const CSCsigFnType     func,
                                            const CSCsigModeType   mode
                                            )
   {
          CSCsigFnType   installStat = SIG_ERR;
   struct sigaction      newAction;
   struct sigaction      oldAction;

   newAction.sa_handler = func;
   newAction.sa_flags   = 0;
   if (sigemptyset(&newAction.sa_mask) == 0)
      {
      switch (mode)
         {
         default:
            ASSERT_RTN (						\
                       CSC_FALSE,					\
                       "CSCsysInstallSignal: terrible excuse for a mode",\
                       SIG_ERR						\
                       );
            break;

         case CSC_SIG_INTERRUPT:
#ifdef SA_INTERRUPT
            newAction.sa_flags |= SA_INTERRUPT;  /* SunOS 4.1.x */
#endif
            break;

         case CSC_SIG_RESTART:
#ifdef SA_RESTART
            newAction.sa_flags |= SA_RESTART;    /* SVR4, 4.3+BSD */
#endif
            break;
         }
      if (sigaction(signo,&newAction,&oldAction) == 0)
         {
         installStat = oldAction.sa_handler;
         }
#ifdef	DEBUG
      else
         {
         perror ("sigaction() failed");
         CSCioErrorPrint (
                         "libcsc",
                         "CSCsysInstallSignal",
                         "can't install signal %d handler (errno %d).\n\t",
                         signo,
                         errno
                         );
         }
#endif
      }
#ifdef	DEBUG
   else
      {
      perror ("sigemptyset() failed");
      CSCioErrorPrint (
                      "libcsc",
                      "CSCsysInstallSignal",
                      "can't create empty signal mask (errno %d).\n\t",
                      errno
                      );
      }
#endif

   return (installStat);
   }


/* End of file. */
