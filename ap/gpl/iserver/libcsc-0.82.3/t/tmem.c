#include	<stdio.h>
#include	"libcsc.h"


static char*   mondata = "my monitor data";


static const char*   tagger (int tag)
   {
   if (tag == 1) return ("number one");
   if (tag == 2) return ("number two");
   if (tag == 3) return ("number three");
   if (tag == 4) return ("number four");
   if (tag == 5) return ("number five");
   if (tag == 6) return ("number six");
   if (tag == 7) return ("number seven");
   if (tag == 8) return ("number eight");
   if (tag == 9) return ("number nine");
   }


static int   monitor (CSCioSwitchType ioswitch, void* myData)
   {
   if (myData != NULL)
      {
      printf ("monitor: switch %d, data \"%s\"\n", ioswitch, myData);
      }
   }


static void   pusage (void)
   {
   fprintf (stderr, "Usage: tmem  [--metrics]\n");
   }


static void   test (void)
   {
   int              stat;
   CSCmemListType   memlist;
   void*            data;

   printf ("\n========================================\n");
   printf ("Create a memlist\n");
   printf ("\n");
   printf ("memlist = CSCmemInit (\"my mem list\", NULL, NULL, NULL, CSC_NO_PROFILING);\n");
   memlist = CSCmemInit ("my mem list", NULL, NULL, NULL, CSC_NO_PROFILING);
   printf ("\tmemlist = %p\n", memlist);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Delete the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemDone (memlist);\n");
   stat = CSCmemDone (memlist);
   printf ("\t[CSCmemDone] stat = %d\n", stat);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n========================================\n");
   printf ("Create a memlist\n");
   printf ("\n");
   printf ("memlist = CSCmemInit (\"my mem list\", tagger, monitor, mondata, CSC_DO_PROFILING);\n");
   memlist = CSCmemInit ("my mem list", tagger, monitor, mondata, CSC_DO_PROFILING);
   printf ("\tmemlist = %p\n", memlist);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Allocate some memory on the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemAlloc (memlist, &data, 1, 20, 5);\n");
   stat = CSCmemAlloc (memlist, &data, 1, 20, 5);
   printf ("\t[CSCmemAlloc] stat = %d\n", stat);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Allocate some memory on the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemAlloc (memlist, &data, 10, 20, 6);\n");
   stat = CSCmemAlloc (memlist, &data, 10, 20, 6);
   printf ("\t[CSCmemAlloc] stat = %d\n", stat);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Allocate some memory on the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemAlloc (memlist, &data, 7, 20, 7);\n");
   stat = CSCmemAlloc (memlist, &data, 7, 20, 7);
   printf ("\t[CSCmemAlloc] stat = %d\n", stat);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Free some memory on the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemFree (memlist, &data, 8);\n");
   stat = CSCmemFree (memlist, &data, 8);
   printf ("\t[CSCmemFree] stat = %d\n", stat);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Free all memory on the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemListFree (memlist, 9);\n");
   stat = CSCmemListFree (memlist, 9);
   printf ("\t[CSCmemListFree] stat = %d\n", stat);
   printf ("\n\tCSCmemListPrintProfile (memlist) => \n");
   stat = CSCmemListPrintProfile (memlist, CSC_SHOW_ALL);
   printf ("\t[CSCmemListPrintProfile] stat = %d\n", stat);

   printf ("\n========================================\n");
   printf ("Delete the memlist\n");
   printf ("\n");
   printf ("stat = CSCmemDone (memlist);\n");
   stat = CSCmemDone (memlist);
   printf ("\t[CSCmemDone] stat = %d\n", stat);

   printf ("\n");
   printf ("test done.\n");
   printf ("\n");
   }


