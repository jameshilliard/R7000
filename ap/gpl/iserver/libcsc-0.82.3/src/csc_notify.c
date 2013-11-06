/* *****************************************************************************

libcsc: Notification System Subsystem

Copyright (c) 1999, 2000, 2002 Douglas R. Jerome, Peoria, AZ USA

	----------------------------------------------------------------

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

	$RCSfile: csc_notify.c,v $
	$Revision: 1.2 $
	$Date: 2003/03/24 04:26:04 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_notify">

NAME
	csc_notify

DESCRIPTION
	Notification System (callback) Subsystem

	Create a notification board, add some notifications to it, then
	regisiter some functions, each with some private data (pointer is
	useful) on some the the notifications.  When a notification is posted,
	the registered functions will be called, each with their corresponding
	private data.

FUNCTIONS
	CSCnotificationBoardNew   - create a new notification board
	CSCnotificationBoardDel   - completely remove a notification board
	CSCnotificationBoardPrint - print a notification board in ASCII format
	CSCnotificationNew        - create a new notification in a board
	CSCnotificationDel        - delete a notification from a board
	CSCnotificationPost       - post to a notification in a board
	CSCnotificationRegister   - register client function to a notification
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added #include <string.h>.

	24apr02	drj	Fixed list usage bug in CSCnotificationBoardPrint().
			Fixed S_notifNodeType usage bug in rmClient() and
			CSCnotificationRegister().

	20apr02	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	13may00	drj	Fixed memory leak in rtsNotificationBoardDel().

	11may00	drj	Fixed several functions to return RTS_BADARG when
			asserting function arguments.

	28apr00	drj	Fixed bug in rtsNotificationDel().

	26apr00	drj	Simplified the function prototypes and external data
			structures. Removed rtsNotificationRemove().

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

#define	NOTIF_SIG	(0x4E4F5449)

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

typedef struct S_notifNodeType
   {
#ifdef	DEBUG
   long                sig_lo;
#endif
   CSCmemListType      memList;
   const char*         name;
   CSCgenFnType        fn;
   const CSCboolean*   runFlag;
   int                 tag;
   const void*         data;
#ifdef	DEBUG
   long                sig_hi;
#endif
   } S_notifNodeType;

typedef struct S_notificationType
   {
#ifdef	DEBUG
   long             sig_lo;
#endif
   const char*      name;
   CSCbinTreeType   clients;
   CSCgenFnType     errfn;
   size_t           notifCount;
#ifdef	DEBUG
   long             sig_hi;
#endif
   } S_notificationType;

typedef struct S_notifBoardType
   {
#ifdef	DEBUG
   long              sig_lo;
#endif
   const char*       name;
   CSCmemListType    memList;
   CSClistType       list;
   CSCprofileType    profiling;
   CSCmonFnType      monFunc;
   const void*       monData;
#ifdef	DEBUG
   long              sig_hi;
#endif
   } S_notifBoardType;


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

PRIVATE int   postAction (
                         void*   binTreeNodePtr,
                         void*   binTreeClientDataPtr
                         );

PRIVATE S_notificationType*   findNotification (
                                          const S_notifBoardType*   const board,
                                          const char*               const name
                                               );

PRIVATE int   rmClient (
                       int     binTreeNodeTag,
                       int     binTreeClientDataSize,
                       void*   binTreeClientDataPtr
                       );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function postAction
 **************************************************************************/

PRIVATE int   postAction (
                         void*   binTreeNodePtr,
                         void*   binTreeClientDataPtr
                         )
   {
         int                         postStat  = CSC_NOTFOUND;
         CSCbinTreeNodeType    const nodePtr   = binTreeNodePtr;
   const S_notificationType*   const notifPtr  = binTreeClientDataPtr;
   const S_notifNodeType*            clientPtr = NULL;

   ASSERT_RTN (nodePtr !=NULL,"postAction: no binTreeNodePtr",      CSC_BADARG);
   ASSERT_RTN (notifPtr!=NULL,"postAction: no binTreeClientDataPtr",CSC_BADARG);

   (void)CSCbinTreeNodeStat (nodePtr, NULL, NULL, NULL, (void**)&clientPtr);
   if (*(clientPtr->runFlag) == CSC_TRUE)
      {
      postStat = (*clientPtr->fn) (
                                  notifPtr->notifCount,
                                  clientPtr->tag,
                                  (void*)clientPtr->data
                                  );
      }

   return (postStat);
   }


