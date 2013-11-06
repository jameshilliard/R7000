/* *****************************************************************************

libcsc: Memory (Dynamic Allocation) Subsystem

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

	$RCSfile: csc_mem.c,v $
	$Revision: 1.6 $
	$Date: 2003/03/24 04:25:42 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_mem">

NAME
	csc_mem

DESCRIPTION
	Memory (Dynamic Allocation) Subsystem

FUNCTIONS
	CSCmemInit - initialize a csc memlist for subsequent memory allocations
	CSCmemDone - cleanup and remove a memList (free all its memory)
	CSCmemAlloc - allocate memory (and keep thrack of it in memList)
	CSCmemDup - duplicate (dynamically allocate and copy) memory
	CSCmemFree - free dynamically allocated memory
	CSCmemLookup - lookup a memory pointer in memList
	CSCmemValidate - validate that a memory pointer is in memList
	CSCmemListFree - free all memory allocated in a memList
	CSCmemListStat - get information about a memList
	CSCmemListPrintProfile - write a memlist profile to standard output
	CSCmemListWriteProfile - write a memlist profile to a file descriptor
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added #include <string.h>.

	06may02	drj	Fixup for compiler warnings on Solaris.

	20apr02	drj	Small comment changes.

	14apr02	drj	Changed some ifdef formating.

	25jun01	drj	Major changes.  Converted to libcsc: renamed
			everything from rt to csc, removed some debug message
			printing code.  Removed macro RTS_ENABLE_MEM_PROFILE.

	13may00	drj	Major changes:  changed to rtsMemLstType from
			rtsMemLstType* and now make use of macro
			RTS_ENABLE_MEM_PROFILE to enable reference checking.
			Added function rtsMemHasProfile().

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
#   define	_POSIX_SOURCE	1	/* posix.1                      */
#   define	_POSIX_C_SOURCE	199309L	/* posix.1 and posix.4          */
#else
#   define	_BSD_SOURCE	1	/* for bsd getpagesize()        */
#   ifndef	SOLARIS
#      define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4 and MORE */
#   endif
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

#define	MEM_SIG		(0x4D454D4F)

#define	GARBAGE_DATA	(0xAA)
#define	NUMBUF_SIZE	(40)

#define	MON_ENTER(x)	{if(x->monFunc!=NULL)(*x->monFunc)(CSC_IN,x->monData);}
#define	MON_EXIT(x)	{if(x->monFunc!=NULL)(*x->monFunc)(CSC_OUT,x->monData);}


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

typedef struct S_memBlockType
   {
#ifdef	DEBUG
          long              sig_lo;
#endif
   struct S_memBlockType*   pred;
   struct S_memBlockType*   succ;
          void*             data;
          size_t            size;
          int               allocTag;
          int               freeTag;
          CSCboolean        deleted;
#ifdef	DEBUG
          long              sig_hi;
#endif
   } S_memBlockType;

typedef struct S_memListType
   {
#ifdef	DEBUG
         long               sig_lo;
#endif
   struct S_memBlockType*   list;
   const char*              name;
         CSCprofileType     profiling;
         CSCtagFnType       tagFunc;
         CSCmonFnType       monFunc;
         void*              monData;
         size_t             allocCount; /* count of total memory allocations */
         size_t             freeCount;  /* count of total memory frees       */
         size_t             curAlloc;   /* current memory allocated          */
         size_t             maxAlloc;   /* most memory allocated at any time */
#ifdef	DEBUG
         long               sig_hi;
#endif
   } S_memListType;


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

PRIVATE int   blockUnlink (
                          S_memListType*    const memList,
                          S_memBlockType*   const block
                          );

PRIVATE int   blockPush (
                        S_memListType*    const memList,
                        S_memBlockType*   const block
                        );

PRIVATE S_memBlockType*   blockNew (
                                   void*    dataPtr,
                                   size_t   dataSz,
                                   int      tag
                                   );

PRIVATE int   blockDel (
                       S_memListType*    const memList,
                       S_memBlockType*   const block,
                       int                     tagData
                       );

PRIVATE int   blockFindAndDel (
                              S_memListType*   const memList,
                              void*                  memPtr,
                              int                    tagData,
                              size_t*                sizePtr
                              );

PRIVATE void   mlWriteName (int fd, const S_memListType* memList);
PRIVATE void   mlWriteTfnc (int fd, const S_memListType* memList);
PRIVATE void   mlWriteMfnc (int fd, const S_memListType* memList);
PRIVATE void   mlWriteProf (int fd, const S_memListType* memList);

PRIVATE void   mlWriteAlloc (int fd, const S_memListType* memList);
PRIVATE void   mlWriteFreed (int fd, const S_memListType* memList);
PRIVATE void   mlWriteCurAl (int fd, const S_memListType* memList);
PRIVATE void   mlWriteMaxAl (int fd, const S_memListType* memList);

PRIVATE void   blockWriteProfile (
                                 const S_memListType*    memList,
                                       int               fd,
                                 const S_memBlockType*   block
                                 );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function blockUnlink
 **************************************************************************/