static void   metrics (void)
   {
   int              stat;
   int              size;
   long             i;
   CSCmemListType   memlist;
   void*            data;
   double           duration0;
   double           duration1_10;
   double           duration2_10;
   double           duration3_10;
   double           duration1_100;
   double           duration2_100;
   double           duration3_100;
   double           duration1_1000;
   double           duration2_1000;
   double           duration3_1000;
   double           duration1_5000;
   double           duration2_5000;
   double           duration3_5000;

   long             iterations = 30000;

   CSCtimerType     timer0 = CSCtimerInit();
   CSCtimerType     timer1 = CSCtimerInit();
   CSCtimerType     timer2 = CSCtimerInit();
   CSCtimerType     timer3 = CSCtimerInit();

   printf ("\nSome Metrics for the csc Memory Subsystem\n\n");

   printf ("Creating a memlist:\n");
   printf ("memlist = CSCmemInit (\"timer list\", NULL, monitor, NULL, CSC_DO_PROFILING);\n");
   memlist = CSCmemInit ("timer list", NULL, monitor, NULL, CSC_DO_PROFILING);
   printf ("memlist = %p: ", memlist);
   if (memlist != NULL)
      {
      printf ("[OK].\n");
      }
   else
      {
      printf ("[OUCH]!\n");
      return;
      }

   printf ("\n");
   printf ("Perform timing on %d iterations.\n", iterations);

   printf ("=> Iterations empty for calibration... ");
   fflush (stdout);
   (void)CSCtimerMark (timer0);
   for (i = 0 ; i < iterations ; i++)
      NULL;
   (void)CSCtimerDiff (timer0, &duration0);
   printf ("done.\n");

   printf ("\n");
   printf ("Memory allocation size is 10 bytes.\n");
   printf ("=> Iterations of CSCmemAlloc()/CSCmemFree() pairs on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer1);
   for (i = 0 ; i < iterations ; i++)
      {
      (void)CSCmemAlloc (memlist, &data, 1, 10, 0);
      (void)CSCmemFree (memlist, &data, 0);
      }
   (void)CSCtimerDiff (timer1, &duration1_10);
   printf ("done.\n");
   (void)CSCmemListFree (memlist, 0);
   printf ("=> Iterations of CSCmemAlloc() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer2);
   for (i = 0 ; i < iterations ; i++)
      (void)CSCmemAlloc (memlist, &data, 1, 10, 0);
   (void)CSCtimerDiff (timer2, &duration2_10);
   printf ("done.\n");
   printf ("=> CSCmemListFree() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer3);
   (void)CSCmemListFree (memlist, 0);
   (void)CSCtimerDiff (timer3, &duration3_10);
   printf ("done.\n");

   printf ("\n");
   printf ("Memory allocation size is 100 bytes.\n");
   printf ("=> Iterations of CSCmemAlloc()/CSCmemFree() pairs on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer1);
   for (i = 0 ; i < iterations ; i++)
      {
      (void)CSCmemAlloc (memlist, &data, 1, 100, 0);
      (void)CSCmemFree (memlist, &data, 0);
      }
   (void)CSCtimerDiff (timer1, &duration1_100);
   printf ("done.\n");
   (void)CSCmemListFree (memlist, 0);
   printf ("=> Iterations of CSCmemAlloc() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer2);
   for (i = 0 ; i < iterations ; i++)
      (void)CSCmemAlloc (memlist, &data, 1, 100, 0);
   (void)CSCtimerDiff (timer2, &duration2_100);
   printf ("done.\n");
   printf ("=> CSCmemListFree() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer3);
   (void)CSCmemListFree (memlist, 0);
   (void)CSCtimerDiff (timer3, &duration3_100);
   printf ("done.\n");

   printf ("\n");
   printf ("Memory allocation size is 1000 bytes.\n");
   printf ("=> Iterations of CSCmemAlloc()/CSCmemFree() pairs on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer1);
   for (i = 0 ; i < iterations ; i++)
      {
      (void)CSCmemAlloc (memlist, &data, 1, 1000, 0);
      (void)CSCmemFree (memlist, &data, 0);
      }
   (void)CSCtimerDiff (timer1, &duration1_1000);
   printf ("done.\n");
   (void)CSCmemListFree (memlist, 0);
   printf ("=> Iterations of CSCmemAlloc() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer2);
   for (i = 0 ; i < iterations ; i++)
      (void)CSCmemAlloc (memlist, &data, 1, 1000, 0);
   (void)CSCtimerDiff (timer2, &duration2_1000);
   printf ("done.\n");
   printf ("=> CSCmemListFree() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer3);
   (void)CSCmemListFree (memlist, 0);
   (void)CSCtimerDiff (timer3, &duration3_1000);
   printf ("done.\n");

   printf ("\n");
   printf ("Memory allocation size is 5000 bytes.\n");
   printf ("=> Iterations of CSCmemAlloc()/CSCmemFree() pairs on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer1);
   for (i = 0 ; i < iterations ; i++)
      {
      (void)CSCmemAlloc (memlist, &data, 1, 5000, 0);
      (void)CSCmemFree (memlist, &data, 0);
      }
   (void)CSCtimerDiff (timer1, &duration1_5000);
   printf ("done.\n");
   (void)CSCmemListFree (memlist, 0);
   printf ("=> Iterations of CSCmemAlloc() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer2);
   for (i = 0 ; i < iterations ; i++)
      (void)CSCmemAlloc (memlist, &data, 1, 5000, 0);
   (void)CSCtimerDiff (timer2, &duration2_5000);
   printf ("done.\n");
   printf ("=> CSCmemListFree() on the memlist... ");
   fflush (stdout);
   (void)CSCtimerMark (timer3);
   (void)CSCmemListFree (memlist, 0);
   (void)CSCtimerDiff (timer3, &duration3_5000);
   printf ("done.\n");

   (void)CSCmemDone (memlist);

   printf ("\n");
   printf ("Calibration (displayed but not used):\n");
   printf (
          "%7.3f seconds [%8.3f usec x %d] empty calibration iterations.\n",
          duration0, (duration0/iterations)*1000000, iterations
          );

   printf ("\n");
   printf ("Allocation Size 10 bytes:\n");
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc/Free() iterations.\n",
          duration1_10, (duration1_10/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc() iterations.\n",
          duration2_10, (duration2_10/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemListFree().\n",
          duration3_10, (duration3_10/iterations)*1000000, iterations
          );

   printf ("\n");
   printf ("Allocation Size 100 bytes:\n");
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc/Free() iterations.\n",
          duration1_100, (duration1_100/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc() iterations.\n",
          duration2_100, (duration2_100/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemListFree().\n",
          duration3_100, (duration3_100/iterations)*1000000, iterations
          );

   printf ("\n");
   printf ("Allocation Size 1000 bytes:\n");
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc/Free() iterations.\n",
          duration1_1000, (duration1_1000/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc() iterations.\n",
          duration2_1000, (duration2_1000/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemListFree().\n",
          duration3_1000, (duration3_1000/iterations)*1000000, iterations
          );

   printf ("\n");
   printf ("Allocation Size 5000 bytes:\n");
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc/Free() iterations.\n",
          duration1_5000, (duration1_5000/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemAlloc() iterations.\n",
          duration2_5000, (duration2_5000/iterations)*1000000, iterations
          );
   printf (
          "%7.3f seconds [%8.3f usec x %d] CSCmemListFree().\n",
          duration3_5000, (duration3_5000/iterations)*1000000, iterations
          );

   (void)CSCtimerDone (timer0);
   (void)CSCtimerDone (timer1);
   (void)CSCtimerDone (timer2);
   (void)CSCtimerDone (timer3);

   printf ("\n");
   }


int   main (int argc, char** argv)
   {
   if (argc == 1)
      {
      test();
      }
   else
      {
      int   usage = 0;
      int   stats = 0;
      while (--argc > 0)
         {
         ++argv;
         if (strcmp(*argv,"--metrics") == 0) stats = 1;
         else
            {
            if (usage == 0) { pusage(); usage = 1; }
            fprintf (stderr, "bad arg: %s\n", *argv);
            }
         }
      if (stats) metrics();
      }
   }
