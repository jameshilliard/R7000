/* *****************************************************************************

libcsc:  Symbol Table Subsystem

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

	$RCSfile: csc_symtab.c,v $
	$Revision: 1.3 $
	$Date: 2003/03/24 04:27:02 $


PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>


FILE DESCRIPTION

<SUBSYSTEM NAME="csc_symtab">

NAME
        csc_symtab

DESCRIPTION
        Symbol Table Subsystem

FUNCTIONS
        CSCsymtabNew       - create a new libcsc hash table
        CSCsymtabDel       - remove a libcsc symbol table
        CSCsymtabStat      - retrieve statistics for a libcsc symbol table
        CSCsymtabEntryPut  - add a symbol to a libcsc symbol table
        CSCsymtabEntryGet  - get a symbol in a libcsc symbol table
        CSCsymtabEntryDel  - remove a symbol from a libcsc symbol table
        CSCsymtabEntryNext - find next entry in a libcsc symbol table
</SUBSYSTEM>

CHANGE LOG

	23mar03	drj	Added a CSCmemListType argument to CSCsymtabEntryGet().

	29apr02	drj	Added internal documentation.

	18apr02	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Tracked changes to rtsMemDup().

	23apr00	drj	Simplified the data types and function prototypes.
			Fixed bugs with symbol usage.  Removed the useless
			function rtsSymTabClr().

	05dec99	drj	Added symbol duplication in rtsSymTabEntryPut().
			Added more housekeeping for dynamically allocated
			symbol fields to avoid memory leaks.

	04dec99	drj	Fixed rtsSymTabEntryPut() bug that sent string, not
			string's address, to rtsHashEntryPut(); removed debug
			errors when adding duplicate symbol.
			Removed rtsSymTabEntryNext() debug errors when at the
			end of symbol table.
			Fixed rtsSymTabEntryGet() bug that sent string, not
			string's address, to rtsHashEntryGet(); removed debug
			errors when getting non-existing symbol.

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

#define	SYMTAB_SIG	(0x53594D54)
#define	SYMTAB_SIZE	(1009)

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

typedef struct S_symTableType
   {
#ifdef	DEBUG
   long             sig_lo;
#endif
   const char*      name;
   void*            table;
   int              keyWordSpec;
   CSCmemListType   memLst;
   CSCmonFnType     monFunc;
   const void*      monData;
   CSCprofileType   profiling;
   size_t           count;
#ifdef	DEBUG
   long             sig_hi;
#endif
   } S_symTableType;


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


/**************************************************************************
 * Public Function CSCsymtabNew
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabNew">

NAME
        CSCsymtabNew - create a new libcsc hash table

SYNOPSYS
        #include "libcsc.h"

        CSCsymTableType   CSCsymtabNew (
                                       const char*          const name,
                                             size_t               size,
                                       const char**               keyWords,
                                             int                  keyWordSpec,
                                             CSCmonFnType         monFunc,
                                       const void*                monData,
                                             CSCprofileType       profiling
                                       );

RETURN VALUE
        CSCsymtabNew(), if successful, returns an opaque data type
        representing a new libcsc symbol table, or NULL if otherwise not
        successful.

DESCRIPTION
        CSCsymtabNew() creates a new libcsc symbol table of `size' entries, and
        initialized with a set of keywords.

        `name' points to an arbitrary string that is used as the name of the
        new libcsc symbol table.

        If `size' is zero, then a default size is used.  Since the symbol table
        is implemented as a hash table, the number of entries can be larger
        than size.

        If `keyWords' is NULL, then no keywords are loaded.  Otherwise, keyWords
        is an array of character pointers; a symbol is created and put into the
        new table for each keyword.  A list of keywords is terminated by a
        keyword of zero length, not a NULL keyword pointer.

        `keyWordType' is the value used for the keyword symbols' type field.

SEE ALSO
        CSCsymtabDel(3)
        CSCsymtabStat(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryDel(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSCsymTableType   (CSCsymtabNew) (
                                        const char*          const name,
                                              size_t               size,
                                        const char**               keyWords,
                                              int                  keyWordSpec,
                                              CSCmonFnType         monFunc,
                                        const void*                monData,
                                              CSCprofileType       profiling
                                        )
   {
   CSCsymTableType   symTab        = NULL;
   CSCmemListType    memList       = NULL;
   size_t            hashTableSize = 0;

   ASSERT_RTN (name != NULL, "CSCsymtabNew: no hash name", NULL);
   ASSERT_RTN (								\
              ((profiling==CSC_DO_PROFILING)||(profiling==CSC_NO_PROFILING)),\
              "CSCsymtabNew: illegal profile value",			\
              NULL							\
              );

   memList = CSCmemInit (name, NULL, monFunc, monData, CSC_NO_PROFILING);
   if (memList != NULL)
      {
      (void)CSCmemAlloc (memList,(void**)&symTab,1,sizeof(S_symTableType),0);
      if (symTab != NULL)
         {
         symTab->name       = name;
         symTab->memLst     = memList;
         symTab->profiling  = profiling;
         symTab->monFunc    = monFunc;
         symTab->monData    = monData;
         symTab->keyWordSpec  = 0;
         symTab->table        = NULL;
         symTab->count        = 0;
#ifdef	DEBUG
         symTab->sig_lo = SYMTAB_SIG;
         symTab->sig_hi = SYMTAB_SIG;
#endif

         hashTableSize = size > 0 ? size : SYMTAB_SIZE;

         symTab->table = CSChashNew (
                                    name,
                                    CSC_HASH_ASCIIZ_KEY,
                                    hashTableSize,
                                    monFunc,
                                    monData,
                                    profiling
                                    );
         if (symTab->table != NULL)
            {
            symTab->keyWordSpec = keyWordSpec;
            if (keyWords != NULL)
               {
               int               keyWordStat = CSC_OK;
               CSCsymbolType*    keyWordSym  = NULL;
               CSChashKeyUnion   hashKey;
               while ((**keyWords != '\0') && (keyWordStat == CSC_OK))
                  {
                  keyWordSym = CSCsymbolIntNew (
                                               *keyWords,   /* symbol name  */
                                               keyWordSpec, /* symbol type  */
                                               0,           /* symbol value */
                                               memList,     /* memList      */
                                               0            /* memTag       */
                                               );
                  hashKey.asciiz = (char*)*keyWords;
                  keyWordStat = CSChashEntryPut (
                                                symTab->table,
                                                &hashKey,
                                                &keyWordSym,
                                                sizeof(CSCsymbolType*)
                                                );
                  ++keyWords;
                  }
               /* FIXME if keyWordStat != CSC_OK is not handled. */
               }
            }
         else
            {
            (void)CSCmemFree (memList, (void**)&symTab, 0);
            (void)CSCmemDone (memList);
            symTab = NULL;
            }
         }
      else
         {
         (void)CSCmemDone (memList);
         }
      }

   return (symTab);
   }