PRIVATE int   blockUnlink (
                          S_memListType*    const memList,
                          S_memBlockType*   const block
                          )
   {
   int   unlinkStat = CSC_OK;

#define	PRED(x)	((x)->pred)
#define	SUCC(x)	((x)->succ)

   if (block == memList->list)
      {
      /* -- DE-LINK FIRST ENTRY --  */
      /* -- DE-LINK SINGLE ENTRY -- */
#ifdef	DEBUG
      if (SUCC(block) != NULL)
         {
         ASSERT_RTN (					\
                    SUCC(block)->sig_lo == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         ASSERT_RTN (					\
                    SUCC(block)->sig_hi == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         }
#endif
      memList->list = SUCC(block);
      if (memList->list != NULL) PRED(memList->list) = NULL;
      }
   else
      {
      if (SUCC(block) == NULL)
         {
         /* -- DE-LINK LAST ENTRY -- */
         ASSERT_RTN (					\
                    PRED(block)->sig_lo == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         ASSERT_RTN (					\
                    PRED(block)->sig_hi == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         SUCC(PRED(block)) = NULL;
         }
      else
         {
         /* -- DE-LINK INNER ENTRY -- */
         ASSERT_RTN (					\
                    SUCC(block)->sig_lo == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         ASSERT_RTN (					\
                    SUCC(block)->sig_hi == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         ASSERT_RTN (					\
                    PRED(block)->sig_lo == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         ASSERT_RTN (					\
                    PRED(block)->sig_hi == MEM_SIG,	\
                    "blockUnlink: block blows",		\
                    CSC_CORRUPT				\
                    );
         SUCC(PRED(block)) = SUCC(block);
         PRED(SUCC(block)) = PRED(block);
         }
      }

#undef	PRED
#undef	SUCC

   return (unlinkStat);
   }


/**************************************************************************
 * Private Function blockPush
 **************************************************************************/

PRIVATE int   blockPush (
                        S_memListType*    const memList,
                        S_memBlockType*   const block
                        )
   {
   int   pushStat = CSC_OK;

   ASSERT_RTN (block != NULL,            "blockPush: NULL block",  CSC_BADARG);
   ASSERT_RTN (block->sig_lo == MEM_SIG, "blockPush: block blows", CSC_CORRUPT);
   ASSERT_RTN (block->sig_hi == MEM_SIG, "blockPush: block blows", CSC_CORRUPT);

#define	PRED(x)	((x)->pred)
#define	SUCC(x)	((x)->succ)

   if (block == NULL) return (CSC_BADARG);

   MON_ENTER (memList);

   SUCC(block) = memList->list;
   PRED(block) = NULL;

   if (memList->list != NULL) PRED(memList->list) = block;
   memList->list = block;

   if (memList->profiling == CSC_DO_PROFILING)
      {
      memList->allocCount += 1;
      memList->curAlloc   += block->size;
      if (memList->curAlloc > memList->maxAlloc)
         {
         memList->maxAlloc = memList->curAlloc;
         }
      }

   MON_EXIT (memList);

#undef	PRED
#undef	SUCC

   return (pushStat);
   }


/**************************************************************************
 * Private Function blockNew
 **************************************************************************/

PRIVATE S_memBlockType*   blockNew (
                                   void*    dataPtr,
                                   size_t   dataSz,
                                   int      tag
                                   )
   {
   S_memBlockType*   block = NULL;

   block = (S_memBlockType*)CSC_MALLOC_FUNC (1, sizeof(S_memBlockType));
   if (block != NULL)
      {
      block->pred     = NULL;
      block->succ     = NULL;
      block->data     = dataPtr;
      block->size     = dataSz;
      block->allocTag = tag;
      block->freeTag  = 0;
      block->deleted  = CSC_FALSE;
#ifdef	DEBUG
      block->sig_lo = MEM_SIG;
      block->sig_hi = MEM_SIG;
#endif
      }

   return (block);
   }


/**************************************************************************
 * Private Function blockDel
 **************************************************************************/

PRIVATE int   blockDel (
                       S_memListType*    const memList,
                       S_memBlockType*   const block,
                       int                     tagData
                       )
   {
   int   delStat = CSC_OK;

   ASSERT_RTN (block->sig_lo == MEM_SIG, "blockDel: block blows", CSC_CORRUPT);
   ASSERT_RTN (block->sig_hi == MEM_SIG, "blockDel: block blows", CSC_CORRUPT);

   if (memList->profiling == CSC_DO_PROFILING)
      {
      memList->curAlloc -= block->size;
      memList->freeCount += 1;
      block->freeTag = tagData;
      block->deleted = CSC_TRUE;
      }
   else
      {
      delStat = blockUnlink (memList, block);
      if (delStat == CSC_OK)
         {
#ifdef	DEBUG
         (void)memset (block, GARBAGE_DATA, sizeof(S_memBlockType));
#endif
         (void)CSC_FREE_FUNC (block);
         }
      }

   return (delStat);
   }


/**************************************************************************
 * Private Function blockFindAndDel
 **************************************************************************/

PRIVATE int   blockFindAndDel (
                              S_memListType*   const memList,
                              void*                  memPtr,
                              int                    tagData,
                              size_t*                sizePtr
                              )
   {
   int               delStat = CSC_NOTFOUND;
   S_memBlockType*   b       = NULL;
   S_memBlockType*   block   = NULL;

   MON_ENTER (memList);

   b = memList->list;
   while (b != NULL)
      {
      ASSERT_RTN (					\
                 b->sig_lo == MEM_SIG,			\
                 "blockFindAndDel: block blows",	\
                 CSC_CORRUPT				\
                 );
      ASSERT_RTN (					\
                 b->sig_hi == MEM_SIG,			\
                 "blockFindAndDel: block blows",	\
                 CSC_CORRUPT				\
                 );
      if (b->data == memPtr)
         {
         block = b;
         b = NULL;
         }
      else
         {
         b = b->succ;
         }
      }

   if (block != NULL)
      {
      if (block->deleted == CSC_FALSE)
         {
         if (sizePtr != NULL) *sizePtr = block->size;
         delStat = blockDel (memList, block, tagData);
         }
      }

   MON_EXIT (memList);

   return (delStat);
   }


/**************************************************************************
 * Private Function mlWriteName
 **************************************************************************/

PRIVATE void   mlWriteName (int fd, const S_memListType* memList)
   {
   (void)write (fd, memList->name, strlen(memList->name));
   (void)write (fd, "\n", 1);
   }


/**************************************************************************
 * Private Function mlWriteTfnc
 **************************************************************************/

PRIVATE void   mlWriteTfnc (int fd, const S_memListType* memList)
   {
   if (memList->tagFunc != NULL)
      (void)write (fd, "yes\n", 4);
   else
      (void)write (fd, "no\n", 3);
   }


/**************************************************************************
 * Private Function mlWriteMfnc
 **************************************************************************/

PRIVATE void   mlWriteMfnc (int fd, const S_memListType* memList)
   {
   if (memList->monFunc != NULL)
      (void)write (fd, "yes\n", 4);
   else
      (void)write (fd, "no\n", 3);
   }


/**************************************************************************
 * Private Function mlWriteProf
 **************************************************************************/

PRIVATE void   mlWriteProf (int fd, const S_memListType* memList)
   {
   if (memList->profiling == CSC_DO_PROFILING)
      (void)write (fd, "yes\n", 4);
   else
      (void)write (fd, "no\n", 3);
   }


/**************************************************************************
 * Private Function mlWriteAlloc
 **************************************************************************/

PRIVATE void   mlWriteAlloc (int fd, const S_memListType* memList)
   {
   char   numbuf[NUMBUF_SIZE];

   (void)sprintf (numbuf, "%d\n", memList->allocCount);
   (void)write (fd, numbuf, strlen(numbuf));

   return;
   }


/**************************************************************************
 * Private Function mlWriteFreed
 **************************************************************************/

PRIVATE void   mlWriteFreed (int fd, const S_memListType* memList)
   {
   char   numbuf[NUMBUF_SIZE];

   (void)sprintf (numbuf, "%d\n", memList->freeCount);
   (void)write (fd, numbuf, strlen(numbuf));

   return;
   }


/**************************************************************************
 * Private Function mlWriteCurAl
 **************************************************************************/

PRIVATE void   mlWriteCurAl (int fd, const S_memListType* memList)
   {
   char   numbuf[NUMBUF_SIZE];

   (void)sprintf (numbuf, "%d\n", memList->curAlloc);
   (void)write (fd, numbuf, strlen(numbuf));

   return;
   }


/**************************************************************************
 * Private Function mlWriteMaxAl
 **************************************************************************/

PRIVATE void   mlWriteMaxAl (int fd, const S_memListType* memList)
   {
   char   numbuf[NUMBUF_SIZE];

   (void)sprintf (numbuf, "%d\n", memList->maxAlloc);
   (void)write (fd, numbuf, strlen(numbuf));

   return;
   }


/**************************************************************************
 * Private Function blockWriteProfile
 **************************************************************************/

PRIVATE void   blockWriteProfile (
                                 const S_memListType*    memList,
                                       int               fd,
                                 const S_memBlockType*   block
                                 )
   {
         CSCboolean   currupt = CSC_FALSE;
         char         numbuf[NUMBUF_SIZE];
   const char*        tagStr;

#ifdef	DEBUG
   if (block->sig_lo != MEM_SIG)
      {
      currupt = CSC_TRUE;
      (void)write (fd, "CORRUPTED BLOCK\n", 16);
      }
   else if (block->sig_hi != MEM_SIG)
      {
      currupt = CSC_TRUE;
      (void)write (fd, "CORRUPTED BLOCK\n", 16);
      }
#endif

   if (currupt == CSC_TRUE) return;

   (void)write (fd, "           deleted: ", 20);
   if (block->deleted == CSC_TRUE)
      (void)write (fd, "yes\n", 4);
   else
      (void)write (fd, "no\n", 3);

   if (block->deleted == CSC_FALSE)
      {
      (void)write (fd, "              data: ", 20);
      (void)sprintf (numbuf, "@%p\n", block->data);
      (void)write (fd, numbuf, strlen(numbuf));
      (void)write (fd, "              size: ", 20);
      (void)sprintf (numbuf, "%d\n", block->size);
      (void)write (fd, numbuf, strlen(numbuf));
      }

   (void)write (fd, "      allocate tag: ", 20);
   (void)sprintf (numbuf, "%d", block->allocTag);
   (void)write (fd, numbuf, strlen(numbuf));
   if ((memList->tagFunc != NULL) && (block->allocTag != 0))
      {
      tagStr = (*memList->tagFunc)(block->allocTag);
      (void)write (fd, " [", 2);
      (void)write (fd, tagStr, strlen(tagStr));
      (void)write (fd, "]\n", 2);
      }
   else
      {
      (void)write (fd, "\n", 1);
      }

   (void)write (fd, "          free tag: ", 20);
   (void)sprintf (numbuf, "%d", block->freeTag);
   (void)write (fd, numbuf, strlen(numbuf));
   if ((memList->tagFunc != NULL) && (block->freeTag != 0))
      {
      tagStr = (*memList->tagFunc)(block->freeTag);
      (void)write (fd, " [", 2);
      (void)write (fd, tagStr, strlen(tagStr));
      (void)write (fd, "]\n", 2);
      }
   else
      {
      (void)write (fd, "\n", 1);
      }

   (void)write (fd, "\n", 1);

   return;
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCmemInit
 ***************************************************************************

<SUBROUTINE NAME="CSCmemInit">

NAME
        CSCmemInit - initialize a csc memlist for subsequent memory allocations

SYNOPSYS
        #include "libcsc.h"

        CSCmemListType   CSCmemInit (
                                    const char*            name,
                                          CSCtagFnType     tagFunc,
                                          CSCmonFnType     monFunc,
                                          void*            monData,
                                          CSCprofileType   profiling
                                    );

RETURN VALUE
        If successful CSCmemInit() returns a newly created csc memlist;
        otherwise, when unsuccessful CSCmemInit() returns NULL.

DESCRIPTION
        CSCmemInit() creates and returns a csc memlist.

        A csc memlist is needed to allocate and free memory using the csc memory
        subsystem. The csc memory subsystem records statistics on its allocate
        and free activities into csc memlists. The csc memory subsystem also
        uses the csc memlist to help detect memory leaks and other misuses.

        Memory allocated with a given csc memlist must be freed with the same
        csc memlist.

        NOTE    No arguments are copied; the string pointed to by `name' (if
                not NULL) and the client data pointed to by `monData' (if not
                NULL) are *NOT* copied. The client is responsible for ensuring
                that the data are valid until the csc memlist itself is freed by
                CSCmemListFree().

        `name' can be NULL, but it should point to a descriptive string. The
        string is printed when the csc memlist profile is printed.

        `tagFunc' can be NULL. When it is not NULL, it is used as a callback
        function during the printing of a csc memlist profile to retreive a
        (descriptive) string associated with the integer tag given when memory
        was allocated/freed. This helps to identified memory that has not been
        freed (leaked).

        `monFunc' and `monData':
        The csc memory subsystem makes no assumptions about the threading
        environment, or even if the environment is threaded or not. It is the
        caller's (client's) responsibility to provide mutual exclusion locking
        for the csc memory subsystem. This allows the csc memory subsystem to
        function in multiple environments. `monFunc' is used to provide mutual
        exclusion locking for thread safty. If a proper modFunc is provided,
        then multiple threads may share a given csc memlist to allocate and free
        memory. `monFunc' is a callback function used to enter and exit the
        critical regions when updating the csc memlist. `monFunc' is invoked
        with the the client's `monData'; the calback function should enforce
        locking (mutex). `monFunc' is invoked with CSC_IO_IN and `monData' when
        entering a critical region an it is invoked with CSC_IO_OUT and
        `monData' when exiting a critical region. `monData' is provided so that
        the client can have it point to the necessary mutex (and/or whatever)
        and the csc memory subsystem delivers it to the callback. In this way
        the client does not otherwise have to keep track of the mutex. If the
        environment is not threaded, and no mutex is needed, then `monFunc'
        should be NULL.

        `profiling' specifies whether alocate/free statistics should actually be
        generated and kept in the csc memlist.

SEE ALSO
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCmemListType   (CSCmemInit) (
                                     const char*            name,
                                           CSCtagFnType     tagFunc,
                                           CSCmonFnType     monFunc,
                                     const void*            monData,
                                           CSCprofileType   profiling
                                     )
   {
   S_memListType*   memList = NULL;

   memList = (S_memListType*)CSC_MALLOC_FUNC (1, sizeof(S_memListType));
   if (memList != NULL)
      {
      memList->list       = NULL;
      memList->name       = name;
      memList->profiling  = profiling;
      memList->tagFunc    = tagFunc;
      memList->monFunc    = monFunc;
      memList->monData    = (void*)monData;
      memList->allocCount = 0;
      memList->freeCount  = 0;
      memList->curAlloc   = 0;
      memList->maxAlloc   = 0;
#ifdef	DEBUG
      memList->sig_lo = MEM_SIG;
      memList->sig_hi = MEM_SIG;
#endif
      }

   return (memList);
   }


/***************************************************************************
 * Public Function CSCmemDone
 ***************************************************************************

<SUBROUTINE NAME="CSCmemDone">

NAME
        CSCmemDone - cleanup and remove a memList (free all its memory)

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemDone (CSCmemListType const memList);

RETURN VALUE
        CSC_OK ......... successful

        CSC_BADARG ..... memList is NULL

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemDone() is compiled with DEBUG

DESCRIPTION
        CSCmemDone() unconditionally remves all memory blocks contained in
        `memList' and then removes `memList' itself. `memList' is not checked
        for profiling; no statistics for `memList' are retained.

        Do not try to use `memList' after calling CSCmemDone(), at least until
        using `memList' in another CSCmemInit().

        If CSCmemDone() is compiled with DEBUG, then the memory is shredded
        by writing well-defined garbage to it before it is freed. This avoids
        code that accidentally works by using deallocated memory that hasn't
        yet changed.

SEE ALSO
        CSCmemInit(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemFree(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemDone) (CSCmemListType const memList)
   {
   int   doneStat = CSC_OK;

   ASSERT_RTN (memList != NULL, "CSCmemDone: NULL memList", CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemDone: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemDone: memList blows",	\
              CSC_CORRUPT			\
              );

   if (memList == NULL) return (CSC_BADARG);

   MON_ENTER(memList);

#ifdef	DEBUG
   {
   S_memBlockType*   block = memList->list;
   while ((block != NULL) && (doneStat == CSC_OK))
      {
      if (block->sig_lo != MEM_SIG) doneStat = CSC_CORRUPT;
      if (block->sig_hi != MEM_SIG) doneStat = CSC_CORRUPT;
      block = block->succ;
      }
   }
   if (doneStat == CSC_OK)
#endif
      {
      S_memBlockType*   block = memList->list;
      S_memBlockType*   next;
      while (block != NULL)
         {
         next = block->succ;
         if (block->deleted == CSC_FALSE)
            {
#ifdef	DEBUG
            (void)memset (block->data, GARBAGE_DATA, block->size);
#endif
            (void)CSC_FREE_FUNC (block->data);
            }
#ifdef	DEBUG
         (void)memset (block, GARBAGE_DATA, sizeof(S_memBlockType));
#endif
         (void)CSC_FREE_FUNC (block);
         block = next;
         }
      {
      CSCmonFnType   monFunc  = memList->monFunc;
      void*          monData  = memList->monData;
#ifdef	DEBUG
      (void)memset (memList, GARBAGE_DATA, sizeof(memList)); /* scribble */
#endif
      (void)CSC_FREE_FUNC (memList);
      if (monFunc != NULL) (*monFunc) (CSC_OUT, monData);
      }
      }

   return (doneStat);
   }


/***************************************************************************
 * Public Function CSCmemAlloc
 ***************************************************************************

<SUBROUTINE NAME="CSCmemAlloc">

NAME
        CSCmemAlloc - allocate memory (and keep thrack of it in memList)

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemAlloc (
                          CSCmemListType   const memList,
                          void**           const memPtrPtr,
                          size_t                 itemCount,
                          size_t                 itemSize,
                          int                    tagData
                          );

RETURN VALUE
        CSC_OK ......... successful

        RTS_NOMEM ...... if no memory can be dynamically allocated

        CSC_BADARG ..... memList or memPtrPtr is NULL or itemCount or itemSize
                         is zero

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemAlloc() is compiled with DEBUG

DESCRIPTION
        CSCmemAlloc() allocates memory; the number of bytes that are allocated
        is `itemCount' multiplied by `itemSize'.

        Multiple calls to CSCmemAlloc() can use the same `memList'; each
        allocated memory block will be put into `memList' and CSCmemFree() can
        be called with `memList' to free the block, or CSCmemListFree() can be
        called to free all the memory blocks in `memList'.

        NOTE    `memList' must first be created with CSCmemInit().

        If CSCmemAlloc() is compiled with DEBUG, then CSCmemAlloc() will fill
        newly allocated memory with some well-defined garbage to prevent the
        use of accidentally good values.

        `tagData' is provided for profiling `memList's. When profiling,
        `memList' continues to contain a record of the allocation and free of
        the memory; the list doesn't really get smaller (the actual memory
        allocations for client code are of course freed). `tagData' is an
        arbitrary integer that the caller supplies for easier identification
        when using CSCmemListPrintProfile() or CSCmemListWriteProfile() on
        `memList'.

EXAMPLE
        CSCmemListType   myList;
        void*            myData;
        int              mysize = 100;
        int              myTag  = 55;
        int              stat;

        myList = CSCmemInit ("my data", NULL, NULL, NULL, CSC_DO_PROFILING);
        stat = CSCmemAlloc (myList, &myData, 1, mySize, myTag);
           .
           .
           .
        stat = CSCmemFree (myList, &myData, myTag);

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemAlloc) (
                           CSCmemListType   const memList,
                           void**           const memPtrPtr,
                           size_t                 itemCount,
                           size_t                 itemSize,
                           int                    tagData
                           )
   {
   int      allocStat;
   size_t   allocSize = itemCount * itemSize;

   ASSERT_RTN (						\
              memList   != NULL,			\
              "CSCmemAlloc: NULL memList",		\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              memPtrPtr != NULL,			\
              "CSCmemAlloc: NULL memPtrPtr",		\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              allocSize != 0,				\
              "CSCmemAlloc: no allocation size",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              memList->sig_lo == MEM_SIG,		\
              "CSCmemAlloc: memList blows",		\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              memList->sig_hi == MEM_SIG,		\
              "CSCmemAlloc: memList blows",		\
              CSC_CORRUPT				\
              );

   if ((memList == NULL) || (memPtrPtr == NULL) || (allocSize == 0))
      {
      return (CSC_BADARG);
      }

   *memPtrPtr = (void*)CSC_MALLOC_FUNC (itemCount, itemSize);

   if (*memPtrPtr != NULL)
      {
      allocStat = CSC_OK;
#ifdef	DEBUG
      (void)memset (*memPtrPtr, GARBAGE_DATA, allocSize); /* scribble */
#else
      {
      /*
       * Force all pages into use. Some systems seem to not count for allocated
       * pages not yet used, which can lead to over allocating (Linux seems to
       * start whacking processes when there is no physical memory for an
       * allocated page).
       */
      size_t   i;
      size_t   pageSize = getpagesize();
      uint8*   p = (uint8*)*memPtrPtr;
      for (i = 0  ;  i <= allocSize  ;  i += pageSize)
         {
         p[i] = GARBAGE_DATA;
         }
      }
#endif
      {
      S_memBlockType*   block = blockNew (*memPtrPtr, allocSize, tagData);
      allocStat = blockPush (memList, block);
      if (allocStat != CSC_OK)
         {
         if (block != NULL) (void)CSC_FREE_FUNC (block);
         (void)CSC_FREE_FUNC (*memPtrPtr);
         *memPtrPtr = NULL;
         }
      }
      }
   else
      {
      allocStat = CSC_NOMEM;
      }

   return (allocStat);
   }


/***************************************************************************
 * Public Function CSCmemDup
 ***************************************************************************

<SUBROUTINE NAME="CSCmemDup">

NAME
        CSCmemDup - duplicate (dynamically allocate and copy) memory

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemDup (
                              CSCmemListType   const memList,
                              void**           const dstPtrPtr,
                        const void*                  srcPtr,
                              size_t                 size,
                              int                    tagData
                        );

RETURN VALUE
        CSC_OK ......... successful, the memory pointed to by memPtr is
                         duplicated

        CSC_BADARG ..... memList, dstPtrPtr, or srcPtr is NULL or size is zero

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemDup() is compiled with DEBUG

DESCRIPTION
        CSCmemDup() dynamically allocates `size' bytes and copies `size' bytes
        from `srcPtr' into the newly allocated memory.

        `tagData' is provided for profiling `memList's. When profiling,
        `memList' continues to contain a record of the allocation and free of
        the memory; the list doesn't really get smaller (the actual memory
        allocations for client code are of course freed). `tagData' is an
        arbitrary integer that the caller supplies for easier identification
        when using CSCmemListPrintProfile() or CSCmemListWriteProfile() on the
        `memList'.

        `srcPtr' can point to any readable memory. This may be usefull for
        creating dynamic duplicates of constant strings, etc.

EXAMPLE
        CSCmemListType   myList;
        void*            myData;
        int              stat;

        myList = CSCmemInit ("my data", NULL, NULL, NULL, CSC_DO_PROFILING);
           .
           .
           .
        stat = CSCmemDup (myList, &myData, "duplicate this string", 22, myTag);

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemDup) (
                               CSCmemListType   const memList,
                               void**           const dstPtrPtr,
                         const void*                  srcPtr,
                               size_t                 size,
                               int                    tagData
                         )
   {
   int   dupStat;

   ASSERT_RTN (memList   != NULL, "CSCmemDup: NULL memList",       CSC_BADARG);
   ASSERT_RTN (dstPtrPtr != NULL, "CSCmemDup: NULL dstPtrPtr",     CSC_BADARG);
   ASSERT_RTN (srcPtr    != NULL, "CSCmemDup: NULL srcPtr",        CSC_BADARG);
   ASSERT_RTN (size      != 0,    "CSCmemDup: no allocation size", CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemDup: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemDup: memList blows",	\
              CSC_CORRUPT			\
              );

#define	I_HAVE_A_BAD_ARGUMENT	(memList == NULL)   ||	\
				(dstPtrPtr == NULL) ||	\
				(srcPtr == NULL)    ||	\
				(size == 0)
   if (I_HAVE_A_BAD_ARGUMENT) return (CSC_BADARG);
#undef	I_HAVE_A_BAD_ARGUMENT

   dupStat = CSCmemAlloc (memList, dstPtrPtr, 1, size, tagData);
   if (dupStat == CSC_OK) (void)memcpy (*dstPtrPtr, srcPtr, size);

   return (dupStat);
   }


/***************************************************************************
 * Public Function CSCmemFree
 ***************************************************************************

<SUBROUTINE NAME="CSCmemFree">

NAME
        CSCmemFree - free dynamically allocated memory

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemFree (
                         CSCmemListType   const memList,
                         void**           const memPtrPtr,
                         int                    tagData
                         );

RETURN VALUE
        CSC_OK ......... successful, memPtr was found in memList, and the
                         memory pointed to by memPtr is freed

        CSC_NOTFOUND ... memPtr not found in memList, or memList has no
                         allocated blocks

        CSC_BADARG ..... memList or memPtrPtr is NULL

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemFree() is compiled with DEBUG

DESCRIPTION
        CSCmemFree() frees the dynamically allocated memory whose address is
        pointed to by `memPtr'. The memory to be freed is checked and validated
        in `memList'. If it is not found in `memList', then no memory is freed.

        Because of the `memList' usage, don't use CSCmemFree() on memory you got
        from malloc(), calloc(), etc.

        If CSCmemFree() is compiled with DEBUG, then the memory is shredded
        by writing well-defined garbage to it before it is freed. This avoids
        code that accidentally works by using deallocated memory that hasn't
        yet changed.

        `tagData' is provided for profiling `memList's. When profiling,
        `memList' continues to contain a record of the allocation and free of
        the memory; the list doesn't really get smaller (the actual memory
        allocations for client code are of course freed). `tagData' is an
        arbitrary integer that the caller supplies for easier identification
        when using CSCmemListPrintProfile() or CSCmemListWriteProfile() on the
        `memList'.

EXAMPLE
        CSCmemListType   myList;
        void*            myData;
        int              mysize = 100;
        int              myTag  = 55;
        int              stat;

        myList = CSCmemInit ("my data", NULL, NULL, NULL, CSC_DO_PROFILING);
        stat = CSCmemAlloc (myList, &myData, 1, mySize, myTag);
           .
           .
           .
        stat = CSCmemFree (myList, &myData, myTag);

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemFree) (
                          CSCmemListType   const memList,
                          void**           const memPtrPtr,
                          int                    tagData
                          )
   {
   int   freeStat;

   ASSERT_RTN (memList   != NULL, "CSCmemFree: NULL memList",   CSC_BADARG);
   ASSERT_RTN (memPtrPtr != NULL, "CSCmemFree: NULL memPtrPtr", CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemFree: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemFree: memList blows",	\
              CSC_CORRUPT			\
              );

   if ((memList == NULL) || (memPtrPtr == NULL)) return (CSC_BADARG);

   {
   size_t   size;
   freeStat = blockFindAndDel (memList, *memPtrPtr, tagData, &size);
   if (freeStat == CSC_OK)
      {
#ifdef	DEBUG
      (void)memset (*memPtrPtr, GARBAGE_DATA, size); /* scribble */
#endif
      (void)CSC_FREE_FUNC (*memPtrPtr);
      *memPtrPtr = NULL;
      }
   }

   return (freeStat);
   }


