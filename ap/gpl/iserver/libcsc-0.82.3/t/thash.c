/*******************************************************************************

X-UIDL: 05e1f19071d4f3deb319c22d3c73e486
X-Mozilla-Status: 0011
X-Mozilla-Status2: 00000000
Received: from smtp02.roc.gblx.net (smtp02.roc.gblx.net [209.130.222.197])
	by smtp-local.globalcrossing.net (8.8.8a/8.8.8) with ESMTP id LAA185352
	for <jerome@smtp-local.globalcrossing.net>; Fri, 21 Feb 2003 11:10:06 -0500
Received: (from daemon@localhost)
	by smtp02.roc.gblx.net (8.9.3/8.9.3) id LAA20400
	for <jerome@globalcrossing.net>; Fri, 21 Feb 2003 11:10:04 -0500
Received: from hermes.epita.fr(163.5.255.10), claiming to be "epita.fr"
 via SMTP by smtp02.roc.gblx.net, id smtpd3bWIia; Fri Feb 21 11:09:57 2003
Received: from orni.epita.fr (orni [10.42.23.21])
	by epita.fr id h1LG9jd18689
	Fri, 21 Feb 2003 17:09:46 +0100 (MET)
To: jerome@globalcrossing.net
Cc: Manu <emmanuel.alliel@epitech.net>
Subject: Re: Your hash lib
From: Manu <emmanuel.alliel@epitech.net>
Organization: arnac & Co
URL: http://www.windar.fr.st
Warning: PINE c'est mal (http://www.epita.fr:8000/~le-che_e/pine.html)
X-Face: AUbo[a?<7\Ee:1%wJy4.iO+Y;%K2'Q[t?LbFjLY^vmDe%pQdH/{mA%ZxLam&N~6a?#35+gf
 !{dm9Qf6UbZFr0,8w{7if~E__nBg!g^qW9V,+_kIRZqTj(K2$)C_)w[*c-ad1{k32#wqFE"{,gcNji
 BX
Date: Fri, 21 Feb 2003 17:09:44 +0100
In-Reply-To: <3E564623.2060407@globalcrossing.net> (Douglas Jerome's message
 of "Fri, 21 Feb 2003 08:30:43 -0700")
Message-ID: <87sznopmx87.fsf@epitech.net>
User-Agent: Gnus/5.090016 (Oort Gnus v0.16) Emacs/21.2
References: <87sn0kpy83w.fsf@epitech.net>
	<3E564623.2060407@globalcrossing.net>
MIME-Version: 1.0
Content-Type: text/plain; charset=iso-8859-1
Content-Transfer-Encoding: 8bit
X-MIME-Autoconverted: from quoted-printable to 8bit by smtp-local.globalcrossing.net id LAA185352
X-UIDL: 05e1f19071d4f3deb319c22d3c73e486

Ok Thank you, I have now downloaded libcsc-0.82.1.tar.gz
I just want a little sample code that just do:

- create a hash table
- put on the hash table a string key and a string values
- get the value if I give the key to the function
- print the value to the stdout

It is just for see how it's work.

Sorry for my english, I am french student.

Bye.

Vous disiez récemment :

> Manu wrote:
>> Hi, I am trying to use your lib for doing Hash Table, but it is very
>> difficult.
>> Can you send me a example of code using hash table please.
>> I have do that but I have a Segmentation Fault:
>> #include "rts.h"
>> int			main()
>> {
>>   rtsHashTableType	*hash_table;
>>   char			*namePtr;
>>   rtsHashKeyUnion	*test;
>>   char			**result;
>>   int			len;
>>   void			*myData1;
>>   size_t		*size;
>>     namePtr = (char *)strdup("hash_table");
>>   test = (rtsHashKeyUnion *)strdup("test");
>>   *hash_table = rtsHashNew(namePtr, RTS_HASH_ASCIIZ_KEY, 42);
>>   rtsHashEntryPut(*hash_table, test,(void *)strdup("data"), 4);
>>   rtsMemAlloc (&myData1, 1, 32, NULL);
>>   rtsHashEntryGet(*hash_table, test, myData1, size);
>> puts(myData1);
>>   rtsMemFree (&myData1, NULL);
>> }
>> Thank you very much.
>>
>
>
> This seems to be an old version of the library. Please
> go to http://www.sf.net/projects/hackerlabs and download
> the newest version of libcsc.
>
> I've a lot of work right now, but this weekend I will
> convert your example code to the new library's hash
> system and return that sample to you.
>
> I agree, it is very difficult to use.

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
/*      Executable Code                                                      */
/*                                                                           */
/* ************************************************************************* */

