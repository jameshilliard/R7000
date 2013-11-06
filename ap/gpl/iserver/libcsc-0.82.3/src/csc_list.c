/* *****************************************************************************

libcsc: List Subsystem

	----------------------------------------------------------------

Copyright (c) 1999, 2000, 2002 Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: csc_list.c,v $
	$Revision: 1.10 $
	$Date: 2002/11/06 16:40:59 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_list">

NAME
	csc_list

DESCRIPTION
	List Subsystem

	The csc library's list subsystem; there are functions for managing
	arbitrary data in lists.  These lists can act like queues, stacks, or
	just linked lists.

FUNCTIONS
	CSClistNew - create a new libcsc list
	CSClistDel - remove a libcsc list
	CSClistRead - read an ASCII format libcsc list
	CSClistWrite - write a libcsc list in an ASCII format
	CSClistSetCFunc - set a libcsc list entry data compare function
	CSClistStat - retrieve libcsc list statistics
	CSClistPush - create a new entry and push it onto a libcsc list
	CSClistPop - pop an entry from a libcsc list and retrieve its data
	CSClistPeek - retrieve data from entry at libcsc list head or tail
	CSClistNodeNext - find next entry (node) in a libcsc list
	CSClistNodeFindByValue - find libcsc list entry by data value
	CSClistNodeFindByReference - find libcsc list entry (node) by reference
	CSClistNodeStat - retrieve data fields from a libcsc list entry (node)
	CSClistNodeValidate - verify an entry (node) is really in a libcsc list
	CSClistNodeDel - remove an entry (node) from a libcsc list
</SUBSYSTEM>

CHANGE LOG

	06nov02	drj	Fixed bug in CSClistPop() wherein popped data that was
			pushed with the push type of CSC_DATA_DUP was freed
			before returning it to the caller.
			Fixed a bug in CSClistNodeNext() wherein the list
			could not be traversed from the tail.

	10may02	drj	Fixed up monitor deadlock caused from externally
			callable functions calling other externally callable
			functions.

	21apr02	drj	Small comment changes.

	14apr02	drj	Removed erroneous comment.
			Fixed debug code in function CSClistNew().

	11apr02	drj	Added assertions to CSClistNew(). Changed `pushType' to
			`push'.

	10apr02	drj	Removed unused tagFunc, and fixed function headers.

	18feb02	drj	Fixed up CSClistDel().

	11feb02	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Tracked changes in rtsMemDup().

	22apr00	drj	Simplified the data types and function prototypes.
			Added bias to the find functions, and added
			rtsListEntryNextWithBias().

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
#include	<stdlib.h>
#include	<string.h>

/*
 * Posix Header Files
 */
#include	<unistd.h>

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

#define	LIST_SIG	(0x4D454D4F)

#define	PRED(x)		((x)->pred)
#define	SUCC(x)		((x)->succ)

#define	MON_ENTER(x)	{if(x->monFunc!=NULL)\
			(*x->monFunc)(CSC_IN,(void*)x->monData);}

#define	MON_EXIT(x)	{if(x->monFunc!=NULL)\
			(*x->monFunc)(CSC_OUT,(void*)x->monData);}


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

typedef struct   S_listNodeType
   {
#ifdef	DEBUG
          long               sig_lo;
#endif
   struct S_listNodeType*    pred;
   struct S_listNodeType*    succ;
          const void*        data;
          size_t             size;
          CSCdataCntrlType   push;
#ifdef	DEBUG
          long               sig_hi;
#endif
   } S_listNodeType;

