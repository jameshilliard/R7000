/* *****************************************************************************

libcsc: BSD Network Socket Subsystem

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

	$RCSfile: csc_sock.c,v $
	$Revision: 1.5 $
	$Date: 2002/05/13 04:26:05 $

PROGRAM INFORMATION

	Developed by:	libcsc project
	Developer:	Douglas R. Jerome, drj, <jerome@primenet.com>

FILE DESCRIPTION

<SUBSYSTEM NAME="csc_sock">

NAME
	csc_sock

DESCRIPTION
	BSD Network Socket Subsystem

FUNCTIONS
	CSCsockConnectTCP - initiate a socket connection
	CSCsockConnectUDP - initiate a socket connection
	CSCsockPassiveTCP - listen for connections on a socket
	CSCsockPassiveUCP - listen for connections on a socket
</SUBSYSTEM>

CHANGE LOG

	12may02	drj	Small changes to support Solaris.

	02may02	drj	Small changes to support Solaris.

	21apr02	drj	Small comment changes.
			Readded support for VxWorks.

	11apr02	drj	Changed `CSCgenfnType' to `CSCgenFnType'.
			               --                --

	25jun01	drj	Converted to libcsc: renamed everything from rt to csc,
			removed some debug message printing code.

	11may00	drj	Free()'d the piePtr calloc()'d in the local
			getprotobyname().

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
#   define	_POSIX_C_SOURCE	199506L	/* posix.1 and posix.4 and MORE */
#else
#   define	_BSD_SOURCE	1	/* 4.3+bsd socket subsystem     */
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
#ifdef	__vxworks__
#   include	<vxWorks.h>
#endif
#ifdef	SOLARIS
#   include	<strings.h> /* for bzero, bcopy */
#endif

/*
 * Standard C (ANSI) Header Files
 */
#include	<errno.h>
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
#ifdef	__vxworks__
#   include	<inetLib.h>
#   include	<sockLib.h>
#else
#   include	<sys/socket.h>  /* for BSD socket functions */
#   include	<netinet/in.h>  /* for struct sockaddr_in   */
#   include	<netdb.h>
#endif

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

#ifndef	INADDR_NONE
#define	INADDR_NONE	(0xFFFFFFFF)
#endif

#ifndef	USHRT_MAX
#define	USHRT_MAX	(65535)
#endif

/*
 * This 4.3+bsd socket subsystem function is prototyped in arpa/in.h, but I
 * don't want to include such an old header file. This sort of usage is also
 * seen in Douglas E. Comer, David L. Stevens "Internetworking with TCP/IP
 * Vol. III", bsd socket version, (Englewood Cliffs: Prentice Hall, 1993).
 */
extern unsigned long   inet_addr (const char*);


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

#ifdef	__vxworks__
struct  protoent
   {
   char*    p_name;     /* official protocol name */
   char**   p_aliases;  /* alias list             */
   int      p_proto;    /* protocol number        */
   };
struct  servent
   {
   char*    s_name;     /* official service name */
   char**   s_aliases;  /* alias list            */
   int      s_port;     /* port number           */
   char*    s_proto;    /* protocol to use       */
   };
#endif


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

#ifdef	__vxworks__
PRIVATE char*   tcpName = "tcp";
PRIVATE char*   tcpAliases[] = { "TCP", "" };
PRIVATE char*   udpName = "udp";
PRIVATE char*   udpAliases[] = { "UDP", "" };
#endif


/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (Locally Used Functions)             */
/*                                                                           */
/* ************************************************************************* */


/**************************************************************************
 * Private Function Prototypes
 **************************************************************************/

#ifdef	__vxworks__
PRIVATE struct protoent*   getprotobyname (char* name);
PRIVATE struct servent*    getservbyname (char* name, char* proto);
#endif

PRIVATE int   connectSocket (
                                  int*           const sPtr,
                            const char*                host,
                            const char*                service,
                            const char*                protocol,
                                  CSCgenFnType         callbackFn
                            );

PRIVATE int    passiveSocket (
                                   int*           const sPtr,
                             const char*                service,
                             const char*                protocol,
                                   int                  backlog,
                                   CSCgenFnType         callbackFn
                             );