/**************************************************************************
 * Public Function CSCsymtabDel
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabDel">

NAME
        CSCsymtabDel - remove a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymtabDel (
                           CSCsymTableType   const symTab
                           );

RETURN VALUE
        CSCsymtabDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        The libcsc symbol table represented by the opaque `symTab' is completely
        removed.

BUGS
        Symbols not created by CSCsymbolFloatNew(), CSCsymbolIntNew(), and
        CSCsymbolPtrNew() may cause problems.  (The name and value.pointer data
        of the symbol should be dynamically allocated, and the valueFlag field
        needs to be set the way CSCsymbolFloatNew(), CSCsymbolIntNew(), and
        CSCsymbolPtrNew() set it.)

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabStat(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryDel(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCsymtabDel) (
                            CSCsymTableType   const symTab
                            )
   {
   int                delStat = CSC_OK;
   CSChashEntryType   entry   = NULL;
   CSCsymbolType*     symPtr  = NULL;

   ASSERT_RTN (symTab != NULL, "CSCsymtabDel: null symTab", CSC_BADARG);
   ASSERT_RTN (					\
              symTab->sig_lo == SYMTAB_SIG,	\
              "CSCsymtabDel: symTab blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              symTab->sig_hi == SYMTAB_SIG,	\
              "CSCsymtabDel: symTab blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(symTab);

/*
 * Things with pointers, like symbols, probably really shouldn't be put into a
 * hash table because the hash table duplicates the data it stores and can't
 * know that it is duplicating pointers.  Since this symbol table subsystem uses
 * the hash table there is the problem of dangling pointers when the hash table
 * subsystem deletes a hash table (because it can't know about the pointers it
 * duplicated when entries were put into it).  So, here we have to remove the
 * dynamically allocated things that would be left dangling when the hash table
 * is deleted.
 */
   entry = NULL;
   while ((entry=CSCsymtabEntryNext(symTab,entry)) != NULL)
      {
      if (CSChashEntryStat(entry,NULL,(void**)&symPtr,NULL) == CSC_OK)
         {
         (void)CSCsymbolDel (&symPtr, symTab->memLst, 0);
         }
      }