/**************************************************************************
 * Private Function findNotification
 **************************************************************************/

PRIVATE S_notificationType*   findNotification (
                                          const S_notifBoardType*   const board,
                                          const char*               const name
                                               )
   {
   S_notificationType*   notif     = NULL;
   CSClistNodeType       listNode  = NULL;
   int                   foundStat = CSC_NOTFOUND;

   ASSERT_RTN (board != NULL, "findNotification: null board", NULL);
   ASSERT_RTN (name != NULL,  "findNotification: null name",  NULL);

   listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, NULL);
   while ((listNode != NULL) && (foundStat == CSC_NOTFOUND))
      {
      (void)CSClistNodeStat (listNode, (void**)&notif, NULL);
      if (notif != NULL)
         {
         if (CSC_STREQ(notif->name,name)) foundStat = CSC_OK;
         }
      listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, listNode);
      }

   return (notif);
   }


/**************************************************************************
 * Private Function rmClient
 **************************************************************************/

PRIVATE int   rmClient (
                       int     binTreeNodeTag,
                       int     binTreeNodeDataSize,
                       void*   binTreeNodeDataPtr
                       )
   {
   S_notifNodeType*   node = (S_notifNodeType*)binTreeNodeDataPtr;
   CSCmemListType     memList;

   ASSERT_RTN (binTreeNodeDataPtr != NULL, "rmClient: null node", CSC_BADARG);

   ASSERT_RTN (node->sig_lo == NOTIF_SIG, "rmClient: node blows", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi == NOTIF_SIG, "rmClient: node blows", CSC_CORRUPT);

   binTreeNodeTag = binTreeNodeTag;           /* keep the compiler quiet */
   binTreeNodeDataSize = binTreeNodeDataSize; /* keep the compiler quiet */

   memList = node->memList;
   (void)CSCmemFree (memList, (void**)&node, 0);

   return (CSC_OK);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCnotificationBoardNew
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationBoardNew">

NAME
        CSCnotificationBoardNew - create a new notification board

SYNOPSYS
        #include "libcsc.h"

        CSCnotificationBoardType   CSCnotificationBoardNew (
                                                const char*            name,
                                                      CSCmonFnType     monFunc,
                                                const void*            monData,
                                                      CSCprofileType   profiling
                                                           );

RETURN VALUE
        CSCnotificationBoardNew(), if successful, returns an opaque data type
        representing a new libcsc notification board, or NULL if otherwise not
        successful.

DESCRIPTION
        CSCnotificationBoardNew() creates a new libcsc notification board.  A
        notification board is simply something to hold an arbitrary number of
        notifications (like a cork note board).

        `profiling' can be CSC_DO_PROFILING or CSC_NO_PROFILING; it specifies
        whether alocate/free statistics should actually be generated and kept
        in the list.

SEE ALSO
        CSCnotificationBoardDel(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationNew(3)
        CSCnotificationDel(3)
        CSCnotificationPost(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCnotificationBoardType   (CSCnotificationBoardNew) (
                                                const char*            name,
                                                      CSCmonFnType     monFunc,
                                                const void*            monData,
                                                      CSCprofileType   profiling
                                                            )
   {
   S_notifBoardType*   newBoard = NULL;
   CSCmemListType      memList  = NULL;

   ASSERT_RTN (name != NULL, "CSCnotificationBoardNew: null name", NULL);
   ASSERT_RTN (							\
              ((profiling==CSC_DO_PROFILING)||(profiling==CSC_NO_PROFILING)),\
              "CSCnotificationBoardNew: illegal profile value",	\
              NULL						\
              );

   memList = CSCmemInit (name, NULL, NULL, NULL, profiling);
   if (memList != NULL)
      {
      (void)CSCmemAlloc (
                        memList,
                        (void**)&newBoard,
                        1,
                        sizeof(S_notifBoardType),
                        0
                        );
      if (newBoard != NULL)
         {
         newBoard->name       = name;
         newBoard->memList    = memList;
         newBoard->list       = CSClistNew (name, NULL, NULL, profiling);
         newBoard->profiling  = profiling;
         newBoard->monFunc    = monFunc;
         newBoard->monData    = monData;
#ifdef  DEBUG
         newBoard->sig_lo = NOTIF_SIG;
         newBoard->sig_hi = NOTIF_SIG;
#endif
         if (newBoard->list == NULL)
            {
            (void)CSCmemFree (memList, (void**)&newBoard, 0);
            (void)CSCmemDone (memList);
            newBoard = NULL;
            }
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (newBoard);
   }


/***************************************************************************
 * Public Function CSCnotificationBoardDel
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationBoardDel">

NAME
        CSCnotificationBoardDel - completely remove a notification board

SYNOPSYS
        #include "libcsc.h"

        int   CSCnotificationBoardDel (
                                      CSCnotificationBoardType   const board
                                      );

RETURN VALUE
        CSCnotificationBoardDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCnotificationBoardDel() deletes the notification `board' including all
        the notification entries it contains.

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationNew(3)
        CSCnotificationDel(3)
        CSCnotificationPost(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCnotificationBoardDel) (
                                       CSCnotificationBoardType   const board
                                       )
   {
   int                   delStat    = CSC_OK;
   int                   tmpStat    = CSC_OK;
   CSClistNodeType       listNode   = NULL;
   S_notificationType*   notif      = NULL;

   ASSERT_RTN (board!=NULL, "CSCnotificationBoardDel: null board", CSC_BADARG);

   ASSERT_RTN (						\
              board->sig_lo == NOTIF_SIG,		\
              "CSCnotificationBoardDel: board blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              board->sig_hi == NOTIF_SIG,		\
              "CSCnotificationBoardDel: board blows",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(board);

   listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, NULL);
   while (listNode != NULL)
      {
      notif = NULL;
      tmpStat = CSClistNodeStat (listNode, (void**)&notif, NULL);
      if (tmpStat == CSC_OK) delStat = tmpStat;
      if (notif != NULL)
         {
         if (notif->clients != NULL)
            {
            tmpStat = CSCbinTreeDel (notif->clients, rmClient);
            if (tmpStat != CSC_OK) delStat = tmpStat;
            }
         (void)CSCmemFree (board->memList, (void**)&notif, 0);
         }
      listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, listNode);
      }

#ifdef	UNDEF
   {
   size_t   pushCount, popCount;
   (void)CSClistStat (board->list, &pushCount, &popCount, NULL, NULL);
   ASSERT (pushCount-popCount == 0);
   }
#endif

   {
   CSCmemListType   memList = board->memList;
   CSCmonFnType     monFunc = board->monFunc;
   const void*      monData = board->monData;
   tmpStat = CSClistDel (board->list);
   if (tmpStat != CSC_OK) delStat = tmpStat;
   (void)CSCmemFree (memList, (void**)&board, 0);
   (void)CSCmemDone (memList);
   if (monFunc != NULL) (*monFunc) (CSC_OUT, (void*)monData);
   }

   return (delStat);
   }


