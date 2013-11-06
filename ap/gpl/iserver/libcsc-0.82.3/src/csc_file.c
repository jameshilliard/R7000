/* *****************************************************************************

libcsc: File Subsystem

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

	$RCSfile: csc_file.c,v $
	$Revision: 1.3 $
	$Date: 2002/04/30 05:35:06 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_file">

NAME
	csc_file

DESCRIPTION
	File Subsystem

FUNCTIONS
	CSCfileReadLock       - read-lock a region in a file
	CSCfileWriteLock      - write-lock a region in a file
	CSCfileUnlock         - unlock a region in a file
	CSCfileGetHomeDir     - find home directory pathname
	CSCfileGetUserHomeDir - find home directory pathname of specific user
	CSCfileBaseName       - strip directory from pathname
	CSCfilePathName       - strip last component (file) from pathname
	CSCfileExpandPath     - expand ~ and environment variables in pathname
	CSCfileOpen           - create a file in a path that doesn't (yet) exist
</SUBSYSTEM>

CHANGE LOG

	20apr02	drj	Small comment changes.

	14apr02	drj	Removed erroneous comment.

	05jul01	drj	Converted to libcsc: renamed everything from rt to csc,
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
#include	<stddef.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

/*
 * Posix Header Files
 */
#include	<unistd.h>
#include	<fcntl.h>
#include	<pwd.h>
#include	<sys/stat.h>
#include	<sys/types.h>

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

PRIVATE int     csc_flock (int, int, int, off_t, int, off_t);
PRIVATE char*   getHomeDir (char* dstPtr, size_t pathMax);
PRIVATE char*   getUserHomeDir (char* dstPtr, char* userName, size_t pathMax);
PRIVATE char*   expandTilde (
                            const char*    dstPtr,
                                  char**   srcPtrPtr,
                            const size_t   pathMax
                            );

PRIVATE char*   expandEnv (
                          const char*    destBuff,
                                char**   srcPtrPtr,
                          const size_t   destBuffSize
                          );


/* ---------------------------------------------------------------------- */


/**************************************************************************
 * Private Function csc_flock
 **************************************************************************/

PRIVATE int   csc_flock (
                        int     fd,
                        int     cmd,
                        int     type,
                        off_t   offset,
                        int     whence,
                        off_t   len
                        )
   {
   struct flock   lock;

   lock.l_type   = type;   /* F_RDLCK, F_WRLCK, F_UNLCK                     */
   lock.l_start  = offset; /* This is the byte offset relative to l_whence. */
   lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END                  */
   lock.l_len    = len;    /* This is the number of bytes (0 means to EOF). */
   lock.l_pid    = 0;      /* This is returned for a an F_GETLK.            */

   return (fcntl(fd,cmd,&lock));
   }


/**************************************************************************
 * Private Function getHomeDir
 **************************************************************************

 Note:  dstPtr is incremented and ends up pointing to the next character
        position AFTER the last character moved into the destination
        (unless pathMax decrements to zero first).

 Bugs:  Is there a memory leak in here?  If the passwd struct is used, it
        is dynamically allocated (I think) by getpwuid. This structure
        contains character pointers to ASCII-Z strings; are these strings
        dynamically allocated?  If so, I need to free them before freeing
        the passwd structure. Read the man page for getpwuid to see what I
        am talking about.

 **************************************************************************/

PRIVATE char*   getHomeDir (
                           char*    dstPtr,
                           size_t   pathMax
                           )
   {
          char*     homeDir;
   struct passwd*   passwdEntry;

   ASSERT_RTN (dstPtr != NULL, "getHomeDir: no dstPtr",  NULL);
   ASSERT_RTN (pathMax > 0,    "getHomeDir: no pathMax", NULL);

   if ((dstPtr == NULL) || (pathMax == 0)) return (NULL);

   if ((homeDir=getenv("HOME")) != NULL)
      {
      while ((*homeDir != '\0') && (pathMax-- > 0)) *dstPtr++ = *homeDir++;
      /* Nothing dynamically allocated here; nothing to free. */
      }
   else
      {
      passwdEntry = getpwuid (getuid()); /* dynamically allocated? */
      if (passwdEntry != NULL)
         {
         homeDir = passwdEntry->pw_dir;
         while ((*homeDir != '\0') && (pathMax-- > 0)) *dstPtr++ = *homeDir++;
         /* Memory leak here?  Free the passwdEntry structure here? */
         }
      else
         {
         dstPtr = NULL;
         }
      }

   return (dstPtr);
   }