typedef struct S_listType
   {
#ifdef	DEBUG
   long              sig_lo;
#endif
   const char*       name;
   CSCmemListType    memList;
   S_listNodeType*   head;
   S_listNodeType*   tail;
   CSCcmpFnType      cmpFunc;
   CSCprofileType    profiling;
   CSCmonFnType      monFunc;
   const void*       monData;
   size_t            pushCount;
   size_t            popCount;
   size_t            curAlloc;
   size_t            maxAlloc;
#ifdef	DEBUG
   long              sig_hi;
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

PRIVATE int   nodeNew (
                            CSCmemListType     const memList,
                            CSClistNodeType*   const node,
                            CSCdataCntrlType         push,
                      const void*              const itemPtr,
                            size_t                   itemSize
                      );

PRIVATE int   nodeDel (
                      CSCmemListType    const memList,
                      CSClistNodeType   const node
                      );

PRIVATE int   nodePush (
                       CSClistType       const list,
                       CSClistNodeType   const node
                       );

PRIVATE int   nodePop (
                      CSClistType        const list,
                      CSClistBiasType          bias,
                      CSClistNodeType*   const node
                      );

PRIVATE int   nodeDelink (
                         CSClistType       const list,
                         CSClistNodeType   const node
                         );

PRIVATE int   nodeValidate (
                           CSClistType       const list,
                           CSClistNodeType   const node
                           );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function nodeNew
 **************************************************************************/

PRIVATE int   nodeNew (
                            CSCmemListType     const memList,
                            CSClistNodeType*   const nodePtr,
                            CSCdataCntrlType         push,
                      const void*              const item,
                            size_t                   size
                      )
   {
   int               newStat = CSC_OK;
   CSClistNodeType   node    = NULL;
   const void*       data    = item;

   ASSERT_RTN (memList != NULL, "nodeNew: null memList", CSC_BADARG);
   ASSERT_RTN (nodePtr != NULL, "nodeNew: null nodePtr", CSC_BADARG);
   ASSERT_RTN (item != NULL,    "nodeNew: null item",    CSC_BADARG);
   ASSERT_RTN (size > 0,        "nodeNew: null size",    CSC_BADARG);
   ASSERT_RTN (								\
              (push == CSC_DATA_NODUP) || (push == CSC_DATA_DUP),	\
              "nodeNew: invalid push",					\
              CSC_BADARG						\
              );

   if (push == CSC_DATA_DUP)
      {
      (void)CSCmemDup (memList, (void**)&data, item, size, 0);
      if (data == NULL) return (CSC_NOMEM);
      }

   (void)CSCmemAlloc (memList, (void**)&node, 1, sizeof(S_listNodeType), 0);
   if (node != NULL)
      {
      node->pred = NULL;
      node->succ = NULL;
      node->data = data;
      node->size = size;
      node->push = push;
#ifdef	DEBUG
      node->sig_lo = LIST_SIG;
      node->sig_hi = LIST_SIG;
#endif
      *nodePtr = node;
      }
   else
      {
      if (push == CSC_DATA_DUP) (void)CSCmemFree(memList,(void**)&data,0);
      newStat = CSC_NOMEM;
      }

   return (newStat);
   }


/**************************************************************************
 * Private Function nodeDel
 **************************************************************************/

PRIVATE int   nodeDel (
                      CSCmemListType    const memList,
                      CSClistNodeType   const node
                      )
   {
   int               delStat = CSC_OK;
   CSClistNodeType   tmpNode = node;

   ASSERT_RTN (memList != NULL, "nodeDel: null memList", CSC_BADARG);
   ASSERT_RTN (node != NULL,    "nodeDel: null node",    CSC_BADARG);

   ASSERT_RTN (node->sig_lo == LIST_SIG, "nodeDel: node blows", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi == LIST_SIG, "nodeDel: node blows", CSC_CORRUPT);

   if (node->push == CSC_DATA_DUP)
      {
      (void)CSCmemFree (memList, (void**)&tmpNode->data, 0);
      }
   (void)CSCmemFree (memList, (void**)&tmpNode, 0);

   return (delStat);
   }


/**************************************************************************
 * Private Function nodePush
 **************************************************************************/

PRIVATE int   nodePush (
                       CSClistType       const list,
                       CSClistNodeType   const node
                       )
   {
   int   pushStat = CSC_OK;

   ASSERT_RTN (list != NULL, "nodePush: null list", CSC_BADARG);
   ASSERT_RTN (node != NULL, "nodePush: null node", CSC_BADARG);

   ASSERT_RTN (list->sig_lo == LIST_SIG, "nodePush: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi == LIST_SIG, "nodePush: list blows", CSC_CORRUPT);

   ASSERT_RTN (node->sig_lo == LIST_SIG, "nodePush: node blows", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi == LIST_SIG, "nodePush: node blows", CSC_CORRUPT);

   SUCC(node) = list->head;
   if (list->head != NULL)
      PRED(list->head) = node;
   else
      {
      ASSERT (list->tail == NULL);
      list->tail = node;
      }
   list->head = node;

   return (pushStat);
   }


/**************************************************************************
 * Private Function nodePop
 **************************************************************************/

PRIVATE int   nodePop (
                      CSClistType        const list,
                      CSClistBiasType          bias,
                      CSClistNodeType*   const nodePtr
                      )
   {
   int               popStat = CSC_OK;
   CSClistNodeType   node = NULL;

   ASSERT_RTN (list != NULL,    "nodePop: null list",    CSC_BADARG);
   ASSERT_RTN (								\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "nodePop: invalid bias",					\
              CSC_BADARG						\
              );
   ASSERT_RTN (nodePtr != NULL, "nodePop: null nodePtr", CSC_BADARG);

   ASSERT_RTN (list->sig_lo == LIST_SIG, "nodePop: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi == LIST_SIG, "nodePop: list blows", CSC_CORRUPT);

   switch (bias)
      {
      default:  popStat = CSC_NOTFOUND;  break;

      case CSC_LIST_HEAD:  node = list->head;
                           if (node != NULL) list->head = SUCC(node);
                           if (list->head != NULL) PRED(list->head) = NULL;
                           break;

      case CSC_LIST_TAIL:  node = list->tail;
                           if (node != NULL) list->tail = PRED(node);
                           if (list->tail != NULL) SUCC(list->tail) = NULL;
                           break;
      }

   *nodePtr = node;

   return (popStat);
   }


/**************************************************************************
 * Private Function nodeDelink
 **************************************************************************/

PRIVATE int   nodeDelink (
                         CSClistType       const list,
                         CSClistNodeType   const node
                         )
   {
   int   delinkStat = CSC_OK;

   ASSERT_RTN (list != NULL, "nodeDelink: null list", CSC_BADARG);
   ASSERT_RTN (node != NULL, "nodeDelink: null node", CSC_BADARG);

   ASSERT_RTN (list->sig_lo == LIST_SIG, "nodeDelink: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi == LIST_SIG, "nodeDelink: list blows", CSC_CORRUPT);

   ASSERT_RTN (node->sig_lo == LIST_SIG, "nodeDelink: node blows", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi == LIST_SIG, "nodeDelink: node blows", CSC_CORRUPT);

    if (node == list->head)
      {
      if (list->head == list->tail)
         {
         /* -- DE-LINK SINGLE ENTRY */
         list->head = NULL;
         list->tail = NULL;
         }
      else
         {
         /* -- DE-LINK FIRST ENTRY  */
         list->head = SUCC(list->head);
         if (list->head != NULL)
            {
            PRED(list->head) = NULL;
            }
        }
      }
   else
      {
      if (node == list->tail)
         {
         /* -- DE-LINK LAST ENTRY  */
         list->tail = PRED(list->tail);
         if (list->tail != NULL)
            {
            SUCC(list->tail) = NULL;
            }
         }
      else
         {
         /* -- DE-LINK INNER ENTRY  */
         SUCC(PRED(node)) = SUCC(node);
         PRED(SUCC(node)) = PRED(node);
         }
      }

   return (delinkStat);
   }


/**************************************************************************
 * Private Function nodeValidate
 **************************************************************************
 *
 * This function duplicates the externally callable CSClistNodeValidate(),
 * but without the monitor function calls.  This is so that this function
 * can be called from other externally callable functions without creating
 * a monitor deadlock.
 *
 **************************************************************************/

PRIVATE int   nodeValidate (
                           CSClistType       const list,
                           CSClistNodeType   const node
                           )
   {
   int               validStat = CSC_NOTFOUND;
   CSClistNodeType   checkNode = NULL;

   ASSERT_RTN (list != NULL, "nodeValidate: null list", CSC_BADARG);
   ASSERT_RTN (node != NULL, "nodeValidate: null node", CSC_BADARG);

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "nodeValidate: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "nodeValidate: list blows",	\
              CSC_CORRUPT			\
              );

   ASSERT_RTN (					\
              node->sig_lo == LIST_SIG,		\
              "nodeValidate: node blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi == LIST_SIG,		\
              "nodeValidate: node blows",	\
              CSC_CORRUPT			\
              );

   checkNode = list->head;
   while ((checkNode != NULL) && (validStat == CSC_NOTFOUND))
      {
      ASSERT (node->sig_hi == LIST_SIG);
      ASSERT (node->sig_lo == LIST_SIG);
      if (checkNode == node)
         validStat = CSC_OK;
      else
         checkNode = SUCC(checkNode);
      }

   return (validStat);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/**************************************************************************
 * Public Function CSClistNew
 **************************************************************************

<SUBROUTINE NAME="CSClistNew">

NAME
        CSClistNew - create a new libcsc list

SYNOPSYS
        #include "libcsc.h"

        CSClistType   CSClistNew (
                                 const char*            name,
                                       CSCmonFnType     monFunc,
                                 const void*            monData,
                                       CSCprofileType   profiling
                                 );

RETURN VALUE
        CSClistNew(), if successful, returns an opaque CSClistType, or NULL
        if otherwise not successful.

DESCRIPTION
        CSClistNew() creates a new list.

        `profiling' can be CSC_DO_PROFILING or CSC_NO_PROFILING; it specifies
        whether alocate/free statistics should actually be generated and kept
        in the list.

SEE ALSO
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSClistType   (CSClistNew) (
                                  const char*            name,
                                        CSCmonFnType     monFunc,
                                  const void*            monData,
                                        CSCprofileType   profiling
                                  )
   {
   S_listType*      newList = NULL;
   CSCmemListType   memList = NULL;

   ASSERT_RTN (name != NULL, "CSClistNew: no list name", NULL);
   ASSERT_RTN (							\
              ((profiling==CSC_DO_PROFILING)||(profiling==CSC_NO_PROFILING)),\
              "CSClistNew: illegal profile value",		\
              NULL						\
              );

   memList = CSCmemInit (name, NULL, NULL, NULL, profiling);
   if (memList != NULL)
      {
      (void)CSCmemAlloc (memList, (void**)&newList, 1, sizeof(S_listType), 0);
      if (newList != NULL)
         {
         newList->name       = name;
         newList->memList    = memList;
         newList->head       = NULL;
         newList->tail       = NULL;
         newList->cmpFunc    = NULL;
         newList->profiling  = profiling;
         newList->monFunc    = monFunc;
         newList->monData    = monData;
         newList->pushCount  = 0;
         newList->popCount   = 0;
         newList->curAlloc   = 0;
         newList->maxAlloc   = 0;
#ifdef	DEBUG
         newList->sig_lo = LIST_SIG;
         newList->sig_hi = LIST_SIG;
#endif
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (newList);
   }


/**************************************************************************
 * Public Function CSClistDel
 **************************************************************************

<SUBROUTINE NAME="CSClistDel">

NAME
        CSClistDel - remove a libcsc list

SYNOPSYS
        #include "libcsc.h"

        int   CSClistDel (
                         CSClistType const   list
                         );

RETURN VALUE
        CSClistDel(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_ERROR can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistDel() completely removes the libcsc list represented by the
        opaque `list'.

SEE ALSO
        CSClistNew(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistDel) (
                          CSClistType   const list
                          )
   {
   int   delStat = CSC_OK;

   ASSERT_RTN (list != NULL, "CSClistDel: null list", CSC_BADARG);

   ASSERT_RTN (list->sig_lo == LIST_SIG, "CSClistDel: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi == LIST_SIG, "CSClistDel: list blows", CSC_CORRUPT);

   MON_ENTER(list);

#ifdef	DEBUG
   {
   S_listNodeType*   node = list->head;
   while ((node != NULL) && (delStat == CSC_OK))
      {
      if (nodeValidate(list,node) != CSC_OK) delStat = CSC_CORRUPT;
      node = node->succ;
      }
   }
   if (delStat != CSC_OK)
      {
      MON_EXIT(list);
      return (delStat);
      }
#endif

   {
   int               tmpStat = CSC_OK;
   S_listNodeType*   node = NULL;
   S_listNodeType*   link = NULL;
   node = list->head;
   while (node != NULL)
      {
      link = SUCC(node);
      MON_EXIT(list);
      tmpStat = CSClistNodeDel (list, node);
      MON_ENTER(list);
      if (tmpStat != CSC_OK) delStat = tmpStat;
      node = link;
      }
   }

   {
   CSCmemListType   memList = list->memList;
   CSCmonFnType     monFunc = list->monFunc;
   const void*      monData = list->monData;
   (void)CSCmemFree (memList, (void**)&list, 0);
   (void)CSCmemDone (memList);
   if (monFunc != NULL) (*monFunc) (CSC_OUT, (void*)monData);
   }

   return (delStat);
   }


/**************************************************************************
 * Public Function CSClistRead
 **************************************************************************

<SUBROUTINE NAME="CSClistRead">

NAME
        CSClistRead - read an ASCII format libcsc list

SYNOPSYS
        #include "libcsc.h"

        int   CSClistRead (
                          int                 fd,
                          CSClistType   const list
                          );

RETURN VALUE
        CSClistRead(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistRead() reads from fd a libcsc list in ASCII format that was
        written with CSClistWrite().

        `list' should be a CSClistType that is set to NULL; a new libcsc
        list will be created.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistRead) (
                           int                 fd,
                           CSClistType   const list
                           )
   {
   int      readStat = CSC_OK;
   int      getStat  = CSC_OK;
   int      pushStat = CSC_OK;
   void*    data  = NULL;
   size_t   size  = 0;

   ASSERT_RTN (fd >= 0,      "CSClistRead: no fd",     CSC_BADARG);
   ASSERT_RTN (list != NULL, "CSClistRead: null list", CSC_BADARG);

   ASSERT_RTN (list->sig_lo==LIST_SIG, "CSClistRead: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi==LIST_SIG, "CSClistRead: list blows", CSC_CORRUPT);

   getStat = CSCioBufRead (fd, &data, &size, list->memList, 0);
   ASSERT (getStat == CSC_OK);
   while ((getStat == CSC_OK) && (pushStat == CSC_OK))
      {
      pushStat = CSClistPush (list, CSC_DATA_NODUP, data, size);
      ASSERT (pushStat == CSC_OK);
      getStat = CSCioBufRead (fd, &data, &size, list->memList, 0);
      ASSERT (getStat == CSC_OK);
      }

   if ((getStat != CSC_OK) || (pushStat != CSC_OK)) readStat = CSC_ERROR;

   return (readStat);
   }


/**************************************************************************
 * Public Function CSClistWrite
 **************************************************************************

<SUBROUTINE NAME="CSClistWrite">

NAME
        CSClistWrite - write a libcsc list in an ASCII format

SYNOPSYS
        #include "libcsc.h"

        int   CSClistWrite (
                           int                 fd,
                           CSClistType   const list
                           );

RETURN VALUE
        CSClistWrite(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistWrite() writes to `fd' the libcsc list represented by the opaque
        `list' in an ASCII format.  Small, simple lists will be human-readable
        by patient humans, but CSClistRead() will be happy to read it and create
        another duplicate libcsc list.  In this way, libcsc lists can be
        transported between processes, in space or time.

        Caution: client pointers stored in the list will be severe aliasing
                 bugs when they are read by a different process.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistWrite) (
                            int                 fd,
                            CSClistType   const list
                            )
   {
   int               writeStat = CSC_OK;
   CSClistNodeType   node      = NULL;

   ASSERT_RTN (fd >= 0,      "CSClistWrite: no fd",     CSC_BADARG);
   ASSERT_RTN (list != NULL, "CSClistWrite: null list", CSC_BADARG);

   ASSERT_RTN (list->sig_lo==LIST_SIG, "CSClistWrite: list blows", CSC_CORRUPT);
   ASSERT_RTN (list->sig_hi==LIST_SIG, "CSClistWrite: list blows", CSC_CORRUPT);

   node = CSClistNodeNext (list, CSC_LIST_HEAD, NULL);
   while ((node != NULL) && (writeStat == CSC_OK))
      {
      ASSERT (node->sig_lo == LIST_SIG);
      ASSERT (node->sig_hi == LIST_SIG);
      writeStat = CSCioBufWrite (fd, node->data, node->size);
      ASSERT (writeStat == CSC_OK);
      node = CSClistNodeNext (list, CSC_LIST_HEAD, node);
      }

   return (writeStat);
   }


/**************************************************************************
 * Public Function CSClistSetCFunc
 **************************************************************************

<SUBROUTINE NAME="CSClistSetCFunc">

NAME
        CSClistSetCFunc - set a libcsc list entry data compare function

SYNOPSYS
        #include "libcsc.h"

        int   CSClistSetCFunc (
                              CSClistType    const list,
                              CSCcmpFnType         funcptr
                              );

RETURN VALUE
        CSClistSetCFunc(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistSetCFunc() sets the client-specified compare function `list'.

        The client-specified compare function is used by the libcsc list find
        functions CSClistNodeFindByValue() and CSClistNodeFindByReference().

        `funcptr' is a function pointer pointer for a libcsc CSCcmpFnType
        function that is called from the libcsc list find functions
        CSClistNodeFindByValue() and CSClistNodeFindByReference().  The
        prototype for `funcptr' is:

                int    (*CSCcmpFnType) (void*, void*);

        The client callback function `funcptr, is called with client supplied
        data and a list entry data pointer.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistSetCFunc) (
                               CSClistType    const list,
                               CSCcmpFnType         funcptr
                               )
   {
   int   setStat = CSC_OK;

   ASSERT_RTN (list != NULL, "CSClistSetCFunc: null list", CSC_BADARG);

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistSetCFunc: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistSetCFunc: list blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(list);
   list->cmpFunc = funcptr;
   MON_EXIT(list);

   return (setStat);
   }


/**************************************************************************
 * Public Function CSClistStat
 **************************************************************************

<SUBROUTINE NAME="CSClistStat">

NAME
        CSClistStat - retrieve libcsc list statistics

SYNOPSYS
        #include "libcsc.h"

        int   CSClistStat (
                          CSClistType   const list,
                          size_t*       const pushCountPtr,
                          size_t*       const popCountPtr,
                          size_t*       const maxAllocPtr,
                          size_t*       const curAllocPtr
                          );

RETURN VALUE
        CSClistStat(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistStat() returns some statistics from `list'.

        If `pushCountPtr' is not NULL, then CSClistStat() writes the total of
        libcsc list pushes to the size_t that is pointed to by `pushCountPtr'.

        If `popCountPtr' is not NULL, then CSClistStat() writes the total of
        libcsc list pops to the size_t that is pointed to by `popCountPtr'.

        If `maxAllocPtr' is not NULL, then CSClistStat() writes the total count
        of bytes pushed to the size_t that is pointed to by `maxAllocPtr'.

        If `curAllocPtr' is not NULL, then CSClistStat() writes the current
        count of bytes in the libcsc list to the size_t that is pointed to by
        `curAllocPtr'.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistStat) (
                           CSClistType   const list,
                           size_t*       const pushCountPtr,
                           size_t*       const popCountPtr,
                           size_t*       const maxAllocPtr,
                           size_t*       const curAllocPtr
                           )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (list != NULL, "CSClistStat: null list", CSC_BADARG);

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistStat: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistStat: list blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(list);

   if (list->profiling == CSC_DO_PROFILING)
      {
      if (pushCountPtr != NULL) *pushCountPtr = list->pushCount;
      if (popCountPtr  != NULL) *popCountPtr  = list->popCount;
      if (maxAllocPtr  != NULL) *maxAllocPtr  = list->maxAlloc;
      if (curAllocPtr  != NULL) *curAllocPtr  = list->curAlloc;
      }
   else
      statStat = CSC_NO_PROFILING;

   MON_EXIT(list);

   return (statStat);
   }


/**************************************************************************
 * Public Function CSClistPush
 **************************************************************************

<SUBROUTINE NAME="CSClistPush">

NAME
        CSClistPush - create a new entry and push it onto a libcsc list

SYNOPSYS
        #include "libcsc.h"

        int   CSClistPush (
                                CSClistType        const list,
                                CSCdataCntrlType         push,
                          const void*              const itemPtr,
                                size_t                   itemSize
                          );

RETURN VALUE
        CSClistPush(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistPush() creates a libcsc list entry from `itemPtr' and `itemSize',
        and pushes it onto the list pointed to by `list'.

        `push' specifies how the client data pointed to by `itemPtr' is used:

                CSC_DATA_NODUP  The new list entry simply copies the data
                                pointer, `itemPtr', itself.  If the data pointed
                                to by `itemPtr' is dynamically allocated and is
                                dellocated while the list entry has a pointer
                                to it, then there will be an aliasing error and
                                goblins will eat you.

                CSC_DATA_DUP    The data pointed to by `itemPtr' is copied for
                                `itemSize' bytes into a new dynamically
                                allocated storage.  The client code is
                                responsible for deallocating the storage when
                                the entry is popped from the list or there will
                                be a memory leak, and you will have to tell your
                                mother what you've done.

        Be careful of mixing push types CSC_DATA_NODUP and CSC_DATA_DUP in the
        same list; there may be no way for clients to later tell these entries
        apart from each other.

        CSClistDel() and CSClistNodeDel() should correctly deallocate data for
        entries with CSC_DATA_DUP push types.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistPush) (
                                 CSClistType        const list,
                                 CSCdataCntrlType         push,
                           const void*              const itemPtr,
                                 size_t                   itemSize
                           )
   {
   int               pushStat = CSC_OK;
   CSClistNodeType   node     = NULL;

   ASSERT_RTN (list    != NULL, "CSClistPush: null list",     CSC_BADARG);
   ASSERT_RTN (itemPtr != NULL, "CSClistPush: null itemPtr",  CSC_BADARG);
   ASSERT_RTN (itemSize > 0,    "CSClistPush: null itemSize", CSC_BADARG);
   ASSERT_RTN (								\
              (push == CSC_DATA_NODUP) || (push == CSC_DATA_DUP),	\
              "CSClistPush: invalid push",				\
              CSC_BADARG						\
              );

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistPush: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistPush: list blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(list);

   pushStat = nodeNew (list->memList, &node, push, itemPtr, itemSize);
   if (pushStat == CSC_OK)
      {
      pushStat = nodePush (list, node);
      }
   if (pushStat == CSC_OK)
      {
      if (list->profiling == CSC_DO_PROFILING)
         {
         list->pushCount += 1;
         list->curAlloc += itemSize;
         if (list->curAlloc > list->maxAlloc) list->maxAlloc = list->curAlloc;
         }
      }
   else
      {
      (void)nodeDel (list->memList, node);
      }

   MON_EXIT(list);

   return (pushStat);
   }


/**************************************************************************
 * Public Function CSClistPop
 **************************************************************************

<SUBROUTINE NAME="CSClistPop">

NAME
        CSClistPop - pop an entry from a libcsc list and retrieve its data

SYNOPSYS
        #include "libcsc.h"

        int   CSClistPop (
                         CSClistType       const list,
                         CSClistBiasType         bias,
                         void**            const itemPtrPtr,
                         size_t*           const itemSizePtr
                         );

RETURN VALUE
        CSClistPop(), if successful, returns CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistPop() pop the head (newest) or tail (oldest) entry from `list'
        depending upon the value of `bias'.  Valid values of `bias':

                CSC_LIST_HEAD   pop the head (newest) entry.

                CSC_LIST_TAIL   pop the tail (oldest) entry.

        The entry is removed from `list', and its data is retrieved.

        If `itemPtrPtr' is not NULL, then the popped entry's data pointer is
        written to the void pointer that is pointed to by `itemPtrPtr'.

        NOTE    If the retreived data was pushed into the list with the push
                type of CSC_DATA_DUP, then the retreived data is dynamically
                allocated (with malloc(), calloc(), etc.) and the caller is
                responsible for freeing (with free()) the retreived data.

        If `itemSizePtr' is not NULL, then the popped entry's data size is
        written to the size_t that is pointed to by `itemSizePtr'.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistPop) (
                          CSClistType       const list,
                          CSClistBiasType         bias,
                          void**            const itemPtrPtr,
                          size_t*           const itemSizePtr
                          )
   {
   int               popStat = CSC_OK;
   CSClistNodeType   node    = NULL;

   ASSERT_RTN (list    != NULL,     "CSClistPop: null list",        CSC_BADARG);
   ASSERT_RTN (itemPtrPtr != NULL,  "CSClistPop: null itemPtrPtr",  CSC_BADARG);
   ASSERT_RTN (itemSizePtr != NULL, "CSClistPop: null itemSizePtr", CSC_BADARG);
   ASSERT_RTN (								\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "CSClistPop: invalid bias",				\
              CSC_BADARG						\
              );

   ASSERT_RTN (				\
              list->sig_lo == LIST_SIG,	\
              "CSClistPop: list blows",	\
              CSC_CORRUPT		\
              );
   ASSERT_RTN (				\
              list->sig_hi == LIST_SIG,	\
              "CSClistPop: list blows",	\
              CSC_CORRUPT		\
              );

   MON_ENTER(list);

   popStat = nodePop (list, bias, &node);
   if (node != NULL)
      {
      ASSERT (node->sig_lo == LIST_SIG);
      ASSERT (node->sig_hi == LIST_SIG);
      if (node->push == CSC_DATA_DUP)
         {
         /* node->data is going to be free()ed, so make a copy of it so that */
         /* it is not free()ed out from under the client just before it is   */
         /* returned from this function.                                     */
         if (itemPtrPtr  != NULL)
            {
            *itemPtrPtr = calloc (node->size, sizeof(char));
            (void)memcpy (*itemPtrPtr, node->data, node->size);
            }
         }
      else
         {
         if (itemPtrPtr  != NULL) *itemPtrPtr  = (void*)node->data;
         }
      if (itemSizePtr != NULL) *itemSizePtr = node->size;
      if (list->profiling == CSC_DO_PROFILING)
         {
         list->popCount += 1;
         list->curAlloc -= node->size;
         }
      (void)nodeDel (list->memList, node);
      }
   else
      {
      if (popStat == CSC_OK) popStat = CSC_NOTFOUND;
      }

   MON_EXIT(list);

   return (popStat);
   }


/**************************************************************************
 * Public Function CSClistPeek
 **************************************************************************

<SUBROUTINE NAME="CSClistPeek">

NAME
        CSClistPeek - retrieve data from entry at libcsc list head or tail

SYNOPSYS
        #include "libcsc.h"

        int   CSClistPeek (
                          CSClistType       const list,
                          CSClistBiasType         bias,
                          void**            const itemPtrPtr,
                          size_t*           const itemSizePtr
                          );

RETURN VALUE
        CSClistPeek(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistPeek() peeks at the head (newest) or tail (oldest) entry in
        `list' and retrieves the data pointer and size.  When bias is:

        CSC_LIST_HEAD   If `itemPtrPtr' is not NULL, then the data pointer from
                        the list head (newest) entry is written to the void
                        pointer that is pointed to by `itemPtrPtr'.

                        If `itemSizePtr' is not NULL, then the data size from
                        the list head (newest) entry is written to the size_t
                        that is pointed to by `itemSizePtr'.

        CSC_LIST_TAIL   If `itemPtrPtr' is not NULL, then the data pointer from
                        the list tail (oldest) entry is written to the void
                        pointer that is pointed to by `itemPtrPtr'.

                        If `itemSizePtr' is not NULL, then the data size from
                        the list tail (oldest) entry is written to the size_t
                        that is pointed to by `itemSizePtr'.

        If both `itemPtrPtr' and `itemSizePtr' are NULL then CSClistPeek()
        doesn't do anything very interesting.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistPeek) (
                           CSClistType       const list,
                           CSClistBiasType         bias,
                           void**            const itemPtrPtr,
                           size_t*           const itemSizePtr
                           )
   {
   int               peekStat = CSC_OK;
   CSClistNodeType   node     = NULL;

   ASSERT_RTN (list!=NULL,        "CSClistPeek: null list",        CSC_BADARG);
   ASSERT_RTN (itemPtrPtr!=NULL,  "CSClistPeek: null itemPtrPtr",  CSC_BADARG);
   ASSERT_RTN (itemSizePtr!=NULL, "CSClistPeek: null itemSizePtr", CSC_BADARG);
   ASSERT_RTN (								\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "CSClistPeek: invalid bias",				\
              CSC_BADARG						\
              );

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistPeek: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistPeek: list blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(list);

   switch (bias)
      {
      default:             peekStat = CSC_ERROR;  break;
      case CSC_LIST_HEAD:  node = list->head;     break;
      case CSC_LIST_TAIL:  node = list->tail;     break;
      }

   if (node != NULL)
      {
      ASSERT (node->sig_lo == LIST_SIG);
      ASSERT (node->sig_hi == LIST_SIG);
      if (itemPtrPtr  != NULL) *itemPtrPtr  = (void*)node->data;
      if (itemSizePtr != NULL) *itemSizePtr = node->size;
      }

   MON_EXIT(list);

   return (peekStat);
   }


/***************************************************************************
 * Public Function CSClistNodeNext
 ***************************************************************************

<SUBROUTINE NAME="CSClistNodeNext">

NAME
        CSClistNodeNext - find next entry (node) in a libcsc list

SYNOPSYS
        #include "libcsc.h"

        CSClistNodeType   CSClistNodeNext (
                                          CSClistType       const list,
                                          CSClistBiasType         bias,
                                          CSClistNodeType         node
                                          );

RETURN VALUE
        CSClistNodeNext(), if successful, returns an opaque libcsc list node.
        If not successful, CSClistNodeNext() returns NULL.

DESCRIPTION
        CSClistNodeNext() uses the libcsc list referred to by the opaque `list'
        and returns the next/previous consecutive entry following/preceding the
        entry indicated by the opaque `node'.

        `bias' specifies whether the next or previous node is retreievd.  Legal
        values for `bias' are CSC_LIST_HEAD and CSC_LIST_TAIL.

        If `node' is NULL, then the first item (head or tail depending upon the
        value of `bias') in list is returned.

        If `list' has no entries, or there are no more entries (nodes) following
        `node', then NULL is returned.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSClistNodeType   (CSClistNodeNext) (
                                           CSClistType       const list,
                                           CSClistBiasType         bias,
                                           CSClistNodeType         node
                                           )
   {
   CSClistNodeType   nextNode = NULL;

   ASSERT_RTN (					\
              list != NULL,			\
              "CSClistNodeNext: null list",	\
              NULL				\
              );

   ASSERT_RTN (							\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "CSClistNodeNext: invalid bias",			\
              NULL						\
              );

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistNodeNext: list blows",	\
              NULL				\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistNodeNext: list blows",	\
              NULL				\
              );

   MON_ENTER(list);

   if (node == NULL)
      {
      switch (bias)
         {
         default:             nextNode = NULL;        break;
         case CSC_LIST_HEAD:  nextNode = list->head;  break;
         case CSC_LIST_TAIL:  nextNode = list->tail;  break;
         }
      }
   else
      {
#ifdef	DEBUG
      if (nodeValidate(list,node) != CSC_OK) nextNode = NULL; else
#endif
      nextNode = SUCC(node);
      switch (bias)
         {
         default:             nextNode = NULL;        break;
         case CSC_LIST_HEAD:  nextNode = SUCC(node);  break;
         case CSC_LIST_TAIL:  nextNode = PRED(node);  break;
         }
      }

#ifdef	DEBUG
   if (nextNode != NULL)
      {
      if ((nextNode->sig_lo != LIST_SIG) || (nextNode->sig_hi != LIST_SIG))
         {
         MON_EXIT(list);
         ASSERT_RTN (CSC_FALSE, "CSClistNodeNext: node blows", NULL);
         }
      }
#endif

   MON_EXIT(list);

   return (nextNode);
   }


/**************************************************************************
 * Private Function CSClistNodeFindByValue
 **************************************************************************

<SUBROUTINE NAME="CSClistNodeFindByValue">

NAME
        CSClistNodeFindByValue - find libcsc list entry by data value

SYNOPSYS
        #include "libcsc.h"

        CSClistNodeType   CSClistNodeFindByValue (
                                                 CSClistType       const list,
                                                 CSClistBiasType         bias,
                                           const void*             const itemPtr
                                                 );

RETURN VALUE
        CSClistNodeFindByValue(), returns a CSClistNodeType if it is
        successful, or NULL if otherwise not successful.

DESCRIPTION
        CSClistNodeFindByValue() searches `list' for an entry (node).  The
        search is either from the head of `list' or the tail; this is specified
        by `bias', which is one of

                CSC_LIST_HEAD   Search from the most recently added entries.

                CSC_LIST_TAIL   Search from the oldest entry.

        Beginning at the specified end (head or tail), each entry's (node's)
        data is compared against the data at `itemPtr'.  This compare is
        implemented by `list's client-specified compare function.  If `list'
        does not have a client specified compare function, then
        CSClistNodeFindByValue() will fail and return NULL.

        `list's client-specified compare function is used in this manner:

                if ((*list->cfunc) ((void*)itemPtr, (void*)entry->dataPtr) == 0)
                        return (entry);

        If `list's client-specified compare function returns zero, then the
        search is terminated, and the first entry found containing the desired
        data is returned.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSClistNodeType   (CSClistNodeFindByValue) (
                                                 CSClistType       const list,
                                                 CSClistBiasType         bias,
                                           const void*             const itemPtr
                                                  )
   {
   CSClistNodeType   node = NULL;
   CSClistNodeType   link = NULL;

   ASSERT_RTN (								\
              list != NULL,						\
              "CSClistNodeFindByValue: null list",			\
              NULL							\
              );
   ASSERT_RTN (								\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "CSClistNodeFindByValue: invalid bias",			\
              NULL							\
              );
   ASSERT_RTN (								\
              itemPtr != NULL,						\
              "CSClistNodeFindByValue: null itemPtr",			\
              NULL							\
              );

   ASSERT_RTN (								\
              list->sig_lo == LIST_SIG,					\
              "CSClistNodeFindByValue: list blows",			\
              NULL							\
              );
   ASSERT_RTN (								\
              list->sig_hi == LIST_SIG,					\
              "CSClistNodeFindByValue: list blows",			\
              NULL							\
              );

   if (list->cmpFunc == NULL) return (NULL);

   MON_ENTER(list);

   switch (bias)
      {
      default:             link = NULL;        break;
      case CSC_LIST_HEAD:  link = list->head;  break;
      case CSC_LIST_TAIL:  link = list->tail;  break;
      }

   while ((link != NULL) && (node == NULL))
      {
      if ((*(list->cmpFunc))((void*)itemPtr,(void*)link->data) == 0)
         node = link;
      else
         switch (bias)
            {
            default:             link = NULL;        break;
            case CSC_LIST_HEAD:  link = SUCC(link);  break;
            case CSC_LIST_TAIL:  link = PRED(link);  break;
            }
      }

   MON_EXIT(list);

   return (node);
   }


/**************************************************************************
 * Private Function CSClistNodeFindByReference
 **************************************************************************

<SUBROUTINE NAME="CSClistNodeFindByReference">

NAME
        CSClistNodeFindByReference - find libcsc list entry (node) by reference

SYNOPSYS
        #include "libcsc.h"

        CSClistNodeType   CSClistNodeFindByReference (
                                                CSClistType       const list,
                                                CSClistBiasType         bias,
                                          const void*             const itemPtr
                                                     );

RETURN VALUE
        CSClistNodeFindByReference(), returns a CSClistNodeType if it is
        successful, or NULL if otherwise not successful.

DESCRIPTION
        CSClistNodeFindByReference() searches `list' for an entry (node).  The
        search is either from the head of `list' or the tail; this is specified
        by `bias', which is one of

                CSC_LIST_HEAD   Search from the most recently added entries.

                CSC_LIST_TAIL   Search from the oldest entry.

        Beginning at the specified end (head or tail), each entry's (node's)
        data pointer is compared to `itemPtr'.  CSClistNodeFindByReference()
        returns the first entry (node) whose data pointer is equal to `itemPtr'.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSClistNodeType   (CSClistNodeFindByReference) (
                                                CSClistType       const list,
                                                CSClistBiasType         bias,
                                          const void*             const itemPtr
                                                      )
   {
   CSClistNodeType   node = NULL;
   CSClistNodeType   link = NULL;

   ASSERT_RTN (								\
              list != NULL,						\
              "CSClistNodeFindByReference: null list",			\
              NULL							\
              );
   ASSERT_RTN (								\
              (bias == CSC_LIST_HEAD) || (bias == CSC_LIST_TAIL),	\
              "CSClistNodeFindByReference: invalid bias",		\
              NULL							\
              );
   ASSERT_RTN (								\
              itemPtr != NULL,						\
              "CSClistNodeFindByReference: null itemPtr",		\
              NULL							\
              );

   ASSERT_RTN (								\
              list->sig_lo == LIST_SIG,					\
              "CSClistNodeFindByReference: list blows",			\
              NULL							\
              );
   ASSERT_RTN (								\
              list->sig_hi == LIST_SIG,					\
              "CSClistNodeFindByReference: list blows",			\
              NULL							\
              );

   MON_ENTER(list);

   switch (bias)
      {
      default:             link = NULL;        break;
      case CSC_LIST_HEAD:  link = list->head;  break;
      case CSC_LIST_TAIL:  link = list->tail;  break;
      }

   while ((link != NULL) && (node == NULL))
      {
      if (link->data == itemPtr)
         node = link;
      else
         switch (bias)
            {
            default:             link = NULL;        break;
            case CSC_LIST_HEAD:  link = SUCC(link);  break;
            case CSC_LIST_TAIL:  link = PRED(link);  break;
            }
      }

   MON_EXIT(list);

   return (node);
   }


/***************************************************************************
 * Public Function CSClistNodeStat
 ***************************************************************************

<SUBROUTINE NAME="CSClistNodeStat">

NAME
        CSClistNodeStat - retrieve data fields from a libcsc list entry (node)

SYNOPSYS
        #include "libcsc.h"

        int   CSClistNodeStat (
                              CSClistNodeType   const node,
                              void**            const itemPtrPtr,
                              size_t*           const itemSizePtr
                              );

RETURN VALUE
        CSClistNodeStat(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistNodeStat() retrieves the relevant values of a list entry (node).

        If `itemPtrPtr' is not NULL, then entry's (node's) data pointer is
        written to the void pointer that is pointed to by `itemPtrPtr'.

        If `itemSizePtr' is not NULL, then entry's (node's) data size is
        written to the size_t that is pointed to by `itemSizePtr'.

        If both itemPtrPtr and itemSizePtr are NULL, then CSClistNodeStat()
        doesn't do anything very interesting.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeValidate(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSClistNodeStat) (
                               CSClistNodeType   const node,
                               void**            const itemPtrPtr,
                               size_t*           const itemSizePtr
                               )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (node != NULL, "CSClistNodeStat: null entry", CSC_BADARG);

   ASSERT_RTN (					\
              node->sig_lo == LIST_SIG,		\
              "CSClistNodeStat: node blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi == LIST_SIG,		\
              "CSClistNodeStat: node blows",	\
              CSC_CORRUPT			\
              );

   if (itemPtrPtr  != NULL) *itemPtrPtr  = (void*)node->data;
   if (itemSizePtr != NULL) *itemSizePtr = node->size;

   return (statStat);
   }


/**************************************************************************
 * Public Function CSClistNodeValidate
 **************************************************************************

<SUBROUTINE NAME="CSClistNodeValidate">

NAME
        CSClistNodeValidate - verify an entry (node) is really in a libcsc list

SYNOPSYS
        #include "libcsc.h"

        int   CSClistNodeValidate (
                                  CSClistType       const list,
                                  CSClistNodeType   const node
                                  );

RETURN VALUE
        CSClistNodeValidate(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSClistNodeValidate() looks up `node' in `list' to validate that `node'
        is actually in `list'.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistNodeValidate) (
                                   CSClistType       const list,
                                   CSClistNodeType   const node
                                   )
   {
   int   validStat = CSC_NOTFOUND;

   ASSERT_RTN (list != NULL, "CSClistNodeValidate: null list", CSC_BADARG);
   ASSERT_RTN (node != NULL, "CSClistNodeValidate: null node", CSC_BADARG);

   ASSERT_RTN (						\
              list->sig_lo == LIST_SIG,			\
              "CSClistNodeValidate: list blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              list->sig_hi == LIST_SIG,			\
              "CSClistNodeValidate: list blows",	\
              CSC_CORRUPT				\
              );

   ASSERT_RTN (						\
              node->sig_lo == LIST_SIG,			\
              "CSClistNodeValidate: node blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              node->sig_hi == LIST_SIG,			\
              "CSClistNodeValidate: node blows",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(list);

   validStat = nodeValidate (list, node);

   MON_EXIT(list);

   return (validStat);
   }


/**************************************************************************
 * Public Function CSClistNodeDel
 **************************************************************************

<SUBROUTINE NAME="CSClistNodeDel">

NAME
        CSClistNodeDel - remove an entry (node) from a libcsc list

SYNOPSYS
        #include "libcsc.h"

        int   CSClistNodeDel (
                             CSClistType       const list,
                             CSClistNodeType         node
                             );

RETURN VALUE
        CSClistNodeDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        The list entry (node)specified by the opaque `node' is removed from
        `list'.

SEE ALSO
        CSClistNew(3)
        CSClistDel(3)
        CSClistRead(3)
        CSClistWrite(3)
        CSClistSetCFunc(3)
        CSClistStat(3)
        CSClistPush(3)
        CSClistPop(3)
        CSClistPeek(3)
        CSClistNodeNext(3)
        CSClistNodeFindByValue(3)
        CSClistNodeFindByReference(3)
        CSClistNodeStat(3)
        CSClistNodeValidate(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSClistNodeDel) (
                              CSClistType       const list,
                              CSClistNodeType         node
                              )
   {
   int   delStat = CSC_OK;

   ASSERT_RTN (list != NULL, "CSClistNodeDel: null list", CSC_BADARG);
   ASSERT_RTN (node != NULL, "CSClistNodeDel: null node", CSC_BADARG);

   ASSERT_RTN (					\
              list->sig_lo == LIST_SIG,		\
              "CSClistNodeDel: list blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              list->sig_hi == LIST_SIG,		\
              "CSClistNodeDel: list blows",	\
              CSC_CORRUPT			\
              );

   ASSERT_RTN (					\
              node->sig_lo == LIST_SIG,		\
              "CSClistNodeDel: node blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi == LIST_SIG,		\
              "CSClistNodeDel: node blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(list);

#ifdef	DEBUG
   if (nodeValidate(list,node) != CSC_OK)
      {
      delStat = CSC_NOTFOUND;
      }
   else
#endif
      {
      delStat = nodeDelink (list, node);
      if (delStat == CSC_OK)
         {
         if (list->profiling == CSC_DO_PROFILING)
            {
            list->popCount += 1;
            list->curAlloc -= node->size;
            }
         (void)nodeDel (list->memList, node);
         }
      }

   MON_EXIT(list);

   return (delStat);
   }


/* End of the file. */
