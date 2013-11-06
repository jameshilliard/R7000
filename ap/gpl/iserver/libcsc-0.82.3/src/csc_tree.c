/* *****************************************************************************

libcsc:  Balanced Binary Tree Subsystem

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

	$RCSfile: csc_tree.c,v $
	$Revision: 1.4 $
	$Date: 2002/04/30 05:41:21 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

	The balanced tree insertion algorithm is directly taken from Donald E.
	Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
	(Reading Mass.:  Addison-Wesley 1973).

<SUBSYSTEM NAME="csc_tree">

NAME
	csc_tree

DESCRIPTION
	Balanced Binary Tree Subsystem

	The CSCbinTree functions provide an interface to a balanced binary tree
	subsystem.  The tree is an opaque data type, and client code never has
	direct access to the nodes.  Note that you can't remove nodes, but the
	tree can be deleted.

	The CSCbinTreeNode functions provide individual node manipulation
	capability.  Trees can be built with the CSCbinTreeNodeJoin function,
	which returns a pointer to the upper node.  These trees are not likely
	to be balanced.

	Don't try mixing the CSCbinTree and CSCbinTreeNode functions on the
	same tree.

FUNCTIONS
		tree
		----
	CSCbinTreeNew - create an empty libcsc balanced binary tree
	CSCbinTreeDel - delete a libcsc balanced binary tree
	CSCbinTreeInsert - insert a node into a libcsc balanced binary tree
	CSCbinTreeTagOrderedInsert - put node into libcsc balanced binary tree
	CSCbinTreeTraverse - traverse a libcsc balanced binary tree
	CSCbinTreeUserSearch - arbitrary search of libcsc balanced binary tree
	CSCbinTreeTagSearch - search a balanced binary tree for node with tag
	CSCbinTreeStat - retrieve libcsc balanced binary tree statistics
	CSCbinTreePrint - print a libcsc balanced binary tree

		node
		----
	CSCbinTreeNodeNew - create a new empty libcsc binary tree node
	CSCbinTreeNodeDel - deallocate a libcsc binary tree node
	CSCbinTreeNodeJoin - join libcsc binary tree nodes
	CSCbinTreeNodeBreak - break libcsc binary tree at a node
	CSCbinTreeNodeTraverse - traverse a libcsc binary tree
	CSCbinTreeNodeUserSearch - arbitrary libcsc binary tree traversal
	CSCbinTreeNodeTagSearch - search a libcsc binary tree for a given tag
	CSCbinTreeNodeStat - retrieve fields from a libcsc binary tree node
	CSCbinTreeNodePrint - print the values of a libcsc binary tree node
</SUBSYSTEM>

CHANGE LOG

	21apr02	drj	Added internal documentation.

	14apr02	drj	Removed erroneous comment.
			Fixed miscellaneous debug code.

	10apr02	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Fixed rtsBinTreePrint() to return RT_ERROR for munged
			tree signature.  Tracked change to rtsMemDup().

	19apr00	drj	Fixed up DEBUG signatures.  Made tree and node types
			more opaque.

	24nov99	drj	Added rtsBinTreeNodeBreak().

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

#define	TREE_SIG	(0x45455254)

#define MON_ENTER(x)    {if(x->monFunc!=NULL)\
			(*x->monFunc)(CSC_IN,(void*)x->monData);}

#define MON_EXIT(x)     {if(x->monFunc!=NULL)\
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

typedef struct S_binTreeNodeType
   {
#ifdef	DEBUG
          long                 sig_lo;
#endif
          CSCmemListType       memList;
   struct S_binTreeNodeType*   left;
   struct S_binTreeNodeType*   right;
          CSCdataCntrlType     push;
          int                  balance;
          long                 tag;
   const  void*                data;
          size_t               size;
#ifdef	DEBUG
          long                 sig_hi;
#endif
   } S_binTreeNodeType;

typedef struct S_binTreeType
   {
#ifdef	DEBUG
          long                 sig_lo;
#endif
          const char*          name;
          CSCmemListType       memList;
   struct S_binTreeNodeType*   root;
          CSCprofileType       profiling;
          CSCmonFnType         monFunc;
          const void*          monData;
          size_t               count;
          size_t               height;
          size_t               compares;
          size_t               rotates;
#ifdef	DEBUG
          long                 sig_hi;
#endif
   } S_binTreeType;


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

PRIVATE int   binTreeDel (
                         CSCbinTreeNodeType   const node,
                         CSCgenFnType               cbFn
                         );

PRIVATE int   tagCompare (
                         void*   newDataPtr,
                         void*   cmpDataPtr
                         );

PRIVATE int   prefixTravel (
                                 CSCbinTreeNodeType   const node,
                                 CSCcmpFnType               clientFn,
                           const void*                const clientData
                           );

PRIVATE int   infixTravel (
                                CSCbinTreeNodeType   const node,
                                CSCcmpFnType               clientFn,
                          const void*                const clientData
                          );

PRIVATE int   postfixTravel (
                                  CSCbinTreeNodeType   const node,
                                  CSCcmpFnType               clientFn,
                            const void*                const clientData
                            );

PRIVATE CSCbinTreeNodeType   tagSearch (
                                       CSCbinTreeNodeType   const node,
                                       long                       tag
                                       );

PRIVATE CSCbinTreeNodeType   userSearch (
                                           CSCbinTreeNodeType   const node,
                                           CSCcmpFnType               clientFn,
                                     const void*                const clientData
                                        );

PRIVATE int   tagsPrint (
                        CSCbinTreeNodeType   const nodePtr
                        );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function binTreeDel
 **************************************************************************/

PRIVATE int   binTreeDel (
                         CSCbinTreeNodeType   const node,
                         CSCgenFnType               cbFn
                         )
   {
   int   freeStat = CSC_OK;

   ASSERT_RTN (node != NULL, "binTreeDel: null node", CSC_BADARG);
   ASSERT_RTN (node->sig_lo==TREE_SIG, "binTreeDel: bad sig", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi==TREE_SIG, "binTreeDel: bad sig", CSC_CORRUPT);

   if (cbFn != NULL) (void)(*cbFn) (node->tag, node->size, (void*)node->data);

   if (node->left  != NULL) (void)binTreeDel (node->left, cbFn);
   if (node->right != NULL) (void)binTreeDel (node->right, cbFn);

   (void)CSCbinTreeNodeDel (node);

   return (freeStat);
   }


/**************************************************************************
 * Private Function tagCompare
 **************************************************************************/

PRIVATE int   tagCompare (
                         void*   newDataPtr,
                         void*   cmpDataPtr
                         )
   {
   register long   newData = *(long*)newDataPtr;
   register long   cmpData = *(long*)cmpDataPtr;
   register int    retVal  = 0;

   if (newData  < cmpData) retVal = -1;
   if (newData == cmpData) retVal =  0;
   if (newData  > cmpData) retVal = +1;

   return (retVal);
   }


/**************************************************************************
 * Private Function prefixTravel
 **************************************************************************/

PRIVATE int   prefixTravel (
                                 CSCbinTreeNodeType   const node,
                                 CSCcmpFnType               clientFn,
                           const void*                const clientData
                           )
   {
   int   travelStat = CSC_NOTFOUND;

   ASSERT_RTN (node != NULL, "prefixTravel: null node", CSC_BADARG);
   ASSERT_RTN (node->sig_lo==TREE_SIG, "prefixTravel: bad sig", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi==TREE_SIG, "prefixTravel: bad sig", CSC_CORRUPT);

   if (clientFn != NULL) travelStat = (*clientFn) (node, (void*)clientData);

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (node->left != NULL)
      {
      travelStat = prefixTravel (node->left, clientFn, clientData);
      }

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (node->right != NULL)
      {
      travelStat = prefixTravel (node->right, clientFn, clientData);
      }

   return (travelStat);
   }