/**************************************************************************
 * Private Function getUserHomeDir
 **************************************************************************

 Note:  dstPtr is incremented and ends up pointing to the next character
        position AFTER the last character moved into the destination
        (unless pathMax decrements to zero first).

 Bugs:  Is there a memory leak in here?  If the passwd struct is used, it
        is dynamically allocated (I think) by getpwnam. This structure
        contains character pointers to ASCII-Z strings; are these strings
        dynamically allocated?  If so, I need to free them before freeing
        the passwd structure. Read the man page for getpwnam to see what I
        am talking about.

 **************************************************************************/

PRIVATE char*   getUserHomeDir (
                               char*    dstPtr,
                               char*    userName,
                               size_t   pathMax
                               )
   {
          char*     homeDir;
   struct passwd*   passwdEntry;

   ASSERT_RTN (dstPtr != NULL,   "getUserHomeDir: no dstPtr",   NULL);
   ASSERT_RTN (userName != NULL, "getUserHomeDir: no userName", NULL);
   ASSERT_RTN (pathMax > 0,      "getUserHomeDir: no pathMax",  NULL);

   if ((dstPtr == NULL) || (userName == NULL) || (pathMax == 0))
      {
      return (NULL);
      }

   passwdEntry = getpwnam (userName); /* dynamically allocated? */
   if (passwdEntry != NULL)
      {
      homeDir = passwdEntry->pw_dir;
      while ((*homeDir != '\0') && (pathMax-- > 0)) *dstPtr++ = *homeDir++;
      /* Memory leak here?  Free the passwdEntry structure here? */
      }
   else
      {
      dstPtr = NULL;
      }

   return (dstPtr);
   }


/**************************************************************************
 * Private Function expandTilde
 **************************************************************************

 This function will return NULL if the tilde thingy expansion fails, but
 *srcPtrPtr will be updated (unless destBuffSize decrements to zero first).

 Bugs:  If the tilde expansion is of the form `~username', then the
        username following the tilde must be no more than 79 characters.
        This is hard coded; see bug #1 below.

 **************************************************************************/

PRIVATE char*   expandTilde (
                            const char*    destBuff,
                                  char**   srcPtrPtr,
                            const size_t   destBuffSize
                            )
   {
   register char*   dstPtr = (char*)destBuff;
   register char*   srcPtr;

   ASSERT_RTN (destBuff != NULL,  "expandTilde: no destBuff",     NULL);
   ASSERT_RTN (srcPtrPtr != NULL, "expandTilde: no srcPtrPtr",    NULL);
   ASSERT_RTN (destBuffSize > 0,  "expandTilde: no destBuffSize", NULL);

   if ((destBuff == NULL) || (srcPtrPtr == NULL) || (destBuffSize == 0))
      {
      return (NULL);
      }

   srcPtr = *srcPtrPtr;

   ASSERT_RTN (srcPtr != NULL, "expandTilde: no srcPtr", NULL);

   if (srcPtr == NULL) return (NULL);

   if ((*srcPtr == '~') && (destBuffSize > 0))
      {

      ++srcPtr;
      if ((*srcPtr == '/') || (*srcPtr == '\0'))
         {
         /* expand `~' to this user's home directory. */
         dstPtr = getHomeDir (dstPtr, destBuffSize);
         }
      else
         {
         /* Buggy: we assume we have a username at srcPtr. */
         /* expand `~<username>' to some <username>'s home directory. */
                  int     index;
                  char*   userName;
         register char*   tmpDst;
         if ((userName=(char*)CSC_MALLOC_FUNC(1,80)) != NULL) /* bug #1 */
            {
            tmpDst = userName;
            index = 79;
            while ((*srcPtr != '/') && (*srcPtr != '\0') && (index-- > 0))
               {
               *tmpDst++ = *srcPtr++;
               }
            *tmpDst = '\0';
            dstPtr = getUserHomeDir (dstPtr, userName, destBuffSize);
            (void)CSC_FREE_FUNC (userName);
            }
         }

      }

   *srcPtrPtr = srcPtr;

   return (dstPtr);
   }