int   main()
   {
   int                stat      = 0;
   CSChashTableType   hashTable = NULL;
   char*              hashName  = "Hash Table";
   CSChashKeyUnion    key1;
   CSChashKeyUnion    key2;
   char*              entry1;
   char*              entry2;
   void*              itemPtr;
   size_t             itemSize;

   /*
    * Initialize some input data.
    */
   key1.asciiz = "key1";
   key2.asciiz = "key2";
   entry1      = "hash table item 1";
   entry2      = "hash table item 2";

   /*
    * - create a hash table
    *
    * Specifying 0 for the hash table size will create hash table that will
    * start small and grow as entries are added to it.
    *
    * This is not a threaded program, so there is no need for a monitor
    * function and data; otherwise, the monitor function should use a mutex
    * semaphore so that acces to the hash table would be one thread at a time.
    */
   (void)printf ("Creating a new hash table named \"%s\".\n", hashName);
   hashTable = CSChashNew (
                          /* table name       */ hashName,
                          /* key type         */ CSC_HASH_ASCIIZ_KEY,
                          /* table size       */ 20,
                          /* monitor function */ NULL,
                          /* monitor data     */ NULL,
                          /* profiling flag   */ CSC_DO_PROFILING
                          );
   if (hashTable == NULL)
      {
      (void)fprintf (stderr, "Can't create new hash table \"%s\".\n", hashName);
      (void)exit (1);
      }

   /*
    * Rene Reitinger reported a problem with malloc(800) after CSChashNew().
    * - fixed a problem, seems to work.
    */
   malloc (800);

   /*
    * - put on the hash table a string key and a string values
    *
    * Two entries are put into the hash table.
    */
   (void)printf ("Added entry with key \"%s\" to the hash table.\n", key1);
   stat = CSChashEntryPut (hashTable, &key1, entry1, strlen(entry1));
   if (stat != 0)
      {
      (void)fprintf (
                    stderr,
                    "Can't add entry \"%s\" to hash table \"%s\": %s.\n",
                    entry1,
                    hashName,
                    CSCstatStr(stat)
                    );
      (void)exit (1);
      }
   (void)printf ("Added entry with key \"%s\" to the hash table.\n", key2);
   stat = CSChashEntryPut (hashTable, &key2, entry2, strlen(entry2));
   if (stat != 0)
      {
      (void)fprintf (
                    stderr,
                    "Can't add entry \"%s\" to hash table \"%s\": %s.\n",
                    entry2,
                    hashName,
                    CSCstatStr(stat)
                    );
      (void)exit (1);
      }

   /*
    * - get the value if I give the key to the function
    *
    * If the item corresponding to the key is found in the table, then a copy
    * of the the data is allocated with CSCmemDup() ...
    *
    */
   (void)printf ("Finding entry with key \"%s\" to the hash table.\n", key1);
   stat = CSChashEntryGet (hashTable, &key1, &itemPtr, &itemSize, NULL);
   if (stat != 0)
      {
      (void)fprintf (
                    stderr,
                    "No entry with key \"%s\" in hash table \"%s\": %s.\n",
                    key1,
                    hashName,
                    CSCstatStr(stat)
                    );
      (void)exit (1);
      }

   /*
    * - print the value to the stdout
    */
   (void)printf (
                "Item with key \"%s\" has value \"%s\" in hash table \"%s\".\n",
                key1,
                itemPtr,
                hashName
                );
   (void)free (itemPtr);

   /*
    * Examine the hash table. It was created with profiling so there will be
    * some usage statistics (number of insertions, deletions, etc.).
    */
   {
   CSChashStatType   hashStat;
   (void)CSChashStat (hashTable, &hashStat);
   (void)printf ("\n");
   (void)printf ("table name ....... %s\n", hashStat.name);
   (void)printf (
                "profiling ........ %s\n",
                hashStat.profiling == CSC_DO_PROFILING ? "yes" : "no"
                );
   (void)printf ("table entries .... %d\n", hashStat.count);
   (void)printf ("hash locations ... %d\n", hashStat.nhash);
   (void)printf (
                "table grows ...... %s\n",
                hashStat.grows == CSC_TRUE ? "yes" : "no"
                );
   (void)printf ("resizes .......... %d\n", hashStat.resizes);
   (void)printf ("deletions ........ %d\n", hashStat.deletions);
   (void)printf ("insertions ....... %d\n", hashStat.insertions);
   (void)printf ("collisions ....... %d\n", hashStat.collisions);
   (void)printf ("\n");
   (void)CSChashWrite (STDOUT_FILENO, hashTable);
   (void)printf ("\n");
   }

   /*
    * Remove the table.
    */
   (void)printf ("Deleting the hash table.\n");
   stat = CSChashDel (hashTable);
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
