/* *****************************************************************************

libcsc: Debug Header File

	----------------------------------------------------------------

Copyright (c) 2001, Douglas R. Jerome, Peoria, AZ USA

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

	$RCSfile: libcsc_debug.h,v $
	$Revision: 1.2 $
	$Date: 2002/05/04 04:50:19 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

	This is the libcsc debug header file. Read it carefully.

CHANGE LOG

	25jun01	drj	File generation.

***************************************************************************** */


/*
 * ABSTRACT
 *
 * This debug resource is a compile-time configuration. Manifest constant
 * macros (#define'd macros) are used to add debug instrumentation with
 * compile-time enabling/disabling via the manifest constant (#define'd)
 * word `DEBUG'.
 *
 * All of the libcsc assertion macros generate usefull function calls only when
 * the manifest constant `DEBUG' is defined. The Standard C manifest constant
 * `NDEBUG' is unused.
 *
 * The "secret" `x' assert functions are prototyped locally and no assumption
 * is made about having `NULL' or any other things from headers files (like
 * printf or stderr). Remember, we don't know, and can't assume, which headers
 * files have been included by the code that includes this header.
 *
 * This header file tries to be passive to form a good debug environment, and
 * therefore cannot include any header files.
 *
 * "Secret" `x' functions are used to do actual work (display of assertions,
 * invocation of debuggers, etc.). This is the ONLY non-passive thing we can
 * do, except possibly declare the manifest constant `ASSERT_FAIL' and define
 * the three assertion macros:
 *	1)	ASSERT
 *	2)	ASSERT_ERRNO
 *	3)	ASSERT_RTN
 *
 * This header file my be included in a source code file multiple times, each
 * time the manifest constant `DEBUG' may be define, or not. In this way,
 * limited parts of the including source code will have the actual debug
 * instrumentation (becuase re-including this header file with out having the
 * manifest constant `DEBUG' defined will redefine the assertion debug macros
 * to be empty). See this example description:
 *
 *	#undef     DEBUG
 *	#include   "libcsc_debug.h"
 *		^
 *		|
 *		|
 *	// In this area of the code the macros `ASSERT', `ASSERT_ERRNO', and
 *	// `ASSERT_RTN' all have no affect; they are not defined to generate any
 *	// error checking. This is because DEBUG is not #define'd.
 *		|
 *		|
 *		v
 *	#define    DEBUG
 *	#include   "libcsc_debug.h"
 *		^
 *		|
 *		|
 *	// In this area of the code the macros `ASSERT', `ASSERT_ERRNO', and
 *	// `ASSERT_RTN' all have debuging affects; they ARE defined to generate
 *	// error checking. This is because DEBUG is #define'd.
 *		|
 *		|
 *		v
 *	#undef     DEBUG
 *	#include   "libcsc_debug.h"
 *		^
 *		|
 *		|
 *	// In this area of the code the macros `ASSERT', `ASSERT_ERRNO', and
 *	// `ASSERT_RTN' all have have been turned off and have no affect; they
 *      // are no longer defined to generate any error checking. This is
 *      // because DEBUG is not #define'd.
 *		|
 *		|
 *		v
 */


#ifndef	__libcsc_debugh
#define	__libcsc_debugh
#endif