/***************************************************************************
 * Public Function CSCnotificationBoardPrint
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationBoardPrint">

NAME
        CSCnotificationBoardPrint - print a notification board in ASCII format

SYNOPSYS
        #include "libcsc.h"

        void   CSCnotificationBoardPrint (
                                         CSCnotificationBoardType   const board
                                         );

RETURN VALUE
        CSCnotificationBoardPrint() has no return value.

DESCRIPTION
        CSCnotificationBoardPrint() prints to standard output the libcsc
        notification board represented by the opaque `board' in an ASCII format.

BUGS
        There is no error check in this function.  Lame.

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardDel(3)
        CSCnotificationNew(3)
        CSCnotificationDel(3)
        CSCnotificationPost(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC void   (CSCnotificationBoardPrint) (
                                          CSCnotificationBoardType   const board
                                          )
   {
   CSClistNodeType       listNode = NULL;
   S_notificationType*   notif    = NULL;
   size_t                pushCount;
   size_t                popCount;

   MON_ENTER(board);

   if (board != NULL)
      {
      (void)CSClistStat (board->list, &pushCount, &popCount, NULL, NULL);
      printf ("\n");
      printf (
             "Dump of Notification Board (%ld entries):\n",
             (long)pushCount-popCount
             );
      printf ("\n");
      listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, NULL);
      while (listNode != NULL)
         {
         (void)CSClistNodeStat (listNode, (void**)&notif, NULL);
         (void)printf ("notifCount:  %d\n", notif->notifCount);
         (void)printf ("      name:  %s\n", notif->name);
         (void)printf ("clientList:  %p\n", notif->clients);
         (void)printf ("     errfn:  %p\n", notif->errfn);
         (void)printf ("\n");
         listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, listNode);
         }
      }
   else
      {
      (void)printf ("\nNo board!\n");
      }

   MON_EXIT(board);

   return;
   }


/***************************************************************************
 * Public Function CSCnotificationNew
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationNew">

NAME
        CSCnotificationNew - create a new notification in a board

SYNOPSYS
        #include "libcsc.h"

        int   CSCnotificationNew (
                                       CSCnotificationBoardType   const board,
                                 const char*                            name,
                                       CSCgenFnType                     errfn
                                 );

RETURN VALUE
        CSCnotificationNew(), if successful, CSC_OK; otherwise, CSC_NOTFOUND,
        CSC_BADARG, and CSC_CORRUPT can be returned corresponding to NULL
        pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCnotificationNew() creates a new notification entry and puts it into
        notification `board'.

        `name' points to the character string that names the new notification
        entry.

        `errfn' is a pointer to a libcsc CSCgenFnType function that is called
        when a call to `post' a notification, CSCnotificationPost() (which
        tries to distribute the notification), results in an an error.  The
        prototype for `errfn' is:

                int    (*CSCgenFnType) (int, int, void*);

        The client callback error function `errfn' is called with the current
        notification count and notification `name'; its return value is ignored:

                (void)((*errfn) (0, count, name);

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardDel(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationDel(3)
        CSCnotificationPost(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCnotificationNew) (
                                      CSCnotificationBoardType   const board,
                                const char*                            name,
                                      CSCgenFnType                     errfn
                                  )
   {
   int                   newStat  = CSC_OK;
   S_notificationType*   newNotif = NULL;
   CSCbinTreeType        clients;

   ASSERT_RTN (board != NULL, "CSCnotificationNew: null board", CSC_BADARG);
   ASSERT_RTN (name != NULL,  "CSCnotificationNew: null name",  CSC_BADARG);

   ASSERT_RTN (						\
              board->sig_lo == NOTIF_SIG,		\
              "CSCnotificationNew: board blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              board->sig_hi == NOTIF_SIG,		\
              "CSCnotificationNew: board blows",	\
              CSC_CORRUPT				\
              );

   clients = CSCbinTreeNew (name, NULL, NULL, board->profiling);
   if (clients == NULL) return (CSC_NOMEM);

   MON_ENTER(board);

   (void)CSCmemAlloc (
                     board->memList,
                     (void**)&newNotif,
                     1,
                     sizeof(S_notificationType),
                     0
                     );

   MON_EXIT(board);

   if (newNotif != NULL)
      {
      newNotif->name       = name;
      newNotif->clients    = clients;
      newNotif->errfn      = errfn;
      newNotif->notifCount = 0;

      MON_ENTER(board);

      newStat = CSClistPush (
                            board->list,
                            CSC_DATA_NODUP,
                            newNotif,
                            sizeof(S_notificationType)
                            );
      if (newStat != CSC_OK)
         {
         (void)CSCmemFree (board->memList, (void**)&newNotif, 0);
         }

      MON_EXIT(board);
      }
   else
      {
      newStat = CSC_NOMEM;
      }

   return (newStat);
   }


/***************************************************************************
 * Public Function CSCnotificationDel
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationDel">

NAME
        CSCnotificationDel - delete a notification from a board

SYNOPSYS
        #include "libcsc.h"

        int   CSCnotificationDel (
                                       CSCnotificationBoardType   const board,
                                 const char*                            name
                                 );

RETURN VALUE
        CSCnotificationDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCnotificationDel() looks in the notification `board' for the
        notification entry whose name matches `name' and deletes it.

BUGS
        Any clients registered for the particular notification being deleted
        will NOT be notified.

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardDel(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationNew(3)
        CSCnotificationPost(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCnotificationDel) (
                                        CSCnotificationBoardType   const board,
                                  const char*                            name
                                  )
   {
   int                   delStat   = CSC_OK;
   int                   tmpStat   = CSC_OK;
   int                   foundStat = CSC_NOTFOUND;
   CSClistNodeType       listNode  = NULL;
   S_notificationType*   notif     = NULL;

   ASSERT_RTN (board != NULL, "CSCnotificationDel: null board", CSC_BADARG);
   ASSERT_RTN (name != NULL,  "CSCnotificationDel: null name",  CSC_BADARG);

   ASSERT_RTN (						\
              board->sig_lo == NOTIF_SIG,		\
              "CSCnotificationDel: board blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              board->sig_hi == NOTIF_SIG,		\
              "CSCnotificationDel: board blows",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(board);

   listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, NULL);
   while ((listNode != NULL) && (foundStat == CSC_NOTFOUND))
      {
      tmpStat = CSClistNodeStat (listNode, (void**)&notif, NULL);
      if (tmpStat != CSC_OK) delStat = tmpStat;
      if (notif != NULL)
         {
         if (CSC_STREQ(notif->name,name))
            {
            if (notif->clients != NULL)
               {
               tmpStat = CSCbinTreeDel (notif->clients, rmClient);
               if (tmpStat != CSC_OK) delStat = tmpStat;
               }
            (void)CSCmemFree (board->memList, (void**)&notif, 0);
            foundStat = CSC_OK;
            }
         }
      if (foundStat == CSC_NOTFOUND)
         {
         listNode = CSClistNodeNext (board->list, CSC_LIST_HEAD, listNode);
         }
      }

   if (foundStat == CSC_OK)
      {
      delStat = CSClistNodeDel (board->list, listNode);
      }

   MON_EXIT(board);

   return (delStat);
   }


/***************************************************************************
 * Public Function CSCnotificationPost
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationPost">

NAME
	CSCnotificationPost - post to a notification in a board

SYNOPSYS
        #include "libcsc.h"

        int   CSCnotificationPost (
                                        CSCnotificationBoardType   const board,
                                  const char*                            name
                                  );

RETURN VALUE
        CSCnotificationPost(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCnotificationPost() dispatches all client functions registered for
        particular notification `name' in notification `board'.

        As the dispatched client functions are called they should return
        CSC_OK or CSC_NOTOUND.  If CSC_NOTFOUND is returned by a client
        function, then no more client functions registered for the notification
        are called for the particular notification action and and the
        notification's error function, pointed to by errfn, is called.  The
        error function, pointed to by errfn, is associated with the
        notification entry when the notification entry is created.  The error
        function's return value is ignored.

        The client functions are called in the order of their priority, which
        they specify with the tag value when they register.

        Client functions are libcsc CSCgenFnType types; their prototype is:

                int    (*CSCgenFnType) (int, int, void*);

        The client functions are called with a notification count,
        client-specified integer tag (used as the priority specifying the order
        in which the client functions are called), and client-specified data
        (with which they register):

                (*fn) (count, tag, data);

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardDel(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationNew(3)
        CSCnotificationDel(3)
        CSCnotificationRegister(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCnotificationPost) (
                                        CSCnotificationBoardType   const board,
                                  const char*                            name
                                   )
   {
   int                   postStat = CSC_OK;
   S_notificationType*   notif    = NULL;

   ASSERT_RTN (board!=NULL, "CSCnotificationPost: null board", CSC_BADARG);
   ASSERT_RTN (name!=NULL,  "CSCnotificationPost: null name",  CSC_BADARG);

   ASSERT_RTN (						\
              board->sig_lo == NOTIF_SIG,		\
              "CSCnotificationPost: board blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              board->sig_hi == NOTIF_SIG,		\
              "CSCnotificationPost: board blows",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(board);

   notif = findNotification (board, name);
   if (notif != NULL)
      {
      notif->notifCount += 1;
      postStat = CSCbinTreeTraverse ("INFIX",notif->clients,postAction,notif);
      if (postStat == CSC_OK) postStat = CSC_ERROR;
      if ((postStat != CSC_NOTFOUND) && (notif->errfn != NULL))
         {
         (void)(*(notif->errfn)) (0, notif->notifCount, (void*)notif->name);
         }
      if (postStat == CSC_NOTFOUND) postStat = CSC_OK;
      }
   else
      {
      postStat = CSC_NOTFOUND;
      }

   MON_EXIT(board);

   return (postStat);
   }


/***************************************************************************
 * Public Function CSCnotificationRegister
 ***************************************************************************

<SUBROUTINE NAME="CSCnotificationRegister">

NAME
        CSCnotificationRegister - register client function to a notification

SYNOPSYS
        #include "libcsc.h"

        int   CSCnotificationRegister (
                                    CSCnotificationBoardType   const board,
                              const char*                            notifName,
                              const char*                            clientName,
                                    CSCgenFnType                     fn,
                              const CSCboolean*                      runFlag,
                                    int                              tag,
                              const void*                            data
                                      );

RETURN VALUE
        CSCnotificationRegister(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCnotificationRegister() registers the client function pointed to by
        `fn' with the notification entry named by `notifName' in the
        notification board associated with `board'.

        Client functions are libcsc CSCgenFnType types; their prototype is:

                int    (*CSCgenFnType) (int, int, void*);

        The client functions are called with a notification count,
        client-specified integer tag, and client-specified data (with which
        they register):

                (*fn) (count, tag, data);

        Client functions should return CSC_OK or CSC_NOTOUND.  If CSC_NOTFOUND
        is returned by a client function, then no more client functions
        registered for the notification are called for the particular
        notification action, and and the notification's error function,
        pointed to by errfn, is called.  The error function, pointed to by
        errfn, is associated with the notification entry when the notification
        entry is created.  The error function's return value is ignored.

        `clientName' is used only for debug messages and notification board
        printing.

        When the notification named `notifName' is posted to, the function
        pointed to by `fn' is called.  `tag' and `data' are returned to the
        client as arguments to the client function `fn'.

        All client functions registered to a notification are called in order
        of their priority.  `tag' is used as the priority; all the client
        functions registered to a notification are called in the numerical
        value order of their tag.

        The client can dynamically control the calling of its registered
        function; if the value at `runFlag' is CSC_FALSE when the notification
        is posted to, then the registered client function will not be called.

SEE ALSO
        CSCnotificationBoardNew(3)
        CSCnotificationBoardDel(3)
        CSCnotificationBoardPrint(3)
        CSCnotificationNew(3)
        CSCnotificationDel(3)
        CSCnotificationPost(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCnotificationRegister) (
                                    CSCnotificationBoardType   const board,
                              const char*                            notifName,
                              const char*                            clientName,
                                    CSCgenFnType                     fn,
                              const CSCboolean*                      runFlag,
                                    int                              tag,
                              const void*                            data
                                       )
   {
   int                         registerStat   = CSC_OK;
   S_notificationType*         notif          = NULL;
   S_notifNodeType*            client         = NULL;
   CSCbinTreeNodeType          tmpBinTreeNode = NULL;

   ASSERT_RTN (						\
              board != NULL,				\
              "CSCnotificationRegister: null board",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              notifName != NULL,			\
              "CSCnotificationRegister: null notifName",\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              clientName != NULL,			\
              "CSCnotificationRegister: null clientName",\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              fn != NULL,				\
              "CSCnotificationRegister: null fn",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              runFlag != NULL,				\
              "CSCnotificationRegister: null runFlag",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              data != NULL,				\
              "CSCnotificationRegister: null data",	\
              CSC_BADARG				\
              );

   MON_ENTER(board);

   notif = findNotification (board, notifName);
   if (notif != NULL)
      {
      (void)CSCmemAlloc (
                        board->memList,
                        (void**)&client,
                        1,
                        sizeof(S_notifNodeType),
                        0
                        );
      if (client != NULL)
         {
         client->memList  = board->memList;
         client->name     = clientName;
         client->fn       = fn;
         client->runFlag  = runFlag;
         client->tag      = tag;
         client->data     = data;
#ifdef	DEBUG
         client->sig_lo = NOTIF_SIG;
         client->sig_hi = NOTIF_SIG;
#endif
         tmpBinTreeNode = CSCbinTreeNodeNew (
                                            CSC_DATA_NODUP,
                                            (long)tag,
                                            client,
                                            sizeof(S_notifNodeType)
                                            );
         if (tmpBinTreeNode != NULL)
            {
            registerStat = CSCbinTreeTagOrderedInsert (
                                                      notif->clients,
                                                      tmpBinTreeNode
                                                      );
            if (registerStat != CSC_OK)
               {
               (void)CSCbinTreeNodeDel (tmpBinTreeNode);
               (void)CSCmemFree (board->memList, (void**)&client, 0);
               }
            }
         else
            {
            registerStat = CSC_NOMEM;
            (void)CSCmemFree (board->memList, (void**)&client, 0);
            }
         }
      else
         {
         registerStat = CSC_NOMEM;
         }
      }
   else
      {
      registerStat = CSC_NOTFOUND;
      }

   MON_EXIT(board);

   return (registerStat);
   }


/* End of the file. */
