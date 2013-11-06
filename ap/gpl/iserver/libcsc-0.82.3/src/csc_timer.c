/* *****************************************************************************

libcsc: Timer Subsystem

	----------------------------------------------------------------

Copyright (c) 2001, 2002 Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: csc_timer.c,v $
	$Revision: 1.7 $
	$Date: 2003/03/24 04:26:37 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_timer">

NAME
	csc_timer

DESCRIPTION
	Timer Subsystem

FUNCTIONS
	CSCtimerInit  - create a timer
	CSCtimerDone  - delete a timer
	CSCtimerClear - clear marks in timer
	CSCtimerMark  - create a mark in a timer
	CSCtimerStat  - create and get current timer's time
	CSCtimerStat  - get current timer's time
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added #include <string.h>.

	10may02	drj	Miscellaneous c-switching and header file changes.

	02may02	drj	Small changes to support Solaris.

	20apr02	drj	Small comments changes.

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
#   define	_POSIX_SOURCE	1	/* posix.1                       */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4           */
#else
#   define	_BSD_SOURCE	1	/* 4.3+bsd subsystems            */
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
#include	<stdlib.h>
#include	<string.h>

/*
 * Posix Header Files
 */
#include	<unistd.h>

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

#define	TIMER_SIG	(0x54494D45)


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

typedef struct S_timerType
   {
#ifdef	DEBUG
          long      sig_lo;
#endif
   struct timeval   mark;
   struct timeval   diffMark;
          double    diffStat;
#ifdef	DEBUG
          long      sig_hi;
#endif
   } S_timerType;


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
 * Public Function CSCtimerInit
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerInit">

NAME
        CSCtimerInit - create a timer

SYNOPSYS
        #include "libcsc.h"

        CSCtimerType   CSCtimerInit (void)

RETURN VALUE
        CSCtimerInit() returns a new timer.

DESCRIPTION
        CSCtimerInit() creates timer for the caller's subsequent calls to
        CSCtimerMark() and CSCtimerDiff().

SEE ALSO
        PRtimerDone(3)
        PRtimerClear(3)
        PRtimerMark(3)
        PRtimerDiff(3)
        PRtimerStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCtimerType   (CSCtimerInit) (void)
   {
   S_timerType*   timer = NULL;

   timer = (S_timerType*)CSC_MALLOC_FUNC (1, sizeof(S_timerType));
   if (timer != NULL)
      {
      timer->mark.tv_sec      = 0;
      timer->mark.tv_usec     = 0;
      timer->diffMark.tv_sec  = 0;
      timer->diffMark.tv_usec = 0;
      timer->diffStat         = 0.0;
#ifdef	DEBUG
      timer->sig_lo = TIMER_SIG;
      timer->sig_hi = TIMER_SIG;
#endif
      }

   return (timer);
   }