/**************************************************************************
 * Private Function expandEnv
 **************************************************************************

 Bugs:  The environment variable name must be no more than 79 characters.
        This is hard coded; see bug #1 below.

 **************************************************************************/

PRIVATE char*   expandEnv (
                          const char*    destBuff,
                                char**   srcPtrPtr,
                          const size_t   destBuffSize
                          )

   {
   register char*   dstPtr = (char*)destBuff;
   register char*   srcPtr;

   ASSERT_RTN (destBuff != NULL,  "expandEnv: no destBuff",     NULL);
   ASSERT_RTN (srcPtrPtr != NULL, "expandEnv: no srcPtrPtr",    NULL);
   ASSERT_RTN (destBuffSize > 0,  "expandEnv: no destBuffSize", NULL);

   if ((destBuff == NULL) || (srcPtrPtr == NULL) || (destBuffSize == 0))
      {
      return (NULL);
      }

   srcPtr = *srcPtrPtr;

   ASSERT_RTN (srcPtr != NULL, "expandEnv: no srcPtr", NULL);

   if (srcPtr == NULL) return (NULL);

   if ((*srcPtr == '$') && (destBuffSize > 0))
      {
               int     index;
               char*   envName;
               char*   envValue;
      register char*   tmpDst;

      if ((envName=(char*)CSC_MALLOC_FUNC(1,80)) != NULL) /* bug #1 */
         {
         tmpDst = envName;

         ++srcPtr;
         if ((*srcPtr == '(') || (*srcPtr == '{')) ++srcPtr;

         index = 79;
         while (
               (*srcPtr != ')') && (*srcPtr != '}') && (*srcPtr != '\0')
               &&
               (index-- > 0)
               )
            *tmpDst++ = *srcPtr++;
         *tmpDst = '\0';

         if ((*srcPtr == ')') || (*srcPtr == '}')) ++srcPtr;

         envValue = getenv (envName);

         ASSERT (envValue != NULL);
         ASSERT (envValue != NULL);

         if (envValue != NULL)
            {
            index = destBuffSize;
            while ((*envValue != '\0') && (index-- > 0))
               *dstPtr++ = *envValue++;

            (void)CSC_FREE_FUNC (envName);
            }
         }
      }

   *srcPtrPtr = srcPtr;

   return (dstPtr);
   }


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCfileReadLock
 ***************************************************************************

<SUBROUTINE NAME="CSCfileReadLock">

NAME
        CSCfileReadLock - read-lock a region in a file

SYNOPSYS
        #include "libcsc.h"

        int   CSCfileReadLock (
                              int     fd,
                              off_t   offset,
                              int     whence,
                              off_t   length
                              );

RETURN VALUE
        CSCfileReadLock() returns 0 if successful, otherwise -1 and errno will
        be set to indicate the error.

DESCRIPTION
        CSCfileReadLock() read locks a region of file associated with fd. The
        locked region in the file is at offset from beginning/end of the file
        depending upon the value of whence. The locked region is length bytes.

        whence usage is as follows:

        SEEK_SET
                The offset is set to offset bytes.

        SEEK_CUR
                The offset is set to its current location plus off-set bytes.

        SEEK_END
                The offset is set to the size of the file plus off-set bytes.

SEE ALSO
        CSCfileWriteLock(3)
        CSCfileUnlock(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCfileReadLock) (int fd, off_t offset, int whence, off_t length)
   {
   ASSERT_RTN (fd >= 0, "CSCfileReadLock: invalid file descriptor.\n", -1);
   ASSERT_RTN (								\
              ((whence==SEEK_SET)||(whence==SEEK_CUR)||(whence==SEEK_END)),\
              "CSCfileReadLock: invalid whence\n",			\
              -1							\
              );
   return (csc_flock(fd,F_SETLK,F_RDLCK,offset,whence,length));
   }