/**************************************************************************
 * Private Function infixTravel
 **************************************************************************/

PRIVATE int   infixTravel (
                                CSCbinTreeNodeType   const node,
                                CSCcmpFnType               clientFn,
                          const void*                const clientData
                          )
   {
   int   travelStat = CSC_NOTFOUND;

   ASSERT_RTN (node != NULL, "infixTravel: null node", CSC_BADARG);
   ASSERT_RTN (node->sig_lo==TREE_SIG, "infixTravel: bad sig", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi==TREE_SIG, "infixTravel: bad sig", CSC_CORRUPT);

   if (node->left != NULL)
      {
      travelStat = infixTravel (node->left, clientFn, clientData);
      }

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (clientFn != NULL) travelStat = (*clientFn) (node, (void*)clientData);

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (node->right != NULL)
      {
      travelStat = infixTravel (node->right, clientFn, clientData);
      }

   return (travelStat);
   }


/**************************************************************************
 * Private Function postfixTravel
 **************************************************************************/

PRIVATE int   postfixTravel (
                                  CSCbinTreeNodeType   const node,
                                  CSCcmpFnType               clientFn,
                            const void*                const clientData
                            )
   {
   int   travelStat = CSC_NOTFOUND;

   ASSERT_RTN (node != NULL, "postfixTravel: null node", CSC_BADARG);
   ASSERT_RTN (node->sig_lo==TREE_SIG, "postfixTravel: bad sig", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi==TREE_SIG, "postfixTravel: bad sig", CSC_CORRUPT);

   if (node->left != NULL)
      {
      travelStat = postfixTravel (node->left, clientFn, clientData);
      }

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (node->right != NULL)
      {
      travelStat = postfixTravel (node->right, clientFn, clientData);
      }

   if (travelStat != CSC_NOTFOUND) return (travelStat);

   if (clientFn != NULL) travelStat = (*clientFn) (node, (void*)clientData);

   return (travelStat);
   }


/**************************************************************************
 * Private Function tagSearch
 **************************************************************************/

PRIVATE CSCbinTreeNodeType   tagSearch (
                                       CSCbinTreeNodeType   const node,
                                       long                       tag
                                       )
   {
   CSCbinTreeNodeType   tagNode = NULL;

   if (node != NULL)
      {
ASSERT_RTN (node->sig_lo==TREE_SIG, "tagSearch: bad sig", NULL);
ASSERT_RTN (node->sig_hi==TREE_SIG, "tagSearch: bad sig", NULL);
      if (tag < node->tag)  tagNode = tagSearch (node->left,  tag);
      if (tag > node->tag)  tagNode = tagSearch (node->right, tag);
      if (tag == node->tag) tagNode = node;
      }

   return (tagNode);
   }


/**************************************************************************
 * Private Function userSearch
 **************************************************************************/

PRIVATE CSCbinTreeNodeType   userSearch (
                                           CSCbinTreeNodeType   const node,
                                           CSCcmpFnType               clientFn,
                                     const void*                const clientData
                                        )
   {
   CSCbinTreeNodeType   userNode = NULL;

   ASSERT_RTN (clientFn != NULL, "userSearch: null clientFn", NULL);

   if (node != NULL)
      {
ASSERT_RTN (node->sig_lo==TREE_SIG, "userSearch: bad sig", NULL);
ASSERT_RTN (node->sig_hi==TREE_SIG, "userSearch: bad sig", NULL);
      switch ((*clientFn)(node,(void*)clientData))
         {
default:  ASSERT_RTN (CSC_FALSE, "userSearch", NULL);                 break;
case -1:  userNode = userSearch (node->left, clientFn, clientData);   break;
case  0:  userNode = node;                                            break;
case  1:  userNode = userSearch (node->right, clientFn, clientData);  break;
         }
      }

   return (userNode);
   }


/**************************************************************************
 * Private Function tagsPrint
 **************************************************************************/

