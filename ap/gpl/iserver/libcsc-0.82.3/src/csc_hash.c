/* *****************************************************************************

libcsc:  Hash Table Subsystem

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

	$RCSfile: csc_hash.c,v $
	$Revision: 1.4 $
	$Date: 2003/03/26 02:03:23 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_hash">

NAME
	csc_hash

DESCRIPTION
	Hash table Subsystem

FUNCTIONS
	CSChashNew       - create a new libcsc hash table
	CSChashDel       - remove a libcsc hash table
	CSChashStat      - query statistics of a libcsc hash table
	CSChashEntryPut  - put an entry into a libcsc hash table
	CSChashEntryGet  - get an item from a libcsc hash table
	CSChashEntryDel  - remove an entry from a libcsc hash table
	CSChashEntryNext - find next entry in a libcsc hash table
	CSChashEntryStat - query the fields of a libcsc hash table entry
	CSChashRead      - read an ASCII format libcsc hash table
	CSChashWrite     - write a libcsc hash table in an ASCII format
	CSChashDump      - write a formatted dump of a libcsc hash table
</SUBSYSTEM>

CHANGE LOG

	25mar03	drj	Fixed bucket allocation problem in initHashTab().
			Corrected previous improvement in CSChashEntryGet().

	23mar03	drj	Added a CSCmemListType argument to CSChashEntryGet().

	22apr02	drj	Added internal documentation.

	13apr02	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Tracked changes to rtsMem*.

	15apr00	drj	Moved the hash union structure definition into rts.h.
			Made the hash structures more opaque and simplified the
			functions that returns pointers.
			Fixed buggy rebuild.
			Fixed buggy entry deletion.
			Fixed up unused stats in rtsHashWrite.
			Fixed bug in rtsHashEntryGet().

	28nov99	drj	Fixed bug in rtsHashEntryNext(); bad return value.
			Added more output text to rtsHashWrite().  Fixed up
			rtsHashWrite() to not crash with empty hash tables.
			Fixed rtsHashNew() to accept zero size indicating a
			growing hash table.

	26nov99	drj	Fixed bug in rtsHashEntryPut(); address operator
			missing.

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

#define	HASH_SIG		(0x48415348)

#define	PRED(x)			((x)->pred)
#define	SUCC(x)			((x)->succ)

#define	COSMOLOGICAL_CONSTANT	(7)
#define	CSC_HASH_GROWS		(0)

#define MON_ENTER(x)    {if(x->monFunc!=NULL)(*x->monFunc)\
			(CSC_IN,(void*)x->monData);}

#define MON_EXIT(x)     {if(x->monFunc!=NULL)(*x->monFunc)\
			(CSC_OUT,(void*)x->monData);}


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

typedef   unsigned long   CSChashType;


/* ************************************************************************* */
/*                                                                           */
/*      N o n - S c a l a r   D a t a   S t r u c t u r e s                  */
/*                                                                           */
/* ************************************************************************* */

typedef struct S_hashEntryType
   {
#ifdef	DEBUG
          long               sig_lo;
#endif
   struct S_hashEntryType*   succ;
   struct S_hashEntryType*   pred;
          S_hashKeyUnion     key;
          void*              data;
          size_t             size;
#ifdef	DEBUG
          long               sig_hi;
#endif
   } S_hashEntryType;

typedef struct S_hashTableType
   {
#ifdef	DEBUG
   long                sig_lo;
#endif
   const char*         name;
   S_hashEntryType**   hash;
   CSChashKeyType      keySpec;
   CSCmemListType      memLst;
   CSCmonFnType        monFunc;
   const void*         monData;
   CSCprofileType      profiling;
   size_t              count;
   size_t              nhash;
   CSCboolean          grows;
   unsigned long       downShift;
   unsigned long       mask;
   size_t              resizes;
   size_t              deletions;
   size_t              insertions;
   size_t              collisions;
#ifdef	DEBUG
   long                sig_hi;
#endif
   } S_hashTableType;


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

PRIVATE CSChashType   CSChashStr (
                                 const size_t         nhash,
                                 const char*    const keyPtr
                                 );

PRIVATE int   CSChash (
                       const CSChashKeyUnion*  const keyPtr,
                       const CSChashTableType        hashTablePtr,
                             CSChashType*      const hashValPtr
                       );

PRIVATE int   hashMatch (
                        const CSChashKeyType           keySpec,
                        const CSChashKeyUnion*   const key1Ptr,
                        const CSChashKeyUnion*   const key2Ptr
                        );

PRIVATE int   initHashTab (
                                CSChashTableType   const hashTablePtr,
                          const CSChashKeyType           keySpec,
                          const size_t                   size
                          );

PRIVATE int   clearHashTab (
                           const CSChashTableType   hashTablePtr
                           );

PRIVATE int   hashEntryNew (
                                 CSChashEntryType*   const entryPtrPtr,
                                 CSCmemListType      const memLst,
                           const CSChashKeyType            keySpec,
                           const CSChashKeyUnion*    const keyPtr,
                           const void*               const itemPtr,
                           const size_t                    itemSize
                           );

PRIVATE int   hashEntryDel (
                                 CSChashEntryType   const oldEntryPtr,
                                 CSCmemListType     const memLst,
                           const CSChashKeyType           keySpec
                           );

PRIVATE int   hashLinkAdd (
                          CSChashEntryType*   const hashListPtrPtr,
                          CSChashEntryType    const newEntryPtr
                          );

PRIVATE int   hashLinkSub (
                          CSChashEntryType*   const hashListPtrPtr,
                          CSChashEntryType    const oldEntryPtr
                          );

PRIVATE int   hashEntryFind (
                            const CSChashEntryType          hashListPtr,
                            const CSChashKeyUnion*    const keyPtr,
                            const CSChashKeyType            keySpec,
                                  CSChashEntryType*   const hashEntryPtrPtr,
                                  void**              const itemPtrPtr,
                                  size_t*             const itemSizePtr
                            );

PRIVATE int   rebuild (
                      const CSChashTableType   hashTablePtr
                      );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function CSChashStr
 **************************************************************************/

PRIVATE CSChashType   CSChashStr (
                                 const size_t         nhash,
                                 const char*    const keyPtr
                                 )
   {
   CSChashType   hashVal;
   CSChashType   hashG;
   char*         bufPtr;
   char          ch;
   int           index;

   ASSERT_RTN (keyPtr != NULL, "CSChashStr: null keyPtr", 0);

   hashVal = 0;
   for  ( bufPtr = (char*) keyPtr, index = 1  ;  (ch = *bufPtr++)  ;  index++ )
      {
      hashVal = (hashVal << 4) + ((CSChashType)ch * 13);
      if ((hashG = hashVal & 0xF0000000))
         {
         hashVal = hashVal ^ (hashG >> 24);
         hashVal = hashVal ^ hashG;
         }
      }
   hashVal %= (CSChashType)nhash;

   return (hashVal);
   }


/**************************************************************************
 * Private Function CSChash
 **************************************************************************/

PRIVATE int   CSChash (
                      const CSChashKeyUnion*   const keyPtr,
                      const CSChashTableType         hashTablePtr,
                            CSChashType*       const hashValuePtr
                      )
   {
   int           hashStat = CSC_OK;
   CSChashType   tmpHash  = 0;

   ASSERT_RTN (keyPtr != NULL,       "CSChash: null keyPtr",       CSC_BADARG);
   ASSERT_RTN (hashTablePtr != NULL, "CSChash: null hashTablePtr", CSC_BADARG);
   ASSERT_RTN (hashValuePtr != NULL, "CSChash: null hashTablePtr", CSC_BADARG);

   switch (hashTablePtr->keySpec)
      {
      default:
         hashStat = CSC_CORRUPT;
         break;

      case CSC_HASH_ASCIIZ_KEY:
         tmpHash = CSChashStr (hashTablePtr->nhash, keyPtr->asciiz);
         break;

      case CSC_HASH_INT32_KEY:
         tmpHash = ((long)(keyPtr->integer) * 1103515245L);
         tmpHash = tmpHash >> hashTablePtr->downShift;
         tmpHash = tmpHash & hashTablePtr->mask;
         break;
      }

   if (hashStat == CSC_OK) *hashValuePtr = tmpHash;

   return (hashStat);
   }