/* ---------------------------------------------------------------------- */


#ifdef	__vxworks__

/**************************************************************************
 * Private Function getprotobyname
 **************************************************************************/

PRIVATE struct protoent*   getprotobyname (char* name)
   {
   struct protoent*   retPtr = NULL;

   retPtr = calloc (1, sizeof(struct protoent));
   if (strcmp(name,"tcp") == 0) /* transmission control protocol */
      {
      retPtr->p_name    = tcpName;
      retPtr->p_aliases = tcpAliases;
      retPtr->p_proto   = 6;
      }
   if (strcmp(name,"ucp") == 0) /* user datagram protocol */
      {
      retPtr->p_name    = udpName;
      retPtr->p_aliases = udpAliases;
      retPtr->p_proto   = 17;
      }

   return (retPtr);
   }


/**************************************************************************
 * Private Function getservbyname
 **************************************************************************/

PRIVATE struct servent*   getservbyname (char* name, char* proto)
   {
   struct servent*   retPtr = NULL;

/*
 * These assignments avoid compiler warnings about unused things.
 */
   name  = name;
   proto = proto;

   return (retPtr);
   }

#endif


/**************************************************************************
 * Private Function connectSocket
 **************************************************************************/

PRIVATE int   connectSocket (
                                  int*           const sPtr,
                            const char*                host,
                            const char*                service,
                            const char*                protocol,
                                  CSCgenFnType         callbackFn
                            )
   {
   struct sockaddr_in   sin;      /* Internet Endpoint Address           */
#ifndef	__vxworks__
   struct hostent*      hiePtr;   /* Host Name Information Entry Pointer */
#endif
   struct servent*      siePtr;   /* Service Information Entry Pointer   */
   struct protoent*     piePtr;   /* Protocol Information Entry Pointer  */
          int           sFd;      /* Socket Descriptor                   */
          int           sType;    /* Socket Descriptor Type              */
          int           sSize;    /* Socket Descriptor Size              */
          int           port;     /* Temporary Port Number               */
          int           myErrNo;  /* Temporary errno                     */
          char          errBuf[80];

   ASSERT_RTN (sPtr != NULL,     "connectSocket: NULL sPtr",     CSC_BADARG);
   ASSERT_RTN (host != NULL,     "connectSocket: NULL host",     CSC_BADARG);
   ASSERT_RTN (service != NULL,  "connectSocket: NULL service",  CSC_BADARG);
   ASSERT_RTN (protocol != NULL, "connectSocket: NULL protocol", CSC_BADARG);

   /*
    * Assume failure.
    */
   *sPtr = -1;

   /*
    * Clear the IP address endpoint structure then set it (correctly) with an
    * Internet Address Family.
    */
   bzero ((char *)&sin, sizeof(struct sockaddr_in));
   sin.sin_family = AF_INET;

   /*
    * Use the host as a name to get the host's IP address; if this fails, then
    * assume the host is an ASCII-Z string of the host IP address itself.
    */
#ifndef	__vxworks__
   if ((hiePtr=gethostbyname(host)) != NULL)
      bcopy (hiePtr->h_addr, (char*)&sin.sin_addr, hiePtr->h_length);
   else
#endif
      {
      sin.sin_addr.s_addr = inet_addr (host);
      if (sin.sin_addr.s_addr == INADDR_NONE)
         {
         myErrNo = errno;
         sprintf (errBuf, "can't get %s host entry (errno %d)", host, myErrNo);
         if (callbackFn != NULL) (*callbackFn) (CSC_NOSOCK, myErrNo, errBuf);
         return (CSC_NOTFOUND);
         }
      }

   /*
    * Use the service as a name to get the port number; if this fails, then
    * assume the service is an ASCII-Z string of the port number itself.
    */
   if ((siePtr=getservbyname((char*)service,(char*)protocol)) != NULL)
      sin.sin_port = siePtr->s_port;  /* This already is in host format. */
   else
      {
      port = atoi (service);
      if (port > USHRT_MAX)
         {
         sprintf (
                 errBuf,
                 "using service entry %s as port number; it is too big",
                 service
                 );
         if (callbackFn != NULL) (*callbackFn) (CSC_NOSVC, CSC_ERROR, errBuf);
         return (CSC_NOSVC);
         }
      if (port != 0)
         sin.sin_port = htons (port);
      else
         {
         sprintf (errBuf, "can't make sense of service entry %s", service);
         if (callbackFn != NULL)
            (*callbackFn) (CSC_NOSVC, CSC_ERROR, errBuf);
         return (CSC_NOSVC);
         }
      }

   /*
    * Map the protocol name to its protocol number.
    */
   if ((piePtr=getprotobyname((char*)protocol)) == 0)
      {
      sprintf (errBuf, "can't make sense of protocol entry %s", protocol);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOPROT, CSC_ERROR, errBuf);
#ifdef	__vxworks__
      (void)free (piePtr); /* it was calloc()'d in the local getprotobyname() */
#endif
      return (CSC_NOPROT);
      }

   /*
    * Use protocol to choose a socket type. NOTE: if protocol is not correct,
    * then the code above would have returned false from this function.
    */
   sType = SOCK_STREAM;
   if (strcmp(protocol,"udp")==0) sType = SOCK_DGRAM;

   /*
    * Allocate a socket. Notice the correct use of PF_INET (Protocol Family:
    * InterNET).
    */
   sFd = socket (PF_INET, sType, piePtr->p_proto);