/***************************************************************************
 * Public Function CSCmemLookup
 ***************************************************************************

<SUBROUTINE NAME="CSCmemLookup">

NAME
        CSCmemLookup - lookup a memory pointer in memList

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemLookup (
                                 CSCmemListType   const memList,
                           const void*                  memPtr,
                                 size_t*          const sizePtr,
                                 int*             const tagPtr
                           );

RETURN VALUE
        CSC_OK ......... successful, memPtr was found in memList

        CSC_NOTFOUND ... memPtr not found in memList, or memList has no
                         allocated blocks

        CSC_BADARG ..... memList or memPtr is NULL

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemLookup() is compiled with DEBUG

DESCRIPTION
        CSCmemLookup() looks up `memPtr' in `memList' to validate it, and if
        found returns its statistics: size of the data block pointer to by
        `memPtr' and the tag that was used to allocate the block of memory
        pointed to by `memPtr'.

        If `sizePtr' is not NULL, then the size of the allocated memory block
        pointed to by `memPtr' is written to the size_t pointed to by `sizePtr'.

        If `tagPtr' is not NULL, then the tag that was used to allocate the
        block of memory pointed to by `memPtr' is written to the int pointed to
        by `tagPtr'.

        Either, or both, of `sizePtr' and `tagPtr' can be NULL. If both are
        NULL, then CSCmemLookup() pretty much acts like CSCmemValidate().

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemLookup) (
                                  CSCmemListType   const memList,
                            const void*                  memPtr,
                                  size_t*          const sizePtr,
                                  int*             const tagPtr
                            )
   {
   int               lookupStat = CSC_NOTFOUND;
   S_memBlockType*   block;
   S_memBlockType*   next;

   ASSERT_RTN (memList != NULL, "CSCmemLookup: NULL memList", CSC_BADARG);
   ASSERT_RTN (memPtr  != NULL, "CSCmemLookup: NULL memPtr",  CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemLookup: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemLookup: memList blows",	\
              CSC_CORRUPT			\
              );

   if ((memList == NULL) || (memPtr == NULL)) return (CSC_BADARG);

   MON_ENTER(memList);

   block = memList->list;
   while (block != NULL)
      {
#ifdef	DEBUG
      if ((block->sig_lo != MEM_SIG) || (block->sig_hi != MEM_SIG))
         {
         lookupStat = CSC_CORRUPT;
         next = NULL;
         }
      else
#endif
         {
         next = block->succ;
         if (block->data == memPtr)
            {
            if (block->deleted == CSC_FALSE)
               {
               lookupStat = CSC_OK;
               if (sizePtr != NULL) *sizePtr = block->size;
               if (tagPtr  != NULL) *tagPtr  = block->allocTag;
               }
            next = NULL;
            }
         }
      block = next;
      }

   MON_EXIT(memList);

   return (lookupStat);
   }


/***************************************************************************
 * Public Function CSCmemValidate
 ***************************************************************************

<SUBROUTINE NAME="CSCmemValidate">

NAME
        CSCmemValidate - validate that a memory pointer is in memList

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemValidate (
                                   CSCmemListType   const memList,
                             const void*                  memPtr
                             );

RETURN VALUE
        CSC_OK ......... successful, memPtr was found in memList

        CSC_NOTFOUND ... memPtr not found in memList, or memList has no
                         allocated blocks

        CSC_BADARG ..... memList is or memPtr NULL

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemValidate() is compiled with DEBUG

DESCRIPTION
        CSCmemValidate() looks up `memPtr' in `memList' to validate it.

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemValidate) (
                                    CSCmemListType   const memList,
                              const void*                  memPtr
                              )
   {
   int               validateStat = CSC_NOTFOUND;
   S_memBlockType*   block;
   S_memBlockType*   next;

   ASSERT_RTN (memList != NULL, "CSCmemValidate: NULL memList", CSC_BADARG);
   ASSERT_RTN (memPtr  != NULL, "CSCmemValidate: NULL memPtr",  CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemValidate: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemValidate: memList blows",	\
              CSC_CORRUPT			\
              );

   if ((memList == NULL) || (memPtr == NULL)) return (CSC_BADARG);

   MON_ENTER(memList);

   block = memList->list;
   while (block != NULL)
      {
#ifdef	DEBUG
      if ((block->sig_lo != MEM_SIG) || (block->sig_hi != MEM_SIG))
         {
         validateStat = CSC_CORRUPT;
         next = NULL;
         }
      else
#endif
         {
         next = block->succ;
         if (block->data == memPtr)
            {
            if (block->deleted == CSC_FALSE) validateStat = CSC_OK;
            next = NULL;
            }
         }
      block = next;
      }

   MON_EXIT(memList);

   return (validateStat);
   }


/***************************************************************************
 * Public Function CSCmemListFree
 ***************************************************************************

<SUBROUTINE NAME="CSCmemListFree">

NAME
        CSCmemListFree - free all memory allocated in a memList

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemListFree (
                             CSCmemListType   const memList,
                             int                    tagData
                             );

RETURN VALUE
        CSC_OK ......... successful

        CSC_NOTFOUND ... memList has no allocated blocks

        CSC_BADARG ..... memList is NULL

        CSC_CORRUPT .... corruption is detected in memList
                         and CSCmemListFree() is compiled with DEBUG

DESCRIPTION
        CSCmemListFree() frees all the memory described by `memList'. This is
        memory allocations for client code that was allocated by using `memList'
        with functions like CSCmemAlloc(). The actual `memList' itself is not
        freed.

        CSCmemListFree() is a convenient mechanism to free many allocations of
        memory with a single function.

        `tagData' is provided for profiling `memList's. When profiling, the
        `memList' continues to contain a record of the allocation and free of
        the memory; the list doesn't really get smaller (the actual memory
        allocations for client code are of course freed). `tagData' is an
        arbitrary integer that the caller supplies for easier identification
        when using CSCmemListPrintProfile() or CSCmemListWriteProfile() on the
        `memList'.

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemListFree) (
                              CSCmemListType   const memList,
                              int                    tagData
                              )
   {
   int   freeStat = CSC_OK;

   ASSERT_RTN (memList != NULL, "CSCmemListFree: NULL memList", CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemListFree: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemListFree: memList blows",	\
              CSC_CORRUPT			\
              );

   if (memList == NULL) return (CSC_BADARG);

   MON_ENTER(memList);

   if (memList->list == NULL) freeStat = CSC_NOTFOUND;

#ifdef	DEBUG
   {
   S_memBlockType*   block = memList->list;
   while ((block != NULL) && (freeStat == CSC_OK))
      {
      if (block->sig_lo != MEM_SIG) freeStat = CSC_CORRUPT;
      if (block->sig_hi != MEM_SIG) freeStat = CSC_CORRUPT;
      block = block->succ;
      }
   }
   if (freeStat == CSC_OK)
#else
   else
#endif
      {
      S_memBlockType*   block = memList->list;
      S_memBlockType*   next;
      void*             data;
      size_t            size;
      while (block != NULL)
         {
         next = block->succ;
         if (block->deleted == CSC_FALSE)
            {
            data = block->data;
            size = block->size;
            freeStat = blockDel (memList, block, tagData);
            if (freeStat == CSC_OK)
               {
#ifdef	DEBUG
               (void)memset (data, GARBAGE_DATA, size); /* scribble */