/**************************************************************************
 * Private Function hashMatch
 **************************************************************************/

PRIVATE int   hashMatch (
                        const CSChashKeyType           keySpec,
                        const CSChashKeyUnion*   const key1Ptr,
                        const CSChashKeyUnion*   const key2Ptr
                        )
   {
   int   matchStat = CSC_NOTFOUND;

   ASSERT_RTN (key1Ptr != NULL, "hashMatch: null key1Ptr", CSC_BADARG);
   ASSERT_RTN (key2Ptr != NULL, "hashMatch: null key2Ptr", CSC_BADARG);

   switch (keySpec)
      {
      default:
         matchStat = CSC_CORRUPT;
         break;

      case CSC_HASH_ASCIIZ_KEY:
         if (CSC_STREQ(key1Ptr->asciiz,key2Ptr->asciiz)) matchStat = CSC_OK;
         break;

      case CSC_HASH_INT32_KEY:
         if (key1Ptr->integer == key2Ptr->integer) matchStat = CSC_OK;
         break;
      }

   return (matchStat);
   }


/**************************************************************************
 * Private Function initHashTab
 **************************************************************************/

PRIVATE int   initHashTab (
                                CSChashTableType   const hashTable,
                          const CSChashKeyType           keySpec,
                          const size_t                   size
                          )
   {
   int   initStat = CSC_OK;
   int   tableSize;
   int   index;

   ASSERT_RTN (hashTable != NULL, "initHashTab: null hashTab", CSC_BADARG);
   ASSERT_RTN (								\
              keySpec==CSC_HASH_ASCIIZ_KEY || keySpec==CSC_HASH_INT32_KEY,\
              "initHashTab: invalid keySpec",				\
              CSC_BADARG						\
              );

   hashTable->hash         = NULL;
   hashTable->keySpec      = -1;
   hashTable->count        = -1;
   hashTable->nhash        = -1;
   hashTable->resizes      = -1;
   hashTable->deletions    = -1;
   hashTable->insertions   = -1;
   hashTable->collisions   = -1;
   hashTable->grows        = CSC_INDETERMINATE;
   hashTable->downShift    = -1;
   hashTable->mask         = -1;

   if (size == CSC_HASH_GROWS)
      tableSize = (int)4;
   else
      tableSize = (int)size;

   initStat = CSCmemAlloc (
                          hashTable->memLst,
                          (void**)&hashTable->hash,
                          tableSize,
                          sizeof(S_hashEntryType),
                          0
                          );

   if (initStat == CSC_OK)
      {
      for  ( index = 0  ;  index < tableSize  ;  index++ )
         {
         hashTable->hash[index] = NULL;
         }
      hashTable->keySpec      = keySpec;
      hashTable->count        = 0;
      hashTable->nhash        = tableSize;
      hashTable->resizes      = 0;
      hashTable->deletions    = 0;
      hashTable->insertions   = 0;
      hashTable->collisions   = 0;
      if (size == CSC_HASH_GROWS)
         {
         hashTable->grows     = CSC_TRUE;
         hashTable->downShift = 28;
         hashTable->mask      = 3;
         }
      else
         {
         hashTable->grows = CSC_FALSE;
         }
      }
   else
      {
      hashTable->hash   = NULL;
      hashTable->memLst = NULL;
      initStat = CSC_NOMEM;
      }

   return (initStat);
   }


/**************************************************************************
 * Private Function clearHashTab
 **************************************************************************/

PRIVATE int   clearHashTab (
                           CSChashTableType   const hashTable
                           )
   {
   int   clrStat = CSC_OK;

   ASSERT_RTN (hashTable != NULL, "clearHashTab: null hashTable", CSC_BADARG);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "clearHashTab: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "clearHashTab: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );

   ASSERT (hashTable->hash != NULL);
   (void)CSCmemFree (hashTable->memLst, (void**)&hashTable->hash, 0);

   hashTable->hash         = NULL;
   hashTable->keySpec      = -1;
   hashTable->count        = -1;
   hashTable->nhash        = -1;
   hashTable->resizes      = -1;
   hashTable->deletions    = -1;
   hashTable->insertions   = -1;
   hashTable->collisions   = -1;
   hashTable->grows        = CSC_INDETERMINATE;
   hashTable->downShift    = -1;
   hashTable->mask         = -1;

   return (clrStat);
   }


/**************************************************************************
 * Private Function hashEntryNew
 **************************************************************************/

PRIVATE int   hashEntryNew (
                                 CSChashEntryType*    const entryPtrPtr,
                                 CSCmemListType       const memLst,
                           const CSChashKeyType             keySpec,
                           const CSChashKeyUnion*     const keyPtr,
                           const void*                const itemPtr,
                           const size_t                     itemSize
                           )
   {
   int                newStat     = CSC_OK;
   CSChashEntryType   newEntryPtr = NULL;

   ASSERT_RTN (entryPtrPtr!=NULL, "hashEntryNew: null entryPtrPtr", CSC_BADARG);
   ASSERT_RTN (keyPtr != NULL,    "hashEntryNew: null keyPtr",      CSC_BADARG);
   ASSERT_RTN (itemPtr != NULL,   "hashEntryNew: null itemPtr",     CSC_BADARG);
   ASSERT_RTN (itemSize > 0,      "hashEntryNew: no itemSize",      CSC_BADARG);
   ASSERT_RTN (								\
              keySpec==CSC_HASH_ASCIIZ_KEY || keySpec==CSC_HASH_INT32_KEY,\
              "hashEntryNew: invalid keySpec",				\
              CSC_BADARG						\
              );

   newStat = CSCmemAlloc (
                         memLst,
                         (void**)&newEntryPtr,
                         1,
                         sizeof(S_hashEntryType),
                         0
                         );

   if (newStat == CSC_OK)
      {
      newEntryPtr->pred = NULL;
      newEntryPtr->succ = NULL;
      newEntryPtr->size = itemSize;
#ifdef	DEBUG
      newEntryPtr->sig_lo = HASH_SIG;
      newEntryPtr->sig_hi = HASH_SIG;
#endif

      (void)CSCmemDup (
                      memLst, (void**)&newEntryPtr->data, itemPtr, itemSize, 0
                      );
      if (newEntryPtr->data != NULL)
         {
         switch (keySpec)
            {
            default:
               (void)CSCmemFree (memLst, (void**)&newEntryPtr->data, 0);
               (void)CSCmemFree (memLst, (void**)&newEntryPtr, 0);
               newStat = CSC_BADARG;
               break;

            case CSC_HASH_ASCIIZ_KEY:
               (void)CSCmemDup (
                               memLst,
                               (void**)&newEntryPtr->key.asciiz,
                               keyPtr->asciiz,
                               strlen(keyPtr->asciiz)+1,
                               0
                               );
               if (newEntryPtr->key.asciiz == NULL)
                  {
                  (void)CSCmemFree (memLst, (void**)&newEntryPtr->data, 0);
                  (void)CSCmemFree (memLst, (void**)&newEntryPtr, 0);
                  newStat = CSC_NOMEM;
                  }
               break;

            case CSC_HASH_INT32_KEY:
               newEntryPtr->key.integer = keyPtr->integer;
               break;
            }
         *entryPtrPtr = newEntryPtr;
         }
      else
         {
         (void)CSCmemFree (memLst, (void**)&newEntryPtr, 0);
         newStat = CSC_NOMEM;
         }
      }

   return (newStat);
   }