/**************************************************************************
 * Public Function CSCfileWriteLock
 **************************************************************************

<SUBROUTINE NAME="CSCfileWriteLock">

NAME
        CSCfileWriteLock - write-lock a region in a file

SYNOPSYS
        #include "libcsc.h"

        int   CSCfileWriteLock (
                               int     fd,
                               off_t   offset,
                               int     whence,
                               off_t   length
                               );

RETURN VALUE
        CSCfileWriteLock() returns 0 if successful, otherwise -1 and errno will
        be set to indicate the error.

DESCRIPTION
        CSCfileWriteLock() read locks a region of file associated with fd. The
        locked region in the file is at offset from beginning/end of the file
        depending upon the value of whence. The locked region is length bytes.

        whence usage is as follows:

        SEEK_SET
                The offset is set to offset bytes.

        SEEK_CUR
                The offset is set to its current location plus off-set bytes.

        SEEK_END
                The offset is set to the size of the file plus off-set bytes.

SEE ALSO
        CSCfileReadLock(3)
        CSCfileUnlock(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCfileWriteLock) (int fd, off_t offset, int whence, off_t length)
   {
   ASSERT_RTN (fd >= 0, "CSCfileWriteLock: invalid file descriptor.\n", -1);
   ASSERT_RTN (								\
              ((whence==SEEK_SET)||(whence==SEEK_CUR)||(whence==SEEK_END)),\
              "CSCfileWriteLock: invalid whence\n",			\
              -1							\
           );
   return (csc_flock(fd,F_SETLK,F_WRLCK,offset,whence,length));
   }


/**************************************************************************
 * Public Function CSCfileUnlock
 **************************************************************************

<SUBROUTINE NAME="CSCfileUnlock">

NAME
        CSCfileUnlock - unlock a region in a file

SYNOPSYS
        #include "libcsc.h"

        int CSCfileUnlock (
                          int     fd,
                          off_t   offset,
                          int     whence,
                          off_t   length
                          );

RETURN VALUE
        CSCfileUnlock() returns 0 if successful, otherwise -1 and errno will
        be set to indicate the error.

DESCRIPTION
        CSCfileUnlock() unlocks a region of file associated with fd. The
        unlocked region in the file is at offset from beginning/end of the
        file depending upon the value of whence. The unlocked region is
        length bytes.

        whence usage is as follows:

        SEEK_SET
                The offset is set to offset bytes.

        SEEK_CUR
                The offset is set to its current location plus off-set bytes.

        SEEK_END
                The offset is set to the size of the file plus off-set bytes.

SEE ALSO
        CSCfileReadLock(3)
        CSCfileWriteLock(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC int   (CSCfileUnlock) (int fd, off_t offset, int whence, off_t length)
   {
   ASSERT_RTN (fd >= 0, "CSCfileUnlock: invalid file descriptor.\n", -1);
   ASSERT_RTN (								\
              ((whence==SEEK_SET)||(whence==SEEK_CUR)||(whence==SEEK_END)),\
              "CSCfileUnlock: invalid whence\n",			\
              -1							\
              );
   return (csc_flock(fd,F_SETLK,F_UNLCK,offset,whence,length));
   }


/**************************************************************************
 * Public Function CSCfileGetHomeDir
 **************************************************************************

<SUBROUTINE NAME="CSCfileGetHomeDir">

NAME
        CSCfileGetHomeDir - find home directory pathname

SYNOPSYS
        #include "libcsc.h"

        char*   CSCfileGetHomeDir (
                                  const size_t                 pathSize,
                                        CSCmemListType   const memList,
                                        int                    memTag
                                  );

RETURN VALUE
        CSCfileGetHomeDir() returns a pointer to the home directory associated
        with the user ID of the process, if successful; otherwise, NULL is
        returned.

DESCRIPTION
        The returned home directory string should be a length less than or
        equal to `pathSize', including the terminating NULL character; if not,
        then an unterminated string containing `pathSize' characters is
        returned.

        If successful, CSCfileGetHomeDir() returns a pointer to a new string
        that is allocated by CSCmemAlloc(); the string must be freed with
        CSCmemFree() to avoid a memory leak.

SEE ALSO
        CSCfileGetUserHomeDir(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC char*   (CSCfileGetHomeDir) (
                                   const size_t                 pathSize,
                                         CSCmemListType   const memList,
                                         int                    memTag
                                   )
   {
   char*   homeDirPath = NULL;

   ASSERT_RTN (pathSize > 0,    "CSCfileGetHomeDir: no pathSize",  NULL);
   ASSERT_RTN (memList != NULL, "CSCfileGetHomeDir: NULL memList", NULL);

   if ((pathSize == 0) || (memList == NULL)) return (NULL);

   if (CSCmemAlloc(memList,(void**)&homeDirPath,1,pathSize,memTag) == CSC_OK)
      {
      homeDirPath = getHomeDir (homeDirPath, pathSize);
      }

   return (homeDirPath);
   }


/**************************************************************************
 * Public Function CSCfileGetUserHomeDir
 **************************************************************************

<SUBROUTINE NAME="CSCfileGetUserHomeDir">

NAME
        CSCfileGetUserHomeDir - find home directory pathname of specific user

SYNOPSYS
        #include "libcsc.h"

        char*   cscFileGetUserHomeDir (
                                       const char*            const userName,
                                       const size_t                 pathSize,
                                             CSCmemListType   const memList,
                                             int                    memTag
                                      );

RETURN VALUE
        CSCfileGetUserHomeDir() returns a pointer to the home directory
        associated with the specific user name userName, if successful;
        otherwise, NULL is returned.

DESCRIPTION
        The returned home directory string should be a length less than or
        equal to `pathSize', including the terminating NULL character; if not,
        then an unterminated string containing `pathSize' characters is
        returned.

        If successful, CSCfileGetUserHomeDir() returns a pointer to a new
        string that is allocated by CSCmemAlloc(); the string must be freed
        with CSCmemFree() to avoid a memory leak.

SEE ALSO
        CSCfileGetHomeDir(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC char*   (CSCfileGetUserHomeDir) (
                                       const char*            const userName,
                                       const size_t                 pathSize,
                                             CSCmemListType   const memList,
                                             int                    memTag
                                       )
   {
   char*   userDirPath = NULL;

   ASSERT_RTN (userName != NULL, "CSCfileGetUserHomeDir: no userName",  NULL);
   ASSERT_RTN (pathSize > 0,     "CSCfileGetUserHomeDir: no pathSize",  NULL);
   ASSERT_RTN (memList != NULL,  "cscFileGetUserHomeDir: NULL memList", NULL);

   if ((userName == NULL) || (pathSize == 0) || (memList == NULL))
      {
      return (NULL);
      }

   if (CSCmemAlloc(memList,(void**)&userDirPath,1,pathSize,memTag) == CSC_OK)
      {
      userDirPath = getUserHomeDir (userDirPath, (char*)userName, pathSize);
      }

   return (userDirPath);
   }


/**************************************************************************
 * Public Function CSCfileBaseName
 **************************************************************************

<SUBROUTINE NAME="CSCfileBaseName">

NAME
        CSCfileBaseName - strip directory from pathname

SYNOPSYS
        #include "libcsc.h"

        char*   CSCfileBaseName (
                                const char*            const path,
                                      CSCmemListType   const memList,
                                      int                    memTag
                                );

RETURN VALUE
        CSCfileBaseName() returns a pointer to a new string that begins with the
        first character in path after the last occurence of a '/' character.

        CSCfileBaseName() returns a pointer to path if the path string does not
        contain a '/' character.

        CSCfileBaseName() returns NULL if `path' or `memList' argument is NULL.

DESCRIPTION
        If CSCfileBaseName() is successful, it returns a pointer to a new string
        that is allocated by CSCmemAlloc(); the string must be freed with
        CSCmemFree() to avoid a memory leak.

SEE ALSO
        CSCfilePathName(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC char*   (CSCfileBaseName) (
                                 const char*            const path,
                                       CSCmemListType   const memList,
                                       int                    memTag
                                 )
   {
   char*   tempPtr = NULL;
   char*   namePtr = NULL;

   ASSERT_RTN (path != NULL,    "CSCfileBaseName: no path",      NULL);
   ASSERT_RTN (memList != NULL, "CSCfileBaseName: NULL memList", NULL);

   if ((path == NULL) || (memList == NULL)) return (NULL);

   tempPtr = strrchr (path, '/');
   if (tempPtr == NULL)
      tempPtr = (char*)path;
   else
      ++tempPtr;
   (void)CSCmemAlloc (memList,(void**)&namePtr,1,strlen(tempPtr)+1,memTag);
   if (namePtr != NULL) strcpy (namePtr, tempPtr);

   return (namePtr);
   }


/**************************************************************************
 * Public Function CSCfilePathName
 **************************************************************************

<SUBROUTINE NAME="CSCfilePathName">

NAME
        CSCfilePathName - strip last component (file) from pathname

SYNOPSYS
        #include "libcsc.h"

        char*   CSCfilePathName (
                                const char*            const path,
                                      CSCmemListType   const memList,
                                      int                    memTag
                                );

RETURN VALUE
        CSCfilePathName() returns a pointer to a new string that begins with
        the first character in path and terminates with the last character
        preceding the last '/' character.

        CSCfilePathName() returns NULL if it is not successful.

DESCRIPTION
        If CSCfilePathName() is successful, it returns a pointer to a new
        string that is allocated by CSCmemAlloc(); the string must be freed
        with CSCmemFree() to avoid a memory leak.

SEE ALSO
        CSCfileBaseName(3)
</SUBROUTINE>

 **************************************************************************/