#endif
               (void)CSC_FREE_FUNC (data);
               }
            else
               next = NULL;
            }
         block = next;
         }
      }

   MON_EXIT(memList);

   return (freeStat);
   }


/***************************************************************************
 * Public Function CSCmemListStat
 ***************************************************************************

<SUBROUTINE NAME="CSCmemListStat">

NAME
        CSCmemListStat - get information about a memList

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemListStat (
                             CSCmemListType   const memList,
                             size_t*          const allocCountPtr,
                             size_t*          const freeCountPtr,
                             size_t*          const maxMemAllocPtr,
                             size_t*          const curMemAllocPtr
                             );

RETURN VALUE
        CSC_OK ............. successful

        CSC_NO_PROFILING ... memList is not profiling

        CSC_BADARG ......... memList is NULL

        CSC_CORRUPT ........ corruption is detected in memList
                             and CSCmemListStat() is compiled with DEBUG

DESCRIPTION
        CSCmemListStat() can return the allocate count, free count, current
        allocating, and highest allocation from `memList', if `memList' was
        specified when it was created by CSCmemInit() to be profiling.

        When profiling:

                If `allocCountPtr' is not NULL, then CSCmemListStat() writes to
                the size_t pointed to by `allocCountPtr' the total number of
                allocates.

                If `freeCountPtr' is not NULL, then CSCmemListStat() writes to
                the size_t pointed to by `freeCountPtr' the total number of
                frees.

                If `maxMemAllocPtr' is not NULL, then CSCmemListStat() writes to
                the size_t pointed to by `maxMemAllocPtr' the number of bytes
                ever allocated at one time.

                If `curMemAllocPtr' is not NULL, then CSCmemListStat() writes to
                the size_t pointed to by `curMemAllocPtr' the number of
                currently allocated bytes.

        CSCmemListStat() can be used to determine if `memList' is profiling by
        using NULL for all of `allocCountPtr', `freeCountPtr', `maxMemAllocPtr',
        and `curMemAllocPtr'. CSC_NO_PROFILING is returned if `memList' is not
        profiling and CSC_OK is returned if `memList' is profiling.

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListPrintProfile(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemListStat) (
                              CSCmemListType   const memList,
                              size_t*          const allocCountPtr,
                              size_t*          const freeCountPtr,
                              size_t*          const maxMemAllocPtr,
                              size_t*          const curMemAllocPtr
                              )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (memList != NULL, "CSCmemListStat: NULL memList", CSC_BADARG);

   ASSERT_RTN (					\
              memList->sig_lo == MEM_SIG,	\
              "CSCmemListStat: memList blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              memList->sig_hi == MEM_SIG,	\
              "CSCmemListStat: memList blows",	\
              CSC_CORRUPT			\
              );

   if (memList == NULL) return (CSC_BADARG);

   MON_ENTER(memList);

   if (memList->profiling == CSC_DO_PROFILING)
      {
      if (allocCountPtr  != NULL) *allocCountPtr  = memList->allocCount;
      if (freeCountPtr   != NULL) *freeCountPtr   = memList->freeCount;
      if (maxMemAllocPtr != NULL) *maxMemAllocPtr = memList->curAlloc;
      if (curMemAllocPtr != NULL) *curMemAllocPtr = memList->maxAlloc;
      }
   else
      statStat = CSC_NO_PROFILING;

   MON_EXIT(memList);

   return (statStat);
   }


/***************************************************************************
 * Public Function CSCmemListPrintProfile
 ***************************************************************************

<SUBROUTINE NAME="CSCmemListPrintProfile">

NAME
        CSCmemListPrintProfile - write a memlist profile to standard output

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemListPrintProfile (
                                     CSCmemListType   const memList,
                                     CSCprofileType         showing
                                     );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... memList is NULL

        CSC_CORRUPT ... corruption is detected in memList
                        and CSCmemListWriteProfile() is compiled with DEBUG

DESCRIPTION
        CSCmemListPrintProfile() writes to standard output the information of
        the dynamically allocated memory blocks that are described in `memList'.

        CSCmemListPrintProfile() calls CSCmemListWriteProfile() to do the work;
        so, go read about CSCmemListWriteProfile().

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListWriteProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemListPrintProfile) (
                                      CSCmemListType   const memList,
                                      CSCprofileType         showing
                                      )
   {
   int   printStat = CSC_NOTFOUND;

   ASSERT_RTN (						\
              memList != NULL,				\
              "CSCmemListPrintProfile: NULL memList",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              memList->sig_lo == MEM_SIG,		\
              "CSCmemListPrintProfile: memList blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              memList->sig_hi == MEM_SIG,		\
              "CSCmemListPrintProfile: memList blows",	\
              CSC_CORRUPT				\
              );

   if (memList == NULL) return (CSC_BADARG);

   printStat = CSCmemListWriteProfile (memList, STDOUT_FILENO, showing);

   return (printStat);
   }


/***************************************************************************
 * Public Function CSCmemListWriteProfile
 ***************************************************************************

<SUBROUTINE NAME="CSCmemListWriteProfile">

NAME
        CSCmemListWriteProfile - write a memlist profile to a file descriptor

SYNOPSYS
        #include "libcsc.h"

        int   CSCmemListWriteProfile (
                                     CSCmemListType   const memList,
                                     int                    fd,
                                     CSCprofileType         showing
                                     );

RETURN VALUE
        CSC_OK ........ successful

        CSC_BADARG .... memList is NULL

        CSC_CORRUPT ... corruption is detected in memList
                        and CSCmemListWriteProfile() is compiled with DEBUG

DESCRIPTION
        CSCmemListWriteProfile() writes to `fd' the information of the
        dynamically allocated memory blocks that are described in `memList'.

        Use CSCmemListWriteProfile() and CSCmemListPrintProfile() to verify that
        there are no memory leaks.

        This information written by CSCmemListWriteProfile() begins with a
        header of the name, tag function, monitor function, and profiling as
        specified when `memList' was created by CSCmemInit(). If `memList' was
        specified when it was created by CSCmemInit() to be profiling, then the
        allocate count, free count, current allocating, and highest allocation
        are included in the header information.

        If `showing' is CSC_SHOW_ALL, then a list of allocationed/freeed blocks
        follows the header. The unfreed memory allocations are described by data
        address, size, and the allocate tag provided by the client code that
        called CSCmemAlloc(). If `memList' was specified to be profiling, then
        freed memory alocations remain in the list. In this case they will be
        included in this list of information but there is no data address and
        size, only an allocate tag and a free tag.

        If `showing' is CSC_SHOW_ALLOCATED, then only allocated blocks are
        shown.

SEE ALSO
        CSCmemInit(3)
        CSCmemDone(3)
        CSCmemAlloc(3)
        CSCmemDup(3)
        CSCmemFree(3)
        CSCmemLookup(3)
        CSCmemValidate(3)
        CSCmemListFree(3)
        CSCmemListStat(3)
        CSCmemListPrintProfile(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCmemListWriteProfile) (
                                      CSCmemListType   const memList,
                                      int                    fd,
                                      CSCprofileType         showing
                                      )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (						\
              memList != NULL,				\
              "CSCmemListWriteProfile: NULL memList",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              (showing==CSC_SHOW_ALL)||(showing==CSC_SHOW_ALLOCATED),\
              "CSCmemListWriteProfile: showing is bad",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              memList->sig_lo == MEM_SIG,		\
              "CSCmemListWriteProfile: memList blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              memList->sig_hi == MEM_SIG,		\
              "CSCmemListWriteProfile: memList blows",	\
              CSC_CORRUPT				\
              );

   if (memList == NULL) return (CSC_BADARG);
   if ((showing != CSC_SHOW_ALL) && (showing != CSC_SHOW_ALLOCATED))
      {
      return (CSC_BADARG);
      }

   MON_ENTER(memList);

(void)write (fd, "\nmemlist Profile\n---------------\n", 33);
(void)write (fd, "              name: ", 20); (void)mlWriteName (fd, memList);
(void)write (fd, "      tag function: ", 20); (void)mlWriteTfnc (fd, memList);
(void)write (fd, "  monitor function: ", 20); (void)mlWriteMfnc (fd, memList);
(void)write (fd, "         profiling: ", 20); (void)mlWriteProf (fd, memList);

   if (memList->profiling == CSC_DO_PROFILING)
      {
(void)write (fd, "    allocate count: ", 20); (void)mlWriteAlloc (fd, memList);
(void)write (fd, "        free count: ", 20); (void)mlWriteFreed (fd, memList);
(void)write (fd, "current allocation: ", 20); (void)mlWriteCurAl (fd, memList);
(void)write (fd, "highest allocation: ", 20); (void)mlWriteMaxAl (fd, memList);
      }

   (void)write (fd, "\n", 1);

   {
   char              numbuf[NUMBUF_SIZE];
   S_memBlockType*   block      = memList->list;
   int               blockCount = 1;
   while (block != NULL)
      {
      if ((showing == CSC_SHOW_ALL) || (block->deleted == CSC_FALSE))
         {
         (void)write (fd, "block #", 7);
         (void)sprintf (numbuf, "%d\n", blockCount);
         (void)write (fd, numbuf, strlen(numbuf));
         (void)blockWriteProfile (memList, fd, block);
         }
      block = block->succ;
      blockCount += 1;
      }
   }

   MON_EXIT(memList);

   return (statStat);
   }


/* End of file. */