/**************************************************************************
 * Private Function hashEntryDel
 **************************************************************************/

PRIVATE int   hashEntryDel (
                                 CSChashEntryType   const oldEntry,
                                 CSCmemListType     const memLst,
                           const CSChashKeyType           keySpec
                           )
   {
   int   delStat  = CSC_OK;

   ASSERT_RTN (oldEntry != NULL, "hashEntryDel: null oldEntry", CSC_BADARG);
   ASSERT_RTN (							\
              oldEntry->sig_lo == HASH_SIG,			\
              "hashEntryDel: bad signature in oldEntry",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              oldEntry->sig_hi == HASH_SIG,			\
              "hashEntryDel: bad signature in oldEntry",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              keySpec==CSC_HASH_ASCIIZ_KEY || keySpec==CSC_HASH_INT32_KEY,\
              "hashEntryDel: invalid keySpec",			\
              CSC_BADARG					\
              );

   if (oldEntry != NULL)
      {
      ASSERT (oldEntry->data != NULL);
      (void)CSCmemFree (memLst, (void**)&oldEntry->data, 0);
      if (keySpec == CSC_HASH_ASCIIZ_KEY)
         {
         ASSERT (oldEntry->key.asciiz != NULL);
         (void)CSCmemFree (memLst, (void**)&oldEntry->key.asciiz, 0);
         }
      (void)CSCmemFree (memLst, (void**)&oldEntry, 0);
      }
   else
      {
      delStat = CSC_NOTFOUND;
      }

   return (delStat);
   }


/**************************************************************************
 * Private Function hashLinkAdd
 **************************************************************************/

PRIVATE int   hashLinkAdd (
                          CSChashEntryType*   const hashListPtrPtr,
                          CSChashEntryType    const newEntryPtr
                          )
   {
   int   addStat = CSC_OK;

   ASSERT_RTN (							\
              hashListPtrPtr != NULL,				\
              "hashLinkAdd: null hashListPtrPtr",		\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              newEntryPtr != NULL,				\
              "hashLinkAdd: null newEntryPtr",			\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              newEntryPtr->sig_lo == HASH_SIG,			\
              "hashLinkAdd: bad signature in newEntryPtr",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              newEntryPtr->sig_hi == HASH_SIG,			\
              "hashLinkAdd: bad signature in newEntryPtr",	\
              CSC_CORRUPT					\
              );

   if (*hashListPtrPtr != NULL)
      {
      ASSERT_RTN (						\
                 (*hashListPtrPtr)->sig_lo == HASH_SIG,		\
                 "hashLinkAdd: bad signature in hash",		\
                 CSC_CORRUPT					\
                 );
      ASSERT_RTN (						\
                 (*hashListPtrPtr)->sig_hi == HASH_SIG,		\
                 "hashLinkAdd: bad signature in hash",		\
                 CSC_CORRUPT					\
                 );
      PRED(*hashListPtrPtr) = newEntryPtr;
      SUCC(newEntryPtr) = *hashListPtrPtr;
      }
   *hashListPtrPtr = newEntryPtr;

   return (addStat);
   }


/**************************************************************************
 * Private Function hashLinkSub
 **************************************************************************/