#ifdef	__vxworks__
   (void)free (piePtr); /* it was calloc()'d in the local getprotobyname() */
#endif
   if (sFd < 0)
      {
      myErrNo = errno;
      sprintf (errBuf, "can't create socket (errno %d)", myErrNo);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOSOCK, myErrNo, errBuf);
      return (CSC_NOSOCK);
      }

   /*
    * bind() is not required: the port number on this machine, through
    * which the connection is made, is dynamically allocated by the
    * operating system's BSD network socket subsystem.
    */

   /*
    * Make the connection
    */
   sSize = sizeof (struct sockaddr_in);
   if (connect(sFd,(struct sockaddr*)&sin,sSize) < 0)
      {
      myErrNo = errno;
      sprintf (errBuf, "can't make connection (errno %d)", myErrNo);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOSOCK, myErrNo, errBuf);
      return (CSC_NOSOCK);
      }

   /*
    * Return OK
    */
   *sPtr = sFd;
   return (CSC_OK);
   }


/**************************************************************************
 * Private Function passiveSocket
 **************************************************************************/

PRIVATE int   passiveSocket (
                                  int*           const sPtr,
                            const char*                service,
                            const char*                protocol,
                                  int                  backlog,
                                  CSCgenFnType         callbackFn
                            )
   {
   struct sockaddr_in   sin;     /* Internet Endpoint Address          */
   struct protoent*     piePtr;  /* Protocol Information Entry Pointer */
   struct servent*      siePtr;  /* Service Information Entry Pointer  */
          int           sFd;     /* Socket Descriptor                  */
          int           sType;   /* Socket Descriptor Type             */
          int           sSize;   /* Socket Descriptor Size             */
          int           port;    /* Temporary Port Number              */
          int           myErrNo;
          char          errBuf[80];

   ASSERT_RTN (sPtr != NULL,     "passiveSocket: NULL sPtr",     CSC_BADARG);
   ASSERT_RTN (service != NULL,  "passiveSocket: NULL service",  CSC_BADARG);
   ASSERT_RTN (protocol != NULL, "passiveSocket: NULL protocol", CSC_BADARG);
   ASSERT_RTN (backlog != 0,     "passiveSocket: no backlog",    CSC_BADARG);

   /*
    * Assume failure.
    */
   *sPtr = -1;

   /*
    * Clear the IP address endpoint structure, then set it with an Internet
    * Address Family and set it to accept a connection from any IP. Notice the
    * correct use of AF_INET (Address Family: InterNET).
    */
   bzero ((char *)&sin, sizeof(struct sockaddr_in));
   sin.sin_family      = AF_INET;
   sin.sin_addr.s_addr = htonl (INADDR_ANY);

   /*
    * Use the service as a name to get the port number; if this fails, then
    * assume the service is an ASCII-Z string of the port number itself.
    */
   if ((siePtr=getservbyname((char*)service,(char*)protocol)) != NULL)
      sin.sin_port = siePtr->s_port; /* This already is in host format. */
   else
      {
      port = atoi (service);
      if (port > USHRT_MAX)
         {
         sprintf (
                 errBuf,
                 "using service entry %s as port number; it is too big",
                 service
                 );
         if (callbackFn != NULL) (*callbackFn) (CSC_NOSVC, CSC_ERROR, errBuf);
         return (CSC_NOSVC);
         }
      if ((sin.sin_port=htons(port)) == 0)
         {
         sprintf (errBuf, "can't make sense of service entry %s", service);
         if (callbackFn != NULL) (*callbackFn) (CSC_NOSVC, CSC_ERROR, errBuf);
         return (CSC_NOSVC);
         }
      }
   port = sin.sin_port;

   /*
    * Map the protocol name to its protocol number.
    */
   if ((piePtr=getprotobyname((char*)protocol)) == 0)
      {
      sprintf (errBuf, "can't make sense of protocol entry %s", protocol);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOPROT, CSC_ERROR, errBuf);
      return (CSC_NOPROT);
      }

   /*
    * Use protocol to choose a socket type. NOTE: if protocol is not correct,
    * then the code above would have returned false from this function.
    */
   sType = SOCK_STREAM;
   if (strcmp(protocol,"udp")==0) sType = SOCK_DGRAM;

   /*
    * Allocate a socket. Notice the correct use of PF_INET (Protocol Family:
    * InterNET).
    */
   sFd = socket (PF_INET, sType, piePtr->p_proto);
   if (sFd < 0)
      {
      myErrNo = errno;
      sprintf (errBuf, "can't create socket (errno %d)", myErrNo);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOSOCK, myErrNo, errBuf);
      return (CSC_NOSOCK);
      }

   /*
    * Allow this server to be quickly brought back up. The socket is set to be
    * able to reuse the same port; otherwise, the TIME_WAIT phenomenon will
    * prevent binding to the local address.
    *
    * This is particularly useful when the server has been shut down and then
    * quickly restarted (while the sockets are still active on its port).
    * Unexpected data may come in and it may confuse the server; but while this
    * is possible, it is very not likely:
    *
    *      "A socket is a 5-tuple (protocol, local address, local port,
    *      remote address, remote port). SO_REUSEADDR just says that
    *      you can reuse local addresses. The 5-tuple still must be
    *      unique!"  -- Michael Hunter (mphunter@qnx.com)
    *
    * This is why it is very unlikely that unexpected data will ever be seen by
    * the server. The danger is that such a 5-tuple is still floating around on
    * the network, and while it is bouncing around a new connection from the
    * same client (on the same system) happens to get the same remote port.
    *
    * Thanks to Vic Metcalfe (vic@acm.org) et. al. Most of this data in this
    * comment block came from his FAQ:
    * ``Programming UNIX Sockets in C - Frequently Asked Questions''
    * dated March 28, 1998. The FAQ was found at
    * http://www.ibrado.com/sock-faq/
    */
   {
   int   on = 1;
   if (setsockopt(sFd,SOL_SOCKET,SO_REUSEADDR,(char*)&on,sizeof(on)) < 0)
      {
      myErrNo = errno;
      sprintf (errBuf, "can't set SO_REUSEADDR on socket (errno %d)", myErrNo);
      if (callbackFn != NULL) (*callbackFn) (CSC_NOSOCK, myErrNo, errBuf);
      return (CSC_NOSOCK);
      }
   }

   /*
    * Bind the socket.
    */
   sSize = sizeof (struct sockaddr_in);
   if (bind(sFd,(struct sockaddr*)&sin,sSize) < 0)
      {
      myErrNo = errno;
      sprintf (
              errBuf,
              "can't bind service %s to port %d (errno %d)",
              service, port, myErrNo
              );
      if (callbackFn != NULL) (*callbackFn) (CSC_NOBIND, myErrNo, errBuf);
      return (CSC_NOBIND);
      }

   /*
    * Listen for something on the port. I've found out that a client's
    * connect() can succeed at this point (before the server's accept())!
    */
   if (sType == SOCK_STREAM)
      if (listen(sFd,backlog) < 0)
         {
         myErrNo = errno;
         sprintf (
                 errBuf,
                 "can't listen on service %s port %d (errno %d)",
                 service, port, myErrNo
                 );
         if (callbackFn != NULL) (*callbackFn) (CSC_NOLISTEN, myErrNo, errBuf);
         return (CSC_NOLISTEN);
         }

   /*
    * Return OK
    */
   *sPtr = sFd;
   return (CSC_OK);
   }



