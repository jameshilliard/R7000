/* *****************************************************************************

libcsc: Symbol Subsystem

	----------------------------------------------------------------

Copyright (c) 1999, 2000, 2001, 2002 Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: csc_symbol.c,v $
	$Revision: 1.4 $
	$Date: 2003/03/24 04:26:16 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_symbol">

NAME
	csc_symbol

DESCRIPTION
	Symbol Subsystem

FUNCTIONS
        CSCsymbolIntInit    - initialize a integer symbol
        CSCsymbolFloatInit  - initialize a floating point symbol
        CSCsymbolPtrInit    - initialize a pointer symbol
        CSCsymbolIntNew     - allocate and initialize a integer symbol
        CSCsymbolFloatNew   - allocate and initialize a floating point symbol
        CSCsymbolPtrNew     - allocate and initialize a pointer symbol
        CSCsymbolIntDel     - delete a integer symbol
        CSCsymbolFloatDel   - delete a floating point symbol
        CSCsymbolPtrDel     - delete a pointer symbol
        CSCsymbolIntWrite   - write a integer symbol in ASCII format
        CSCsymbolFloatWrite - write a floating point symbol in ASCII format
        CSCsymbolPtrWrite   - write a pointer symbol in ASCII format
        CSCsymbolDup        - dynamically allocate and duplicate a symbol
        CSCsymbolDel        - remove a libcsc symbol table
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added #include <string.h>.

	20apr02	drj	Small comment changes.

	14apr02	drj	Undefined _BSD_SOURCE.

	25jun01	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Tracked changes to rtsMemDup().

	23apr00	drj	Added function rtsSymbolDel().

	05dec99	drj	Added initialization of new `valueFlag' symbol field.
			Added rtsSymbolDup().

	29mar99	drj	Rebaselined from librt version 0.3.1.

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
 * Public Function CSCsymbolIntInit
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolIntInit">

NAME
        CSCsymbolIntInit - initialize a integer symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolIntInit (
                                     CSCsymbolType*   const symbol,
                               const char*            const symName,
                                     long                   symType,
                                     int                    symVal
                               );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... symbol or symName is equal to NULL

DESCRIPTION
        CSCsymbolIntInit() initializes the symbol pointed to by `symbol' with
        `symName', `symType', and `symVal'. Client code probably should use the
        same `symType' value for all integer symbols, and `symName' probably
        should be the ASCII string equivalent of `symVal'.

BUGS
        The pointer `symName' is copied into the symbol structure; therefore, if
        `symName' is subsequently freed, then the newly initialized symbol will
        have an aliasing error (pointer to freed memory).

        And remember:   CSCsymbolIntDel() will try to deallocate the name, so
                        it won't be happy if the name was not dynamically
                        allocated.

HINT
        The symbol's valueFlag field is set to 1.

SEE ALSO
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolIntInit) (
                                      CSCsymbolType*   const symbol,
                                const char*            const symName,
                                      long                   symType,
                                      int                    symVal
                                )
   {
   int   newSymStat = CSC_OK;

   ASSERT_RTN (symbol != NULL,  "CSCsymbolIntInit: NULL symbol", CSC_BADARG);
   ASSERT_RTN (symName != NULL, "CSCsymbolIntInit: NULL symName", CSC_BADARG);

   if ((symbol == NULL) || (symName == NULL)) return (CSC_BADARG);

   symbol->name = (char*)symName;
   symbol->type = symType;
   symbol->valueFlag = 1;
   symbol->dvSize    = 0;
   symbol->value.integer = symVal;

   return (newSymStat);
   }


/***************************************************************************
 * Public Function CSCsymbolFloatInit
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolFloatInit">

NAME
        CSCsymbolFloatInit - initialize a floating point symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolFloatInit (
                                       CSCsymbolType*   const symbol,
                                 const char*            const symName,
                                       long                   symType,
                                       float                  symVal
                                 );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... symbol or symName is equal to NULL

DESCRIPTION
        CSCsymbolFloatInit() initializes the symbol pointed to by `symbol' with
        `symName', `symType', and `symVal'. Client code probably should use the
        same `symType' value for all floating point symbols, and `symName'
        probably should be the ASCII string equivalent of `symVal'.

BUGS
        The pointer `symName' is copied into the symbol structure; therefore, if
        `symName' is subsequently freed, then the newly initialized symbol will
        have an aliasing error (pointer to freed memory).

        And remember:   CSCsymbolFloatDel() will try to deallocate the name, so
                        it won't be happy if the name was not dynamically
                        allocated.

HINT
        The symbol's valueFlag field is set to 2.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolFloatInit) (
                                        CSCsymbolType*   const symbol,
                                  const char*            const symName,
                                        long                   symType,
                                        float                  symVal
                                  )
   {
   int   newSymStat = CSC_OK;

   ASSERT_RTN (symbol != NULL,  "CSCsymbolFloatInit: NULL symbol",  CSC_BADARG);
   ASSERT_RTN (symName != NULL, "CSCsymbolFloatInit: NULL symName", CSC_BADARG);

   if ((symbol == NULL) || (symName == NULL)) return (CSC_BADARG);

   symbol->name = (char*)symName;
   symbol->type = symType;
   symbol->valueFlag = 2;
   symbol->dvSize    = 0;
   symbol->value.real = symVal;

   return (newSymStat);
   }


/***************************************************************************
 * Public Function CSCsymbolPtrInit
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolPtrInit">

NAME
        CSCsymbolPtrInit - initialize a pointer symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolPtrInit (
                                     CSCsymbolType*   const symbol,
                               const char*            const symName,
                                     long                   symType,
                               const void*                  symVal,
                                     size_t                 symValSize
                               );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... symbol, symName, or symVal is equal to NULL

DESCRIPTION
        CSCsymbolPtrInit() initializes the symbol pointed to by `symbol' with
        `symName', `symType', and `symVal' for `symValSize'. Client code
        probably should use the same `symType' value for all pointer symbols.

BUGS
        The pointers `symName' and `symval' are copied into the symbol
        structure; therefore, if `symName' or `symVal' is subsequently freed,
        then the newly initialized symbol will have an aliasing error (pointer
        to freed memory).

        And remember:   CSCsymbolPtrDel() will try to deallocate the name and
                        pointer, so it won't be happy if they were not
                        dynamically allocated.

HINT
        The symbol's valueFlag field is set to 3.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolPtrInit) (
                                      CSCsymbolType*   const symbol,
                                const char*            const symName,
                                      long                   symType,
                                const void*                  symVal,
                                      size_t                 symValSize
                                )
   {
   int   newSymStat = CSC_OK;

   ASSERT_RTN (symbol != NULL,  "CSCsymbolPtrInit: NULL symbol",  CSC_BADARG);
   ASSERT_RTN (symName != NULL, "CSCsymbolPtrInit: NULL symName", CSC_BADARG);
   ASSERT_RTN (symVal != NULL,  "CSCsymbolPtrInit: NULL symVal",  CSC_BADARG);

   if ((symbol == NULL) || (symName == NULL) || (symVal == NULL))
      {
      return (CSC_BADARG);
      }

   symbol->name = (char*)symName;
   symbol->type = symType;
   symbol->valueFlag = 3;
   symbol->dvSize = symValSize;
   symbol->value.pointer = (void*)symVal;

   return (newSymStat);
   }


/***************************************************************************
 * Public Function CSCsymbolIntNew
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolIntNew">

NAME
        CSCsymbolIntNew - allocate and initialize a integer symbol

SYNOPSYS
        #include "libcsc.h"

        CSCsymbolType*   CSCsymbolIntNew (
                                         const char*            const symName,
                                               long                   symType,
                                               int                    symVal,
                                               CSCmemListType   const memList,
                                               int                    memTag
                                         );

RETURN VALUE
        CSCsymbolIntNew() returns a pointer to the newly allocated symbol, if
        successful; otherwise, NULL is returned.

DESCRIPTION
        CSCsymbolIntNew() dynamically allocates a new symbol structure and
        fills it in with `symName', `symType', and `symVal'. Client code
        probably should use the same `symType' value for all integer symbols,
        and `symName' probably should be the ASCII string equivalent of
        `symVal'.

HINTS
        Memory for the new symbol's name is allocated and `symName' is copied
        in to it, so client code can immediately free `symName' upon returning
        from CSCsymbolIntNew().

        The symbol's valueFlag field is set to 1.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCsymbolType*   (CSCsymbolIntNew) (
                                          const char*            const symName,
                                                long                   symType,
                                                int                    symVal,
                                                CSCmemListType   const memList,
                                                int                    memTag
                                          )
   {
   CSCsymbolType*   newSymPtr  = NULL;
   char*            newSymName = NULL;

   ASSERT_RTN (symName != NULL, "CSCsymbolIntNew: NULL symName", NULL);
   ASSERT_RTN (memList != NULL, "CSCsymbolIntNew: NULL memList", NULL);

   if ((symName == NULL) || (memList == NULL)) return (NULL);

   (void)CSCmemAlloc (
                     memList,
                     (void**)&newSymPtr,
                     1,
                     sizeof(CSCsymbolType),
                     memTag
                     );
   if (newSymPtr != NULL)
      {
      (void)CSCmemDup (
                      memList,
                      (void**)&newSymName,
                      symName,
                      strlen(symName)+1,
                      memTag
                      );
      if (newSymName != NULL)
         (void)CSCsymbolIntInit (newSymPtr, newSymName, symType, symVal);
      else
         {
         (void)CSCmemFree (memList, (void**)&newSymPtr, memTag);
         newSymPtr = NULL;
         }
      }

   return (newSymPtr);
   }


/***************************************************************************
 * Public Function CSCsymbolFloatNew
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolFloatNew">

NAME
        CSCsymbolFloatNew - allocate and initialize a floating point symbol

SYNOPSYS
        #include "libcsc.h"

        CSCsymbolType*   CSCsymbolFloatNew (
                                           const char*            const symName,
                                                 long                   symType,
                                                 float                  symVal,
                                                 CSCmemListType   const memList,
                                                 int                    memTag
                                           );

RETURN VALUE
        CSCsymbolFloatNew() returns a pointer to the newly allocated symbol, if
        successful; otherwise, NULL is returned.

DESCRIPTION
        CSCsymbolFloatNew() dynamically allocates a new symbol structure and
        fills it in with `symName', `symType', and `symVal'. Client code
        probably should use the same `symType' value for all floating point
        symbols, and `symName' probably should be the ASCII string equivalent of
        `symVal'.

HINTS
        Memory for the new symbol's name is allocated and `symName' is copied
        in to it, so client code can immediately free `symName' upon returning
        from CSCsymbolFloatNew().

        The symbol's valueFlag field is set to 2.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCsymbolType*   (CSCsymbolFloatNew) (
                                            const char*           const symName,
                                                  long                  symType,
                                                  float                 symVal,
                                                  CSCmemListType  const memList,
                                                  int                   memTag
                                            )
   {
   CSCsymbolType*   newSymPtr  = NULL;
   char*            newSymName = NULL;

   ASSERT_RTN (symName != NULL, "CSCsymbolFloatNew: NULL symName", NULL);
   ASSERT_RTN (memList != NULL, "CSCsymbolFloatNew: NULL memList", NULL);

   if ((symName == NULL) || (memList == NULL)) return (NULL);

   (void)CSCmemAlloc (
                     memList,
                     (void**)&newSymPtr,
                     1,
                     sizeof(CSCsymbolType),
                     memTag
                     );
   if (newSymPtr != NULL)
      {
      (void)CSCmemDup (
                      memList,
                      (void**)&newSymName,
                      symName,
                      strlen(symName)+1,
                      memTag
                      );
      if (newSymName != NULL)
         (void)CSCsymbolFloatInit (newSymPtr, newSymName, symType, symVal);
      else
         {
         (void)CSCmemFree (memList, (void**)&newSymPtr, memTag);
         newSymPtr = NULL;
         }
      }

   return (newSymPtr);
   }


/***************************************************************************
 * Public Function CSCsymbolPtrNew
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolPtrNew">

NAME
        CSCsymbolPtrNew - allocate and initialize a pointer symbol

SYNOPSYS
        #include "libcsc.h"

        CSCsymbolType*   CSCsymbolPtrNew (
                                        const char*            const symName,
                                              long                   symType,
                                        const void*                  symVal,
                                              size_t                 symValSize,
                                              CSCmemListType   const memList,
                                              int                    memTag
                                         );

RETURN VALUE
        CSCsymbolPtrNew() returns a pointer to the newly allocated symbol, if
        successful; otherwise, NULL is returned.

DESCRIPTION
        CSCsymbolPtrNew() dynamically allocates a new symbol structure and
        fills it in with `symName', `symType', and `symVal' for `symValSize'.
        Client code probably should use the same `symType' value for all pointer
        symbols.

HINTS
        Memory for the new `symName' and `symval' are allocated and they are
        copied in to it, so client code can immediately free `symName' and
        `symVal' upon returning from CSCsymbolPtrNew().

        The symbol's valueFlag field is set to 3.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCsymbolType*   (CSCsymbolPtrNew) (
                                         const char*           const symName,
                                               long                  symType,
                                         const void*                 symVal,
                                               size_t                symValSize,
                                               CSCmemListType  const memList,
                                               int                   memTag
                                          )
   {
   CSCsymbolType*   newSymPtr  = NULL;
   char*            newSymName = NULL;
   void*            newSymVal  = NULL;

   ASSERT_RTN (symName != NULL, "CSCsymbolPtrNew: NULL symName",  NULL);
   ASSERT_RTN (symVal  != NULL, "CSCsymbolPtrNew: NULL symVal",   NULL);
   ASSERT_RTN (symValSize > 0,  "CSCsymbolPtrNew: no symValSize", NULL);
   ASSERT_RTN (memList != NULL, "CSCsymbolPtrNew: NULL memList",  NULL);

   if ((symName == NULL) || (symVal == NULL) ||
       (symValSize == 0) || (memList == NULL))
      {
      return (NULL);
      }

   (void)CSCmemAlloc (
                     memList,
                     (void**)&newSymPtr,
                     1,
                     sizeof(CSCsymbolType),
                     memTag
                     );
   if (newSymPtr == NULL) return (NULL);

   (void)CSCmemDup (
                   memList,
                   (void**)&newSymName,
                   symName,
                   strlen(symName)+1,
                   memTag
                   );
   if (newSymName == NULL)
      {
      (void)CSCmemFree (memList, (void**)&newSymPtr, memTag);
      return (NULL);
      }

   (void)CSCmemDup (
                   memList,
                   (void**)&newSymVal,
                   symVal,
                   symValSize,
                   memTag
                   );
   if (newSymVal == NULL)
      {
      (void)CSCmemFree (memList, (void**)&newSymPtr, memTag);
      (void)CSCmemFree (memList, (void**)&newSymName, memTag);
      return (NULL);
      }

   (void)CSCsymbolPtrInit (
                          newSymPtr,
                          newSymName,
                          symType,
                          newSymVal,
                          symValSize
                          );

   return (newSymPtr);
   }


/***************************************************************************
 * Public Function CSCsymbolIntDel
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolIntDel">

NAME
        CSCsymbolIntDel - delete a integer symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolIntDel (
                              CSCsymbolType**   const symPtrPtr,
                              CSCmemListType    const memList,
                              int                     memTag
                              );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... symPtrPtr or memList is NULL

        CSC_ERROR .... other errors

DESCRIPTION
        CSCsymbolIntDel() removes the integer symbol whose pointer is pointed
        to by `symPtrPtr'.

BUGS
        The name field of the symbol structure is a character pointer and
        CSCsymbolIntDel() tries to deallocate it; therefore, don't create a
        symbol with a statically allocated name.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolIntDel) (
                               CSCsymbolType**   const symPtrPtr,
                               CSCmemListType    const memList,
                               int                     memTag
                               )
   {
   int   delSymStat = CSC_OK;

   ASSERT_RTN (symPtrPtr != NULL,"CSCsymbolIntDel: NULL symPtrPtr",CSC_BADARG);
   ASSERT_RTN (memList != NULL,  "CSCsymbolIntDel: NULL symName",  CSC_BADARG);

   if ((symPtrPtr == NULL) || (memList == NULL)) return (CSC_BADARG);

   delSymStat |= CSCmemFree (memList, (void**)&((*symPtrPtr)->name), memTag);
   delSymStat |= CSCmemFree (memList, (void**)symPtrPtr, memTag);

   if (delSymStat != CSC_OK) delSymStat = CSC_ERROR;

   return (delSymStat);
   }


/***************************************************************************
 * Public Function CSCsymbolFloatDel
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolFloatDel">

NAME
        CSCsymbolFloatDel - delete a floating point symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolFloatDel (
                                CSCsymbolType**   const symPtrPtr,
                                CSCmemListType    const memList,
                                int                     memTag
                                );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... symPtrPtr or memList is NULL

        CSC_ERROR .... other errors

DESCRIPTION
        CSCsymbolFloatDel() removes the floating point symbol whose pointer is
        pointed to by `symPtrPtr'.

BUGS
        The name field of the symbol structure is a character pointer and
        CSCsymbolFloatDel() tries to deallocate it; therefore, don't create a
        symbol with a statically allocated name.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolFloatDel) (
                                 CSCsymbolType**   const symPtrPtr,
                                 CSCmemListType    const memList,
                                 int                     memTag
                                 )
   {
   int   delSymStat = CSC_OK;

   ASSERT_RTN(symPtrPtr != NULL,"CSCsymbolFloatDel: NULL symPtrPtr",CSC_BADARG);
   ASSERT_RTN(memList != NULL,  "CSCsymbolFloatDel: NULL symName",  CSC_BADARG);

   if ((symPtrPtr == NULL) || (memList == NULL)) return (CSC_BADARG);

   delSymStat |= CSCmemFree (memList, (void**)&((*symPtrPtr)->name), memTag);
   delSymStat |= CSCmemFree (memList, (void**)symPtrPtr, memTag);

   if (delSymStat != CSC_OK) delSymStat = CSC_ERROR;

   return (delSymStat);
   }


/***************************************************************************
 * Public Function CSCsymbolPtrDel
 ***************************************************************************

<SUBROUTINE NAME="CSCsymbolPtrDel">

NAME
        CSCsymbolPtrDel - delete a pointer symbol

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolPtrDel (
                              CSCsymbolType**   const symPtrPtr,
                              CSCmemListType    const memList,
                              int                     memTag
                              );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... symPtrPtr or memList is NULL

        CSC_ERROR .... other errors

DESCRIPTION
        CSCsymbolPtrDel() removes the pointer symbol whose pointer is pointed
        to by `symPtrPtr'.

BUGS
        The name and value fields of the symbol structure are pointers and
        CSCsymbolPtrDel() tries to deallocate them; therefore, don't create a
        symbol with a statically allocated name or pointer.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolPtrDel) (
                               CSCsymbolType**   const symPtrPtr,
                               CSCmemListType    const memList,
                               int                     memTag
                               )
   {
   int   delSymStat = CSC_OK;

   ASSERT_RTN (symPtrPtr != NULL,"CSCsymbolPtrDel: NULL symPtrPtr",CSC_BADARG);
   ASSERT_RTN (memList != NULL,  "CSCsymbolPtrDel: NULL symName",  CSC_BADARG);

   if ((symPtrPtr == NULL) || (memList == NULL)) return (CSC_BADARG);

delSymStat |= CSCmemFree(memList,(void**)&((*symPtrPtr)->value.pointer),memTag);
delSymStat |= CSCmemFree(memList,(void**)&((*symPtrPtr)->name),memTag);
delSymStat |= CSCmemFree(memList,(void**)symPtrPtr,memTag);

   if (delSymStat != CSC_OK) delSymStat = CSC_ERROR;

   return (delSymStat);
   }


/**************************************************************************
 * Public Function CSCsymbolIntWrite
 **************************************************************************

<SUBROUTINE NAME="CSCsymbolIntWrite">

NAME
        CSCsymbolIntWrite - write a integer symbol in ASCII format

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolIntWrite (
                                const int                    fd,
                                const CSCsymbolType*   const symPtr
                                );

RETURN VALUE
        CSC_OK ....... always

DESCRIPTION
        CSCsymbolIntWrite() writes to fd the fields of the symbol in an ASCII
        format.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolIntWrite) (
                                 const int                    fd,
                                 const CSCsymbolType*   const symPtr
                                 )
   {
   char   ioLine[ 80 ];

   ASSERT_RTN (fd >= 0,        "CSCsymbolIntWrite: no fd",       CSC_BADARG);
   ASSERT_RTN (symPtr != NULL, "CSCsymbolIntWrite: NULL symPtr", CSC_BADARG);

   if ((fd < 0) || (symPtr == NULL)) return (CSC_BADARG);

   (void)write (fd, "\n-- int symbol\nname:  ", 24);
   if (symPtr->name != NULL)
      (void)write (fd, symPtr->name, strlen(symPtr->name));
   else
      (void)write (fd, "<null>", 6);
   (void)write (fd, "\n", 1);
   (void)sprintf (
                 ioLine,
                 "type:  %d (%08X)\n",
                 (int)symPtr->type, (int)symPtr->type
                 );
   (void)write (fd, ioLine, strlen(ioLine));
   (void)sprintf (
                 ioLine,
                 "value.integer:  %d (%08X)\n",
                 (int)symPtr->value.integer, (int)symPtr->value.integer
                 );
   (void)write (fd, ioLine, strlen(ioLine));

   return (CSC_OK);
   }


/**************************************************************************
 * Public Function CSCsymbolFloatWrite
 **************************************************************************

<SUBROUTINE NAME="CSCsymbolFloatWrite">

NAME
        CSCsymbolFloatWrite - write a floating point symbol in ASCII format

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolFloatWrite (
                                  const int                    fd,
                                  const CSCsymbolType*   const symPtr
                                  );

RETURN VALUE
        CSC_OK ....... always

DESCRIPTION
        CSCsymbolFloatWrite() writes to fd the fields of the symbol in an ASCII
        format.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolFloatWrite) (
                                   const int                    fd,
                                   const CSCsymbolType*   const symPtr
                                   )
   {
   char   ioLine[ 80 ];

   ASSERT_RTN (fd >= 0,        "CSCsymbolFloatWrite: no fd",       CSC_BADARG);
   ASSERT_RTN (symPtr != NULL, "CSCsymbolFloatWrite: NULL symPtr", CSC_BADARG);

   if ((fd < 0) || (symPtr == NULL)) return (CSC_BADARG);

   (void)write (fd, "\n-- float symbol\nname:  ", 25);
   if (symPtr->name != NULL)
      (void)write (fd, symPtr->name, strlen(symPtr->name));
   else
      (void)write (fd, "<null>", 6);
   (void)write (fd, "\n", 1);
   (void)sprintf (
                 ioLine,
                 "type:  %d (%08X)\n",
                 (int)symPtr->type, (int)symPtr->type
                 );
   (void)write (fd, ioLine, strlen(ioLine));
   (void)sprintf (
                 ioLine,
                 "value.real:  %f (%08X)\n",
                 symPtr->value.real, (int)symPtr->value.integer
                 );
   (void)write (fd, ioLine, strlen(ioLine));

   return (CSC_OK);
   }


/**************************************************************************
 * Public Function CSCsymbolPtrWrite
 **************************************************************************

<SUBROUTINE NAME="CSCsymbolPtrWrite">

NAME
        CSCsymbolPtrWrite - write a pointer symbol in ASCII format

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolPtrWrite (
                                const int                    fd,
                                const CSCsymbolType*   const symPtr
                                );

RETURN VALUE
        CSC_OK ....... always

DESCRIPTION
        CSCsymbolPtrWrite() writes to fd the fields of the symbol in an ASCII
        format.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolDup(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolPtrWrite) (
                                 const int                    fd,
                                 const CSCsymbolType*   const symPtr
                                 )
   {
   char   ioLine[ 80 ];

   ASSERT_RTN (fd >= 0,        "CSCsymbolPtrWrite: no fd",       CSC_BADARG);
   ASSERT_RTN (symPtr != NULL, "CSCsymbolPtrWrite: NULL symPtr", CSC_BADARG);

   if ((fd < 0) || (symPtr == NULL)) return (CSC_BADARG);

   (void)write (fd, "\n-- pointer symbol\nname:  ", 26);
   (void)sprintf (ioLine, "%d (%08X)\n", (int)symPtr->type, (int)symPtr->type);
   if (symPtr->name != NULL)
      (void)write (fd, symPtr->name, strlen(symPtr->name));
   else
      (void)write (fd, "<null>", 6);
   (void)write (fd, "\n", 1);
   (void)write (fd, ioLine, strlen(ioLine));
   (void)write (fd, "\"", 1);
   if (symPtr->value.pointer != NULL)
     (void)write (fd, symPtr->value.pointer, strlen(symPtr->value.pointer));
   else
     (void)write (fd, "<null>", 6);
   (void)write (fd, "\"\n", 3);

   return (CSC_OK);
   }


/**************************************************************************
 * Public Function CSCsymbolDup
 **************************************************************************

<SUBROUTINE NAME="CSCsymbolDup">

NAME
        CSCsymbolDup - dynamically allocate and duplicate a symbol

SYNOPSYS
        #include "libcsc.h"

        CSCsymbolType*   CSCsymbolDup (
                                      const CSCsymbolType*   const symPtr,
                                            CSCmemListType   const memList,
                                            int                    memTag
                                      );

RETURN VALUE
        CSCsymbolDup(), if successful, returns a pointer to the newly created
        symbol, otherwise NULL is returned.

DESCRIPTION
        CSCsymbolDup() dynamically allocates a symbol structure and copies the
        symbol pointed to by `symPtr' into the new symbol.

        The symbol's name is also dynamically allocated and copied.  To free
        the newly created symbol's memory, the name field and the symbol
        structure itself must be freed; use the appropriate CSCsymbol*Del()
        function.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCsymbolType*   (CSCsymbolDup) (
                                       const CSCsymbolType*   const symPtr,
                                             CSCmemListType   const memList,
                                             int                    memTag
                                       )
   {
   CSCsymbolType*   newSymPtr = NULL;

   ASSERT_RTN (symPtr != NULL,  "CSCsymbolDup: NULL symPtr",  NULL);
   ASSERT_RTN (memList != NULL, "CSCsymbolDup: NULL memList", NULL);

   if ((symPtr == NULL) || (memList == NULL)) return (NULL);

   switch (symPtr->valueFlag)
         {
         default:  break;
         case 1:  newSymPtr = CSCsymbolIntNew (
                                              symPtr->name,
                                              symPtr->type,
                                              symPtr->value.integer,
                                              memList,
                                              memTag
                                              );
                  break;
         case 2:  newSymPtr = CSCsymbolFloatNew (
                                                symPtr->name,
                                                symPtr->type,
                                                symPtr->value.real,
                                                memList,
                                                memTag
                                                );
                  break;
         case 3:  newSymPtr = CSCsymbolPtrNew (
                                              symPtr->name,
                                              symPtr->type,
                                              symPtr->value.pointer,
                                              symPtr->dvSize,
                                              memList,
                                              memTag
                                              );
         }

   return (newSymPtr);
   }


/**************************************************************************
 * Public Function CSCsymbolDel
 **************************************************************************

<SUBROUTINE NAME="CSCsymbolDel">

NAME
        CSCsymbolDel - remove a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymbolDel (
                           CSCsymbolType**   const symPtrPtr,
                           CSCmemListType    const memList,
                           int                     memTag
                           );

RETURN VALUE
        CSC_OK ....... successful

        CSC_BADARG ... symPtrPtr or memList is NULL

        CSC_ERROR .... other errors

DESCRIPTION
        CSCsymbolDel() deletes the symbol whose pointer is pointed to by
        `symPtrPtr'.

        If the symbol was created by CSCsymbolFloatInit(), CSCsymbolIntInit(),
        CSCsymbolPtrInit(), or otherwise does not have a dynamically allocated
        name, then there will be some complaints (crashes? heap corruption?)
        when the name field is freed.

HINT
        If the symbol's valueFlag field is set to 1, 2 or 3, then the name
        field is deallocated.  If the symbol's valueFlag field is set to 3,
        then the value.pointer field is also deallocated.

SEE ALSO
        CSCsymbolIntInit(3)
        CSCsymbolFloatInit(3)
        CSCsymbolPtrInit(3)
        CSCsymbolIntNew(3)
        CSCsymbolFloatNew(3)
        CSCsymbolPtrNew(3)
        CSCsymbolIntDel(3)
        CSCsymbolFloatDel(3)
        CSCsymbolPtrDel(3)
        CSCsymbolIntWrite(3)
        CSCsymbolFloatWrite(3)
        CSCsymbolPtrWrite(3)
        CSCsymbolDup(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsymbolDel) (
                            CSCsymbolType**   const symPtrPtr,
                            CSCmemListType    const memList,
                            int                     memTag
                            )
   {
   int   delSymStat = CSC_ERROR;

   ASSERT_RTN (symPtrPtr != NULL, "CSCsymbolDel: NULL symPtrPtr", CSC_BADARG);
   ASSERT_RTN (memList != NULL,   "CSCsymbolDel: NULL memList",   CSC_BADARG);

   if ((symPtrPtr == NULL) || (memList == NULL)) return (CSC_BADARG);

   switch ((*symPtrPtr)->valueFlag)
         {
         default:  break;
         case 1:  delSymStat = CSCsymbolIntDel (symPtrPtr, memList, memTag);
                  break;
         case 2:  delSymStat = CSCsymbolFloatDel (symPtrPtr, memList, memTag);
                  break;
         case 3:  delSymStat = CSCsymbolPtrDel (symPtrPtr, memList, memTag);
         }

   return (delSymStat);
   }


/* End of file. */