/***************************************************************************
 * Public Function CSCtimerDone
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerDone">

NAME
        CSCtimerDone - delete a timer

SYNOPSYS
        #include "libcsc.h"

        int   CSCtimerDone (
                           CSCtimerType   const timer
                           );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... timer is NULL

        CSC_CORRUPT ... corruption is detected in timer
                        and CSCtimerDone() is compiled with DEBUG

DESCRIPTION
        CSCtimerDone() completely removes `timer'.

        Do not try to use `timer' again. At least until it is reset by assigning
        it the results of a subsequent call to PRtimerInit();

SEE ALSO
        PRtimerInit(3)
        PRtimerClear(3)
        PRtimerMark(3)
        PRtimerDiff(3)
        PRtimerStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCtimerDone) (CSCtimerType const timer)
   {
          int            freeStat = CSC_OK;
   struct S_timerType*   t        = timer;

   ASSERT_RTN (timer != NULL, "CSCtimerDone: NULL timer", CSC_BADARG);

   ASSERT_RTN (					\
              t->sig_lo == TIMER_SIG,		\
              "CSCtimerDone: timer blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              t->sig_hi == TIMER_SIG,		\
              "CSCtimerDone: timer blows",	\
              CSC_CORRUPT			\
              );

   if (t == NULL) return (CSC_BADARG);
   (void)memset (t, 0xFF, sizeof(S_timerType));
   (void)CSC_FREE_FUNC (t);

   return (freeStat);
   }


/***************************************************************************
 * Public Function CSCtimerClear
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerClear">

NAME
        CSCtimerClear - clear marks in timer

SYNOPSYS
        #include "libcsc.h"

        int   CSCtimerClear (
                            CSCtimerType   const timer
                            );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... timer is NULL

        CSC_CORRUPT ... corruption is detected in timer
                        and CSCtimerClear() is compiled with DEBUG

DESCRIPTION
        CSCtimerClear() clears marks (and all the stats) in `timer'.

SEE ALSO
        PRtimerInit(3)
        PRtimerDone(3)
        PRtimerMark(3)
        PRtimerDiff(3)
        PRtimerStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCtimerClear) (CSCtimerType const timer)
   {
          int            clearStat = CSC_OK;
   struct S_timerType*   t         = timer;

   ASSERT_RTN (timer != NULL, "CSCtimerClear: NULL timer", CSC_BADARG);

   ASSERT_RTN (					\
              t->sig_lo == TIMER_SIG,		\
              "CSCtimerClear: timer blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              t->sig_hi == TIMER_SIG,		\
              "CSCtimerClear: timer blows",	\
              CSC_CORRUPT			\
              );

   if (t == NULL) return (CSC_BADARG);
   t->mark.tv_sec      = 0;
   t->mark.tv_usec     = 0;
   t->diffMark.tv_sec  = 0;
   t->diffMark.tv_usec = 0;
   t->diffStat         = 0.0;

   return (clearStat);
   }


/***************************************************************************
 * Public Function CSCtimerMark
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerMark">

NAME
        CSCtimerMark - create a mark in a timer

SYNOPSYS
        #include "libcsc.h"

        int   CSCtimerMark (
                           CSCtimerType   const timer
                           );

RETURN VALUE
        CSC_OK ........ successful

        CSC_ERROR ..... an error occurs trying to get system time

        CSC_BADARG .... timer is NULL

        CSC_CORRUPT ... corruption is detected in timer
                        and CSCtimerMark() is compiled with DEBUG

DESCRIPTION
        CSCtimerMark() creates a mark in `timer' for the caller's subsequent
        call to CSCtimerDiff() with `timer'.

        Given the some `timer', CSCtimerDiff() will create the time value of
        the number of seconds that passed since the call to this function
        CSCtimerMark().

SEE ALSO
        PRtimerInit(3)
        PRtimerDone(3)
        PRtimerClear(3)
        PRtimerDiff(3)
        PRtimerStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCtimerMark) (CSCtimerType const timer)
   {
          int            markStat = CSC_OK;
   struct S_timerType*   t        = timer;

   ASSERT_RTN (timer != NULL, "CSCtimerMark: NULL timer", CSC_BADARG);

   ASSERT_RTN (					\
              t->sig_lo == TIMER_SIG,		\
              "CSCtimerMark: timer blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              t->sig_hi == TIMER_SIG,		\
              "CSCtimerMark: timer blows",	\
              CSC_CORRUPT			\
              );

   if (t == NULL) return (CSC_BADARG);
   markStat = gettimeofday (&t->mark, NULL);
   if (markStat != 0) markStat = CSC_ERROR;

   return (markStat);
   }


/***************************************************************************
 * Public Function CSCtimerDiff
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerDiff">

NAME
        CSCtimerStat - create and get current timer's time

SYNOPSYS
        #include "libcsc.h"

        int   CSCtimerDiff (
                           CSCtimerType   const timer,
                           double*        const diffPtr
                           );

RETURN VALUE
        CSC_OK ........ successful

        CSC_ERROR ..... an error occurs trying to get system time or there was
                        no previous call to PRtimerMark() with the timer

        CSC_BADARG .... timer is NULL

        CSC_CORRUPT ... corruption is detected in timer
                        and CSCtimerDiff() is compiled with DEBUG

DESCRIPTION
        CSCtimerDiff() creates a time from the caller's previous call to
        CSCtimerMark() with `timer' and the call to this function. The
        difference is stored in a double as seconds.

        A previous call to PRtimerMark() must have been made with `timer'.

        If the `diffPtr' argument is not NULL, then CSCtimerDiff() writes to
        the double pointed to by `diffPtr' the difference between the marks
        taken with `timer'.

SEE ALSO
        PRtimerInit(3)
        PRtimerDone(3)
        PRtimerClear(3)
        PRtimerMark(3)
        PRtimerStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCtimerDiff) (
                            CSCtimerType   const timer,
                            double*        const diffPtr
                            )
   {
          int            diffStat = CSC_ERROR;
   struct S_timerType*   t        = timer;

   ASSERT_RTN (timer != NULL, "CSCtimerDiff: NULL timer", CSC_BADARG);

   ASSERT_RTN (					\
              t->sig_lo == TIMER_SIG,		\
              "CSCtimerDiff: timer blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              t->sig_hi == TIMER_SIG,		\
              "CSCtimerDiff: timer blows",	\
              CSC_CORRUPT			\
              );

#define	MARK1	(t->mark)
#define	MARK2	(t->diffMark)
#define	DIFF	(t->diffStat)

   if (t == NULL) return (CSC_BADARG);
   if (timerisset(&MARK1))
      {
      diffStat = gettimeofday (&MARK2, NULL);
      if (diffStat == 0)
         {
         double m1 = (double)MARK1.tv_sec + (double)MARK1.tv_usec / (1000*1000);
         double m2 = (double)MARK2.tv_sec + (double)MARK2.tv_usec / (1000*1000);
         DIFF = m2 - m1;
         if (diffPtr != NULL) *diffPtr = DIFF;
         diffStat = CSC_OK;
         }
      else
         {
         diffStat = CSC_ERROR;
         }
      }

#undef	MARK1
#undef	MARK2

   return (diffStat);
   }


/***************************************************************************
 * Public Function CSCtimerStat
 ***************************************************************************

<SUBROUTINE NAME="CSCtimerStat">

NAME
        CSCtimerStat - get current timer's time

SYNOPSYS
        #include "libcsc.h"

        int   CSCtimerStat (
                           CSCtimerType   const timer,
                           double*        const diffPtr
                           );

RETURN VALUE
        CSC_OK ........ successful

        CSC_ERROR ..... at least one of the two marks has not been taken with
                        timer

        CSC_BADARG .... timer is NULL

        CSC_CORRUPT ... corruption is detected in timer
                        and CSCtimerStat() is compiled with DEBUG

DESCRIPTION
        CSCtimerStat() writes to the double pointed to by `diffPtr' the
        difference between the marks taken with `timer'. The difference is in
        seconds.

        Marks are taken with `timer' by using functions CSCtimerMark() and
        CSCtimerDiff(). The difference in seconds between CSCtimerMark() and
        CSCtimerDiff() is kept in `timer' as a double.

        The `timer's difference between marks is created by CSCtimerDiff();
        CSCtimerStat() merely returns the saved value.

SEE ALSO
        PRtimerInit(3)
        PRtimerDone(3)
        PRtimerClear(3)
        PRtimerMark(3)
        PRtimerDiff(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCtimerStat) (
                            CSCtimerType   const timer,
                            double*        const diffPtr
                            )
   {
          int            statStat = CSC_ERROR;
   struct S_timerType*   t        = timer;

   ASSERT_RTN (timer != NULL, "CSCtimerStat: NULL timer", CSC_BADARG);

   ASSERT_RTN (					\
              t->sig_lo == TIMER_SIG,		\
              "CSCtimerStat: timer blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              t->sig_hi == TIMER_SIG,		\
              "CSCtimerStat: timer blows",	\
              CSC_CORRUPT			\
              );

   if (t == NULL) return (CSC_BADARG);
   if ((timerisset(&t->mark)) && (timerisset(&t->diffMark)))
      {
      if (diffPtr != NULL) *diffPtr = t->diffStat;
      statStat = CSC_OK;
      }

   return (statStat);
   }


/* End of file. */