/*
 * Now, it should be safe to delete the hash.
 */
   delStat = CSChashDel ((CSChashTableType)symTab->table);

   if (delStat == CSC_OK)
      {
      CSCmemListType   memList = symTab->memLst;
      CSCmonFnType     monFunc = symTab->monFunc;
      const void*      monData = symTab->monData;
      symTab->name       = NULL;
      symTab->memLst     = NULL;
      symTab->profiling  = -1;
      symTab->monFunc    = NULL;
      symTab->monData    = NULL;
      symTab->keyWordSpec  = 0;
      symTab->table        = NULL;
      symTab->count        = 0;
#ifdef	DEBUG
      symTab->sig_lo = -1;
      symTab->sig_hi = -1;
#endif
      (void)CSCmemFree (memList, (void**)&symTab, 0);
      (void)CSCmemDone (memList);
      if (monFunc != NULL) (*monFunc) (CSC_OUT, (void*)monData);
      }
   else
      {
      MON_EXIT(symTab);
      }

   return (delStat);
   }


/**************************************************************************
 * Public Function CSCsymtabStat
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabStat">

NAME
        CSCsymtabStat - retrieve statistics for a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymtabStat (
                            CSCsymTableType   const symTab,
                            size_t*           const sizePtr
                            );

RETURN VALUE
        CSCsymtabStat(), if successful, returns RTS_OK; otherwise,
        RTS_NOTFOUND, RTS_BADARG, and RTS_ERROR can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCsymtabStat() queries the libcsc symbol table specified by the
        opaque `symTab'.

        If `sizePtr' is not NULL, then the count of symbols in `symTab' is
        written to the size_t that is pointed to by `sizePtr'.

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabDel(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryDel(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCsymtabStat) (
                             CSCsymTableType   const symTab,
                             size_t*           const sizePtr
                             )
   {
   int   statStat = CSC_OK;

   ASSERT_RTN (symTab != NULL, "CSCsymtabStat: null symTab", CSC_BADARG);
   ASSERT_RTN (					\
              symTab->sig_lo == SYMTAB_SIG,	\
              "CSCsymtabStat: symTab blows",	\
              CSC_CORRUPT			\
              );
   ASSERT_RTN (					\
              symTab->sig_hi == SYMTAB_SIG,
              "CSCsymtabStat: symTab blows",	\
              CSC_CORRUPT			\
              );

   MON_ENTER(symTab);

   if (sizePtr != NULL) *sizePtr = symTab->count;

   MON_EXIT(symTab);

   return (statStat);
   }


/**************************************************************************
 * Public Function CSCsymtabEntryPut
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabEntryPut">

NAME
        CSCsymtabEntryPut - add a symbol to a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymtabEntryPut (
                                CSCsymTableType   const symTab,
                                CSCsymbolType*    const symbol
                                );

RETURN VALUE
        CSCsymtabEntryPut(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCsymtabEntryPut() puts `symbol' into the symbol table specified by
        `symTab'.

        NOTE    Its best to put only symbols created by CSCsymbolFloatNew(),
                CSCsymbolIntNew(), and CSCsymbolPtrNew() because the symbol
                table delete functions expect the symbols to be created the
                way these function do, with the name and value.pointer data
                being dynamically allocated, and the valueFlag field being
                correctly set.

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabDel(3)
        CSCsymtabStat(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryDel(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCsymtabEntryPut) (
                                 CSCsymTableType   const symTab,
                                 CSCsymbolType*    const symbol
                                 )
   {
   int               putStat = CSC_OK;
   CSCsymbolType*    newSym;
   CSChashKeyUnion   hashKey;

   ASSERT_RTN (symTab != NULL, "CSCsymtabEntryPut: null symTab", CSC_BADARG);
   ASSERT_RTN (symbol != NULL, "CSCsymtabEntryPut: null symbol", CSC_BADARG);
   ASSERT_RTN (						\
              symTab->sig_lo == SYMTAB_SIG,		\
              "CSCsymtabEntryPut: symTab blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              symTab->sig_hi == SYMTAB_SIG,		\
              "CSCsymtabEntryPut: symTab blows",	\
              CSC_CORRUPT				\
              );

   newSym = CSCsymbolDup (symbol, symTab->memLst, 0);
   if (newSym != NULL)
      {

      MON_ENTER(symTab);

      hashKey.asciiz = newSym->name;
      putStat = CSChashEntryPut (
                                symTab->table,
                                &hashKey,
                                &newSym,
                                sizeof(CSCsymbolType*)
                                );
      ASSERT ((putStat == CSC_OK) || (putStat == CSC_DUPKEY));
      if (putStat == CSC_OK) symTab->count += 1;

      MON_EXIT(symTab);

      }

   return (putStat);
   }


/**************************************************************************
 * Public Function CSCsymtabEntryGet
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabEntryGet">

NAME
        CSCsymtabEntryGet - get a symbol in a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        CSCsymbolType*   CSCsymtabEntryGet (
                                           CSCsymTableType   const symTab,
                                           char*             const symName,
                                           CSCmemListType    const memLst
                                           );

RETURN VALUE
        CSCsymtabEntryGet(), if successful, returns a pointer to a
        CSCsymbolType, or NULL if otherwise unsuccessful.

DESCRIPTION
        CSCsymtabEntryGet() returns a pointer to a duplicate symbol from
        `symTab' whose name field matches `symName'.

        If `memLst' is not NULL the duplicated symbol is dynamically allocated
        with CSCmemDup(), and should be removed with CSCmemFree() (with
        "tagData" of zero) to avoid leaking memory.

        If `memLst' is NULL the duplicated symbol is dynamically allocated with
        malloc() and should be removed with free() to avoid leaking memory.

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabDel(3)
        CSCsymtabStat(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryDel(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC CSCsymbolType*   (CSCsymtabEntryGet) (
                                            CSCsymTableType   const symTab,
                                            char*             const symName,
                                            CSCmemListType    const memLst
                                            )
   {
   CSCsymbolType*    symPtr = NULL;
   CSChashKeyUnion   hashKey;
   int               getStat;
   size_t            entrySize;

   ASSERT_RTN (symTab != NULL,  "CSCsymtabEntryGet: null symTab",  NULL);
   ASSERT_RTN (symName != NULL, "CSCsymtabEntryGet: null symName", NULL);
   ASSERT_RTN (						\
              symTab->sig_lo == SYMTAB_SIG,		\
              "CSCsymtabEntryGet: symTab blows",	\
              NULL					\
              );
   ASSERT_RTN (						\
              symTab->sig_hi == SYMTAB_SIG,		\
              "CSCsymtabEntryGet: symTab blows",	\
              NULL					\
              );

   MON_ENTER(symTab);

   hashKey.asciiz = (char*)symName;
   getStat = CSChashEntryGet (
                             symTab->table,
                             &hashKey,
                             (void**)&symPtr,
                             &entrySize,
                             memLst
                             );
   ASSERT ((getStat == CSC_OK) || (getStat == CSC_NOTFOUND));
   ASSERT (entrySize == sizeof(CSCsymbolType*));

   MON_EXIT(symTab);

   return (symPtr);
   }


/**************************************************************************
 * Public Function CSCsymtabEntryDel
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabEntryDel">

NAME
        CSCsymtabEntryDel - remove a symbol from a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        int   CSCsymtabEntryDel (
                                CSCsymTableType   const symTab,
                                char*             const symName
                                );

RETURN VALUE
        CSCsymtabEntryDel(), if successful, returns CSC_OK; otherwise,
        CSC_NOTFOUND, CSC_BADARG, and CSC_CORRUPT can be returned corresponding
        to NULL pointers, bad function arguments, and internal data errors,
        respectively.

DESCRIPTION
        CSCsymtabEntryDel() removes the symbol entry specified by `symName'
        from `symTab'.  The symbol in `symTab' whose name field contains
        `symName' is removed.

BUGS
        Symbols not created by CSCsymbolFloatNew(), CSCsymbolIntNew(), and
        CSCsymbolPtrNew() may cause problems.  (The name and value.pointer data
        of the symbol should be dynamically allocated, and the valueFlag field
        needs to be set the way CSCsymbolFloatNew(), CSCsymbolIntNew(), and
        CSCsymbolPtrNew() set it.)

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabDel(3)
        CSCsymtabStat(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryNext(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCsymtabEntryDel) (
                                 CSCsymTableType   const symTab,
                                 char*             const symName
                                 )
   {
   int               delStat = CSC_OK;
   CSChashKeyUnion   hashKey;

   ASSERT_RTN (symTab != NULL,  "CSCsymtabEntryDel: null symTab",  CSC_BADARG);
   ASSERT_RTN (symName != NULL, "CSCsymtabEntryDel: null symName", CSC_BADARG);
   ASSERT_RTN (						\
              symTab->sig_lo == SYMTAB_SIG,		\
              "CSCsymtabEntryDel: symTab blows",	\
              CSC_CORRUPT				\
              );
   ASSERT_RTN (						\
              symTab->sig_hi == SYMTAB_SIG,		\
              "CSCsymtabEntryDel: symTab blows",	\
              CSC_CORRUPT				\
              );

   MON_ENTER(symTab);

   hashKey.asciiz = (char*)symName;
   delStat = CSChashEntryDel (symTab->table, &hashKey);
   ASSERT (delStat == CSC_OK);
   if (delStat == CSC_OK)
      {
      ASSERT(symTab->count>=1);
      symTab->count -= 1;
      }

   MON_EXIT(symTab);

   return (delStat);
   }


/**************************************************************************
 * Public Function CSCsymtabEntryNext
 **************************************************************************

<SUBROUTINE NAME="CSCsymtabEntryNext">

NAME
        CSCsymtabEntryNext - find next entry in a libcsc symbol table

SYNOPSYS
        #include "libcsc.h"

        void*   CSCsymtabEntryNext (
                                   CSCsymTableType   const symTab,
                                   void*             const lhPtr
                                   );

RETURN VALUE
        CSCsymtabEntryNext(), if successful, returns an opaque symbol table
        entry.  If not successful, CSCsymtabEntryNext() returns NULL.

DESCRIPTION
        CSCsymtabEntryNext() uses the libcsc symbol table specified by the
        opaque `symTab' and returns a pointer to the next consecutive entry
        following the entry pointed to by `lhPtr'.  This next consecutive entry
        is the entry physically following the entry pointed to by `lhPtr'.

        If `lhPtr' is NULL, then the first item in the table is returned.

        If `symTab' is a table with no entries, or there are no more entries
        following the entry pointed to by `lhPtr', then NULL is returned.

BUGS
        There is no legitimate way for client code to know what to do with the
        void pointer returned from this function.  The secret is the returned
        value is a CSChashEntryType with its dataPtr field being a pointer to
        the symbol, but that might (very much not likely) change.

SEE ALSO
        CSCsymtabNew(3)
        CSCsymtabDel(3)
        CSCsymtabStat(3)
        CSCsymtabEntryPut(3)
        CSCsymtabEntryGet(3)
        CSCsymtabEntryDel(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC void*   (CSCsymtabEntryNext) (
                                    CSCsymTableType   const symTab,
                                    void*             const lhPtr
                                    )
   {
   CSChashEntryType   nextHashEntry = NULL;

   ASSERT_RTN (symTab!=NULL, "CSCsymtabEntryNext: null symTab", NULL);
   ASSERT_RTN (						\
              symTab->sig_lo == SYMTAB_SIG,		\
              "CSCsymtabEntryNext: symTab blows",	\
              NULL					\
              );
   ASSERT_RTN (						\
              symTab->sig_hi == SYMTAB_SIG,		\
              "CSCsymtabEntryNext: symTab blows",	\
              NULL					\
              );

   MON_ENTER(symTab);

   nextHashEntry = (CSChashEntryType)lhPtr;
   nextHashEntry = CSChashEntryNext (symTab->table, nextHashEntry);

   MON_EXIT(symTab);

   return (nextHashEntry);
   }


/* End of the file. */
