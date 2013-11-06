/* *****************************************************************************

libcsc:  Math Subsystem

	----------------------------------------------------------------

Copyright (c) 1999, 2002 Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: csc_math.c,v $
	$Revision: 1.2 $
	$Date: 2002/04/30 05:37:34 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_math">

NAME
	csc_math

DESCRIPTION
	Miscellaneous math functions.

FUNCTIONS
	CSC2x    - 2 to a the power of x, 0 <= x <= 30
        CSCurand - uniform random number generator
</SUBSYSTEM>

CHANGE LOG

	20apr02	drj	Small comment changes.

	13apr02	drj	Converted to libcsc: renamed everything from rt to csc,
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
#include	<math.h>

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

PRIVATE int32   y2xTable [31] =
   {
            1,  /* 2**0  */
            2,  /* 2**1  */
            4,  /* 2**2  */
            8,  /* 2**3  */
           16,  /* 2**4  */
           32,  /* 2**5  */
           64,  /* 2**6  */
          128,  /* 2**7  */
          256,  /* 2**8  */
          512,  /* 2**9  */
         1024,  /* 2**10 */
         2048,  /* 2**11 */
         4096,  /* 2**12 */
         8192,  /* 2**13 */
        16384,  /* 2**14 */
        32768,  /* 2**15 */
        65536,  /* 2**16 */
       131072,  /* 2**17 */
       262144,  /* 2**18 */
       524288,  /* 2**19 */
      1048576,  /* 2**20 */
      2097152,  /* 2**21 */
      4194304,  /* 2**22 */
      8388608,  /* 2**23 */
     16777216,  /* 2**24 */
     33554432,  /* 2**25 */
     67108864,  /* 2**26 */
    134217728,  /* 2**27 */
    268435456,  /* 2**28 */
    536870912,  /* 2**29 */
   1073741824   /* 2**30 */
   };


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
 * Public Function CSC2x
 ***************************************************************************

<SUBROUTINE NAME="CSC2x">

NAME
        CSC2x - 2 to a the power of x, 0 <= x <= 30

SYNOPSYS
        #include "libcsc.h"

        int   CSC2x (
                    int   exponent
                    );

RETURN VALUE
DESCRIPTION
        CSC2x() returns 2 to the power of exponent, unless exponent is less
        than 0 or greater than 30, in which case CSC2x() returns -1.

        CSC2x() uses a table, so it is extremly fast.

SEE ALSO
        CSCurand(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSC2x) (int exp)
   {
   if ((exp >= 0) && (exp <= 30))
      return (y2xTable[exp]);
   else
      return (-1);
   }


/***************************************************************************
 * Public Function CSCurand
 ***************************************************************************

<SUBROUTINE NAME="CSCurand">

NAME
        CSCurand - uniform random number generator

SYNOPSYS
        #include "libcsc.h"

        int   CSCurand (
                       int       y,
                       double*   dptr
                       );

RETURN VALUE
        urand() returns a random int.

DESCRIPTION
        Urand is a Uniform/Universal RANDom number generator.

        The integer argument y should be initialized to some arbitrary non-zero
        number prior to the first call to CSCurand.

        Function CSCurand takes the form:  f(x) = a(x) + c(modulo m)

        m is 2 to the power of t for t-bit integers.  X, a, and c are
        themselves integers in the same range.  Some choices of a and c are
        good; urand chooses values suggested by Knuth (1969).  The scale factor
        that is used for converting y to a floating point value in the interval
        (0,1) is s = (double) 0.5 / halfm.

        CSCurand is taken from George E. Forsythe, Michael A. Malcolm, and Cleve
        B. Moler, "Computer Methods for Mathematical Programming" (Englewood
        Cliffs: Prentice Hall, 1977), 246.

        CSCurand is based on theory and suggestions given in Donald E. Knuth
        "Seminumerical Algorithms," The Art of Computer Programming, vol. 2
        (Reading Mass.:  Addison-Wesley 1969).

BUGS
        Using CSCurand() always seems too difficult.

SEE ALSO
        CSC2x(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCurand) (int y, double* dptr)
   {
   static double   s;
   static    int   a, mc, m2 = 0;
          double   halfm;
             int   c, m;

/*
 * There are several things to do the first time urand is called:
 */
   if (m2 == 0)
      {
      m = 1;
      do
         {
         m2 = m;
         m = 2 * m2;
         }
      while (m > m2);
      halfm = (double) m2;

/*
 * The multiplier and increment for the linear congruential method are found
 * in the next few statements.
 */
      a = 8 * (unsigned int)(halfm * atan((double)(1.0)) / (double)(8.0)) + 5;
      c = 2 * (unsigned int)(
                   halfm * ((double)(0.5) - sqrt((double)(3.0)) / (double)(6.0))
                            ) + 1;

      mc = (m2 - c) + m2;
      s  = (double)(0.5) / halfm;
      }

/*
 * Begin computing the next random number:
 */
   y = y * a;		/* The multiplier is applied to the next random       */
			/* number.                                            */

   if (y > mc)		/* This is for computers that do not allow integer    */
      y = (y-m2) - m2;	/* overflow on addition.                              */

   y = y + mc;		/* The increment is applied to the next random        */
			/* number.                                            */

   if (y/2 > m2)	/* This is for computers that have a word length for  */
      y = (y-m2) - m2;	/* addition which is greater than for multiplication. */

   if (y < 0)		/* This is for computers in which integer overflow    */
      y = (y+m2) + m2;	/* affects the sign bit.                              */

   *dptr = s * (double)(y);
   return (y);
   }


/* End of the file. */