PUBLIC char*   (CSCfilePathName) (
                                 const char*            const path,
                                       CSCmemListType   const memList,
                                       int                    memTag
                                 )
   {
   char*    tempPtr = NULL;
   char*    tailPtr = NULL;
   char*    namePtr = NULL;
   size_t   strSz   = 0;

   ASSERT_RTN (path != NULL,    "CSCfilePathName: no path",      NULL);
   ASSERT_RTN (memList != NULL, "CSCfilePathName: NULL memList", NULL);

   if ((path == NULL) || (memList == NULL)) return (NULL);

   tempPtr = (char*)path;
   tailPtr = strrchr (tempPtr, '/');
   if (tailPtr != NULL)
      {
      strSz = (size_t)tailPtr - (size_t)tempPtr + 1;
      if (CSCmemAlloc(memList,(void**)&namePtr,1,strSz,memTag) == CSC_OK)
         {
         (void)memcpy (namePtr, tempPtr, strSz-1);
         namePtr[strSz-1] = '\0';
         }
      else
         {
         namePtr = NULL;
         }
      }

   return (namePtr);
   }


/**************************************************************************
 * Public Function CSCfileExpandPath
 *************************************************************************

<SUBROUTINE NAME="CSCfileExpandPath">

NAME
        CSCfileExpandPath - expand ~ and environment variables in pathname

SYNOPSYS
        #include "libcsc.h"

        char*   cscFileExpandPath (
                                  const char*            const path,
                                  const size_t                 pathMax,
                                        CSCmemListType   const memList,
                                        int                    memTag
                                  );

RETURN VALUE
        CSCfileExpandPath() returns a pointer to a newly allocated string, if
        successful; otherwise, it returns NULL on failure.

DESCRIPTION
        CSCfileExpandPath() expands the `~' character and environment variables
        in the string in the path argument. The new expanded string must be a
        length less than or equal to pathMax, including the terminating NULL
        character.

        If successful, cscFileExpandPath() returns a pointer to a new string
        that is allocated by rtsMemAlloc(); the string must be freed with
        CSCmemFree() to avoid a memory leak.

SEE ALSO
</SUBROUTINE>

 **************************************************************************

 Note:  There is some pointer arithemtic below (see lines with `Note #1'
        comments); this ought to work for all Standard C (ANSI) compilers
        particularly if the ptrdiff_t assertion is OK. Remember to always
        group pointer arithematic operations:
                (int + ptr) - ptr != int + (ptr - ptr)

 **************************************************************************/