PRIVATE int   tagsPrint (
                        CSCbinTreeNodeType   const node
                        )
   {
   int   printStat = CSC_OK;

   ASSERT_RTN (node != NULL, "tagsPrint:  no nodePtr", CSC_BADARG);
   ASSERT_RTN (node->sig_lo==TREE_SIG, "tagsPrint: bad sig", CSC_CORRUPT);
   ASSERT_RTN (node->sig_hi==TREE_SIG, "tagsPrint: bad sig", CSC_CORRUPT);

   if (node->left != NULL)
      printStat = tagsPrint (node->left);

   (void)CSCbinTreeNodePrint (node);

   if (node->left != NULL)
      (void)printf ("LEFT=%ld   ",node->left->tag);
   else
      (void)printf ("LEFT=NULL   ");

   if (node->right != NULL)
      (void)printf ("RIGHT=%ld\n\n", node->right->tag);
   else
      (void)printf ("RIGHT=NULL\n\n");

   if (node->right != NULL)
      printStat = tagsPrint (node->right);

   return (printStat);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCbinTreeNew
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNew">

NAME
        CSCbinTreeNew - create an empty libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeType   CSCbinTreeNew (
                                       const char*            namePtr,
                                             CSCmonFnType     monFunc,
                                       const void*            monData,
                                             CSCprofileType   profiling
                                       );

RETURN VALUE
        CSCbinTreeNew(), if successful, returns an opaque data type that
        represents the newly created libcsc balanced binary tree, or NULL if
        otherwise unsuccessful.

DESCRIPTION
        CSCbinTreeNew() creates and initializes a libcsc balanced binary tree
        and returns a CSCbinTreeType; the data structure is opaque.

        DANGER  Take care to never insert into a balanced binary tree a node
                that was joined with another by using CSCbinTreeNodeJoin()
                because it lacks balance information and will completely whack
                a balanced tree.

        DANGER  Never, never, never use CSCbinTreeNodeBreak() on a node in a
                libcsc balanced binary tree.

        In general:  do not try mixing the CSCbinTree and CSCbinTreeNode
        functions on the same tree.

SEE ALSO
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeType   (CSCbinTreeNew) (
                                        const char*            namePtr,
                                              CSCmonFnType     monFunc,
                                        const void*            monData,
                                              CSCprofileType   profiling
                                        )
   {
   CSCbinTreeType   newTree = NULL;
   CSCmemListType   memList = NULL;

   ASSERT_RTN (namePtr != NULL, "CSCbinTreeNew: no tree name", NULL);
   ASSERT_RTN (							\
              ((profiling==CSC_DO_PROFILING)||(profiling==CSC_NO_PROFILING)),\
              "CSCbinTreeNew: illegal profile value",		\
              NULL						\
              );

   memList = CSCmemInit (namePtr, NULL, monFunc, monData, CSC_NO_PROFILING);
   if (memList != NULL)
      {
      (void)CSCmemAlloc (memList,(void**)&newTree,1,sizeof(S_binTreeType),0);
      if (newTree != NULL)
         {
         newTree->name      = namePtr;
         newTree->memList   = memList;
         newTree->root      = NULL;
         newTree->profiling = profiling;
         newTree->monFunc   = monFunc;
         newTree->monData   = monData;
         newTree->count     = 0;
         newTree->height    = 0;
         newTree->compares  = 0;
         newTree->rotates   = 0;
#ifdef	DEBUG
         newTree->sig_lo = TREE_SIG;
         newTree->sig_hi = TREE_SIG;
#endif
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (newTree);
   }


/***************************************************************************
 * Public Function CSCbinTreeDel
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeDel">

NAME
        CSCbinTreeDel - delete a libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeDel (
                            CSCbinTreeType   const tree,
                            CSCgenFnType           cbFn
                            );

RETURN VALUE
        CSC_OK ......... if successful, and the opaque data structure
                         represented by `tree' will be deallocated.

        CSC_NOTFOUND ... if not successful.

        CSC_BADARG ..... if libcsc was compiled with the DEBUG macro and
                         `tree' or `cbFn' is NULL.

        CSC_CORRUPT .... if libcsc was compiled with the DEBUG macro and
                         CSCbinTreeDel() detects something munged up in the
                         tree or in some internal data.

DESCRIPTION
        CSCbinTreeDel() delete the balanced binary tree and the opaque
        CSCbinTreeType data structure represented by `tree'.  Probably the only
        way to get a valid CSCbinTreeType data structure in the first place is
        by calling CSCbinTreeNew().

        `cbFn' is a pointer to a libcsc CSCgenFnType function that is called for
        EACH NODE in the tree, before each node is deallocated.  The prototype
        for CSCgenFnType is:

                int    (*CSCgenFnType) (int, int, void*);

        The client callback function `cbFn' is called with the client defined
        node data:

                (*cbFn) (tag, dataSize, dataPtr);

        This gives the client an opportunity to process the client node data
        (such as CSCmemFree() any client CSCmemAlloc()'d node data) before the
        node is deallocated.

BUGS
        When CSCbinTreeDel() fails to deallocate internal nodes, in some
        conditions, CSC_OK may still be returned.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeDel) (
                             CSCbinTreeType   const tree,
                             CSCgenFnType           cbFn
                             )
   {
   int   delStat = CSC_OK;

   ASSERT_RTN (tree != NULL, "CSCbinTreeDel: null tree", CSC_BADARG);
   ASSERT_RTN (cbFn != NULL, "CSCbinTreeDel: null cbFn", CSC_BADARG);

   ASSERT_RTN (tree->sig_lo==TREE_SIG,"CSCbinTreeDel: tree blows",CSC_CORRUPT);
   ASSERT_RTN (tree->sig_hi==TREE_SIG,"CSCbinTreeDel: tree blows",CSC_CORRUPT);

   MON_ENTER(tree);

   if (tree->root != NULL) delStat = binTreeDel (tree->root, cbFn);

   if (delStat != CSC_OK)
      {
      MON_EXIT(tree);
      return (delStat);
      }

   {
   CSCmemListType   memList = tree->memList;
   CSCmonFnType     monFunc = tree->monFunc;
   const void*      monData = tree->monData;
   (void)CSCmemFree (memList, (void**)&tree, 0);
   (void)CSCmemDone (memList);
   if (monFunc != NULL) (*monFunc) (CSC_OUT, (void*)monData);
   }

   return (delStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeInsert
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeInsert">

NAME
        CSCbinTreeInsert - insert a node into a libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeInsert (
                               CSCbinTreeType       const tree,
                               CSCbinTreeNodeType   const node,
                               CSCcmpFnType               cmpfn
                               );

RETURN VALUE
        CSC_OK ........ if successful.

        CSC_DUPKEY .... if `node' already exists in `tree'; this is defined
                        by the value of tree nodes' tags and is discerned by
                        the client callback function pointed to by `cmpfn'.

        CSC_BADARG .... if libcsc was compiled with the DEBUG macro and
                        `tree', `node', or `cmpfn' is NULL.

        CSC_CORRUPT ... if libcsc was compiled with the DEBUG macro and
                        CSCbinTreeInsert() detects something munged up in the
                        tree or in some internal data.

DESCRIPTION
        CSCbinTreeInsert() inserts `node' into the libcsc balanced binary tree
        `tree', and then maintains the balance.

        DANGER  Take care to never insert a node that was joined with another
                with CSCbinTreeNodeJoin() because it lacks balance information
                and will completely whack a balanced tree.

        `cmpfn' is a pointer to a libcsc CSCcmpFnType function that is called
        for each node in the tree, until the node pointed to by node is
        inserted.  The prototype for `cmpfn' is:

                int    (*cmpfn) (void*, void*);

        The client callback function `cmpfn' is called to compare the tag
        field values of the node at node with a node, P, in the tree (note
        the actual arguments are the addresses of the tag fields):

                (*cmpfuncptr) ((void*)&node->tag, (void*)&P->tag);

        This gives the client control over the insertion order.  The
        CSCcmpFnType function should return only the values -1, 0, and 1:

                -1 .... indicates less than (new node goes into left subtree).
                 0 .... indicates a duplicate.
                 1 .... indicates more than (new node goes into right subtree).

        The tag field of libcsc balanced binary tree nodes is a long, but its
        semantics are entirely up to the client.

        Insertion metrics, count comparisons and subtree rotations, can be
        gotten with CSCbinTreeStat().

CREDITS
        The balanced tree insertion algorithm is directly taken from Donald E.
        Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
        (Reading Mass.:  Addison-Wesley 1973).

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeInsert) (
                                CSCbinTreeType       const tree,
                                CSCbinTreeNodeType   const node,
                                CSCcmpFnType               cmpfn
                                )
   {
   int   insertStat = CSC_OK;

   /*
    * The balanced tree insertion algorithm is directly taken from Donald E.
    * Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
    * (Reading Mass.:  Addison-Wesley 1973).
    *
    * I've kept the same cool variable names that Knuth used in his book:  P,
    * Q, R, S, T, and a.  I added metrics to count comparisions and subtree
    * rotations.
    */

   int                  a = 0;
   CSCbinTreeNodeType   P = NULL;
   CSCbinTreeNodeType   Q = NULL;
   CSCbinTreeNodeType   R = NULL;
   CSCbinTreeNodeType   S = NULL;
   CSCbinTreeNodeType   T = NULL;

   ASSERT_RTN (tree != NULL,  "CSCbinTreeInsert: null tree", CSC_BADARG);
   ASSERT_RTN (node != NULL,  "CSCbinTreeInsert: null node", CSC_BADARG);
   ASSERT_RTN (cmpfn != NULL, "CSCbinTreeInsert: no cmpfn",  CSC_BADARG);

   ASSERT_RTN(tree->sig_lo==TREE_SIG,"CSCbinTreeInsert: tree sig",CSC_CORRUPT);
   ASSERT_RTN(tree->sig_hi==TREE_SIG,"CSCbinTreeInsert: tree sig",CSC_CORRUPT);

   ASSERT_RTN(node->sig_lo==TREE_SIG,"CSCbinTreeInsert: node sig",CSC_CORRUPT);
   ASSERT_RTN(node->sig_hi==TREE_SIG,"CSCbinTreeInsert: node sig",CSC_CORRUPT);

   MON_ENTER(tree);

   if (tree->root == NULL)
      {
      tree->root = node;
      }
   else
      {
      S = P = tree->root;

      /*
       * P will move down the tree; S will point to the place where rebalancing
       * may be necessary, and T always points to the parent of S.
       */

COMPARE:
      ASSERT (P->sig_lo==TREE_SIG);
      ASSERT (P->sig_hi==TREE_SIG);
      tree->compares += 1;
      switch ((*cmpfn)((void*)&(node->tag), (void*)&(P->tag)))
         {
         default:
            MON_EXIT(tree);
            ASSERT_RTN (CSC_FALSE,"CSCbinTreeInsert: compare error",CSC_ERROR);
            break;

         case 0:
            insertStat = CSC_DUPKEY;
            goto DONE;

         case -1:
            Q = P->left;
            if (Q == NULL)
               {
               P->left = node;
               Q = node;
               goto ADJUST;
               }
            break;

         case +1:
            Q = P->right;
            if (Q == NULL)
               {
               P->right = node;
               Q = node;
               goto ADJUST;
               }
            break;
         }

      if (Q->balance != 0)
         {
         T = P;
         S = Q;
         }
      P = Q;
      goto COMPARE;

ADJUST:
      /*
       * Now the balance factors on nodes between S and Q need to be changed
       * from zero to +/- 1.
       */
      tree->compares += 1;
      if ((*cmpfn)((void*)&(node->tag), (void*)&(S->tag)) == -1)
         R = P = S->left;
      else
         R = P = S->right;

      if (P == Q)
         goto BALANCE;
      while (P != Q)
         {
         tree->compares += 1;
         if ((*cmpfn)((void*)&(node->tag), (void*)&(P->tag)) == -1)
            {
            P->balance = -1;
            P = P->left;
            }
         tree->compares += 1;
         if ((*cmpfn)((void*)&(node->tag), (void*)&(P->tag)) == +1)
            {
            P->balance = +1;
            P = P->right;
            }
         }

BALANCE:
      tree->compares += 1;
      if ((*cmpfn)((void*)&(node->tag), (void*)&(S->tag)) == -1)
         a = -1;
      else
         a = +1;
      if (S->balance == 0) /* tree has grown higher */
         {
         tree->height += 1;
         S->balance = a;
         goto DONE;
         }
      if (S->balance == -a) /* tree has gotten more balanced */
         {
         S->balance = 0;
         goto DONE;
         }
      if (S->balance == +a) /* tree has gotten out of balance */
         {
         if (R->balance == -a) goto DOUBLE_ROTATE;
         if (R->balance == +a) goto SINGLE_ROTATE;
         }

SINGLE_ROTATE:
      tree->rotates += 1;
      P = R;
      if (a == +1)
         {
         S->right = R->left;
         R->left  = S;
         }
      if (a == -1)
         {
         S->left  = R->right;
         R->right = S;
         }
      S->balance = R->balance = 0;
      goto FINISH_ROTATE;

DOUBLE_ROTATE:
      tree->rotates += 2;
      if (a == +1)
         {
         P = R->left;
         R->left = P->right;
         P->right = R;
         S->right = P->left;
         P->left = S;
         }
      if (a == -1)
         {
         P = R->right;
         R->right = P->left;
         P->left = R;
         S->left = P->right;
         P->right = S;
         }
      if (P->balance == +a)
         {
         S->balance = -a;
         R->balance = 0;
         }
      if (P->balance ==  0)
         {
         S->balance = 0;
         R->balance = 0;
         }
      if (P->balance == -a)
         {
         S->balance = 0;
         R->balance = a;
         }
      P->balance = 0;
      goto FINISH_ROTATE;

FINISH_ROTATE:
      if (T == NULL)
         tree->root = P;
      else
         if (S == T->right)
            T->right = P;
         else
            T->left = P;

DONE:
      }

   if (insertStat == CSC_OK) tree->count += 1;

   MON_EXIT(tree);

   return (insertStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeTagOrderedInsert
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeTagOrderedInsert">

NAME
        CSCbinTreeTagOrderedInsert - put node into libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeTagOrderedInsert (
                                         CSCbinTreeType       const tree,
                                         CSCbinTreeNodeType   const node
                                         );

RETURN VALUE
        CSC_OK ........ if successful.

        CSC_DUPKEY .... if `node' already exists in `tree' (this is defined
                        by the value of the nodes' tags).

        CSC_BADARG .... if libcsc was compiled with the DEBUG macro and `tree'
                        or `node' is NULL.

        CSC_CORRUPT ... if libcsc was compiled with the DEBUG macro and
                        CSCbinTreeTagOrderedInsert() detects something munged
                        up in the tree or in some internal data.

DESCRIPTION
        CSCbinTreeTagOrderedInsert() inserts `node' into the libcsc balanced
        binary tree `tree', and then CSCbinTreeTagOrderedInsert() maintains the
        balance.

        The insertion order is strictly based upon the tag field values of node
        and the tag field values of the nodes in the libcsc balanced binary
        tree.

        DANGER  Take care to never insert a node that was joined with another
                by using CSCbinTreeNodeJoin() because it lacks balance
                information and will completely whack a balanced tree.

        This function internally calls CSCbinTreeInsert() with its own internal
        tag comparison function.

        Insertion metrics, count comparisons and subtree rotations, can be
        gotten with CSCbinTreeStat().

CREDITS
        The balanced tree insertion algorithm is directly taken from Donald E.
        Knuth, "Sorting and Searching," The Art of Computer Programming, vol. 3
        (Reading Mass.:  Addison-Wesley 1973).

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeTagOrderedInsert) (
                                          CSCbinTreeType       const tree,
                                          CSCbinTreeNodeType   const node
                                          )
   {
   return (CSCbinTreeInsert(tree,node,tagCompare));
   }


/***************************************************************************
 * Public Function CSCbinTreeTraverse
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeTraverse">

NAME
        CSCbinTreeTraverse - traverse a libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeTraverse (
                                 const char*            const method,
                                       CSCbinTreeType   const tree,
                                       CSCcmpFnType           clientFn,
                                 const void*            const clientData
                                 );

RETURN VALUE
        CSC_OK ......... on a successful traversal with the desired node being
                         found.

        CSC_NOTFOUND ... on a successful traversal with the desired node being
                         not found.

        CSC_BADARG ..... if libcsc was compiled with the DEBUG macro and
                         `method', `tree', or `clientFn' is NULL.

        CSC_CORRUPT .... if libcsc was compiled with the DEBUG macro and
                         CSCbinTreeTraverse() detects something munged up in'
                         the tree or in some internal data.

DESCRIPTION
        CSCbinTreeTraverse() traverses the libcsc balanced binary tree `tree'.
        `method' is a string that specifies the search algorithm (case IS
        important):

                method
                ------

                "PREFIX"
                "INFIX"
                "POSTFIX"

        `clientFn' is a pointer to a libcsc CSCcmpFnType function that is
        called for EACH NODE in the tree.  The prototype for CSCcmpFnType is:

                int    (*CSCcmpFnType) (void*, void*);

        The client callback function `clientFn' is called with the client
        supplied data and a node pointer (on which the client then needs to use
        rtsBinTreeNodeQuery()):

                stat = (*clientFn) ((void*)&node, (void*)clientData);

        This gives the client an opportunity to terminate the traversal by
        `clientFn' returning CSC_OK (indicating a match); otherwise, `clientFn'
        should return CSC_NOTFOUND.

        If `clientFn' returns any value besides CSC_NOTFOUND then the traversal
        is terminated, and the return value from CSCbinTreeTraverse() will be
        the value returned from `clientFn'.  In this case, if libcsc was
        compiled with the DEBUG macro, then there will be an assertion if the
        return value is not CSC_OK or CSC_NOTFOUND, but no other processing is
        affected.

        If clientFn is NULL, then the libcsc balanced binary tree is traversed
        according to method, but nothing interesting happens; except if libcsc
        was compiled with the DEBUG macro, in which case the tree will be
        sanity checked.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeTraverse) (
                                  const char*            const method,
                                        CSCbinTreeType   const tree,
                                        CSCcmpFnType           clientFn,
                                  const void*            const clientData
                                  )
   {
   int   travStat = CSC_BADARG;

   ASSERT_RTN (method != NULL,  "CSCbinTreeTraverse: null method",  CSC_BADARG);
   ASSERT_RTN (tree != NULL,    "CSCbinTreeTraverse: null tree",    CSC_BADARG);

   ASSERT_RTN (						\
              tree->sig_lo==TREE_SIG,			\
              "CSCbinTreeTraverse: tree blows",		\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              tree->sig_hi==TREE_SIG,			\
              "CSCbinTreeTraverse: tree blows",		\
              CSC_CORRUPT				\
              );

   if (CSC_STREQ(method,"PREFIX"))
      {
      travStat = prefixTravel (tree->root, clientFn, clientData);
      }
   else if (CSC_STREQ(method,"INFIX"))
      {
      travStat = infixTravel (tree->root, clientFn, clientData);
      }
   else if (CSC_STREQ(method,"POSTFIX"))
      {
      travStat = postfixTravel (tree->root, clientFn, clientData);
      }

   ASSERT (travStat == CSC_OK || travStat == CSC_NOTFOUND);

   return (travStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeUserSearch
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeUserSearch">

NAME
        CSCbinTreeUserSearch - arbitrary search of libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeNodeType   CSCbinTreeUserSearch (
                                               CSCbinTreeType   const tree,
                                               CSCcmpFnType           clientFn,
                                         const void*            const clientData
                                                  );

RETURN VALUE
        CSCbinTreeUserSearch(), if successful, returns a CSCbinTreeNodeType
        that is a node from the libcsc balanced binary tree `tree'.
        CSCbinTreeUserSearch() returns NULL, if not successful.

DESCRIPTION
        CSCbinTreeUserSearch() traverses the libcsc balanced binary tree `tree'.
        The tree traversal algorithm and traversal termination are controlled by
        the client callback function `clientFn'.

        `clientFn' is a pointer to a libcsc CSCcmpFnType function that is called
        for each node in `tree'.  The prototype for clientFn is:

                int    (*clientFn) (void*, void*);

        The client callback function `clientFn' is called with the client
        supplied data `clientData' and a node pointer (on which the client then
        needs to use CSCbinTreeNodeStat()):

                switchValue = (*clientFn) ((void*)&node, (void*)clientData);

        This gives the client control over tree traversal.  `clientFn' should
        return only the values -1, 0, and 1:

                -1 .... traversal continues on left node.
                 0 .... terminate traversal.
                 1 .... traversal continues on right node.

BUGS
        This function probably makes no sense.

        If `clientFn' is NULL, and libcsc was NOT compiled with the DEBUG macro,
        then CSCbinTreeUserSearch() probably dies a horrible segfault death.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeNodeType   (CSCbinTreeUserSearch) (
                                               CSCbinTreeType   const tree,
                                               CSCcmpFnType           clientFn,
                                         const void*            const clientData
                                                   )
   {
   CSCbinTreeNodeType   tmpNode = NULL;

   ASSERT_RTN (tree != NULL,     "CSCbinTreeUserSearch: null tree",     NULL);
   ASSERT_RTN (clientFn != NULL, "CSCbinTreeUserSearch: null clientFn", NULL);

   ASSERT_RTN (tree->sig_lo==TREE_SIG,"CSCbinTreeUserSearch: tree blows",NULL);
   ASSERT_RTN (tree->sig_hi==TREE_SIG,"CSCbinTreeUserSearch: tree blows",NULL);

   tmpNode = userSearch (tree->root, clientFn, clientData);

   return (tmpNode);
   }


/***************************************************************************
 * Public Function CSCbinTreeTagSearch
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeTagSearch">

NAME
        CSCbinTreeTagSearch - search a balanced binary tree for node with tag

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeNodeType   CSCbinTreeTagSearch (
                                                 CSCbinTreeType   const tree,
                                                 long                   tag
                                                 );

RETURN VALUE
        CSCbinTreeTagSearch(), if successful, returns a CSCbinTreeNodeType that
        is a libcsc balanced binary tree node whose tag-field value is equal to
        `tag', or NULL if otherwise not successful.

DESCRIPTION
        CSCbinTreeTagSearch() searches the libcsc balanced binary tree `tree'
        for a node with a tag-field that is equal to `tag'.

        A recursive postfix tree traversal algorithm is used.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeNodeType   (CSCbinTreeTagSearch) (
                                                  CSCbinTreeType   const tree,
                                                  long                   tag
                                                  )
   {
   CSCbinTreeNodeType   tempNode = NULL;

   ASSERT_RTN (tree != NULL, "CSCbinTreeTagSearch: null tree", NULL);
   ASSERT_RTN (
              tree->sig_lo==TREE_SIG,			\
              "CSCbinTreeTagSearch: tree blows",	\
              NULL					\
              );
   ASSERT_RTN (						\
              tree->sig_hi==TREE_SIG,			\
              "CSCbinTreeTagSearch: tree blows",	\
              NULL					\
              );

   tempNode = tagSearch (tree->root, tag);

   return (tempNode);
   }


/***************************************************************************
 * Public Function CSCbinTreeStat
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeStat">

NAME
        CSCbinTreeStat - retrieve libcsc balanced binary tree statistics

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeStat (
                             CSCbinTreeType   const tree,
                             size_t*          const countPtr,
                             size_t*          const heightPtr,
                             size_t*          const comparesPtr,
                             size_t*          const rotatesPtr
                             );

RETURN VALUE
        CSCbinTreeStat() returns CSC_OK.

        If libcsc was compiled with the DEBUG macro and tree is NULL, then
        CSCbinTreeStat() returns CSC_BADARG.

        If libcsc was compiled with the DEBUG macro and some internal tree data
        is munged up, then CSCbinTreeStat() returns CSC_CORRUPT.

DESCRIPTION
        CSCbinTreeStat() retrieves these statistics from the libcsc balanced
        binary tree `tree':

                statistic
                ---------
                count ......... total number of nodes in the tree.
                height ........ maximum current height of the tree.
                compares ...... number of compares from most recent insert.
                rotates ....... number of rotations from most recent insert.

        If `countPtr' is not NULL, then the total number of nodes in the tree is
        written to the size_t pointed to by `countPtr'.

        If `heightPtr' is not NULL, then the maximum current height of the tree
        is written to the size_t pointed to by `heightPtr'.

        If `comparesPtr' is not NULL, then the number of compares from most
        recent insert is written to the size_t pointed to by `comparesPtr'.

        If `rotatesPtr' is not NULL, then the number of rotations from most
        recent insert is written to the size_t pointed to by `rotatesPtr'.

        If `countPtr', `heightPtr', `comparesPtr', and `rotatesPtr' are all
        NULL, then this function does nothing interesting.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeStat) (
                              CSCbinTreeType   const tree,
                              size_t*          const countPtr,
                              size_t*          const heightPtr,
                              size_t*          const comparesPtr,
                              size_t*          const rotatesPtr
                              )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (tree != NULL, "CSCbinTreeQuery: null tree", CSC_BADARG);

   ASSERT_RTN(tree->sig_lo==TREE_SIG,"CSCbinTreeQuery: tree blows",CSC_CORRUPT);
   ASSERT_RTN(tree->sig_hi==TREE_SIG,"CSCbinTreeQuery: tree blows",CSC_CORRUPT);

   MON_ENTER(tree);

   if (tree->profiling == CSC_DO_PROFILING)
      {
      if (countPtr != NULL)    *countPtr    = tree->count;
      if (heightPtr != NULL)   *heightPtr   = tree->height;
      if (comparesPtr != NULL) *comparesPtr = tree->compares;
      if (rotatesPtr != NULL)  *rotatesPtr  = tree->rotates;
      }
   else
      statStat = CSC_NO_PROFILING;

   MON_EXIT(tree);

   return (statStat);
   }


/***************************************************************************
 * Public Function CSCbinTreePrint
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreePrint">

NAME
        CSCbinTreePrint - print a libcsc balanced binary tree

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreePrint (
                              CSCbinTreeType   const tree
                              );

RETURN VALUE
        CSCbinTreePrint() returns CSC_OK.

        If libcsc was compiled with the DEBUG macro and tree is NULL, then
        CSCbinTreePrint() returns CSC_BADARG.

        If libcsc was compiled with the DEBUG macro and some internal tree data
        is munged up, then CSCbinTreePrint() returns CSC_CORRUPT.

DESCRIPTION
        CSCbinTreePrint() writes to standard output these statistics for the
        libcsc balanced binary tree `tree':

                statistic
                ---------
                count ......... total number of nodes in the tree.
                height ........ maximum current height of the tree.
                compares ...... number of compares from most recent insert.
                rotates ....... number of rotations from most recent insert.

        After the overall tree statistics, various fields of all the nodes in
        tree are written, to standard output, via an internal call to
        CSCbinTreeNodePrint().  For each node, the value of the left and right
        node's tag field is printed for tracability.

        A prefix binary tree traversal algorithm is used.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreePrint) (
                               CSCbinTreeType   const tree
                               )
   {
   int   printStat;

   ASSERT_RTN (tree != NULL, "CSCbinTreeTagDump: null tree", CSC_BADARG);
   ASSERT_RTN (					\
              tree->sig_lo==TREE_SIG,		\
              "CSCbinTreeTagDump: tree blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              tree->sig_hi==TREE_SIG,		\
              "CSCbinTreeTagDump: tree blows",	\
              CSC_CORRUPT			\
              );

   printf ("\n-----------------------------------------------------------\n\n");

   MON_ENTER(tree);

   printf ("   count:  %ld\n", (long)tree->count);
   printf ("  height:  %ld\n", (long)tree->height);
   printf ("compares:  %ld\n", (long)tree->compares);
   printf (" rotates:  %ld\n", (long)tree->rotates);

   printStat = tagsPrint (tree->root);

   MON_EXIT(tree);

   return (printStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeNew
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeNew">

NAME
        CSCbinTreeNodeNew - create a new empty libcsc binary tree node

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeNodeType   CSCbinTreeNodeNew (
                                               CSCdataCntrlType         push,
                                               long                     tag,
                                         const void*              const dataPtr,
                                               size_t                   dataSize
                                               );

RETURN VALUE
        CSCbinTreeNodeNew(), if successful, returns a CSCbinTreeNodeType for the
        newly created libcsc binary tree node, or NULL if otherwise not
        successful.

DESCRIPTION
        CSCbinTreeNodeNew() creates a new libcsc binary tree node that is
        appropriate for use:

                1) with CSCbinTreeInsert() on libcsc balanced binary trees that
                   are created with CSCbinTreeNew()

                2) for joining together with CSCbinTreeNodeJoin()

        The new node's `tag' is used by client callback compare functions when
        libcsc balanced binary tree nodes are inserted, searched, or traversed.

        `push' is one of

                CSC_DATA_DUP    the data pointed to by `dataPtr', for `dataSize'
                                bytes, is duplicated and put into the new node.

                CSC_DATA_NODUP  `dataPtr' and `dataSize' are directly put into
                                the new node.  This new node will retain the
                                reference to the data at `dataPtr'; therefore,
                                it should be clear that if that data is changed
                                (or deallocated!) then it is the data that this
                                new node points to that is affected.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeNodeType   (CSCbinTreeNodeNew) (
                                               CSCdataCntrlType         push,
                                               long                     tag,
                                         const void*              const dataPtr,
                                               size_t                   dataSize
                                                )
   {
   CSCbinTreeNodeType   newNode = NULL;
   CSCmemListType       memList = NULL;


   ASSERT_RTN (								\
              (push == CSC_DATA_DUP) || (push == CSC_DATA_NODUP),	\
              "CSCbinTreeNodeNew: invalid push",			\
              NULL							\
              );

   memList = CSCmemInit ("NODE", NULL, NULL, NULL, CSC_NO_PROFILING);
   if (memList != NULL)
      {
      (void)CSCmemAlloc(memList,(void**)&newNode,1,sizeof(S_binTreeNodeType),0);
      if (newNode != NULL)
         {
         newNode->memList = memList;
         newNode->left    = NULL;
         newNode->right   = NULL;
         newNode->push    = push;
         newNode->balance = 0;
         newNode->tag     = tag;
         newNode->size    = dataSize;
         newNode->data    = dataPtr;
#ifdef	DEBUG
         newNode->sig_lo = TREE_SIG;
         newNode->sig_hi = TREE_SIG;
#endif
         if ((push == CSC_DATA_DUP) && (dataPtr != NULL) && (dataSize > 0))
            {
            (void)CSCmemDup (memList,(void**)&newNode->data,dataPtr,dataSize,0);
            if (newNode->data == NULL)
               {
               (void)CSCmemFree (memList, (void**)&newNode, 0);
               newNode = NULL;
               (void)CSCmemDone (memList);
               }
            }
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (newNode);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeDel
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeDel">

NAME
        CSCbinTreeNodeDel - deallocate a libcsc binary tree node

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodeDel (
                                CSCbinTreeNodeType   const node
                                );

RETURN VALUE
        CSC_OK ......... if successful.

        CSC_NOTFOUND ... if not successful.

        CSC_BADARG ..... if libcsc was compiled with the DEBUG macro and node is
                         NULL.

        CSC_CORRUPT .... if libcsc was compiled with the DEBUG macro and some
                         internal tree data is munged up.

DESCRIPTION
        CSCbinTreeNodeDel() deallocates `node'.

        NEVER, EVER do this to a node in a libcsc balanced binary tree.  Only
        use CSCbinTreeNodeDel() on nodes removed from tree that are built with
        CSCbinTreeNodeJoin().  Nodes in a libcsc balanced binary trees cannot
        be removed. :/

        The node data should be retreived with CSCbinTreeNodeStat() and removed,
        or otherwise cleaned up, before calling this function.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodeDel) (
                                 CSCbinTreeNodeType   const node
                                 )
   {
   int   delStat = CSC_OK;

   ASSERT_RTN (node != NULL, "CSCbinTreeNodeFree: null node", CSC_BADARG);
   ASSERT_RTN (					\
              node->sig_lo==TREE_SIG,		\
              "CSCbinTreeNodeFree: bad sig",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi==TREE_SIG,		\
              "CSCbinTreeNodeFree: bad sig",	\
              CSC_CORRUPT			\
              );

   if ((node->push == CSC_DATA_DUP) && (node->data != NULL))
      {
      (void)CSCmemFree (node->memList, (void**)&node->data, 0);
      }
   {
   CSCmemListType   memList = node->memList;
   (void)CSCmemFree (memList, (void**)&node, 0);
   (void)CSCmemDone (memList);
   }

   return (delStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeJoin
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeJoin">

NAME
        CSCbinTreeNodeJoin - join libcsc binary tree nodes

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodeJoin (
                                 CSCbinTreeNodeType   const node,
                                 CSCbinTreeNodeType   const left,
                                 CSCbinTreeNodeType   const right
                                 );

RETURN VALUE
        CSCbinTreeNodeJoin() returns CSC_OK unless node is NULL, in which case
        CSC_BADARG is returned.  If libcsc is compiled with the DEBUG macro and
        some internal tree data is munged, then rtsBinTreeNodeJoin() returns
        CSC_CORRUPT.

DESCRIPTION
        CSCbinTreeNodeJoin() simply assigns `left' to the left node pointer of
        `node', and assigns `right' to the right pointer of `node'.

        Use CSCbinTreeNodeJoin() to create your own libcsc binary trees that
        are distinct and separate from libcsc balanced binary trees that are
        created with CSCbinTreeNew() and CSCbinTreeInsert().

        It is completely acceptable for `left' and/or `right' to be NULL.

        Beware, if the the `left' and/or `right' node pointer of the node is
        already in use, then it will be lost.  Don't create dangling trees.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodeJoin) (
                                  CSCbinTreeNodeType   const node,
                                  CSCbinTreeNodeType   const left,
                                  CSCbinTreeNodeType   const right
                                  )
   {
   int   joinStat = CSC_OK;

   ASSERT_RTN (node!= NULL, "CSCbinTreeNodeJoin: null tree", CSC_BADARG);
   ASSERT_RTN (					\
               node->sig_lo==TREE_SIG,		\
               "CSCbinTreeNodeJoin: bad sig",	\
               CSC_CORRUPT			\
               );
   ASSERT_RTN (					\
               node->sig_hi==TREE_SIG,		\
               "CSCbinTreeNodeJoin: bad sig",	\
               CSC_CORRUPT			\
               );

#ifdef	DEBUG
   if (left!= NULL)
      {
      ASSERT_RTN (				\
                 left->sig_lo==TREE_SIG,	\
                 "CSCbinTreeNodeJoin: bad sig",	\
                 CSC_CORRUPT			\
                 );
      ASSERT_RTN (				\
                 left->sig_hi==TREE_SIG,	\
                 "CSCbinTreeNodeJoin: bad sig",	\
                 CSC_CORRUPT			\
                 );
      }
   if (right!= NULL)
      {
      ASSERT_RTN (				\
                 right->sig_lo==TREE_SIG,	\
                 "CSCbinTreeNodeJoin: bad sig",	\
                 CSC_CORRUPT			\
                 );
      ASSERT_RTN (				\
                 right->sig_hi==TREE_SIG,	\
                 "CSCbinTreeNodeJoin: bad sig",	\
                 CSC_CORRUPT			\
                 );
      }
#endif

   if (node!= NULL)
      {
      node->left  = left;
      node->right = right;
      }
   else
      {
      joinStat = CSC_BADARG;
      }

   return (joinStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeBreak
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeBreak">

NAME
        CSCbinTreeNodeBreak - break libcsc binary tree at a node

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodeBreak (
                                  CSCbinTreeNodeType    const node,
                                  CSCbinTreeNodeType*   const leftPtr,
                                  CSCbinTreeNodeType*   const rightPtr
                                  );

RETURN VALUE
        CSCbinTreeNodeBreak() returns CSC_OK, unless node is NULL, in which
        case CSC_BADARG is returned.

DESCRIPTION
        CSCbinTreeNodeBreak() takes `node' and optionally replaces its left
        and/or right node pointers with NULL and writes its original left and/or
        right node pointers to the CSCbinTreeNodeTypethat are pointed to by
        `leftPtr' and `rightPtr'.

        NEVER, EVER do this to a node in a libcsc balanced binary tree.  Only
        use CSCbinTreeNodeBreak() on nodes in trees that are built with
        CSCbinTreeNodeJoin().

        If `leftPtr' is not NULL, then `node''s left node is written to the
        CSCbinTreeNodeType pointed to by `leftPtr'.

        If `rightPtr' is not NULL, then `node''s right node is written to the
        CSCbinTreeNodeType pointed to by `rightPtr'.

        Remember .....> Either of the left and/or right nodes that may be
                        returned via `leftPtr' and `rightPtr' may be NULL;
                        certainly this is the case when node is a leaf node.

BUGS
        Odd But True Department: If `leftPtr' and `rightPtr' are both NULL then
        no action is taken and CSC_OK is returned.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodeBreak) (
                                   CSCbinTreeNodeType    const node,
                                   CSCbinTreeNodeType*   const leftPtr,
                                   CSCbinTreeNodeType*   const rightPtr
                                   )
   {
   int   breakStat = CSC_OK;

   ASSERT_RTN (node != NULL, "CSCbinTreeNodeBreak: null tree", CSC_BADARG);

   if (node != NULL)
      {
      if (leftPtr != NULL)
         {
         *leftPtr = node->left;
         node->left = NULL;
         }
      if (rightPtr != NULL)
         {
         *rightPtr = node->right;
         node->right = NULL;
         }
      }
   else
      {
      breakStat = CSC_BADARG;
      }

   return (breakStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeTraverse
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeTraverse">

NAME
        CSCbinTreeNodeTraverse - traverse a libcsc binary tree


SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodeTraverse (
                                    const char*                const method,
                                          CSCbinTreeNodeType   const node,
                                          CSCcmpFnType               clientFn,
                                    const void*                const clientData
                                     );

RETURN VALUE
        CSCbinTreeNodeTraverse() returns CSC_OK on a successful traversal with
        the desired node being found, or CSC_NOTFOUND on a successful traversal
        with the desired node being not found.

        If libcsc was compiled with the DEBUG macro and some internal tree data
        is munged up then rtsBinTreeNodeTraverse() returns CSC_CORRUPT.

        If libcsc was compiled with the DEBUG macro and invalid arguments are
        detected, then rtsBinTreeNodeTraverse() returns CSC_BADARG.

DESCRIPTION
        CSCbinTreeNodeTraverse() traverses a libcsc binary tree beginning with
        `node'.  `method' is a string that specifies the search algorithm (case
        IS important):

                method
                ------

                "PREFIX"
                "INFIX"
                "POSTFIX"

        If `clientFn' is not NULL, then it is a pointer to a libcsc CSCcmpFnType
        function that is called for EACH NODE in the tree.  The prototype for
        clientFn is:

                int    (*clientFn) (void*, void*);

        The client callback function `clientFn' is called with the client
        supplied data and a node pointer (on which the client then needs to use
        CSCbinTreeNodeQuery()):

                stat = (*clientFn) ((void*)&node, (void*)clientData);

        This gives the client an opportunity to terminate the traversal by
        returning CSC_OK; otherwise, the function pointed to by `clientFn'
        should return CSC_NOTFOUND.

        If `clientFn' returns any value besides CSC_NOTFOUND, then the tree
        traversal is terminated, and the return value from
        CSCbinTreeNodeTraverse() will be the value returned from `clientFn'.
        In this case, if libcsc was compiled with the DEBUG macro, then there
        will be an assertion if the return value is not CSC_OK or CSC_NOTFOUND,
        but no other processing is affected.

        If `clientFn' is NULL, then the libcsc binary tree is traversed
        according to `method', but nothing interesting happens.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodeTraverse) (
                                    const char*                const method,
                                          CSCbinTreeNodeType   const node,
                                          CSCcmpFnType               clientFn,
                                    const void*                const clientData
                                      )
   {
   int   travStat = CSC_BADARG;

   ASSERT_RTN (						\
              method != NULL,				\
              "CSCbinTreeNodeTraverse: null method",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              node != NULL,				\
              "CSCbinTreeNodeTraverse: null node",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              clientFn != NULL,				\
              "CSCbinTreeNodeTraverse: null clientFn",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              node->sig_lo==TREE_SIG,			\
              "CSCbinTreeNodeTraverse: bad tree sig",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              node->sig_hi==TREE_SIG,			\
              "CSCbinTreeNodeTraverse: bad tree sig",	\
              CSC_CORRUPT				\
              );

   if (CSC_STREQ(method,"PREFIX"))
      {
      travStat = prefixTravel (node, clientFn, clientData);
      }
   else if (CSC_STREQ(method,"INFIX"))
      {
      travStat = infixTravel (node, clientFn, clientData);
      }
   else if (CSC_STREQ(method,"POSTFIX"))
      {
      travStat = postfixTravel (node, clientFn, clientData);
      }

   ASSERT (travStat == CSC_OK || travStat == CSC_NOTFOUND);

   return (travStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeUserSearch
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeUserSearch">

NAME
        CSCbinTreeNodeUserSearch - arbitrary libcsc binary tree traversal

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeNodeType   CSCbinTreeNodeUserSearch (
                                           CSCbinTreeNodeType   const node,
                                           CSCcmpFnType               clientFn,
                                     const void*                const clientData
                                                      );

RETURN VALUE
        CSCbinTreeNodeUserSearch(), if successful, returns a CSCbinTreeNodeType
        that is the desired libcsc binary tree node; otherwise NULL is returned
        if not successful.

DESCRIPTION
        CSCbinTreeNodeUserSearch() traverses the libcsc binary tree beginning
        with `node'.  The tree traversal algorithm and traversal termination are
        controlled by the client callback function `clientFn'.

        `clientFn' is a libcsc CSCcmpFnType function that is called for each
        node in the tree.  The prototype for clientFn is:

                int    (*clientFn) (void*, void*);

        `clientFn' is called with the client supplied data and a node pointer
        (on which the client then needs to use CSCbinTreeNodeQuery()):

                switchValue = (*clientFn) ((void*)&node, (void*)clientData);

        This gives the client control over tree traversal.  `clientFn' should
        return only the values -1, 0, and 1:

                -1 .... traversal continues on left node.
                 0 .... terminate traversal.
                 1 .... traversal continues on right node.

        This function probably makes sense only with oddly shaped binary trees
        constructed with CSCbinTreeNodeJoin().

BUGS
        If `clientFn' is NULL, and libcsc was NOT compiled with the DEBUG macro,
        then CSCbinTreeNodeUserSearch() probably dies a horrible segfault death.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeNodeType   (CSCbinTreeNodeUserSearch) (
                                           CSCbinTreeNodeType   const node,
                                           CSCcmpFnType               clientFn,
                                     const void*                const clientData
                                                       )
   {
   CSCbinTreeNodeType   tmpNode = NULL;

   ASSERT_RTN (node != NULL,    "CSCbinTreeNodeUserSearch: null node",    NULL);
   ASSERT_RTN (clientFn != NULL,"CSCbinTreeNodeUserSearch: null clientFn",NULL);

   ASSERT_RTN (						\
              node->sig_lo==TREE_SIG,			\
              "CSCbinTreeNodeUserSearch: bad tree sig",	\
              NULL					\
              );
   ASSERT_RTN (						\
              node->sig_hi==TREE_SIG,			\
              "CSCbinTreeNodeUserSearch: bad tree sig",	\
              NULL					\
              );

   tmpNode = userSearch (node, clientFn, clientData);

   return (tmpNode);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeTagSearch
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeTagSearch">

NAME
        CSCbinTreeNodeTagSearch - search a libcsc binary tree for a given tag

SYNOPSYS
        #include "libcsc.h"

        CSCbinTreeNodeType   CSCbinTreeNodeTagSearch (
                                                CSCbinTreeNodeType   const node,
                                                long                       tag
                                                     );

RETURN VALUE
        CSCbinTreeNodeTagSearch(), if successful, returns a CSCbinTreeNodeType
        that is the node whose tag-field value is equal to tag, or NULL if
        otherwise not successful.

DESCRIPTION
        CSCbinTreeNodeTagSearch() searches `node', and recursively all of its
        children, for a node with a tag-field that is equal to `tag'.

        A recursive postfix tree traversal algorithm is used.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeStat(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC CSCbinTreeNodeType   (CSCbinTreeNodeTagSearch) (
                                                CSCbinTreeNodeType   const node,
                                                long                       tag
                                                      )
   {
   CSCbinTreeNodeType   tmpNode = NULL;

   ASSERT_RTN (node != NULL, "CSCbinTreeNodeTagSearch: null node", NULL);
   ASSERT_RTN (						\
              node->sig_lo==TREE_SIG,			\
              "CSCbinTreeNodeTagSearch: bad tree sig",	\
              NULL					\
              );
   ASSERT_RTN (						\
              node->sig_hi==TREE_SIG,			\
              "CSCbinTreeNodeTagSearch: bad tree sig",	\
              NULL					\
              );

   tmpNode = tagSearch (node, tag);

   return (tmpNode);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodeStat
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodeStat">

NAME
        CSCbinTreeNodeStat - retrieve fields from a libcsc binary tree node

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodeStat (
                                 CSCbinTreeNodeType   const node,
                                 CSCdataCntrlType*    const pushPtr,
                                 long*                const tagPtr,
                                 size_t*              const sizePtr,
                                 void**               const dataPtrPtr
                                 );

RETURN VALUE
        CSCbinTreeNodeStat() returns CSC_OK.  If libcsc was compiled with the
        DEBUG macro and node is NULL, then CSCbinTreeNodeStat() returns
        CSC_BADARG.  If libcsc was compiled with the DEBUG macro and some
        internal tree data is munged up then CSCbinTreeNodeStat() returns
        CSC_CORRUPT.

DESCRIPTION
        CSCbinTreeNodeStat() is used to get values of various fields from the
        given libcsc binary tree node `node'.

        if `pushPtr' is not NULL, then the value of the push field of `node' is
        written to the CSCdataCntrlType pointed to by `pushPtr'.

        if `tagPtr' is not NULL, then the value of the tag field of `node' is
        written to the long pointed to by `tagPtr'.

        if `sizePtr' is not NULL, then the value of the data size field of
        `node' is written to the size_t pointed to by `sizePtr'.

        if `dataPtrPtr' is not NULL, then the value of the data pointer field
        `node' is written to the void pointer pointed to by `dataPtrPtr'.

        If tagPtr, sizePtr, and dataPtrPtr are all NULL, then this function
        does nothing interesting.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodePrint(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodeStat) (
                                  CSCbinTreeNodeType   const node,
                                  CSCdataCntrlType*    const pushPtr,
                                  long*                const tagPtr,
                                  size_t*              const sizePtr,
                                  void**               const dataPtrPtr
                                  )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (node != NULL, "CSCbinTreeNodeQuery: null node", CSC_BADARG);
   ASSERT_RTN (					\
              node->sig_lo==TREE_SIG,		\
              "CSCbinTreeNodeQuery: bad sig",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi==TREE_SIG,		\
              "CSCbinTreeNodeQuery: bad sig",	\
              CSC_CORRUPT			\
              );

   if (pushPtr != NULL)    *pushPtr    = node->push;
   if (tagPtr != NULL)     *tagPtr     = node->tag;
   if (sizePtr != NULL)    *sizePtr    = node->size;
   if (dataPtrPtr != NULL) *dataPtrPtr = (void* const)node->data;

   return (statStat);
   }


/***************************************************************************
 * Public Function CSCbinTreeNodePrint
 ***************************************************************************

<SUBROUTINE NAME="CSCbinTreeNodePrint">

NAME
        CSCbinTreeNodePrint - print the values of a libcsc binary tree node

SYNOPSYS
        #include "libcsc.h"

        int   CSCbinTreeNodePrint (
                                  CSCbinTreeNodeType   const node
                                  );

RETURN VALUE
        CSCbinTreeNodePrint() returns CSC_OK.  If libcsc was compiled with the
        DEBUG macro and node is NULL, then CSCbinTreeNodePrint() returns
        CSC_BADARG.  If libcsc was compiled with the DEBUG macro and some
        internal tree data is munged up then CSCbinTreeNodePrint() returns
        CSC_CORRUPT.

DESCRIPTION
        CSCbinTreeNodePrint() writes to standard output the values of the
        balance, tag, and data size fields of node.

SEE ALSO
        CSCbinTreeNew(3)
        CSCbinTreeDel(3)
        CSCbinTreeInsert(3)
        CSCbinTreeTagOrderedInsert(3)
        CSCbinTreeTraverse(3)
        CSCbinTreeUserSearch(3)
        CSCbinTreeTagSearch(3)
        CSCbinTreeStat(3)
        CSCbinTreePrint(3)
        CSCbinTreeNodeNew(3)
        CSCbinTreeNodeDel(3)
        CSCbinTreeNodeJoin(3)
        CSCbinTreeNodeBreak(3)
        CSCbinTreeNodeTraverse(3)
        CSCbinTreeNodeUserSearch(3)
        CSCbinTreeNodeTagSearch(3)
        CSCbinTreeNodeStat(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCbinTreeNodePrint) (
                                   CSCbinTreeNodeType   const node
                                   )
   {
   int   printStat = CSC_OK;

   ASSERT_RTN (node != NULL, "CSCbinTreeNodePrint: null node", CSC_BADARG);
   ASSERT_RTN (					\
              node->sig_lo==TREE_SIG,		\
              "CSCbinTreeNodePrint: bad sig",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              node->sig_hi==TREE_SIG,		\
              "CSCbinTreeNodePrint: bad sig",	\
              CSC_CORRUPT			\
              );

   printf ("\n-------------------------\n\n");

   printf ("balance:  %d\n",  node->balance);
   printf ("    tag:  %ld\n", node->tag);
   printf ("   data:  %ld bytes at %p\n", (long)node->size, node->data);

   return (printStat);
   }


/* End of the file. */