/* ************************************************************************* */
/*                                                                           */
/*      E x e c u t a b l e   C o d e   (External Interface Functions)       */
/*                                                                           */
/* ************************************************************************* */


/***************************************************************************
 * Public Function CSCsockConnectTCP
 ***************************************************************************

<SUBROUTINE NAME="CSCsockConnectUDP">

NAME
        CSCsockConnectTCP - initiate a socket connection

SYNOPSYS
        #include "libcsc.h"

        int   CSCsockConnectTCP (
                                      int*           const socketPtr,
                                const char*                host,
                                const char*                service,
                                      CSCgenFnType         errorCallback
                                );

RETURN VALUE
        CSC_OK .......... successful, and the integer pointed to by socketPtr
                          will be updated with the new socket descriptor

        CSC_NOTFOUND .... can't make sense of host

        CSC_NOSVC ....... can't make sense of service

        CSC_NOPROT ...... can't make any sense out of the UDP protocol

        CSC_NOSOCK ...... can't allocate a new socket or can't set a socket
                          option

        CSC_BADARG ...... socketPtr or service is NULL or connectCount is zero

DESCRIPTION
        CSCsockConnectTCP() attempts to create a PF_INET (IPv4) protocol
        socket and make a TCP (SOCK_STREAM) connection to another socket.

        The other socket to which to connect is expected to be on `host' and
        `service', where `host' is the hostname or IP address, and `service' is
        the service or port number. If `service' specifies port number, then the
        integer value must fit in an unsigned 16 bit variable
        (0 <= sevice <= 65535). For example:

                host            service
                ----            -------
                "batman"        "telnet"
                "spidergirl"    "5200"
                "198.168.0.2"   "finger"
                "198.168.0.2"   "5200"

        Error conditions are announced via `errorCallback', if it is not NULL.
        The `errorCallback' function is called with the CSCsockConnectTCP()
        return value, errno, and a string describing the error e.g.,

                (*errorCallback) (CSC_NOSOCK, errno, "can't create socket");

SEE ALSO
        CSCsockConnectUDP(3)
        CSCsockPassiveTCP(3)
        CSCsockPassiveUDP(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsockConnectTCP) (
                                       int*           const socketPtr,
                                 const char*                host,
                                 const char*                service,
                                       CSCgenFnType         errorCallback
                                 )
   {
   ASSERT_RTN (						\
              socketPtr != NULL,			\
              "CSCsockPassiveTCP: NULL socketPtr",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              host != NULL,				\
              "CSCsockPassiveTCP: NULL host",		\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              service != NULL,			\
              "CSCsockPassiveTCP: NULL service",	\
              CSC_BADARG				\
              );
   return (connectSocket(socketPtr,host,service,"tcp",errorCallback));
   }

/***************************************************************************
 * Public Function CSCsockConnectUDP
 ***************************************************************************

<SUBROUTINE NAME="CSCsockConnectUDP">

NAME
        CSCsockConnectUDP - initiate a socket connection

SYNOPSYS
        #include "libcsc.h"

        int   CSCsockConnectUDP (
                                      int*           const socketPtr,
                                const char*                host,
                                const char*                service,
                                      CSCgenFnType         errorCallback
                                );

RETURN VALUE
        CSC_OK .......... successful, and the integer pointed to by socketPtr
                          will be updated with the new socket descriptor

        CSC_NOTFOUND .... can't make sense of host

        CSC_NOSVC ....... can't make sense of service

        CSC_NOPROT ...... can't make any sense out of the UDP protocol

        CSC_NOSOCK ...... can't allocate a new socket or can't set a socket
                          option

        CSC_BADARG ...... socketPtr or service is NULL or connectCount is zero

DESCRIPTION
        CSCsockConnectUDP() attempts to create a PF_INET (IPv4) protocol
        socket and make a UDP (SOCK_DGRAM) connection to another socket.

        The other socket to which to connect is expected to be on `host' and
        `service', where `host' is the hostname or IP address, and `service' is
        the service or port number. If `service' specifies port number, then the
        integer value must fit in an unsigned 16 bit variable
        (0 <= sevice <= 65535). For example:

                host            service
                ----            -------
                "batman"        "telnet"
                "spidergirl"    "5200"
                "198.168.0.2"   "finger"
                "198.168.0.2"   "5200"

        Error conditions are announced via `errorCallback', if it is not NULL.
        The `errorCallback' function is called with the CSCsockConnectUDP()
        return value, errno, and a string describing the error e.g.,

                (*errorCallback) (CSC_NOSOCK, errno, "can't create socket");

BUGS
        There's no "connection" in UDP! CSCsockConnectUDP() probably shouldn't
        call connect() to make a connection.

SEE ALSO
        CSCsockConnectTCP(3)
        CSCsockPassiveTCP(3)
        CSCsockPassiveUDP(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsockConnectUDP) (
                                       int*           const socketPtr,
                                 const char*                host,
                                 const char*                service,
                                       CSCgenFnType         errorCallback
                                 )
   {
   ASSERT_RTN (						\
              socketPtr != NULL,			\
              "CSCsockPassiveUDP: NULL socketPtr",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              host != NULL,				\
              "CSCsockPassiveUDP: NULL host",		\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              service != NULL,				\
              "CSCsockPassiveUDP: NULL service",	\
              CSC_BADARG				\
              );
   return (connectSocket(socketPtr,host,service,"udp",errorCallback));
   }


/***************************************************************************
 * Public Function CSCsockPassiveTCP
 ***************************************************************************

<SUBROUTINE NAME="CSCsockPassiveTCP">

NAME
        CSCsockPassiveTCP - listen for connections on a socket

SYNOPSYS
        #include "libcsc.h"

        int   CSCsockPassiveTCP (
                                      int*           const socketPtr,
                                const char*                service,
                                      int                  connectCount,
                                      CSCgenFnType         errorCallback
                                );

RETURN VALUE
        CSC_OK .......... successful, and the integer pointed to by socketPtr
                          will be updated with the new socket descriptor

        CSC_NOSVC ....... can't make sense of service

        CSC_NOPROT ...... can't make any sense out of the UDP protocol

        CSC_NOSOCK ...... can't allocate a new socket or can't set a socket
                          option

        CSC_NOBIND ...... can't bind socket to service

        CSC_NOLISTEN .... can't listen to socket

        CSC_BADARG ...... socketPtr or service is NULL or connectCount is zero

DESCRIPTION
        CSCsockPassiveTCP() attempts to create a PF_INET (IPv4) protocol socket
        and prepares it to accept TCP (SOCK_STREAM) connections. No accept() is
        actually tried, this must be done after calling CSCsockPassiveTCP().

        If successful, CSCsockPassiveTCP() creates a socket that is prepared
        to accept a connection from any IP.

        The `service' argument is a string that represents the the service (see
        /etc/services) or port number. If `service' specifies port number, then
        the integer value must fit in an unsigned 16 bit variable
        (0 <= sevice <= 65535). For example:

                service
                -------
                "echo"
                "5200"
                "fsp"
                "7200"

        The socket is set with the SO_REUSEADDR option to enable quick reuse of
        the same port.

        `connectCount' is the connection backlog (the number of allowed
        concurrent connections).

        Error conditions are announced via `errorCallback', if it is not NULL.
        The `errorCallback' function is called with the CSCsockPassiveUDP()
        return value, errno, and a string describing the error e.g.,

                (*errorCallback) (CSC_NOSOCK, errno, "can't create socket");

BUGS
        Cannot select a desired host from which to accept a connection.

SEE ALSO
        CSCsockConnectTCP(3)
        CSCsockConnectUDP(3)
        CSCsockPassiveUDP(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsockPassiveTCP) (
                                       int*           const socketPtr,
                                 const char*                service,
                                       int                  connectCount,
                                       CSCgenFnType         errorCallback
                                 )
   {
   ASSERT_RTN (						\
              socketPtr != NULL,			\
              "CSCsockPassiveTCP: NULL socketPtr",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              service != NULL,				\
              "CSCsockPassiveTCP: NULL service",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              connectCount != 0,			\
              "CSCsockPassiveTCP: no connectCount",	\
              CSC_BADARG				\
              );
   return (passiveSocket(socketPtr,service,"tcp",connectCount,errorCallback));
   }


/***************************************************************************
 * Public Function CSCsockPassiveUDP
 ***************************************************************************

<SUBROUTINE NAME="CSCsockPassiveUDP">

NAME
        CSCsockPassiveUDP - listen for connections on a socket

SYNOPSYS
        #include "libcsc.h"

        int   CSCsockPassiveUDP (
                                      int*           const socketPtr,
                                const char*                service,
                                      int                  connectCount,
                                      CSCgenFnType         errorCallback
                                );

RETURN VALUE
        CSC_OK .......... successful, and the integer pointed to by socketPtr
                          will be updated with the new socket descriptor

        CSC_NOSVC ....... can't make sense of service

        CSC_NOPROT ...... can't make any sense out of the UDP protocol

        CSC_NOSOCK ...... can't allocate a new socket or can't set a socket
                          option

        CSC_NOBIND ...... can't bind socket to service

        CSC_NOLISTEN .... can't listen to socket

        CSC_BADARG ...... socketPtr or service is NULL or connectCount is zero

DESCRIPTION
        CSCsockPassiveUDP() attempts to create a PF_INET (IPv4) protocol socket
        and prepares it to accept UDP (SOCK_DGRAM) connections.

        If successful, CSCsockPassiveUDP() creates a socket that is prepared
        to accept a datagrams from any IP.

        The `service' argument is a string that represents the the service (see
        /etc/services) or port number. If `service' specifies port number, then
        the integer value must fit in an unsigned 16 bit variable
        (0 <= sevice <= 65535). For example:

                service
                -------
                "echo"
                "5200"
                "fsp"
                "7200"

        The socket is set with the SO_REUSEADDR option to enable quick reuse of
        the same port.

        `connectCount' is the connection backlog (the number of allowed
        concurrent connections).

        Error conditions are announced via `errorCallback', if it is not NULL.
        The `errorCallback' function is called with the CSCsockPassiveUDP()
        return value, errno, and a string describing the error e.g.,

                (*errorCallback) (CSC_NOSOCK, errno, "can't create socket");

BUGS
        There's no "connection" in UDP!  This function should be re-coded to
        remove the TCPisms. I think this function has never been used.

SEE ALSO
        CSCsockConnectTCP(3)
        CSCsockConnectUDP(3)
        CSCsockPassiveTCP(3)
</SUBROUTINE>

 ***************************************************************************/

PUBLIC int   (CSCsockPassiveUDP) (
                                       int*           const socketPtr,
                                 const char*                service,
                                       int                  connectCount,
                                       CSCgenFnType         errorCallback
                                 )
   {
   ASSERT_RTN (						\
              socketPtr != NULL,			\
              "CSCsockPassiveUDP: NULL socketPtr",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              service != NULL,				\
              "CSCsockPassiveUDP: NULL service",	\
              CSC_BADARG				\
              );
   ASSERT_RTN (						\
              connectCount != 0,			\
              "CSCsockPassiveUDP: no connectCount",	\
              CSC_BADARG				\
              );
   return (passiveSocket(socketPtr,service,"udp",connectCount,errorCallback));
   }


/* End of file. */