PUBLIC char*   (CSCfileExpandPath) (
                                   const char*            const path,
                                   const size_t                 pathMax,
                                         CSCmemListType   const memList,
                                         int                    memTag
                                   )
   {
   char*    dstPtr = NULL;
   char*    tmpPtr = NULL;
   char*    srcPtr = (char*)path;
   size_t   index;

   ASSERT_RTN (path != NULL,    "CSCfileExpandPath: NULL path",    NULL);
   ASSERT_RTN (pathMax > 0,     "CSCfileExpandPath: no pathMax",   NULL);
   ASSERT_RTN (memList != NULL, "CSCfileExpandPath: NULL memList", NULL);

   ASSERT (sizeof(ptrdiff_t) <= sizeof(size_t)); /* note #1 */

   if ((path == NULL) || (pathMax == 0) || (memList == NULL)) return (NULL);

   if (CSCmemAlloc(memList,(void**)&dstPtr,1,pathMax+1,memTag) == CSC_OK)
      {
      (void)memset (dstPtr, '\0', pathMax+1);

      tmpPtr = expandTilde (dstPtr, &srcPtr, pathMax);
      if (tmpPtr != NULL)
         index = (size_t)(tmpPtr - dstPtr); /* note #1 */
      else
         {
         index = (size_t)pathMax + 1;
         }

      while ((*srcPtr != '\0') && (index <= pathMax))
         {
         while ((*srcPtr != '$') && (*srcPtr != '\0') && (index++ <= pathMax))
            {
            *tmpPtr++ = *srcPtr++;
            }
         if (*srcPtr == '$')
            {
            tmpPtr = expandEnv (tmpPtr, &srcPtr, pathMax-index);
            index = (size_t)(tmpPtr - dstPtr); /* note #1 */
            }
         }
      *tmpPtr = '\0';

      if (*srcPtr != '\0')
         {
         (void)CSCmemFree (memList, (void**)&dstPtr, memTag);
         dstPtr = NULL;
         }
      }

   return (dstPtr);
   }