#ifdef	__cplusplus
extern	"C"	{
#endif


#ifdef	DEBUG


/* ************************************************************************* */
/*                                                                           */
/*      H A V E   D E B U G                                                  */
/*                                                                           */
/* ************************************************************************* */

/*
 * The libcsc version of `ASSERT' is parameterized by the `ASSERT_FAIL'
 * manifest constant. If `ASSERT_FAIL' is defined as a non-zero value, then
 * the secret assertion function `xcsc_assert_fail()' should call `abort()'
 * or some other debug function. If `ASSERT_FAIL' is defined as zero, then
 * the secret assertion function `xcsc_assert_fail()' should simply return.
 */

#undef	ASSERT
#define	ASSERT(exp)							\
	((void) ((exp) ? (void)0 :					\
	xcsc_assert_fail(__FILE__,__LINE__,#exp,(char*)0,ASSERT_FAIL)))

/*
 * The libcsc version of `ASSERT_ERRNO' is parameterized by the `ASSERT_FAIL'
 * manifest constant in the same way as the libcsc version of `ASSERT'.
 */
#define	ASSERT_ERRNO(exp)						\
	((void) (!(exp) ? (void)0 :					\
	xassert_errno(__FILE__,__LINE__,(exp),ASSERT_FAIL)))

/*
 * The `ASSERT_RTN' macro is parameterized by the `ASSERT_FAIL' manifest
 * constant in the same way as the libcsc version of `ASSERT'; however, it will
 * execute a return instruction if the assertion function `xcsc_assert_fail()'
 * returns, i.e. if `ASSERT_FAIL' is defined as zero. The `ASSERT_RTN' macro
 * also accepts a user-specified string which should be printed by the secret
 * assertion function `xcsc_assert_fail()'.
 */
#define	ASSERT_RTN(exp,str,ret)	\
	{if(!(exp))		\
	{xcsc_assert_fail(__FILE__,__LINE__,#exp,str,ASSERT_FAIL);return(ret);}}


/*
 * If not defined, define the manifest constant `ASSERT_FAIL' such that the
 * `x' assert "secret" functions harmlessly return.
 */
#ifndef	ASSERT_FAIL
#define	ASSERT_FAIL	(0)
#endif

/*
 * Here's a debug/trace print macro.
 ---------- REMOVED
#define	dprint(x)	cout << x;
#define	dtrace(x)	{cout << __FILE__ << "(" << __LINE__<< "): ";	\
			cout << x;}
 ---------- end of REMOVED
 */

/*
 Enable debug version of miscellaneous standard str and mem functions.
 */

#define  csc_memcpy(dst,src,size)   xcsc_memcpy(__FILE__,__LINE__,dst,src,size)
#define  csc_memmove(dst,src,size)  xcsc_memmove(__FILE__,__LINE__,dst,src,size)
#define  csc_memset(dst,c,size)     xcsc_memset(__FILE__,__LINE__,dst,c,size)
#define  csc_strcat(dst,src)        xcsc_strcat(__FILE__,__LINE__,dst,src)
#define  csc_strcmp(str1,str2)      xcsc_strcmp(__FILE__,__LINE__,str1,str2)
#define  csc_strncmp(str1,str2,n)   xcsc_strncmp(__FILE__,__LINE__,str1,str2,n)
#define  csc_strcpy(dst,src)        xcsc_strcpy(__FILE__,__LINE__,dst,src)
#define  csc_strncpy(dst,src,n)     xcsc_strncpy(__FILE__,__LINE__,dst,src,n)
#define  csc_strlen(ptr)            xcsc_strlen(__FILE__,__LINE__,ptr)
#define  csc_strrchr(ptr,c)         xcsc_strrchr(__FILE__,__LINE__,ptr,c)

extern void   xcsc_assert_fail  (
                                const char*          file_name,
                                      unsigned int   line_number,
                                const char*          assert_expression,
                                const char*          user_string,
                                      int            fail_flag
                                );

extern void   xcsc_assert_errno (
                                const char*          file_name,
                                      unsigned int   line_number,
                                               int   error_number,
                                               int   fail_flag
                                );

extern void*   xcsc_memcpy  (
                            const char*          file_name,
                                  unsigned int   line_number,
                                  void*          dst,
                            const void*          src,
                                  size_t         n
                            );

extern void*   xcsc_memset  (
                            const char*          file_name,
                                  unsigned int   line_number,
                                  void*          dst,
                                  int            c,
                                  size_t         n
                            );

extern char*   xcsc_strcat  (
                            const char*          file_name,
                                  unsigned int   line_number,
                                  char*          dst,
                            const char*          src
                            );

extern int     xcsc_strcmp  (
                            const char*          file_name,
                                  unsigned int   line_number,
                            const char*          str1,
                            const char*          str2
                            );

extern int     xcsc_strncmp  (
                             const char*          file_name,
                                   unsigned int   line_number,
                             const char*          str1,
                             const char*          str2,
                                   size_t         n
                             );

extern char*   xcsc_strcpy  (
                            const char*          file_name,
                                  unsigned int   line_number,
                                  char*          dst,
                            const char*          src
                            );

extern char*   xcsc_strncpy  (
                             const char*          file_name,
                                   unsigned int   line_number,
                                   char*          dst,
                             const char*          src,
                                   size_t         n
                             );

extern int     xcsc_strlen  (
                            const char*          file_name,
                                  unsigned int   line_number,
                            const char*          ptr
                            );

extern char*   xcsc_strrchr  (
                             const char*          file_name,
                                   unsigned int   line_number,
                             const char*          ptr,
                                   int            c
                             );


#else


/* ************************************************************************* */
/*                                                                           */
/*      N O   D E B U G                                                      */
/*                                                                           */
/* ************************************************************************* */

#undef	ASSERT
#undef	ASSERT_ERRNO
#undef	ASSERT_RTN

#define	ASSERT(expression)			((void)0)
#define	ASSERT_ERRNO(expresssion)		((void)0)
#define	ASSERT_RTN(expression,string,return)	((void)0)

#undef	ASSERT_FAIL

/*
 ---------- REMOVED
#define	dprint(x)	((void)0)
#define	dtrace(x)	((void)0)
 ---------- end of REMOVED
*/

#define	csc_memcpy	memcpy
#define	csc_memmove	memmove
#define	csc_memset	memset
#define	csc_strcat	strcat
#define	csc_strcmp	strcmp
#define	csc_strncmp	strncmp
#define	csc_strcpy	strcpy
#define	csc_strncpy	strncpy
#define	csc_strlen	strlen
#define	csc_strrchr	strrchr


/*
 * end of `#ifdef DEBUG'
 */
#endif


#ifdef	__cplusplus
}
#endif


#undef	__libcsc_debugh
