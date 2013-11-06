#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"libcsc.h"


static CSClistType         m_list    = NULL;
static const char*   const m_monData = "this is monitor data";


static int   monitor (CSCioSwitchType a_ioSwitch, void* a_monData)
   {
   (void)printf ("monitor [%s]", (char*)a_monData);
   switch (a_ioSwitch)
      {
      default:             (void)printf (" UNKNOWN ");  break;
      case CSC_IO_INPUT:   (void)printf (" IN ");       break;
      case CSC_IO_OUTPUT:  (void)printf (" OUT ");      break;
      case CSC_IO_NULL:    (void)printf (" NULL ");     break;
      }
   (void)printf ("\n");
   return (CSC_OK);
   }


int   main (void)
   {
   int      stat;
   void*    itemPtr;
   size_t   itemSz;

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("Create a list.\n");

   printf ("\n");
   printf ("1)\tCreating a new list.\n");
   printf ("  \tm_list = %p\n", m_list);
   printf ("  \tm_list = CSClistNew (\n");
   printf ("  \t                    \"my list\",\n");
   printf ("  \t                    monitor,\n");
   printf ("  \t                    m_monData,\n");
   printf ("  \t                    CSC_DO_PROFILING\n");
   printf ("  \t                    );\n");
   m_list = CSClistNew ("my list", monitor, m_monData, CSC_DO_PROFILING);
   printf ("  \tm_list = %p\n", m_list);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("2)\tPut an ASCII-Z string, include terminal \\0, into the list.\n");
   printf ("  \tstat = CSClistPush (\n");
   printf ("  \t                   m_list,\n");
   printf ("  \t                   CSC_DATA_NODUP,\n");
   printf ("  \t                   \"first data in\",\n");
   printf ("  \t                   strlen(\"first data in\")+1\n");
   printf ("  \t                   );\n");
   stat = CSClistPush (m_list, CSC_DATA_NODUP, "first data in", strlen("first data in")+1);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("3)\tPut another ASCII-Z string into the list.\n");
   printf ("  \tstat = CSClistPush (\n");
   printf ("  \t                   m_list,\n");
   printf ("  \t                   CSC_DATA_NODUP,\n");
   printf ("  \t                   \"second data in\",\n");
   printf ("  \t                   strlen(\"second data in\")+1\n");
   printf ("  \t                   );\n");
   stat = CSClistPush (m_list, CSC_DATA_NODUP, "second data in", strlen("second data in")+1);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("4)\tPut the last ASCII-Z string into the list, duping it.\n");
   printf ("  \tstat = CSClistPush (\n");
   printf ("  \t                   m_list,\n");
   printf ("  \t                   CSC_DATA_DUP,\n");
   printf ("  \t                   \"last data in\",\n");
   printf ("  \t                   strlen(\"last data in\")+1\n");
   printf ("  \t                   );\n");
   stat = CSClistPush (m_list, CSC_DATA_DUP, "last data in", strlen("last data in")+1);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("5)\tPeek at the head of the list.\n");
   printf ("  \tstat = CSClistPeek (\n");
   printf ("  \t                   m_list,\n");
   printf ("  \t                   CSC_LIST_HEAD,\n");
   printf ("  \t                   &itemPtr,\n");
   printf ("  \t                   &itemSz\n");
   printf ("  \t                   );\n");
   stat = CSClistPeek (m_list, CSC_LIST_HEAD, &itemPtr, &itemSz);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));
   printf ("  \t*itemPtr = \"%s\"\n", itemPtr);
   printf ("  \titemSz   = %d (includes terminal \\0)\n", itemSz);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("6)\tPeek at the tail of the list.\n");
   printf ("  \tstat = CSClistPeek (\n");
   printf ("  \t                   m_list,\n");
   printf ("  \t                   CSC_LIST_TAIL,\n");
   printf ("  \t                   &itemPtr,\n");
   printf ("  \t                   &itemSz\n");
   printf ("  \t                   );\n");
   stat = CSClistPeek (m_list, CSC_LIST_TAIL, &itemPtr, &itemSz);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));
   printf ("  \t*itemPtr = \"%s\"\n", itemPtr);
   printf ("  \titemSz   = %d (includes terminal \\0)\n", itemSz);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("7)\tIterate through the list with CSClistNodeNext() and get the\n");
   printf ("  \tdata from each node in the list with CSClistNodeStat().\n");
   {
   CSClistNodeType   node = NULL;
   int               i    = 1;
   while ((node=CSClistNodeNext(m_list,CSC_LIST_HEAD,node)) != NULL)
      {
      stat = CSClistNodeStat (node, &itemPtr, &itemSz);
      printf ("\t=>Item and size from node #%d\n", i++);
      printf ("\t\tstat = %d [%s]\n", stat, CSCstatStr(stat));
      printf ("\t\t*item = \"%s\"\n", itemPtr);
      printf ("\t\tsize  = %d (includes terminal \\0)\n", itemSz);
      }
   }

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("8)\tPop the head (newest) entry from the list.\n");
   printf ("  \tstat = CSClistPop (\n");
   printf ("  \t                  m_list,\n");
   printf ("  \t                  CSC_LIST_HEAD,\n");
   printf ("  \t                  &itemPtr,\n");
   printf ("  \t                  &itemSz\n");
   printf ("  \t                  );\n");
   stat = CSClistPop (m_list, CSC_LIST_HEAD, &itemPtr, &itemSz);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));
   printf ("  \t*itemPtr = \"%s\"\n", itemPtr);
   printf ("  \titemSz   = %d (includes terminal \\0)\n", itemSz);
   printf ("\n");
   printf ("  \tThe retreievd data must be free()ed because it was pushed\n");
   printf ("  \tinto the list with the push type CSC_DATA_DUP.\n");
   printf ("  \tfree (itemPtr);\n");
   free (itemPtr);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("9)\tIterate backward through the list with CSClistNodeNext()\n");
   printf ("  \tand get the data from each node with CSClistNodeStat().\n");
   {
   CSClistNodeType   node = NULL;
   int               i    = 1;
   while ((node=CSClistNodeNext(m_list,CSC_LIST_TAIL,node)) != NULL)
      {
      stat = CSClistNodeStat (node, &itemPtr, &itemSz);
      printf ("\t=>Item and size from node #%d\n", i++);
      printf ("\t\tstat = %d [%s]\n", stat, CSCstatStr(stat));
      printf ("\t\t*item = \"%s\"\n", itemPtr);
      printf ("\t\tsize  = %d (includes terminal \\0)\n", itemSz);
      }
   }

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("Program exit.\n");
   printf ("\n");
   exit (EXIT_SUCCESS);
   }