/**************************************************************************
 * Public Function CSCfileOpen
 **************************************************************************

<SUBROUTINE NAME="CSCfileOpen">

NAME
        CSCfileOpen - create a file in a path that doesn't (yet) exist

SYNOPSYS
        #include "libcsc.h"

        FILE*   CSCfileOpen (
                            const char*            const path,
                            const int                    mask,
                            const size_t                 pathMax,
                                  CSCmemListType   const memList,
                                  int                    memTag
                            );

RETURN VALUE
        CSCfileOpen() returns a new file, open for writing, if successful. On
        failure, CSCfileOpen() returns NULL.

DESCRIPTION
        CSCfileOpen() opens a new file for writing, creating the path if
        necessary.

SEE ALSO
</SUBROUTINE>

 **************************************************************************/

PUBLIC FILE*   (CSCfileOpen) (
                             const char*            const path,
                             const int                    mask,
                             const size_t                 pathMax,
                                   CSCmemListType   const memList,
                                   int                    memTag
                             )
   {
            FILE*   fileStream = NULL;
            int     oldMask;
            char*   fileName;
   register char*   tmpPtr;

   ASSERT_RTN (path != NULL,    "CSCfileOpen: NULL path",    NULL);
   ASSERT_RTN (pathMax > 0,     "CSCfileOpen: no pathMax",   NULL);
   ASSERT_RTN (memList != NULL, "CSCfileOpen: NULL memList", NULL);

   if ((path == NULL) || (pathMax == 0) || (memList == NULL)) return (NULL);

   fileName = CSCfileExpandPath (path, pathMax, memList, memTag);
   tmpPtr = *fileName == '/' ? fileName+1 : fileName;

   oldMask = umask (mask);

   while (*tmpPtr != '\0')
      {
      while ((*tmpPtr != '/') && (*tmpPtr != '\0')) ++tmpPtr;
      if (*tmpPtr == '/')
         {
         *tmpPtr = '\0';
         if (access(fileName,F_OK) == 0) /* There's something there... */
            {
            if (access(fileName,(R_OK)|(X_OK)) != 0) /* should be directory. */
               {
               (void)CSCmemFree (memList, (void**)&fileName, memTag);
               return (NULL);
               }
            }
         else
            {
            /* Nothing there; we must create the directory. */
            if (mkdir(fileName,0755) == 0)
               {
               (void)CSCmemFree (memList, (void**)&fileName, memTag);
               return (NULL);
               }
            }
         *tmpPtr++ = '/';
         }
      }

   /*
    * OK, we have a pathname to a file, the path part exists (we may have
    * created part of it) and it has the correct accessability. Now open the
    * file for writing.
    */
   fileStream = fopen (fileName,"w");
   (void)CSCmemFree (memList, (void**)&fileName, memTag);

   (void)umask (oldMask);

   return (fileStream);
   }


/* End of file. */
