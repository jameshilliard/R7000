/* *****************************************************************************

libcsc: Main Header File

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

	$RCSfile: libcsc.h,v $
	$Revision: 1.9 $
	$Date: 2003/03/24 04:08:00 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

	This is the main libcsc header file. This file contains libcsc external
	data and functions that are exported for libcsc client code.

CHANGE LOG

	23mar03	drj	Added CSCmemListType argument to CSChashEntryGet() and
			CSCsymtabEntryGet().

	03may02	drj	Small comment changes.

	23apr02	drj	Changed several subsystems function prototypes.

	20apr02	drj	Fixed list subsystem prototypes.

	18apr02	drj	Added symbol table subsystem.

	15apr02	drj	Added hash and math subsystems.

	13apr02	drj	Added CSCsysUsleep().

	11apr02	drj	Added binary tree subsystem.

	16feb02	drj	Added list subsystem.

	25jun01	drj	File generation.

***************************************************************************** */


#ifndef __libcsch
#define __libcsch


#ifdef	__cplusplus
extern	"C"	{
#endif


/* ************************************************************************* */
/*                                                                           */
/*      I n c l u d e d   F i l e s                                          */
/*                                                                           */
/* ************************************************************************* */

#include	<stdlib.h>    /* for calloc() and free() */
#include	<stdio.h>     /* for FILE */
#include	<unistd.h>
#include	<sys/types.h> /* for off_t */


/* ************************************************************************* */
/*                                                                           */
/*      M a n i f e s t   C o n s t a n t s                                  */
/*                                                                           */
/* ************************************************************************* */

#define	PRIVATE	static	/* Use this when static really means private. */
#define	PUBLIC		/* This tags exported functions and data.     */

#define	CSC_MALLOC_FUNC(x,y)	calloc(x,y)
#define	CSC_FREE_FUNC(x)	free(x)

/* misc function wrapper subsystem */
#define	CSC_STREQ(s1,s2)	(strcmp(s1,s2)==0)
#define	CSC_STRNEQ(s1,s2)	(strcmp(s1,s2)!=0)

/* hash table subsystem */
#define	CSChashPrint(x)		CSChashWrite(STDOUT_FILENO,x)

/* list subsystem */
#define	CSClistScan(x)		CSClistRead(STDIN_FILENO,x)
#define	CSClistPrint(x)		CSClistWrite(STDOUT_FILENO,x)

/* symbol subsystem */
#define	CSCsymbolIntPrint(x)	CSCsymbolIntWrite(STDOUT_FILENO,x)
#define	CSCsymbolFloatPrint(x)	CSCsymbolFloatWrite(STDOUT_FILENO,x)
#define	CSCsymbolPtrPrint(x)	CSCsymbolPtrWrite(STDOUT_FILENO,x)


/* ************************************************************************* */
/*                                                                           */
/*      S c a l a r   D a t a   T y p e s                                    */
/*                                                                           */
/* ************************************************************************* */

/*
 * These are compiler dependent scalar data types.
 */

typedef   unsigned int     uint32;
typedef   int               int32;

typedef   unsigned short   uint16;
typedef   short             int16;

typedef   unsigned char    uint8;
typedef   char              int8;

/*
 * The following enumerations may be used to flag binary switches; there is
 * also a null state for some of these, which makes them tri-state.
 */

typedef enum
   {
   CSC_IO_INPUT = 0, CSC_IO_OUTPUT = 1, CSC_IO_NULL = 2
   } CSCioDeviceType;

typedef enum
   {
   CSC_IN = 0, CSC_OUT = 1
   } CSCioSwitchType;

typedef enum
   {
   CSC_FALSE = 0, CSC_TRUE = 1, CSC_INDETERMINATE = 2
   } CSCboolean;

typedef enum
   {
   CSC_OFF = 0, CSC_ON = 1, CSC_HIGH_Z = 2
   } CSConOffType;

typedef enum
   {
   CSC_FAIL = 0, CSC_PASS = 1, CSC_UNGRADED = 2
   } CSCpassFailType;

/*
 * These enumerations are the collection of function arguments that are given
 * to various libcsc functions.
 */

typedef enum
   {
   CSC_NO_PROFILING = 0, CSC_DO_PROFILING   = 1,
   CSC_SHOW_ALL     = 2, CSC_SHOW_ALLOCATED = 3
   } CSCprofileType;

/*
 * These are used to specify to restart or not to restart interrupted slow
 * system calls.
 */
typedef enum
   {
   CSC_SIG_INTERRUPT, CSC_SIG_RESTART
   } CSCsigModeType;

/*
 * These flags are used as arguments to some of the csc functions.  Some of the
 * csc subsystems' functions operate with user's data passed to them as an
 * argument; this client data may be directly used, duplicated, or removed
 * depending upon the value of a flag argument.  These are the values of the
 * flag arguments:
 */
typedef enum
   {
   CSC_DATA_OK    = 0,
   CSC_DATA_NODUP = 0x4E4F434F,
   CSC_DATA_DUP   = 0x434F5043,
   CSC_DATA_RM    = 0x524D4441
   } CSCdataCntrlType;

/*
 * Hash table key types; these specify the type of key used by a particlar hash
 * table.
 */
typedef enum
   {
   CSC_HASH_ASCIIZ_KEY = 0x41734349,
   CSC_HASH_INT32_KEY  = 0x494E5431
   } CSChashKeyType;

/*
 * Some list operations work on the front (head) or back (tail) of a list;
 * these are used to specify such.
 */
typedef enum
   {
   CSC_LIST_HEAD = 0x48454144,
   CSC_LIST_TAIL = 0x5441494C
   } CSClistBiasType;

/*
 * This enumeration is the collection of return values that are returned by
 * libcsc functions.
 */

typedef enum
   {
   CSC_ERROR    = -1, /* general error         */
   CSC_OK       = 0,  /* all ok                */
   CSC_BADARG   = 1,  /* bad argument          */
   CSC_CORRUPT  = 2,  /* internal corruption   */
   CSC_NOMEM    = 3,  /* can't allocate memory */
   CSC_NOTFOUND = 4,  /* can't find item       */
   CSC_NOSVC    = 5,  /* no service available  */
   CSC_NOPROT   = 6,  /* no protocol available */
   CSC_NOSOCK   = 7,  /* no socket available   */
   CSC_NOBIND   = 8,  /* can't bind something  */
   CSC_NOLISTEN = 9,  /* listen() failed       */
   CSC_DUPKEY   = 10  /* duplicate key         */
   } CSCstatusType;

/*
 * Some csc subsystems make use of client callback functions. Client code
 * provides function pointers (callbacks) and csc subsystems will invoke the
 * client functions via these function callback pointers. These are the
 * types of callbacks and what they are asked to do.
 *      compare - compare two void pointers
 *      general - accept data (probably status) from subsystem
 *      monitor - critical region locking
 *      tag     - return a string (const char*) corresponding to an integer
 *
 * The function pointers are typedef'ed here:
 */
typedef int           (*CSCcmpFnType)(void*,void*);           /* compare */
typedef int           (*CSCgenFnType)(int,int,void*);         /* general */
typedef int           (*CSCmonFnType)(CSCioSwitchType,void*); /* monitor */
typedef void          (*CSCsigFnType)(int);                   /* signal  */
typedef const char*   (*CSCtagFnType)(int);                   /* tag     */


/* ************************************************************************* */
/*                                                                           */
/*      N o n - S c a l a r   D a t a   S t r u c t u r e s                  */
/*                                                                           */
/* ************************************************************************* */

/*
 * The following are some opaque data types for some of the various subsystems.
 */

/* -- Binary Tree Subsystem */

typedef   struct S_binTreeType*       CSCbinTreeType;
typedef   struct S_binTreeNodeType*   CSCbinTreeNodeType;

/* -- Hash Table Subsystem*/

typedef struct   CSChashStatType
   {
   char             name[80];
   CSCprofileType   profiling;
   size_t           count;
   size_t           nhash;
   CSCboolean       grows;
   size_t           resizes;
   size_t           deletions;
   size_t           insertions;
   size_t           collisions;
   } CSChashStatType;

typedef union S_hashKeyUnion
   {
   int32   integer;
   char*   asciiz;
   } S_hashKeyUnion;

typedef   union  S_hashKeyUnion     CSChashKeyUnion;
typedef   struct S_hashEntryType*   CSChashEntryType;
typedef   struct S_hashTableType*   CSChashTableType;

/* -- List Subsystem */

typedef   struct S_listType*       CSClistType;
typedef   struct S_listNodeType*   CSClistNodeType;

/* -- Memory Subsystem */

typedef   struct S_memListType*   CSCmemListType;

/* -- Notification System Subsystem */

typedef   struct S_notifBoardType*   CSCnotificationBoardType;

/* -- Symbol Subsystem */

/*
 * The libcsc symbol subsystem does not use an opaque data type, symbol
 * subsystem client code is free to use the symbol structure; this subsystem
 * originally was nothing more than some definitions in a header file, but,
 * as you can find in the function prototypes below, there are now some simple
 * helper functions in the libcsc symbol subsystem.
 */
typedef struct symbol
   {
   char*    name;
   long     type;
   int      valueFlag; /* 1=>integer, 2=>float, 3=>pointer */
   size_t   dvSize;
   union
      {
      int     integer; /* => valueFlag == 1 */
      float   real;    /* => valueFlag == 2 */
      void*   pointer; /* => valueFlag == 3 */
      } value;
   } CSCsymbolType;

/* -- Symbol Table Subsystem */

typedef   struct S_symTableType*   CSCsymTableType;

/* -- Timer Subsystem */

typedef   struct S_timerType*   CSCtimerType;


/* ************************************************************************* */
/*                                                                           */
/*      P u b l i c   G l o b a l   V a r i a b l e s                        */
/*                                                                           */
/* ************************************************************************* */

/*  (None.)  */


/* ************************************************************************* */
/*                                                                           */
/*      F u n c t i o n   P r o t o t y p e s                                */
/*                                                                           */
/* ************************************************************************* */

/* -- libcsc Configuration and General Function Prototypes */

PUBLIC const char*   CSCstatStr (int status);
PUBLIC const char*   CSCcflags (void);
PUBLIC const char*   CSCldflags (void);
PUBLIC const char*   CSClibs (void);
PUBLIC const char*   CSCcredits (void);
PUBLIC const char*   CSCversion (void);
PUBLIC void          CSCchkup (void);

/* -- Binary Tree Subsystem Function Prototypes */

PUBLIC CSCbinTreeType   CSCbinTreeNew (
                                      const char*            namePtr,
                                            CSCmonFnType     monFunc,
                                      const void*            monData,
                                            CSCprofileType   profiling
                                      );

PUBLIC int   CSCbinTreeDel (
                           CSCbinTreeType   const tree,
                           CSCgenFnType           cbFn
                           );

PUBLIC int   CSCbinTreeInsert (
                              CSCbinTreeType       const tree,
                              CSCbinTreeNodeType   const node,
                              CSCcmpFnType               cmpfn
                              );

PUBLIC int   CSCbinTreeTagOrderedInsert (
                                        CSCbinTreeType       const tree,
                                        CSCbinTreeNodeType   const node
                                        );

PUBLIC int   CSCbinTreeTraverse (
                                const char*            const method,
                                      CSCbinTreeType   const tree,
                                      CSCcmpFnType           clientFn,
                                const void*            const clientData
                                );

PUBLIC CSCbinTreeNodeType   CSCbinTreeUserSearch (
                                               CSCbinTreeType   const tree,
                                               CSCcmpFnType           clientFn,
                                         const void*            const clientData
                                                 );

PUBLIC CSCbinTreeNodeType   CSCbinTreeTagSearch (
                                                CSCbinTreeType   const tree,
                                                long                   tag
                                                );

PUBLIC int   CSCbinTreeStat (
                            CSCbinTreeType   const tree,
                            size_t*          const countPtr,
                            size_t*          const heightPtr,
                            size_t*          const comparesPtr,
                            size_t*          const rotatesPtr
                            );

PUBLIC int   CSCbinTreePrint (
                             CSCbinTreeType   const tree
                             );

PUBLIC CSCbinTreeNodeType   CSCbinTreeNodeNew (
                                               CSCdataCntrlType         push,
                                               long                     tag,
                                         const void*              const dataPtr,
                                               size_t                   dataSize
                                              );

PUBLIC int   CSCbinTreeNodeDel (
                               CSCbinTreeNodeType   const node
                               );

PUBLIC int   CSCbinTreeNodeJoin (
                                CSCbinTreeNodeType   const node,
                                CSCbinTreeNodeType   const left,
                                CSCbinTreeNodeType   const right
                                );

PUBLIC int   CSCbinTreeNodeBreak (
                                 CSCbinTreeNodeType    const node,
                                 CSCbinTreeNodeType*   const leftPtr,
                                 CSCbinTreeNodeType*   const rightPtr
                                 );

PUBLIC int   CSCbinTreeNodeTraverse (
                                    const char*                const method,
                                          CSCbinTreeNodeType   const node,
                                          CSCcmpFnType               clientFn,
                                    const void*                const clientData
                                    );

PUBLIC CSCbinTreeNodeType   CSCbinTreeNodeUserSearch (
                                           CSCbinTreeNodeType   const node,
                                           CSCcmpFnType               clientFn,
                                     const void*                const clientData
                                                     );

PUBLIC CSCbinTreeNodeType   CSCbinTreeNodeTagSearch (
                                                CSCbinTreeNodeType   const node,
                                                long                       tag
                                                    );

PUBLIC int   CSCbinTreeNodeStat (
                                CSCbinTreeNodeType   const node,
                                CSCdataCntrlType*    const pushPtr,
                                long*                const tagPtr,
                                size_t*              const sizePtr,
                                void**               const dataPtrPtr
                                );

PUBLIC int   CSCbinTreeNodePrint (
                                 CSCbinTreeNodeType   const node
                                 );

/* -- File Subsystem Function Prototypes */

PUBLIC int   CSCfileReadLock (int fd, off_t offset, int whence, off_t length);
PUBLIC int   CSCfileWriteLock (int fd, off_t offset, int whence, off_t length);
PUBLIC int   CSCfileUnlock (int fd, off_t offset, int whence, off_t length);

PUBLIC char*   CSCfileGetHomeDir (
                                 const size_t                 pathSize,
                                       CSCmemListType   const memList,
                                       int                    memTag
                                 );

PUBLIC char*   CSCfileGetUserHomeDir (
                                     const char*            const userName,
                                     const size_t                 pathSize,
                                           CSCmemListType   const memList,
                                           int                    memTag
                                     );

PUBLIC char*   CSCfileBaseName (
                               const char*            const path,
                                     CSCmemListType   const memList,
                                     int                    memTag
                               );

PUBLIC char*   CSCfilePathName (
                               const char*            const path,
                                     CSCmemListType   const memList,
                                     int                    memTag
                               );

PUBLIC char*   CSCfileExpandPath (
                                 const char*            const path,
                                 const size_t                 pathMax,
                                       CSCmemListType   const memList,
                                       int                    memTag
                                 );

PUBLIC FILE*   CSCfileOpen (
                           const char*            const path,
                           const int                    mask,
                           const size_t                 pathMax,
                                 CSCmemListType   const memList,
                                 int                    memTag
                           );

/* -- Hash Table Subsystem Function Prototypes */

PUBLIC CSChashTableType   CSChashNew (
                                     const char*            const namePtr,
                                           CSChashKeyType         keySpec,
                                           size_t                 size,
                                           CSCmonFnType           monFunc,
                                     const void*                  monData,
                                           CSCprofileType         profiling
                                       );

PUBLIC int   CSChashDel (
                        CSChashTableType   const hashTable
                        );

PUBLIC int   CSChashStat (
                         CSChashTableType   const hashTable,
                         CSChashStatType*   const statStruct
                         );

PUBLIC int   CSChashEntryPut (
                             CSChashTableType   const hashTable,
                             CSChashKeyUnion*   const keyPtr,
                             void*              const itemPtr,
                             size_t                   itemSize
                             );

PUBLIC int   CSChashEntryGet (
                             CSChashTableType   const hashTable,
                             CSChashKeyUnion*   const keyPtr,
                             void**             const itemPtrPtr,
                             size_t*            const itemSizePtr,
                             CSCmemListType     const memLst
                             );

PUBLIC int   CSChashEntryDel (
                             CSChashTableType   const hashTable,
                             CSChashKeyUnion*   const keyPtr
                             );

PUBLIC CSChashEntryType   CSChashEntryNext (
                                           CSChashTableType   const hashTable,
                                           CSChashEntryType   const entry
                                           );

PUBLIC int   CSChashEntryStat (
                              CSChashEntryType    const entry,
                              CSChashKeyUnion**   const keyPtrPtr,
                              void**              const itemPtrPtr,
                              size_t*             const itemSizePtr
                              );

PUBLIC int   CSChashRead (
                               int                       fd,
                               CSChashTableType*   const hashTablePtr,
                               CSCmonFnType              monFunc,
                         const void*                     monData,
                               CSCprofileType            profiling
                         );

PUBLIC int   CSChashWrite (
                          int                      fd,
                          CSChashTableType   const hashTable
                          );

PUBLIC int   CSChashDump (
                         int                      fd,
                         CSChashTableType   const hashTable
                         );

/* -- I/O Subsystem Function Prototypes */

PUBLIC void   CSCioInfoPrint (
                             const char*   cscPtr,
                             const char*   csuPtr,
                             const char*   fmtPtr,
                             ...
                             );

PUBLIC void   CSCioWarnPrint (
                             const char*   cscPtr,
                             const char*   csuPtr,
                             const char*   fmtPtr,
                             ...
                             );

PUBLIC void   CSCioErrorPrint (
                              const char*   cscPtr,
                              const char*   csuPtr,
                              const char*   fmtPtr,
                              ...
                              );

PUBLIC void   CSCioSoftwareError (
                                 const char*   identPtr,
                                 const char*   csciPtr,
                                 const char*   fmtPtr,
                                 ...
                                 );

PUBLIC int   CSCioRead (
                       int            fd,
                       char*    const bufPtr,
                       size_t         size
                       );

PUBLIC int   CSCioReadLine (
                           int                    fd,
                           char**           const bufPtrPtr,
                           CSCmemListType   const memList,
                           int                    tagData
                           );

PUBLIC int   CSCioBufWrite (
                                 int      fd,
                           const void*    dataPtr,
                                 size_t   size
                           );

PUBLIC int   CSCioBufRead (
                          int                    fd,
                          void**           const dataPtrPtr,
                          size_t*          const sizePtr,
                          CSCmemListType   const memList,
                          int                    tagData
                          );

/* -- List Subsystem Function Prototypes */

PUBLIC CSClistType   CSClistNew (
                                const char*            namePtr,
                                      CSCmonFnType     monFunc,
                                const void*            monData,
                                      CSCprofileType   profiling
                                );

PUBLIC int   CSClistDel (CSClistType const list);

PUBLIC int   CSClistRead (
                         int                 fd,
                         CSClistType   const list
                         );

PUBLIC int   CSClistWrite (
                          int                 fd,
                          CSClistType   const list
                          );

PUBLIC int   CSClistSetCFunc (
                             CSClistType    const list,
                             CSCcmpFnType         funcptr
                             );

PUBLIC int   CSClistStat (
                         CSClistType   const list,
                         size_t*       const pushCountPtr,
                         size_t*       const popCountPtr,
                         size_t*       const maxAllocPtr,
                         size_t*       const curAllocPtr
                         );

PUBLIC int   CSClistPush (
                               CSClistType        const list,
                               CSCdataCntrlType         push,
                         const void*              const itemPtr,
                         const size_t                   itemSize
                         );

PUBLIC int   CSClistPop (
                        CSClistType       const list,
                        CSClistBiasType         bias,
                        void**            const itemPtrPtr,
                        size_t*           const itemSizePtr
                        );

PUBLIC int   CSClistPeek (
                         CSClistType       const list,
                         CSClistBiasType         bias,
                         void**            const itemPtrPtr,
                         size_t*           const itemSizePtr
                         );

PUBLIC CSClistNodeType   CSClistNodeNext (
                                         CSClistType       const list,
                                         CSClistBiasType         bias,
                                         CSClistNodeType         node
                                         );

PUBLIC CSClistNodeType   CSClistNodeFindByValue (
                                                CSClistType       const list,
                                                CSClistBiasType         bias,
                                          const void*             const itemPtr
                                                );

PUBLIC CSClistNodeType   CSClistNodeFindByReference (
                                                CSClistType       const list,
                                                CSClistBiasType         bias,
                                          const void*             const itemPtr
                                                    );

PUBLIC int   CSClistNodeStat (
                             CSClistNodeType   const node,
                             void**            const itemPtrPtr,
                             size_t*           const itemSizePtr
                             );

PUBLIC int   CSClistNodeValidate (
                                  CSClistType       const list,
                                  CSClistNodeType   const node
                                  );

PUBLIC int   CSClistNodeDel (
                            CSClistType       const list,
                            CSClistNodeType         node
                            );


/* -- Math Subsystem Function Prototypes */

PUBLIC int   CSC2x (int exp);

PUBLIC int   CSCurand (int y, double* dptr);

/* -- Memory (Dynamic Allocation) Subsystem Function Prototypes */

PUBLIC CSCmemListType   CSCmemInit (
                                   const char*            namePtr,
                                         CSCtagFnType     tagFunc,
                                         CSCmonFnType     monFunc,
                                   const void*            monData,
                                         CSCprofileType   profiling
                                   );

PUBLIC int   CSCmemDone (CSCmemListType const memList);

PUBLIC int   CSCmemAlloc (
                         CSCmemListType   const memList,
                         void**           const memPtrPtr,
                         size_t                 itemCount,
                         size_t                 itemSize,
                         int                    tagData
                         );

PUBLIC int   CSCmemDup (
                             CSCmemListType   const memList,
                             void**           const dstPtrPtr,
                       const void*                  srcPtr,
                             size_t                 size,
                             int                    tagData
                       );

PUBLIC int   CSCmemLookup (
                                CSCmemListType   const memList,
                          const void*                  memPtr,
                                size_t*          const sizePtr,
                                int*             const tagPtr
                          );

PUBLIC int   CSCmemValidate (
                                  CSCmemListType   const memList,
                            const void*                  memPtr
                            );

PUBLIC int   CSCmemFree (
                        CSCmemListType   const memList,
                        void**           const memPtrPtr,
                        int                    tagData
                        );

PUBLIC int   CSCmemListFree (
                            CSCmemListType   const memList,
                            int                    tagData
                            );

PUBLIC int   CSCmemListStat (
                            CSCmemListType   const memList,
                            size_t*          const allocCountPtr,
                            size_t*          const freeCountPtr,
                            size_t*          const maxMemAllocPtr,
                            size_t*          const curMemAllocPtr
                            );

PUBLIC int   CSCmemListPrintProfile (
                                    CSCmemListType   const memList,
                                    CSCprofileType         showing
                                    );

PUBLIC int   CSCmemListWriteProfile (
                                    CSCmemListType   const memList,
                                    int                    fd,
                                    CSCprofileType         showing
                                    );

/* -- Notification System Subsystem */

PUBLIC CSCnotificationBoardType   CSCnotificationBoardNew (
                                                const char*            namePtr,
                                                      CSCmonFnType     monFunc,
                                                const void*            monData,
                                                      CSCprofileType   profiling
                                                          );

PUBLIC int   CSCnotificationBoardDel (
                                     CSCnotificationBoardType   const board
                                     );

PUBLIC int   CSCnotificationNew (
                                      CSCnotificationBoardType   const board,
                                const char*                            namePtr,
                                      CSCgenFnType                     errfn
                                );

PUBLIC int   CSCnotificationDel (
                                      CSCnotificationBoardType   const board,
                                const char*                            namePtr
                                );

PUBLIC int   CSCnotificationPost (
                                       CSCnotificationBoardType   const board,
                                 const char*                            namePtr
                                 );

PUBLIC int   CSCnotificationRegister (
                                  CSCnotificationBoardType   const board,
                            const char*                            notifName,
                            const char*                            clientName,
                                  CSCgenFnType                     fn,
                            const CSCboolean*                      runFlag,
                                  int                              tag,
                            const void*                            data
                                     );

PUBLIC void   CSCnotificationBoardPrint (
                                        CSCnotificationBoardType   const board
                                        );

/* -- BSD Socket Subsystem Function Prototypes */

PUBLIC int   CSCsockConnectTCP (
                                     int*           const socketPtr,
                               const char*                host,
                               const char*                service,
                                     CSCgenFnType         errorCallback
                               );

PUBLIC int   CSCsockConnectUDP (
                                     int*           const socketPtr,
                               const char*                host,
                               const char*                service,
                                     CSCgenFnType         errorCallback
                               );

PUBLIC int   CSCsockPassiveTCP (
                                     int*           const socketPtr,
                               const char*                service,
                                     int                  connectCount,
                                     CSCgenFnType         errorCallback
                               );

PUBLIC int   CSCsockPassiveUDP (
                                     int*           const socketPtr,
                               const char*                service,
                                     int                  connectCount,
                                     CSCgenFnType         errorCallback
                               );

/* -- String Subsystem Function Prototypes */

PUBLIC char*   CSCstringOctal (
                              char*   const bufPtr,
                              int32         item
                              );

PUBLIC char*   CSCstringBinary (
                               char*   const bufPtr,
                               int32         item
                               );

PUBLIC char*   CSCstringBasename (
                                 char**   const pathPtrPtr
                                 );

/* -- Symbol Subsystem Function Prototypes */

PUBLIC int   CSCsymbolIntInit (
                                    CSCsymbolType*   const symbol,
                              const char*            const symName,
                                    long                   symType,
                                    int                    symVal
                              );

PUBLIC int   CSCsymbolFloatInit (
                                      CSCsymbolType*   const symbol,
                                const char*            const symName,
                                      long                   symType,
                                      float                  symVal
                                );

PUBLIC int   CSCsymbolPtrInit (
                                    CSCsymbolType*   const symbol,
                              const char*            const symName,
                                    long                   symType,
                              const void*                  symVal,
                                    size_t                 symValSize
                              );

PUBLIC CSCsymbolType*   CSCsymbolIntNew (
                                        const char*            const symName,
                                              long                   symType,
                                              int                    symVal,
                                              CSCmemListType   const memList,
                                              int                    memTag
                                        );

PUBLIC CSCsymbolType*   CSCsymbolFloatNew (
                                          const char*           const symName,
                                                long                  symType,
                                                float                 symVal,
                                                CSCmemListType  const memList,
                                                int                   memTag
                                          );

PUBLIC CSCsymbolType*   CSCsymbolPtrNew (
                                         const char*           const symName,
                                               long                  symType,
                                         const void*                 symVal,
                                               size_t                symValSize,
                                               CSCmemListType  const memList,
                                               int                   memTag
                                          );

PUBLIC int   CSCsymbolIntDel (
                             CSCsymbolType**   const symPtrPtr,
                             CSCmemListType    const memList,
                             int                     memTag
                             );

PUBLIC int   CSCsymbolFloatDel (
                               CSCsymbolType**   const symPtrPtr,
                               CSCmemListType    const memList,
                               int                     memTag
                               );

PUBLIC int   CSCsymbolPtrDel (
                             CSCsymbolType**   const symPtrPtr,
                             CSCmemListType    const memList,
                             int                     memTag
                             );

PUBLIC int   CSCsymbolIntWrite (
                               const int                    fd,
                               const CSCsymbolType*   const symPtr
                               );

PUBLIC int   CSCsymbolFloatWrite (
                                 const int                    fd,
                                 const CSCsymbolType*   const symPtr
                                 );

PUBLIC int   CSCsymbolPtrWrite (
                               const int                    fd,
                               const CSCsymbolType*   const symPtr
                               );

PUBLIC CSCsymbolType*   CSCsymbolDup (
                                     const CSCsymbolType*   const symPtr,
                                           CSCmemListType   const memList,
                                           int                    memTag
                                     );

PUBLIC int   CSCsymbolDel (
                          CSCsymbolType**   const symPtrPtr,
                          CSCmemListType    const memList,
                          int                     memTag
                          );

/* -- Symbol Table Subsystem Function Prototypes */

PUBLIC CSCsymTableType   CSCsymtabNew (
                                      const char*          const namePtr,
                                            size_t               size,
                                      const char**               keyWords,
                                            int                  keyWordSpec,
                                            CSCmonFnType         monFunc,
                                      const void*                monData,
                                            CSCprofileType       profiling
                                      );

PUBLIC int   CSCsymtabDel (
                          CSCsymTableType   const symTab
                          );

PUBLIC int   CSCsymtabStat (
                           CSCsymTableType   const symTab,
                           size_t*           const sizePtr
                           );

PUBLIC int   CSCsymtabEntryPut (
                               CSCsymTableType   const symTab,
                               CSCsymbolType*    const symbol
                               );

PUBLIC CSCsymbolType*   CSCsymtabEntryGet (
                                          CSCsymTableType   const symTab,
                                          char*             const symName,
                                          CSCmemListType     const memLst
                                          );

PUBLIC int   CSCsymtabEntryDel (
                               CSCsymTableType   const symTab,
                               char*             const symName
                               );

PUBLIC void*   CSCsymtabEntryNext (
                                  CSCsymTableType   const symTab,
                                  void*             const lhPtr
                                  );

/* -- System Subsystem Function Prototypes */

PUBLIC int   CSCsysLimitsGet (
                             int*    const fileOpenMaxPtr,
                             int*    const fileNameLengthPtr,
                             int*    const filePathLengthPtr
                             );

PUBLIC CSCsigFnType   CSCsysInstallSignal (
                                          const int              signo,
                                          const CSCsigFnType     func,
                                          const CSCsigModeType   mode
                                          );

PUBLIC void   CSCsysUsleep (
                           const size_t   microseconds
                           );

/* -- Timer Subsystem Function Prototypes */

PUBLIC CSCtimerType   CSCtimerInit (void);

PUBLIC int   CSCtimerDone (CSCtimerType const timer);

PUBLIC int   CSCtimerClear (CSCtimerType const timer);

PUBLIC int   CSCtimerMark (CSCtimerType const timer);

PUBLIC int   CSCtimerDiff (
                          CSCtimerType   const timer,
                          double*        const diffPtr
                          );

PUBLIC int   CSCtimerStat (
                          CSCtimerType   const timer,
                          double*        const diffPtr
                          );


#ifdef	__cplusplus
}
#endif


#endif