PRIVATE int   hashLinkSub (
                          CSChashEntryType*   const hashListPtrPtr,
                          CSChashEntryType    const oldEntryPtr
                          )
   {
   int   subStat = CSC_OK;

   ASSERT_RTN (							\
              hashListPtrPtr != NULL,				\
              "hashLinkSub: null hashListPtrPtr",		\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              oldEntryPtr != NULL,				\
              "hashLinkSub: null oldEntryPtr",			\
              CSC_BADARG					\
              );
   ASSERT_RTN (							\
              oldEntryPtr->sig_lo == HASH_SIG,			\
              "hashLinkSub: bad signature in oldEntryPtr",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              oldEntryPtr->sig_hi == HASH_SIG,			\
              "hashLinkSub: bad signature in oldEntryPtr",	\
              CSC_CORRUPT					\
              );

   if (oldEntryPtr == *hashListPtrPtr)
      {
      /* -- DE-LINK FIRST ENTRY --  */
      /* -- DE-LINK SINGLE ENTRY -- */
      *hashListPtrPtr = SUCC(oldEntryPtr);
      if (*hashListPtrPtr != NULL)
         PRED(*hashListPtrPtr) = NULL;
      }
   else
      {
      if (SUCC(oldEntryPtr) == NULL)
         {
         /* -- DE-LINK LAST ENTRY -- */
         ASSERT_RTN (							\
                    (PRED(oldEntryPtr))->sig_lo == HASH_SIG,		\
                    "hashLinkSub: bad signature in PRED(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         ASSERT_RTN (							\
                    (PRED(oldEntryPtr))->sig_hi == HASH_SIG,		\
                    "hashLinkSub: bad signature in PRED(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         SUCC(PRED(oldEntryPtr)) = NULL;
         }
      else
         {
         /* -- DE-LINK INNER ENTRY -- */
         ASSERT_RTN (							\
                    (PRED(oldEntryPtr))->sig_lo == HASH_SIG,		\
                    "hashLinkSub: bad signature in PRED(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         ASSERT_RTN (							\
                    (PRED(oldEntryPtr))->sig_hi == HASH_SIG,		\
                    "hashLinkSub: bad signature in PRED(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         ASSERT_RTN (							\
                    (SUCC(oldEntryPtr))->sig_lo == HASH_SIG,		\
                    "hashLinkSub: bad signature in SUCC(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         ASSERT_RTN (							\
                    (SUCC(oldEntryPtr))->sig_hi == HASH_SIG,		\
                    "hashLinkSub: bad signature in SUCC(oldEntryPtr)",	\
                    CSC_CORRUPT						\
                    );
         SUCC(PRED(oldEntryPtr)) = SUCC(oldEntryPtr);
         PRED(SUCC(oldEntryPtr)) = PRED(oldEntryPtr);
         }
      }

   return (subStat);
   }


/**************************************************************************
 * Private Function hashEntryFind
 **************************************************************************/

PRIVATE int   hashEntryFind (
                            const CSChashEntryType          hashListPtr,
                            const CSChashKeyUnion*    const keyPtr,
                            const CSChashKeyType            keySpec,
                                  CSChashEntryType*   const hashEntryPtrPtr,
                                  void**              const itemPtrPtr,
                                  size_t*             const itemSizePtr
                            )
   {
   int                findStat = CSC_NOTFOUND;
   CSChashEntryType   entryPtr = NULL;

   entryPtr = (CSChashEntryType)hashListPtr;
   while ((entryPtr != NULL) && (findStat == CSC_NOTFOUND))
      {
      ASSERT_RTN (						\
                 entryPtr->sig_lo == HASH_SIG,			\
                 "hashEntryFind: bad signature in entryPtr",	\
                 CSC_CORRUPT					\
                 );
      ASSERT_RTN (						\
                 entryPtr->sig_hi == HASH_SIG,			\
                 "hashEntryFind: bad signature in entryPtr",	\
                 CSC_CORRUPT					\
                 );
      findStat = hashMatch (keySpec, &entryPtr->key, keyPtr);
      if (findStat == CSC_NOTFOUND) entryPtr = SUCC(entryPtr);
      }

   if (findStat == CSC_OK)
      {
      if (hashEntryPtrPtr != NULL) *hashEntryPtrPtr = entryPtr;
      if (itemPtrPtr      != NULL) *itemPtrPtr      = entryPtr->data;
      if (itemSizePtr     != NULL) *itemSizePtr     = entryPtr->size;
      }

   return (findStat);
   }


/**************************************************************************
 * Private Function rebuild
 **************************************************************************/

PRIVATE int   rebuild (
                      CSChashTableType   const hashTablePtr
                      )
   {
   int                 rebuildStat = CSC_OK;
   CSChashEntryType*   oldHashPtr  = NULL;
   CSChashEntryType    oldHashPtr2 = NULL;
   CSChashEntryType    oldHashPtr3 = NULL;
   size_t              oldNhash    = 0;
   int                 index       = 0;
   CSChashType         hashVal;

   ASSERT_RTN (hashTablePtr != NULL, "rebuild: null hashTablePtr", CSC_BADARG);
   ASSERT_RTN (						\
              hashTablePtr->sig_lo == HASH_SIG,		\
              "rebuild: bad signature in hashTablePtr",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              hashTablePtr->sig_hi == HASH_SIG,		\
              "rebuild: bad signature in hashTablePtr",	\
              CSC_CORRUPT				\
              );

   oldHashPtr = hashTablePtr->hash;
   oldNhash   = hashTablePtr->nhash;

   hashTablePtr->hash = NULL;
   rebuildStat = CSCmemAlloc (
                             hashTablePtr->memLst,
                             (void**)&hashTablePtr->hash,
                             hashTablePtr->nhash*4,
                             sizeof(S_hashEntryType),
                             0
                             );

   if (rebuildStat == CSC_OK)
      {
      hashTablePtr->nhash *= 4;
      hashTablePtr->downShift -= 2;
      hashTablePtr->mask = (hashTablePtr->mask << 2) + 3;
      hashTablePtr->resizes += 1;

      hashTablePtr->deletions  = 0;
      hashTablePtr->insertions = 0;
      hashTablePtr->collisions = 0;

      for  ( index = 0  ;  index < (int)hashTablePtr->nhash  ;  index++ )
         hashTablePtr->hash[index] = NULL;

      for  ( index = 0  ;  index < (int)oldNhash  ;  index++ )
         {
         oldHashPtr2 = oldHashPtr[index];
         while (oldHashPtr2 != NULL)
            {
            oldHashPtr3 = SUCC(oldHashPtr2);
            (void)CSChash (&(oldHashPtr2->key), hashTablePtr, &hashVal);
            (void)hashLinkSub (&(oldHashPtr[index]), oldHashPtr2);
            SUCC(oldHashPtr2) = NULL;
            PRED(oldHashPtr2) = NULL;
            (void)hashLinkAdd (&(hashTablePtr->hash[hashVal]), oldHashPtr2);
            oldHashPtr2 = oldHashPtr3;
            }
         }

      (void)CSCmemFree (hashTablePtr->memLst, (void**)&oldHashPtr, 0);
      }
   else
      {
      hashTablePtr->hash = oldHashPtr;
      }

   return (rebuildStat);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/**************************************************************************
 * Public Function CSChashNew
 **************************************************************************

<SUBROUTINE NAME="CSChashNew">

NAME
        CSChashNew - create a new libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        CSChashTableType   CSChashNew (
                                      const char*            const name,
                                            CSChashKeyType         keySpec,
                                            size_t                 size,
                                            CSCmonFnType           monFunc,
                                      const void*                  monData,
                                            CSCprofileType         profiling
                                      );

RETURN VALUE
        CSChashNew(), if successful, returns an opaque data type representing
        a new libcsc hash table, or NULL if otherwise not successful.

DESCRIPTION
        CSChashNew() creates a new libcsc hash table with several attributes:
        name, type of key, and number of hash locations.

        `name' points to an arbitrary string that is used as the name of the
        new libcsc hash table.

        `keySpec' specifies the type of keys used by the new hash table; it is
        one of:

                CSC_HASH_ASCIIZ_KEY ... hash keys for this table will be ASCII
                                        NULL-terminated (ASCIIZ) strings.

                CSC_HASH_INT32_KEY .... hash keys for this table will be
                                        integers of the type int32.

        `size' specifies the number of hash locations, or buckets, in the new
        libcsc hash table.  If size is zero, then the new libcsc hash table
        will begin life with four hash locations and will quadruple whenever the
        number of hash locations is some mysterious factor of the total number
        of hashed items (gets overfull).

        `profiling' can be CSC_DO_PROFILING or CSC_NO_PROFILING; it specifies
        whether alocate/free, insertion/deletion, etc. statistics should
        actually be generated and kept in the hash table.

SEE ALSO
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSChashTableType   (CSChashNew) (
                                       const char*            const name,
                                             CSChashKeyType         keySpec,
                                             size_t                 size,
                                             CSCmonFnType           monFunc,
                                       const void*                  monData,
                                             CSCprofileType         profiling
                                       )
   {
   CSChashTableType   newHash = NULL;
   CSCmemListType     memList = NULL;
   int                hashStat;

   ASSERT_RTN (name != NULL, "CSChashNew: no hash name", NULL);
   ASSERT_RTN (								\
              keySpec==CSC_HASH_ASCIIZ_KEY || keySpec==CSC_HASH_INT32_KEY,\
              "CSChashNew: invalid keySpec",				\
              NULL							\
              );
   ASSERT_RTN (								\
              ((profiling==CSC_DO_PROFILING)||(profiling==CSC_NO_PROFILING)),\
              "CSChashNew: illegal profile value",			\
              NULL							\
              );

   memList = CSCmemInit (name, NULL, monFunc, monData, CSC_NO_PROFILING);
   if (memList != NULL)
      {
      (void)CSCmemAlloc (memList,(void**)&newHash,1,sizeof(S_hashTableType),0);
      if (newHash != NULL)
         {
         newHash->name       = name;
         newHash->memLst     = memList;
         newHash->profiling  = profiling;
         newHash->monFunc    = monFunc;
         newHash->monData    = monData;
#ifdef  DEBUG
         newHash->sig_lo = HASH_SIG;
         newHash->sig_hi = HASH_SIG;
#endif
         hashStat = initHashTab (newHash, keySpec, size);
         if (hashStat != CSC_OK)
            {
            (void)CSCmemFree (memList, (void**)&newHash, 0);
            (void)CSCmemDone (memList);
            newHash = NULL;
            }
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (newHash);
   }


/**************************************************************************
 * Public Function CSChashDel
 **************************************************************************

<SUBROUTINE NAME="CSChashDel">

NAME
        CSChashDel - remove a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashDel (
                         CSChashTableType   const hashTable
                         );

RETURN VALUE
        CSChashDel(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        The libcsc hash table represented by the opaque `hashTable' is
        completely removed.

SEE ALSO
        CSChashNew(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashDel) (
                          CSChashTableType   const hashTable
                          )
   {
   int                 delStat   = CSC_OK;
   CSChashEntryType    entry     = NULL;
   CSChashEntryType    nextEntry = NULL;
   CSChashKeyType      keySpec   = 0;
   size_t*             countPtr  = NULL;
   int                 nhash;
   int                 index;

   ASSERT_RTN (hashTable != NULL, "CSChashDel: null hashTable", CSC_BADARG);
   ASSERT_RTN (						\
              hashTable->sig_lo == HASH_SIG,		\
              "CSChashDel: bad signature in hashTable",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              hashTable->sig_hi == HASH_SIG,		\
              "CSChashDel: bad signature in hashTable",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(hashTable);

   keySpec  = hashTable->keySpec;
   countPtr = &hashTable->count;
   nhash    = (int)hashTable->nhash;

   for  ( index = 0  ;  index < nhash  ;  ++index )
      {
      int   tmpStat = CSC_OK;
      entry = hashTable->hash[ index ];
      while (entry != NULL)
         {
         nextEntry = SUCC(entry);
         tmpStat = hashEntryDel (entry, hashTable->memLst, keySpec);
         if (tmpStat == CSC_OK)
            {
            --(*countPtr);
            }
         else
            {
            delStat = tmpStat;
            }
         entry = nextEntry;
         }
      }
   ASSERT (hashTable->count == 0);

   if (delStat == CSC_OK)
      {
      CSCmemListType   memList = hashTable->memLst;
      CSCmonFnType     monFunc = hashTable->monFunc;
      const void*      monData = hashTable->monData;
      delStat = clearHashTab (hashTable);
      hashTable->name       = NULL;
      hashTable->memLst     = NULL;
      hashTable->profiling  = -1;
      hashTable->monFunc    = NULL;
      hashTable->monData    = NULL;
#ifdef	DEBUG
      hashTable->sig_lo = -1;
      hashTable->sig_hi = -1;
#endif
      (void)CSCmemFree (memList, (void**)&hashTable, 0);
      (void)CSCmemDone (memList);
      if (monFunc != NULL) (*monFunc) (CSC_OUT, (void*)monData);
      }
   else
      {
      MON_EXIT(hashTable);
      }

   return (delStat);
   }


/**************************************************************************
 * Public Function CSChashStat
 **************************************************************************

<SUBROUTINE NAME="CSChashStat">

NAME
        CSChashStat - query statistics of a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashStat (
                          CSChashTableType   const hashTable,
                          CSChashStatType*   const statStruct
                          );

RETURN VALUE
        CSChashStat(), if successful, returns a pointer to a structure of
        queried data, or NULL if otherwise not successful.
        CSChashStat(), returns CSC_OK, or CSC_BADARG and CSC_CORRUPT can be
        returned corresponding to NULL pointers, bad function arguments, and
        internal data errors, respectively.

DESCRIPTION
        CSChashStat() queries the libcsc hash table represented by the opaque
        `hashTable' and fills a CSChashStatType structure.  The CSChashStatType
        structure is

                typedef struct   CSChashStatType
                   {
                   char            name[80];   // name of hash table
                   CSCprofileType  profiling;  // profiling flag
                   size_t          count;      // count of items in table
                   size_t          nhash;      // number of hash locations
                   CSCboolean      grows;      // CSC_TRUE or CSC_FALSE
                   size_t          resizes;    // num of resizes, if table grows
                   size_t          deletions;  // num of deletions since resize
                   size_t          insertions; // num of insertions since resize
                   size_t          collisions; // num of collisions since resize
                   } CSChashStatType;

        Only up to seventy nine characters of the table name are retrieved.

        If the table size was specified a zero when it was created with
        CSChashNew() then the table quadruples its hash locations as it gets
        full.  In this case the grows flag will be CSC_TRUE, otherwise it will
        be CSC_FALSE.

        If the table grows, then the deletions, insertions, and collisions
        fields of the CSChashStatType structure will represent those
        statistics only since the last time the table resized itself i.e., the
        deletions, insertions, and collisions are reset to zero when the table
        resizes itself.

EXAMPLE
        CSChashTableType   myTable;
        CSChashQueryType   statStruct;
        int                stat

           .
           .
           .
        stat = CSChashStat (myTable, &statStruct);
           .
           // do something with the statistics
           .
           .
           .

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashStat) (
                           CSChashTableType   const hashTable,
                           CSChashStatType*   const statStruct
                           )
   {
   ASSERT_RTN (hashTable != NULL, "CSChashStat: null hashTable", CSC_BADARG);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "CSChashStat: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "CSChashStat: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );

   MON_ENTER(hashTable);

   (void)memset (statStruct->name, '\0', 80);
   (void)strncpy (statStruct->name, hashTable->name, 79);
   statStruct->profiling  = hashTable->profiling;
   statStruct->count      = hashTable->count;
   statStruct->nhash      = hashTable->nhash;
   statStruct->grows      = hashTable->grows;
   statStruct->resizes    = hashTable->resizes;
   statStruct->deletions  = hashTable->deletions;
   statStruct->insertions = hashTable->insertions;
   statStruct->collisions = hashTable->collisions;

   MON_EXIT(hashTable);

   return (CSC_OK);
   }


/**************************************************************************
 * Public Function CSChashEntryPut
 **************************************************************************

<SUBROUTINE NAME="CSChashEntryPut">

NAME
        CSChashEntryPut - put an entry into a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashEntryPut (
                              CSChashTableType   const hashTable,
                              CSChashKeyUnion*   const keyPtr,
                              void*              const itemPtr,
                              size_t                   itemSize
                              );

RETURN VALUE
        CSChashEntryPut(), if successful, returns CSC_OK.  If the key is
        already in use in the table, then CSChashEntryPut() will return
        CSC_DUPKEY.  Other values, CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can
        be returned corresponding to NULL pointers, bad function arguments, and
        internal data errors, respectively.

DESCRIPTION
        CSChashEntryPut() puts the data pointed to by `itemPtr', whose key is
        pointed to by `keyPtr' and size in bytes is `itemSize', into the libcsc
        hash table represented by the opaque `hashTable'.

        The data that goes into the table is a duplicate of `itemSize' bytes
        from the address `itemPtr'.  To avoid duplicating static data, put a
        pointer of the client data into the table.  If the item being put into
        the table contains a pointer, beware of aliasing errors if the pointer
        is to allocated memory that becomes deallocated while the item is in the
        table.

        Of course, the type of the key pointed to by `keyPtr' must match the
        type of keys (CSC_HASH_INT32_KEY or CSC_HASH_ASCIIZ_KEY) used by
        `hashTable'.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashEntryPut) (
                               CSChashTableType   const hashTable,
                               CSChashKeyUnion*   const keyPtr,
                               void*              const itemPtr,
                               size_t                   itemSize
                               )
   {
   int                 putStat = CSC_OK;
   CSChashEntryType*   newListPtr     = NULL;
   CSChashEntryType    newHEntry      = NULL;
   CSChashType         hashVal;

   ASSERT_RTN (hashTable != NULL, "CSChashEntryPut: no hashTable", CSC_BADARG);
   ASSERT_RTN (keyPtr != NULL,    "CSChashEntryPut: no keyPtr",    CSC_BADARG);
   ASSERT_RTN (itemPtr != NULL,   "CSChashEntryPut: no itemPtr",   CSC_BADARG);
   ASSERT_RTN (itemSize > 0,      "CSChashEntryPut: no itemSize",  CSC_BADARG);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "CSChashEntryPut: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "CSChashEntryPut: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );

   MON_ENTER(hashTable);

   (void)CSChash (keyPtr, hashTable, &hashVal);
   ASSERT (hashVal < hashTable->nhash);

   newListPtr = &(hashTable->hash[hashVal]);

   putStat = hashEntryFind (
                           *newListPtr,
                           keyPtr,
                           hashTable->keySpec,
                           NULL,
                           NULL,
                           NULL
                           );

   if (putStat == CSC_OK)
      {
      putStat = CSC_DUPKEY;
      }
   else
      {
      if (putStat == CSC_NOTFOUND)
         {
         putStat = hashEntryNew (
                                &newHEntry,
                                hashTable->memLst,
                                hashTable->keySpec,
                                keyPtr,
                                itemPtr,
                                itemSize
                                );
         if (putStat == CSC_OK)
            {
            if (*newListPtr != NULL) ++(hashTable->collisions);
            (void)hashLinkAdd (newListPtr, newHEntry);
            ++(hashTable->count);
            ++(hashTable->insertions);
            }

         if (hashTable->grows == CSC_TRUE)
            if (hashTable->count > COSMOLOGICAL_CONSTANT * hashTable->nhash)
               rebuild (hashTable);
         }
      }

   MON_EXIT(hashTable);

   return (putStat);
   }


/**************************************************************************
 * Public Function CSChashEntryGet
 **************************************************************************

<SUBROUTINE NAME="CSChashEntryGet">

NAME
        CSChashEntryGet - get an item from a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashEntryGet (
                              CSChashTableType   const hashTable,
                              CSChashKeyUnion*   const keyPtr,
                              void**             const itemPtrPtr,
                              size_t*            const itemSizePtr,
                              CSCmemListType     const memLst
                              );

RETURN VALUE
        CSChashEntryGet(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSChashEntryGet() looks up the key pointed to by `keyPtr' in the libcsc
        hash table represented by the opaque `hashTable'.

        If the item corresponding to the key is found in the table, then a copy
        of the the data is allocated with CSCmemDup(), or malloc() if `memLst'
        is NULL, and the pointer of the newly allocated data it is written to
        the void pointer that is pointed to by `itemPtrPtr', and its size in
        bytes is written to the size_t pointed to by `itemSizePtr'.

        Since CSChashEntryGet(), if successful, allocates storage for the
        retrieved item. If `memLst' is not null then CSCmemDup() is used with
        the value of `memLst'; the data should be removed with CSCmemFree(),
        using "tagData" value of zero, to avoid leaking this memory. If `memLst'
        is NULL, then malloc() is use to allocate storage, and free() should be
        used to remove the data to avoid leaking this memory.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashEntryGet) (
                               CSChashTableType   const hashTable,
                               CSChashKeyUnion*   const keyPtr,
                               void**             const itemPtrPtr,
                               size_t*            const itemSizePtr,
                               CSCmemListType     const memLst
                               )
   {
   int                hashTabGetStat = CSC_OK;
   CSChashType        hashVal        = 0;
   CSChashEntryType   hashList       = NULL;
   void*              localItemPtr   = NULL;
   size_t             localSize;

   ASSERT_RTN (hashTable!=NULL, "CSChashEntryGet: null hashTable", CSC_BADARG);
   ASSERT_RTN (keyPtr!=NULL,    "CSChashEntryGet: null keyPtr",    CSC_BADARG);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "CSChashEntryGet: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "CSChashEntryGet: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );

   MON_ENTER(hashTable);

   (void)CSChash (keyPtr, hashTable, &hashVal);
   ASSERT (hashVal < hashTable->nhash);

   hashList = hashTable->hash[hashVal];
   hashTabGetStat = hashEntryFind (
                                  hashList,
                                  keyPtr,
                                  hashTable->keySpec,
                                  NULL,
                                  &localItemPtr,
                                  &localSize
                                  );

   if (hashTabGetStat == CSC_OK)
      {
      if (memLst != NULL)
         {
         hashTabGetStat = CSCmemDup (
                                    memLst,
                                    itemPtrPtr,
                                    localItemPtr,
                                    localSize,
                                    0
                                    );
         *itemSizePtr = localSize;
         }
      else
         {
         *itemPtrPtr = calloc (localSize, sizeof(char));
         if (*itemPtrPtr != NULL)
            {
            hashTabGetStat = CSC_OK;
            (void)memcpy (*itemPtrPtr, localItemPtr, localSize);
            *itemSizePtr = localSize;
            }
         else
            {
            hashTabGetStat = CSC_NOMEM;
            *itemSizePtr = 0;
            }
         }
      if (hashTabGetStat != CSC_OK)
         {
         *itemPtrPtr  = NULL;
         *itemSizePtr = 0;
         }
      }

   MON_EXIT(hashTable);

   return (hashTabGetStat);
   }


/**************************************************************************
 * Public Function CSChashEntryDel
 **************************************************************************

<SUBROUTINE NAME="CSChashEntryDel">

NAME
        CSChashEntryDel - remove an entry from a libcsc hash table

SYNOPSYS
        #include "lib.h"

        int   CSChashEntryDel (
                              CSChashTableType   const hashTable,
                              CSChashKeyUnion*   const keyPtr
                              );

RETURN VALUE
        CSChashEntryDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        The hash table entry with the key value that is pointed to by `keyPtr'
        is removed from the hash table represented by the opaque `hashTable'.

        Of course, the type of the key pointed to by `keyPtr' must match the
        type of keys (CSC_HASH_INT32_KEY or CSC_HASH_ASCIIZ_KEY) used by
        `hashTable'.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashEntryDel) (
                               CSChashTableType   const hashTable,
                               CSChashKeyUnion*   const keyPtr
                               )
   {
   int                 delStat    = CSC_OK;
   CSChashType         hashVal    = 0;
   CSChashEntryType*   oldListPtr = NULL;
   CSChashEntryType    oldEntry   = NULL;

   ASSERT_RTN (hashTable!=NULL, "CSChashEntryDel: null hashTable", CSC_BADARG);
   ASSERT_RTN (keyPtr!=NULL,    "CSChashEntryDel: null keyPtr",    CSC_BADARG);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "CSChashEntryDel: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "CSChashEntryDel: bad signature in hashTable",	\
              CSC_CORRUPT					\
              );

   MON_ENTER(hashTable);

   (void)CSChash (keyPtr, hashTable, &hashVal);
   ASSERT (hashVal < hashTable->nhash);

   oldListPtr = &(hashTable->hash[hashVal]);

   delStat = hashEntryFind (
                           *oldListPtr,
                           keyPtr,
                           hashTable->keySpec,
                           &oldEntry,
                           NULL,
                           NULL
                           );
   if (delStat == CSC_OK)
      {
      delStat = hashLinkSub (oldListPtr, oldEntry);
      if (delStat == CSC_OK)
         {
         delStat = hashEntryDel (
                                oldEntry, hashTable->memLst, hashTable->keySpec
                                );
         ASSERT (hashTable->count >= 1);
         --(hashTable->count);
         ++(hashTable->deletions);
         }
      }

   MON_EXIT(hashTable);

   return (delStat);
   }


/**************************************************************************
 * Public Function CSChashEntryNext
 **************************************************************************

<SUBROUTINE NAME="CSChashEntryNext">

NAME
        CSChashEntryNext - find next entry in a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        CSChashEntryType   CSChashEntryNext (
                                            CSChashTableType   const hashTable,
                                            CSChashEntryType   const entry
                                            );

RETURN VALUE
        CSChashEntryNext(), if successful, returns an opaque libcsc hash table
        entry.  If not successful, CSChashEntryNext() returns NULL.

DESCRIPTION
        CSChashEntryNext() uses the libcsc hash table referred to by the opaque
        `hashTable' and returns the next consecutive entry following the entry
        indicated by the opaque `entry'.  This next consecutive entry is the
        entry physically following `entry', its key may hash to the save value
        as `entry''s key, or it may be some larger hash value.

        If `entry' is NULL, then the first item in the table is returned.

        If `hashTable' is a table with no entries, or there are no more entries
        following entry, then NULL is returned.

BUGS
        This function provides one of the few ways to get direct access to a
        libcsc hash table's internal data.  Avoid using this function.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSChashEntryType   (CSChashEntryNext) (
                                             CSChashTableType   const hashTable,
                                             CSChashEntryType   const entry
                                             )
   {
   int                nextStat  = CSC_OK;
   CSChashEntryType   nextEntry = NULL;
   CSChashType        hashVal   = 0;

   ASSERT_RTN (hashTable != NULL, "CSChashEntryNext: null hashTable", NULL);
   ASSERT_RTN (							\
              hashTable->sig_lo == HASH_SIG,			\
              "CSChashEntryNext: bad signature in hashTable",	\
              NULL						\
              );
   ASSERT_RTN (							\
              hashTable->sig_hi == HASH_SIG,			\
              "CSChashEntryNext: bad signature in hashTable",	\
              NULL						\
              );

   MON_ENTER(hashTable);

   if (entry != NULL)
      {
      ASSERT_RTN (						\
                 entry->sig_lo == HASH_SIG,			\
                 "CSChashEntryNext: bad signature in entry",	\
                 NULL						\
                 );
      ASSERT_RTN (						\
                 entry->sig_hi == HASH_SIG,			\
                 "CSChashEntryNext: bad signature in entry",	\
                 NULL						\
                 );
      if (SUCC(entry) != NULL)
         nextEntry = SUCC(entry);
      else
         {
         nextStat = CSChash (&entry->key, hashTable, &hashVal);
         hashVal += 1;
         }
      }

   while ((nextEntry == NULL) && (hashVal < hashTable->nhash))
      nextEntry = hashTable->hash[hashVal++];

   MON_EXIT(hashTable);

   return (nextEntry);
   }


/**************************************************************************
 * Public Function CSChashEntryStat
 **************************************************************************

<SUBROUTINE NAME="CSChashEntryStat">

NAME
        CSChashEntryStat - query the fields of a libcsc hash table entry

SYNOPSYS
        #include "libcsc.h"

        int   CSChashEntryStat (
                               CSChashEntryType    const entry,
                               CSChashKeyUnion**   const keyPtrPtr,
                               void**              const itemPtrPtr,
                               size_t*             const itemSizePtr
                               );

RETURN VALUE
        If successful, CSChashEntryStat() returns CSC_OK.  If entry is NULL,
        then CSC_BADARG is returned.  If libcsc was compiled with the DEBUG
        macro and the libcsc hash entry at entry is munged up, then CSC_CORRUPT
        is returned.

DESCRIPTION
        CSChashEntryStat() queries the libcsc hash table entry represented by
        the opaque `entry'.

        If `keyPtrPtr' is not NULL, then the a pointer to `entry''s key is
        written to the CSChashKeyUnion pointer that is pointed to by
        `keyPtrPtr'.

        If `itemPtrPtr' is not NULL, then `entry''s item pointer is written to
        the void pointer that is pointed to by `itemPtrPtr'.

        If `itemSizePtr' is not NULL, then the size, in bytes, of `entry''s
        item is written to the size_t pointed to by `itemSizePtr'.

BUGS
        This function provides one of the few ways to get direct access to a
        libcsc hash table's internal data.  Avoid using this function.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashRead(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashEntryStat) (
                                CSChashEntryType    const entry,
                                CSChashKeyUnion**   const keyPtrPtr,
                                void**              const itemPtrPtr,
                                size_t*             const itemSizePtr
                                )
   {
   int   queryStat = CSC_OK;

   ASSERT_RTN (entry != NULL, "CSChashEntryStat: null entry", CSC_BADARG);
   ASSERT_RTN (							\
              entry->sig_lo == HASH_SIG,			\
              "CSChashEntryStat: bad signature in entry",	\
              CSC_CORRUPT					\
              );
   ASSERT_RTN (							\
              entry->sig_hi == HASH_SIG,			\
              "CSChashEntryStat: bad signature in entry",	\
              CSC_CORRUPT					\
              );

   if (entry != NULL)
      {
      if (keyPtrPtr   != NULL) *keyPtrPtr   = (CSChashKeyUnion*)&entry->key;
      if (itemPtrPtr  != NULL) *itemPtrPtr  = entry->data;
      if (itemSizePtr != NULL) *itemSizePtr = entry->size;
      }
   else
      queryStat = CSC_BADARG;

   return (queryStat);
   }


/**************************************************************************
 * Public Function CSChashRead
 **************************************************************************

<SUBROUTINE NAME="CSChashRead">

NAME
        CSChashRead - read an ASCII format libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashRead (
                                int                       fd,
                                CSChashTableType*   const hashTablePtr,
                                CSCmonFnType              monFunc,
                          const void*                     monData,
                                CSCprofileType            profiling
                          );

RETURN VALUE
        CSChashRead() always returns CSC_OK.  Lame.

DESCRIPTION
        CSChashRead() reads from `fd' a libcsc hash table in ASCII format that
        was written with CSChashWrite().

        `hashTablePtr' should point to a CSChashTableType that is set to NULL; a
        new libcsc hash table will be created.

BUGS
        There is no error checking in this function.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashWrite(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashRead) (
                                 int                       fd,
                                 CSChashTableType*   const hashTablePtr,
                                 CSCmonFnType              monFunc,
                           const void*                     monData,
                                 CSCprofileType            profiling
                           )
   {
   int               readStat   = CSC_OK;
   CSCmemListType    memList    = NULL;
   char*             objectName = NULL;
   char*             tableName  = NULL;
   char*             keySpecStr = NULL;
   char*             tableSize  = NULL;
   char*             tableCount = NULL;
   int               index      = 0;
   CSChashKeyType    keySpec    = 0;
   size_t            nhash      = 0;
   int               count      = 0;
   void*             bufPtr     = NULL;
   size_t            bufSize    = 0;
   char*             keyValPtr  = NULL;
   CSChashKeyUnion   key;

   memList = CSCmemInit ("TEMP", NULL, NULL, NULL, CSC_NO_PROFILING);
   if (memList == NULL) return (CSC_NOMEM);

   (void)CSCioReadLine (fd, &objectName, memList, 0);
   (void)CSCioReadLine (fd, &tableName,  memList, 0);
   (void)CSCioReadLine (fd, &keySpecStr, memList, 0);
   (void)CSCioReadLine (fd, &tableSize,  memList, 0);
   (void)CSCioReadLine (fd, &tableCount, memList, 0);

   keySpec = (CSChashKeyType)atoi(keySpecStr);
   nhash = (size_t)atoi(tableSize);
   count = (size_t)atoi(tableCount);

   *hashTablePtr = CSChashNew (
                              tableName,
                              keySpec,
                              nhash,
                              monFunc,
                              monData,
                              profiling
                              );
   for ( index = 0  ;  index < count  ;  index++)
      {
      (void)CSCioReadLine (fd, &keyValPtr, memList, 0);
      switch (keySpec)
         {
         default: break;
         case CSC_HASH_ASCIIZ_KEY: (void)CSCmemDup (
                                                   (*hashTablePtr)->memLst,
                                                   (void**)&key.asciiz,
                                                   keyValPtr,
                                                   strlen(keyValPtr)+1,
                                                   0
                                                   );
                                   break;
         case CSC_HASH_INT32_KEY: key.integer = atoi(keyValPtr); break;
         }
      (void)CSCioBufRead (fd, &bufPtr, &bufSize, memList, 0);
      (void)CSChashEntryPut (*hashTablePtr, &key, bufPtr, bufSize);
      if (keySpec == CSC_HASH_ASCIIZ_KEY)
         {
         (void)CSCmemFree ((*hashTablePtr)->memLst, (void**)&key.asciiz, 0);
         }
      (void)CSCmemFree (memList, (void**)&keyValPtr, 0);
      (void)CSCmemFree (memList, (void**)&bufPtr, 0);
      }

   (void)CSCmemFree (memList, (void**)&objectName, 0);
   (void)CSCmemFree (memList, (void**)&tableName, 0);
   (void)CSCmemFree (memList, (void**)&keySpecStr, 0);
   (void)CSCmemFree (memList, (void**)&tableSize, 0);
   (void)CSCmemFree (memList, (void**)&tableCount, 0);

   (void)CSCmemDone (memList);

   return (readStat);
   }


/**************************************************************************
 * Public Function CSChashWrite
 **************************************************************************

<SUBROUTINE NAME="CSChashWrite">

NAME
        CSChashWrite - write a libcsc hash table in an ASCII format

SYNOPSYS
        #include "libcsc.h"

        int   CSChashWrite (
                           int                      fd,
                           CSChashTableType   const hashTable
                           );

RETURN VALUE
        CSChashWrite() always returns CSC_OK.  Lame.

DESCRIPTION
        CSChashWrite() writes to `fd' the libcsc hash table represented by the
        opaque `hashTable' in an ASCII format.  Small, simple tables will be
        human-readable by patient humans, but CSChashRead() will be happy to
        read it and create another duplicate libcsc hash table.  In this way,
        libcsc hash tables can be transported between processes, in space or
        time.

        Caution: client pointers stored in the table will be severe aliasing
                 bugs when they are read by a different process.

BUGS
        There is no error checking in this function.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashDump(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashWrite) (
                            int                      fd,
                            CSChashTableType   const hashTable
                            )
   {
   int                writeStat = CSC_OK;
   CSChashEntryType   entry     = NULL;
   char               ioLine[ 80 ];
   CSChashKeyType     keySpec;

   MON_ENTER(hashTable);

   (void)write (fd, "HASH TABLE => ", 14);
   (void)write (fd, hashTable->name, strlen(hashTable->name));
   (void)write (fd, "\n", 1);

   switch ((int)hashTable->keySpec)
      {
      default:
         (void)write (fd, "unknown key type => ", 20);
         break;

      case CSC_HASH_ASCIIZ_KEY:
         (void)write (fd, "key type:  CSC_HASH_ASCIIZ_KEY => ", 34);
         break;

      case CSC_HASH_INT32_KEY:
         (void)write (fd, "key type:  CSC_HASH_INT32_KEY  => ", 34);
         break;
      }
   (void)sprintf (ioLine, "%d\n", (int)hashTable->keySpec);
   (void)write (fd, ioLine, strlen(ioLine));

   (void)write (fd, "nhash => ", 9);
   (void)sprintf (ioLine, "%d\n", (int)hashTable->nhash);
   (void)write (fd, ioLine, strlen(ioLine));

   (void)write (fd, "count => ", 9);
   (void)sprintf (ioLine, "%d\n", (int)hashTable->count);
   (void)write (fd, ioLine, strlen(ioLine));

   keySpec = hashTable->keySpec;
   while ((entry=CSChashEntryNext(hashTable,entry)) != NULL)
      {
      (void)write (fd, "--\n", 3);
      switch (keySpec)
         {
         default:
            break;

         case CSC_HASH_ASCIIZ_KEY:
            (void)write (fd, entry->key.asciiz, strlen(entry->key.asciiz));
            (void)write (fd, "\n", 1);
            break;

         case CSC_HASH_INT32_KEY:
            (void)sprintf (ioLine, "%d\n", (int)entry->key.integer);
            (void)write (fd, ioLine, strlen(ioLine));
            break;
         }
      CSCioBufWrite (fd, entry->data, entry->size);
      }

   MON_EXIT(hashTable);

   return (writeStat);
   }


/**************************************************************************
 * Public Function CSChashDump
 **************************************************************************

<SUBROUTINE NAME="CSChashDump">

NAME
        CSChashDump - write a formatted dump of a libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        int   CSChashDump (
                          int                      fd,
                          CSChashTableType   const hashTable
                          );

RETURN VALUE
        CSChashDump() always returns CSC_OK.  Lame.

DESCRIPTION
        CSChashDump() writes to `fd' a formatted dump of the entire hash table
        represented by the opaque `hashTable'.

        This formatted dump of the hash table is for visual inspection of the
        hash table.  After a short header, each item's hash value, key, data
        size, and data dump is written.

        Don't do this with large hash tables, even if they are sparsely
        populated; nobody would read it.

SEE ALSO
        CSChashNew(3)
        CSChashDel(3)
        CSChashStat(3)
        CSChashEntryPut(3)
        CSChashEntryGet(3)
        CSChashEntryDel(3)
        CSChashEntryNext(3)
        CSChashEntryStat(3)
        CSChashRead(3)
        CSChashWrite(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSChashDump) (
                           int                      fd,
                           CSChashTableType   const hashTable
                           )
   {
   int                dumpStat  = CSC_OK;
   CSCmemListType     memList   = NULL;
   int                index     = 0;
   char*              msgBufPtr = NULL;
   CSChashEntryType   entry     = NULL;
   CSChashKeyType     keySpec;

   memList = CSCmemInit ("TEMP", NULL, NULL, NULL, CSC_NO_PROFILING);
   if (memList == NULL) return (CSC_NOMEM);

   MON_ENTER(hashTable);

#define	SIGNON	"\nRTHASHSYS-I-DUMP, hash table dump follows.\n\n"
   (void)write (fd, SIGNON, strlen(SIGNON));
#undef	SIGNON

#define	FMT_STR	"Hash table `%s' has %d hash positions and %d items.\n"
#define	FMT_SZ	(strlen(FMT_STR)+strlen(hashTable->name)+20+1)

   (void)CSCmemAlloc (memList, (void**)&msgBufPtr, 1, FMT_SZ, 0);
   (void)sprintf (
                 msgBufPtr,
                 FMT_STR,
                 hashTable->name,
                 hashTable->nhash,
                 hashTable->count
                 );
   (void)write (fd, msgBufPtr, strlen(msgBufPtr));
   (void)CSCmemFree (memList, (void**)&msgBufPtr, 0);
#undef	FMT_STR
#undef	FMT_SZ

#define	MSG_STR	"hash\t\tkey\tsize\n----\t\t---\t----\n\n"
   (void)write (fd, MSG_STR, strlen(MSG_STR));
#undef	MSG_STR

   keySpec = hashTable->keySpec;
   for  ( index = 0  ;  index < (int)hashTable->nhash  ;  ++index )
      {
      entry = hashTable->hash[index];
#define	FMT_STR	"%05d"
#define	FMT_SZ	(strlen(FMT_STR)+20+1)
   (void)CSCmemAlloc (memList, (void**)&msgBufPtr, 1, FMT_SZ, 0);
   (void)sprintf (msgBufPtr, FMT_STR, index);
   (void)write (fd, msgBufPtr, strlen(msgBufPtr));
   (void)CSCmemFree (memList, (void**)&msgBufPtr, 0);
#undef	FMT_STR
#undef	FMT_SZ
      if (entry != NULL)
         {
         while (entry != NULL)
            {

#define	FMT_STR_A	"\t\t%s\t%ld (%08lX hex)\n"
#define	FMT_STR_I	"\t\t%ld\t%ld (%08lX hex)\n"

            switch (keySpec)
               {
               default:
                  break;
               case CSC_HASH_ASCIIZ_KEY:
#define	FMT_STR	"\t\t%s\t%d (%08X hex)\n"
#define	FMT_SZ	(strlen(FMT_STR)+strlen(entry->key.asciiz)+20+1)
                  (void)CSCmemAlloc (memList, (void**)&msgBufPtr, 1, FMT_SZ, 0);
                  (void)sprintf (
                                msgBufPtr,
                                FMT_STR,
                                entry->key.asciiz,
                                entry->size,
                                entry->size
                                );
#undef	FMT_STR
#undef	FMT_SZ
                  break;
               case CSC_HASH_INT32_KEY:
#define	FMT_STR	"\t\t%d\t%d (%08X hex)\n"
#define	FMT_SZ	(strlen(FMT_STR)+sizeof(entry->key.integer)+20+1)
                  (void)CSCmemAlloc (memList, (void**)&msgBufPtr, 1, FMT_SZ, 0);
                  (void)sprintf (
                                msgBufPtr,
                                FMT_STR,
                                entry->key.integer,
                                entry->size,
                                entry->size
                                );
#undef	FMT_STR
#undef	FMT_SZ
                  break;
               }
            (void)write (fd, msgBufPtr, strlen(msgBufPtr));
            (void)CSCmemFree (memList, (void**)&msgBufPtr, 0);
/*
            (void)rtsMemDump (fd, entry->data, entry->size, NULL);
*/
            entry = SUCC(entry);
            }
         }
      else
         {
#define	MSG_STR	"\t\tEMPTY\n"
         (void)write (fd, MSG_STR, strlen(MSG_STR));
#undef	MSG_STR
         }
      }

   write (fd, "\n", 1);

   (void)CSCmemDone (memList);

   return (dumpStat);
   }


/* End of the file. */
