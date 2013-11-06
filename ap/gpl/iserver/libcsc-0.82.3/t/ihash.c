/*******************************************************************************

X-UIDL: 61064e07c8942a325fa988badcbf9ead
X-Mozilla-Status: 0011
X-Mozilla-Status2: 00000000
Received: from smtp02.roc.gblx.net (smtp02.roc.gblx.net [209.130.222.197])
	by smtp-local.globalcrossing.net (8.8.8a/8.8.8) with ESMTP id PAA109666
	for <jerome@smtp-local.globalcrossing.net>; Sun, 23 Feb 2003 15:32:15 -0500
Received: (from daemon@localhost)
	by smtp02.roc.gblx.net (8.9.3/8.9.3) id PAA92782
	for <jerome@globalcrossing.net>; Sun, 23 Feb 2003 15:32:15 -0500
Received: from hermes.epita.fr(163.5.255.10), claiming to be "epita.fr"
 via SMTP by smtp02.roc.gblx.net, id smtpdqr1CMa; Sun Feb 23 15:32:11 2003
Received: from pipe.epita.fr (pipe [10.42.22.42])
	by epita.fr id h1NKW0t08158 for <jerome@globalcrossing.net> 
	EPITA Paris France Sun, 23 Feb 2003 21:32:02 +0100 (MET)
To: jerome@globalcrossing.net
Subject: Re: Your hash lib
From: Manu <emmanuel.alliel@epitech.net>
Organization: arnac & Co
URL: http://www.windar.fr.st
Warning: PINE c'est mal (http://www.epita.fr:8000/~le-che_e/pine.html)
X-Face: AUbo[a?<7\Ee:1%wJy4.iO+Y;%K2'Q[t?LbFjLY^vmDe%pQdH/{mA%ZxLam&N~6a?#35+gf
 !{dm9Qf6UbZFr0,8w{7if~E__nBg!g^qW9V,+_kIRZqTj(K2$)C_)w[*c-ad1{k32#wqFE"{,gcNji
 BX
Date: Sun, 23 Feb 2003 21:32:01 +0100
In-Reply-To: <3E57B341.6010909@globalcrossing.net> (Douglas Jerome's message
 of "Sat, 22 Feb 2003 10:28:33 -0700")
Message-ID: <87ssmuerb5q.fsf@epitech.net>
User-Agent: Gnus/5.090016 (Oort Gnus v0.16) Emacs/21.2
References: <87sn0kpy83w.fsf@epitech.net>
	<3E564623.2060407@globalcrossing.net> <87sznopmx87.fsf@epitech.net>
	<3E57B341.6010909@globalcrossing.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
X-UIDL: 61064e07c8942a325fa988badcbf9ead

Hi,
for my school I have to do a project using hash tables. The goal is to
go as fast as posible. I tryed with your library, but it is slower
than using perl or the glib.
This is my code, maybe I am wrong somewhere:

The subject is to do a program that reads on the stdin a string. For
example if the string is:
test 42
the program put test and 42 on the hash table, and print:
test 42
and after if I print:
test ?
the program has to print:
test 42

-- 
Manu - alliel_e@epitech.net
uin 58000566
Tek 2

*******************************************************************************/


/* ************************************************************************* */
/*                                                                           */
/*      Included Files                                                       */
/*                                                                           */
/* ************************************************************************* */

#include	<stdio.h>
#include	<unistd.h>
#include	"libcsc.h"


/* ************************************************************************* */
/*                                                                           */
/*      Executable Code - MAIN                                               */
/*                                                                           */
/* ************************************************************************* */

int   main (void)
   {
   int                stat     = 0;
   char*              hashName = "Hash Table";
   CSCmemListType     memlist;
   CSCtimerType       timer;
   double             duration;
   CSChashTableType   hashTable;
   CSChashKeyUnion    key;
   char*              inbuf;
   char*              keyPtr;

   memlist = CSCmemInit ("mem list", NULL, NULL, NULL, CSC_NO_PROFILING);
   if (memlist == NULL)
      {
      (void)fprintf (stderr, "Can't create mem list.\n");
      (void)exit (1);
      }

   timer = CSCtimerInit();
   if (timer == NULL)
      {
      (void)fprintf (stderr, "Can't create new timer.\n");
      (void)exit (1);
      }

   (void)printf ("=> Creating empty hash table ... ");
   (void)fflush (stdout);
   (void)CSCtimerMark (timer);
   hashTable = CSChashNew (
                          /* table name       */ hashName,
                          /* key type         */ CSC_HASH_INT32_KEY,
                          /* table size       */ 0,
                          /* monitor function */ NULL,
                          /* monitor data     */ NULL,
                          /* profiling flag   */ CSC_NO_PROFILING
                          );
   (void)CSCtimerDiff (timer, &duration);
   (void)printf ("done. [%9.6f seconds]\n", duration);
   if (hashTable == NULL)
      {
      (void)fprintf (stderr, "Can't create new hash table \"%s\".\n", hashName);
      (void)exit (1);
      }

   while (CSCioReadLine(STDIN_FILENO,&inbuf,memlist,0) > 0)
      {
      keyPtr = strchr (inbuf, ' ');
      if (keyPtr != NULL)
         {
         *keyPtr++ = '\0';
         key.integer = (int32)atoi (keyPtr);
         if (inbuf[0] == '?')
            {
            char*    itemPtr;
            size_t   itemSize;
            (void)printf ("=> GET from the hash table ... ");
            (void)fflush (stdout);
            (void)CSCtimerMark (timer);
            stat = CSChashEntryGet (
                                   hashTable,
                                   &key,
                                   (void**)&itemPtr,
                                   &itemSize,
                                   NULL
                                   );
            (void)CSCtimerDiff (timer, &duration);
            (void)printf ("done. [%9.6f seconds]\n", duration);
            if (stat == 0)
               {
              (void)printf ("=> key,value = %d,\"%s\"\n", key.integer, itemPtr);
              (void)free (itemPtr);
               }
            else
               {
               (void)printf (
                          "=> No entry with key %d in hash table \"%s\": %s.\n",
                          key.integer,
                          hashName,
                          CSCstatStr(stat)
                            );
               }
            }
         else
            {
            (void)printf ("=> PUT from the hash table ... ");
            (void)fflush (stdout);
            (void)CSCtimerMark (timer);
            stat = CSChashEntryPut (hashTable, &key, inbuf, strlen(inbuf)+1);
            (void)CSCtimerDiff (timer, &duration);
            (void)printf ("done. [%9.6f seconds]\n", duration);
            if (stat != 0)
               {
               (void)fprintf (
                           stderr,
                           "Can't add entry \"%s\" to hash table \"%s\": %s.\n",
                           inbuf,
                           hashName,
                           CSCstatStr(stat)
                             );
               }
            }
         }
      else
         {
         (void)printf ("=> Bad input, try again.\n");
         }
      (void)CSCmemFree (memlist, (void**)&inbuf, 0);
      }

   /*
    * Remove the table.
    */
   (void)printf ("=> Deleting the hash table ... ");
   (void)fflush (stdout);
   (void)CSCtimerMark (timer);
   stat = CSChashDel (hashTable);
   (void)CSCtimerDiff (timer, &duration);
   (void)printf ("done. [%9.6f seconds]\n", duration);
   if (stat != 0)
      {
      (void)fprintf (
                    stderr,
                    "Can't delete hash table \"%s\": %s.\n",
                    hashName,
                    CSCstatStr(stat)
                    );
      }

   /*
    * All done.
    */
   (void)printf ("\nThanks for flying libcsc airlines.\n");
   exit (0);
   }


/* End of file. */
